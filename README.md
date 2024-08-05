# Color converter

This is a little header-only library providing such data types for color
representation as ```RGB```, ```HSL``` and ```HSV```. The library supports
conversion from a ```HEX``` to an ```RGB``` and vice versa as well.

> [!NOTE]
> Hexadecimal values are stored in plain integers.

## API

```c
typedef struct hsl {
    float h;
    float s;
    float l;
} hsl_t;

typedef struct hsv {
    float h;
    float s;
    float v;
} hsv_t;

typedef struct rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_t;

typedef struct rgba {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} rgba_t;

typedef struct cmyk {
    float c;
    float m;
    float y;
    float k;
} cmyk_t;

/*             COLOR RANGES
 *
 * RGB  - R[0; 255]  G[0; 255]  B[0; 255]
 * RGBA - R[0; 255]  G[0; 255]  B[0; 255]  A[0; 255]
 * HSL  - H[0; 360)  S[0; 1]    L[0; 1]
 * HSV  - H[0; 360)  S[0; 1]    V[0; 1]
 * CMYK - C[0; 1]    M[0; 1]    Y[0; 1]    K[0; 1]
 *
 */

int  hsl_valid(const struct hsl  *);
int  hsv_valid(const struct hsv  *);
int cmyk_valid(const struct cmyk *);

void  rgb2hsl (const struct rgb  *in, struct hsl  *out);
void  rgb2hsv (const struct rgb  *in, struct hsv  *out);
void  rgb2cmyk(const struct rgb  *in, struct cmyk *out);
void  rgb2hex (const struct rgb  *in,        int  *out);
void  hsl2rgb (const struct hsl  *in, struct rgb  *out);
void  hsv2rgb (const struct hsv  *in, struct rgb  *out);
void cmyk2rgb (const struct cmyk *in, struct rgb  *out);
void  hex2rgb (const        int  *in, struct rgb  *out);
void  hsl2hsv (const struct hsl  *in, struct hsv  *out);
void  hsv2hsl (const struct hsv  *in, struct hsl  *out);

void rgb_invert(struct rgb *);
void rgb_blend(struct rgb *dst, const struct rgba *src);
```

## Usage example

```c
#include <stdio.h>

#define COLOR_CONVERT_IMPLEMENTATION
#include "color_convert.h"

int main(void)
{
    struct rgb c1 = { 127, 63, 31 };
    struct hsl c2 = { 180.f, .75f, .40f };
    int        c3 = 0xABCDEF;

    printf("rgb(%d, %d, %d)\n", c1.r, c1.g, c1.b);
    printf("hsl(%.0f deg, %.0f %%, %.0f %%)\n", c2.h, c2.s * 100, c2.l * 100);
    printf("hex(#%06X)", c3);

    rgb2hsl(&c1, &c2);
    hsl2rgb(&c2, &c1);

    c2.h += 60.f;
    if (!hsl_valid(&c2)) return -1; /* will never return */

    rgb_invert(&c1);

    return 0;
}
```

## Current state

- [x] RGB
- [x] HSL
- [x] HSV
- [x] CMYK
- [ ] Corresponding types with an alpha channel
