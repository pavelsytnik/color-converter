# Usage example

```c
#include <stdio.h>

#define COLOR_CONVERT_IMPLEMENTATION
#include "color_convert.h"

int main(void)
{
    struct rgb rgb_color = rgb(127, 63, 31);
    struct hsl hsl_color = hsl(180, 100, 50); /* degrees then percents */

    printf("rgb(%d, %d, %d)\n", rgb_color.r, rgb_color.g, rgb_color.b);
    printf("hsl(%f degrees, %f %%, %f %%)\n",
           hsl_color.h * 360, hsl_color.s * 100, hsl_color.l * 100);

    rgb_color = hex2rgb(0xABCDEF);
    rgb_color = hsl2rgb(&hsl_color);
    hsl_color = rgb2hsl(&rgb_color);
    
    rgb_invert(&rgb_color);
    
    return 0;
}
```
