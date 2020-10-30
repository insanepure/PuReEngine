#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <cstring>
#include <stdint.h>

#define PuRe_max(a,b)            (((a) > (b)) ? (a) : (b))
#define PuRe_min(a,b)            (((a) < (b)) ? (a) : (b))
#define PuRe_clamp(value, min, max) PuRe_min(PuRe_max(value, min), max)

#define PuRe_CLEAR(s) memset(&(s), 0, sizeof(s))

#define SAFE_RELEASE(x) if(x != NULL){ x->Release(); }
#define SAFE_DELETE(x) if(x != NULL){ delete x; }
#define SAFE_DELETE_ARRAY(x) if(x != NULL){ delete[] x; }

#define PuRe_DegToRad 0.0174532925f
#define PuRe_RadToDeg 57.2957795f

namespace PuReEngine
{
    typedef char          char8;
    typedef wchar_t       char16;
    typedef char          int8;
    typedef int16_t       int16;
    typedef int32_t       int32;
    typedef int64_t       int64;
    typedef uint8_t       uint8;
    typedef uint16_t      uint16;
    typedef uint32_t      uint32;
    typedef uint64_t      uint64;
    typedef float         float32;
    typedef double        float64;


}
#endif /* _DEFINES_H_ */