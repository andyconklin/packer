#include "utils.h"

u32 get_u32(VBYTES const & buffer, u32 index)
{
    return (buffer[index] << 24) | 
        (buffer[index + 1] << 16) | 
        (buffer[index + 2] << 8) | 
        (buffer[index + 3]);
}

u64 get_u64(VBYTES const & buffer, u32 index)
{
    return ((u64)get_u32(buffer, index) << 32) |
        (u64)get_u32(buffer, index + 4);
}

u16 get_u16(VBYTES const & buffer, u32 index) 
{
    return (buffer[index] << 8) | buffer[index + 1];
}

u8 get_u8(VBYTES const & buffer, u32 index) 
{
    return buffer[index];
}

VBYTES ReadIntoBuffer(std::string path) 
{
    /* Got this off stackoverflow*/
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    VBYTES buffer(size);
    if (!file.read((char*)buffer.data(), size))
    {
        throw "a fit";
    }

    return buffer;
}