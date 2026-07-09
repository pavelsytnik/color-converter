# Color Converter

A small header-only library for working with colors. It provides data types for
representing RGB, RGBA, CMYK, HSL, and HSV colors. Hexadecimal colors are
represented as plain integers.

Although the library is primarily used for color conversion, it has some other
functions as well.

> [!NOTE]
> See `include/color_convert.h` for the full documentation.

## Usage Example

```c
#define COLOR_CONVERT_IMPLEMENTATION
#include "color_convert.h"

#include <stdio.h>

int main(void)
{
    struct rgb  c1 = { 127, 63, 31 };
    struct hsl  c2 = { 180.f, .75f, .40f };
    int         c3 = 0xABCDEF;
    struct rgba c4 = { 148, 42, 89, 51 };

    printf("rgb(%d, %d, %d)\n", c1.r, c1.g, c1.b);
    printf("hsl(%.0f deg, %.0f %%, %.0f %%)\n", c2.h, c2.s * 100, c2.l * 100);
    printf("hex(#%06X)\n", c3);

    rgb2hsl(&c1, &c2);
    hsl2rgb(&c2, &c1);

    c2.h += 200.f;
    if (!hsl_valid(&c2)) {
        fprintf(stderr, "Invalid HSL color\n");
    }

    rgb_invert(&c1);

    rgb_blend(&c1, &c4); /* Blend c4 over c1. */

    return 0;
}
```
