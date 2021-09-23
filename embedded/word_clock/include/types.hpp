#ifndef __WC_TYPES_H__
#define __WC_TYPES_H__

#include <stdint.h>
#include <array>
#include <etl/multi_array.h>


#define SCREEN_WIDTH 12
#define SCREEN_HEIGHT 12


using Frame = etl::multi_array<uint32_t, SCREEN_WIDTH, SCREEN_HEIGHT>; // Store the entire pixel color


#endif /* __WC_TYPES_H__ */
