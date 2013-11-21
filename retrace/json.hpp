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

/*
 * JSON writing functions.
 */

#ifndef _JSON_HPP_
#define _JSON_HPP_

#include <stddef.h>
#include <wchar.h>

#ifdef _MSC_VER
#  include <float.h>
#  define isfinite _finite
#  define isnan _isnan
#else
#  include <math.h> // isfinite, isnan
#endif

#include <iomanip>
#include <limits>
#include <ostream>
#include <string>


namespace image {
    class Image;
}


class JSONWriter
{
private:
    std::ostream &os;

    int level;
    bool value;
    char space;

    void
    newline(void);

    void
    separator(void);

public:
    JSONWriter(std::ostream &_os);

    ~JSONWriter();

    void
    beginObject();

    void
    endObject();

    void
    beginMember(const char * name);

    inline void
    beginMember(const std::string &name) {
        beginMember(name.c_str());
    }

    void
    endMember(void);

    void
    beginArray();

    void
    endArray(void);

    void
    writeString(const char *s);

    inline void
    writeString(const std::string &s) {
        writeString(s.c_str());
    }

    void
    writeBase64(const void *bytes, size_t size);

    void
    writeNull(void);

    void
    writeBool(bool b);

    /**
     * Special case for char to prevent it to be written as a literal
     * character.
     */
    inline void
    writeInt(signed char n) {
        separator();
        os << std::dec << static_cast<int>(n);
        value = true;
        space = ' ';
    }

    inline void
    writeInt(unsigned char n) {
        separator();
        os << std::dec << static_cast<unsigned>(n);
        value = true;
        space = ' ';
    }

    template<class T>
    inline void
    writeInt(T n) {
        separator();
        os << std::dec << n;
        value = true;
        space = ' ';
    }

    template<class T>
    void
    writeFloat(T n) {
        separator();
        if (isnan(n)) {
            // NaN is non-standard but widely supported
            os << "NaN";
        } else if (!isfinite(n)) {
            // Infinite is non-standard but widely supported
            if (n < 0) {
                os << '-';
            }
            os << "Infinity";
        } else {
            os << std::dec << std::setprecision(std::numeric_limits<T>::digits10 + 1) << n;
        }
        value = true;
        space = ' ';
    }
    
    inline void
    writeStringMember(const char *name, const char *s) {
        beginMember(name);
        writeString(s);
        endMember();
    }

    inline void
    writeBoolMember(const char *name, bool b) {
        beginMember(name);
        writeBool(b);
        endMember();
    }

    template<class T>
    inline void
    writeIntMember(const char *name, T n) {
        beginMember(name);
        writeInt(n);
        endMember();
    }

    void
    writeImage(image::Image *image, const char *format, unsigned depth = 1);
};

#endif /* _JSON_HPP_ */
