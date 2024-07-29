# Usage example

```c
#include <stdio.h>

#define COLOR_CONVERT_IMPLEMENTATION
#include "color_convert.h"

int main(void)
{
    struct rgb rgb_color = hsl_to_rgb(15/360.f, 1.f, 0.5f);
    printf("rgb(%d, %d, %d)\n", rgb_color.r, rgb_color.g, rgb_color.b);

    struct hsl hsl_color = rgb_to_hsl(158, 74, 26);
    printf("hsl(%f degrees, %f %%, %f %%)\n", hsl_color.h * 360, hsl_color.s * 100, hsl_color.l * 100);

    rgb_color = hex_to_rgb(0xABCDEF);

    invert_hsl(&hsl_color);
    
    return 0;
}
```
