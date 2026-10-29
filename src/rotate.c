#include <stdint.h>
#include "screenflip.h"

/*
 * Pure 180-degree framebuffer transform.
 * Source and destination must be distinct buffers.
 * Supports PSP 16-bit RGB565 and 32-bit pixel formats.
 *
 * This routine is NOT yet wired into the live display path.
 */
void screenflip_rotate180(const void *src, void *dst,
                          int width, int height, int stride_pixels,
                          int bytes_per_pixel)
{
    const uint8_t *s = (const uint8_t *)src;
    uint8_t *d = (uint8_t *)dst;

    if (!src || !dst || width <= 0 || height <= 0 ||
        stride_pixels < width ||
        (bytes_per_pixel != 2 && bytes_per_pixel != 4))
        return;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int src_index = (y * stride_pixels + x) * bytes_per_pixel;
            int dst_index = ((height - 1 - y) * stride_pixels +
                             (width - 1 - x)) * bytes_per_pixel;
            for (int b = 0; b < bytes_per_pixel; ++b)
                d[dst_index + b] = s[src_index + b];
        }
    }
}
