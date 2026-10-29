#ifndef SCREENFLIP_H
#define SCREENFLIP_H

void screenflip_rotate180(const void *src, void *dst,
                          int width, int height, int stride_pixels,
                          int bytes_per_pixel);
int screenflip_is_enabled(void);

#endif
