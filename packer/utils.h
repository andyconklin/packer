#pragma once

#include "types.h"

extern "C" {
#include "aes.h"
}

u64 get_u64(VBYTES const & buffer, u32 index);
u32 get_u32(VBYTES const & buffer, u32 index);
u16 get_u16(VBYTES const & buffer, u32 index);
u8 get_u8(VBYTES const & buffer, u32 index);

VBYTES ReadIntoBuffer(std::string path);