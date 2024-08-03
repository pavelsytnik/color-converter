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

typedef struct cmyk {
    float c;
    float m;
    float y;
    float k;
} cmyk_t;

struct rgb rgb(unsigned char r, unsigned char g, unsigned char b);
struct hsl hsl(float hue, float saturation, float lightness);
struct hsv hsv(float hue, float saturation, float value);
struct cmyk cmyk(float c, float m, float y, float k);

int hsl_valid(const struct hsl *);
int hsv_valid(const struct hsv *);
int cmyk_valid(const struct cmyk *);

struct rgb hsl2rgb(const struct hsl *);
struct rgb hex2rgb(int code);
struct hsl rgb2hsl(const struct rgb *);
struct hsv rgb2hsv(const struct rgb *);
struct rgb hsv2rgb(const struct hsv *);
struct hsl hsv2hsl(const struct hsv *);
struct hsv hsl2hsv(const struct hsl *);
int rgb2hex(const struct rgb *);
struct cmyk rgb2cmyk(const struct rgb *);
struct rgb cmyk2rgb(const struct cmyk *);

void rgb_invert(struct rgb *);
```

## Usage example

```c
#include <stdio.h>

#define COLOR_CONVERT_IMPLEMENTATION
#include "color_convert.h"

int main(void)
{
    struct rgb rgb_color = rgb(127, 63, 31);

    /*  h[0;360)    s[0;1)    l[0;1)  */
    struct hsl hsl_color = hsl(180, 1.00f, .50f);

    printf("rgb(%d, %d, %d)\n", rgb_color.r, rgb_color.g, rgb_color.b);
    printf("hsl(%f degrees, %f %%, %f %%)\n",
           hsl_color.h, hsl_color.s * 100, hsl_color.l * 100);

    rgb_color = hex2rgb(0xABCDEF);
    rgb_color = hsl2rgb(&hsl_color);
    hsl_color = rgb2hsl(&rgb_color);
    
    rgb_invert(&rgb_color);
    
    return 0;
}
```

## Current state

- [x] RGB
- [x] HSL
- [x] HSV
- [x] CMYK
- [ ] Corresponding types with an alpha channel
