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

#include <iostream>

#include "glproc.hpp"
#include "glws.hpp"


namespace glws {


void
getProfileVersion(Profile profile, unsigned &major, unsigned &minor, bool &core)
{
    major = (profile >> 4) & 0xf;
    minor =  profile       & 0xf;
    core = isCoreProfile(profile);
}


bool
checkExtension(const char *extName, const char *extString)
{
    assert(extName);
    assert(extString);

    const char *p = extString;
    const char *q = extName;
    char c;
    do {
        c = *p++;
        if (c == '\0' || c == ' ') {
            if (q && *q == '\0') {
                return true;
            } else {
                q = extName;
            }
        } else {
            if (q && *q == c) {
                ++q;
            } else {
                q = 0;
            }
        }
    } while (c);
    return false;
}


void
Drawable::copySubBuffer(int x, int y, int width, int height) {
    std::cerr << "warning: copySubBuffer not yet implemented\n";
}


bool
Context::hasExtension(const char *string) {
    if (extensions.empty()) {
        if (isCoreProfile(profile)) {
            // Use glGetStringi
            GLint num_extensions = 0;
            glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
            for (int i = 0; i < num_extensions; ++i) {
                const char *extension = reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i));
                if (extension) {
                    extensions.insert(extension);
                }
            }
        } else {
            // Use glGetString
            const char *begin = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
            do {
                const char *end = begin;
                char c = *end;
                while (c != '\0' && c != ' ') {
                    ++end;
                    c = *end;
                }
                if (end != begin) {
                    extensions.insert(std::string(begin, end));
                }
                
                if (c == '\0') {
                    break;
                }
                begin = end + 1;
            } while(1);
        }
    }

    return extensions.find(string) != extensions.end();
}


} /* namespace glws */
