#ifndef __WC_TYPES_H__
#define __WC_TYPES_H__

#include <stdint.h>
#include <array>

#define SCREEN_WIDTH 12
#define SCREEN_HEIGHT 12

typedef std::array<std::array<uint32_t, SCREEN_HEIGHT>, SCREEN_WIDTH> Frame;

#endif /* __WC_TYPES_H__ */