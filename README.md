# Color converter

This is a little header-only library providing such data types for color
representation as ```RGB```, ```RGBA```, ```CMYK```, ```HSL``` and ```HSV```.
For ```HEX``` use a plain integer.

> [!NOTE]
> To know more about the API and code in general, see ```color_convert.h```.

## Usage example

```c
#include <stdio.h>

#define COLOR_CONVERT_IMPLEMENTATION
#include "color_convert.h"

int main(void)
{
    struct rgb  c1 = { 127, 63, 31 };
    struct hsl  c2 = { 180.f, .75f, .40f };
    int         c3 = 0xABCDEF;
    struct rgba c4 = { 148, 42, 89, 51 };

    printf("rgb(%d, %d, %d)\n", c1.r, c1.g, c1.b);
    printf("hsl(%.0f deg, %.0f %%, %.0f %%)\n", c2.h, c2.s * 100, c2.l * 100);
    printf("hex(#%06X)", c3);

    rgb2hsl(&c1, &c2);
    hsl2rgb(&c2, &c1);

    c2.h += 60.f;
    if (!hsl_valid(&c2))
        return -1; /* will never return */

    rgb_invert(&c1);

    /* c1 and c4 are blended and then the result is stored back in c1 */
    rgb_blend(&c1, &c4);

    return 0;
}
```
