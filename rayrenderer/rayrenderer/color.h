#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdint.h>

using color = vec3;

void write_color(unsigned char* p, int r, int g, int b, int alpha) {
	*(p) = (uint8_t)(r);
	*(p + 1) = (uint8_t)(g);
	*(p + 2) = (uint8_t)(b);
	*(p + 3) = alpha;
}

void write_color(unsigned char* p, const color& input, int alpha) {
	*(p) = (uint8_t)(static_cast<int>(255.999 * input.e[0]));
	*(p + 1) = (uint8_t)(static_cast<int>(255.999 * input.e[1]));
	*(p + 2) = (uint8_t)(static_cast<int>(255.999 * input.e[2]));
	*(p + 3) = alpha;
}

#endif