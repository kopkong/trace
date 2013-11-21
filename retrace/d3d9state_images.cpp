/**************************************************************************
 *
 * Copyright 2011 Jose Fonseca
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/


#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "image.hpp"
#include "json.hpp"
#include "d3d9imports.hpp"
#include "d3dstate.hpp"


namespace d3dstate {


static image::Image *
getSurfaceImage(IDirect3DDevice9 *pDevice,
                IDirect3DSurface9 *pSurface) {
    image::Image *image = NULL;
    D3DSURFACE_DESC Desc;
    D3DLOCKED_RECT LockedRect;
    const unsigned char *src;
    unsigned char *dst;
    HRESULT hr;

    if (!pSurface) {
        return NULL;
    }

    hr = pSurface->GetDesc(&Desc);
    assert(SUCCEEDED(hr));

    unsigned numChannels;
    image::ChannelType channelType;
    switch (Desc.Format) {
    case D3DFMT_X8R8G8B8:
    case D3DFMT_A8R8G8B8:
    case D3DFMT_R5G6B5:
        numChannels = 3;
        channelType = image::TYPE_UNORM8;
        break;
    case D3DFMT_D16:
    case D3DFMT_D16_LOCKABLE:
    case D3DFMT_D32F_LOCKABLE:
        numChannels = 1;
        channelType = image::TYPE_FLOAT;
        break;
    default:
        std::cerr << "warning: unsupported D3DFORMAT " << Desc.Format << "\n";
        goto no_lock;
    }

    hr = pSurface->LockRect(&LockedRect, NULL, D3DLOCK_READONLY);
    if (FAILED(hr)) {
        goto no_lock;
    }

    image = new image::Image(Desc.Width, Desc.Height, numChannels, true, channelType);
    if (!image) {
        goto no_image;
    }

    dst = image->start();
    src = (const unsigned char *)LockedRect.pBits;
    for (unsigned y = 0; y < Desc.Height; ++y) {
        switch (Desc.Format) {
        case D3DFMT_R5G6B5:
            for (unsigned x = 0; x < Desc.Width; ++x) {
                uint32_t pixel = ((const uint16_t *)src)[x];
                dst[3*x + 0] = (( pixel        & 0x1f) * (2*0xff) + 0x1f) / (2*0x1f);
                dst[3*x + 1] = (((pixel >>  5) & 0x3f) * (2*0xff) + 0x3f) / (2*0x3f);
                dst[3*x + 2] = (( pixel >> 11        ) * (2*0xff) + 0x1f) / (2*0x1f);
            }
            break;
        case D3DFMT_X8R8G8B8:
        case D3DFMT_A8R8G8B8:
            for (unsigned x = 0; x < Desc.Width; ++x) {
                dst[3*x + 0] = src[4*x + 2];
                dst[3*x + 1] = src[4*x + 1];
                dst[3*x + 2] = src[4*x + 0];
            }
            break;
        case D3DFMT_D16:
        case D3DFMT_D16_LOCKABLE:
            for (unsigned x = 0; x < Desc.Width; ++x) {
                ((float *)dst)[x] = ((const uint16_t *)src)[x] * (1.0f / 0xffff);
            }
            break;
        case D3DFMT_D32F_LOCKABLE:
            memcpy(dst, src, Desc.Width * sizeof(float));
            break;
        default:
            assert(0);
            break;
        }

        src += LockedRect.Pitch;
        dst += image->stride();
    }

no_image:
    pSurface->UnlockRect();
no_lock:
    return image;
}


static image::Image *
getRenderTargetImage(IDirect3DDevice9 *pDevice,
                     IDirect3DSurface9 *pRenderTarget) {
    image::Image *image = NULL;
    D3DSURFACE_DESC Desc;
    IDirect3DSurface9 *pStagingSurface = NULL;
    HRESULT hr;

    if (!pRenderTarget) {
        return NULL;
    }

    hr = pRenderTarget->GetDesc(&Desc);
    assert(SUCCEEDED(hr));

    hr = pDevice->CreateOffscreenPlainSurface(Desc.Width, Desc.Height, Desc.Format, D3DPOOL_SYSTEMMEM, &pStagingSurface, NULL);
    if (FAILED(hr)) {
        goto no_staging;
    }

    hr = pDevice->GetRenderTargetData(pRenderTarget, pStagingSurface);
    if (FAILED(hr)) {
        goto no_rendertargetdata;
    }

    image = getSurfaceImage(pDevice, pStagingSurface);

no_rendertargetdata:
    pStagingSurface->Release();
no_staging:
    return image;
}


image::Image *
getRenderTargetImage(IDirect3DDevice9 *pDevice) {
    HRESULT hr;

    IDirect3DSurface9 *pRenderTarget = NULL;
    hr = pDevice->GetRenderTarget(0, &pRenderTarget);
    if (FAILED(hr)) {
        return NULL;
    }
    assert(pRenderTarget);

    image::Image *image = NULL;
    if (pRenderTarget) {
        image = getRenderTargetImage(pDevice, pRenderTarget);
        pRenderTarget->Release();
    }

    return image;
}


void
dumpFramebuffer(JSONWriter &json, IDirect3DDevice9 *pDevice)
{
    HRESULT hr;

    json.beginMember("framebuffer");
    json.beginObject();

    D3DCAPS9 Caps;
    pDevice->GetDeviceCaps(&Caps);

    for (UINT i = 0; i < Caps.NumSimultaneousRTs; ++i) {
        IDirect3DSurface9 *pRenderTarget = NULL;
        hr = pDevice->GetRenderTarget(i, &pRenderTarget);
        if (FAILED(hr)) {
            continue;
        }

        if (!pRenderTarget) {
            continue;
        }

        image::Image *image;
        image = getRenderTargetImage(pDevice, pRenderTarget);
        if (image) {
            char label[64];
            _snprintf(label, sizeof label, "RENDER_TARGET_%u", i);
            json.beginMember(label);
            json.writeImage(image, "UNKNOWN");
            json.endMember(); // RENDER_TARGET_*
        }

        pRenderTarget->Release();
    }

    IDirect3DSurface9 *pDepthStencil = NULL;
    hr = pDevice->GetDepthStencilSurface(&pDepthStencil);
    if (SUCCEEDED(hr) && pDepthStencil) {
        image::Image *image;
        image = getSurfaceImage(pDevice, pDepthStencil);
        if (image) {
            json.beginMember("DEPTH_STENCIL");
            json.writeImage(image, "UNKNOWN");
            json.endMember(); // RENDER_TARGET_*
        }
    }


    json.endObject();
    json.endMember(); // framebuffer
}


} /* namespace d3dstate */
