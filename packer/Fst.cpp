#include "Fst.h"

int Fst::LoadValuesFromBuffer(VBYTES const & buffer)
{
    if (get_u32(buffer, 0) & 0xFFFFFF00 != 0x46535400)
        throw "a fit";
    unknown = get_u32(buffer, 4);
    num_contents = get_u32(buffer, 8);

    u32 entries_begin = 0x20 + 0x20 * num_contents;
    u32 num_entries = get_u32(buffer, entries_begin + 8);
    u32 names_begin = entries_begin + 0x10 * num_entries;

    for (int i = 0; i < num_entries; i++)
    {

        std::cout << (char*)(buffer.data() + names_begin + get_u16(buffer, entries_begin + 0x10 * i + 2));
        std::cout << "\t" << std::setw(4) << std::setfill('0') << std::hex << get_u16(buffer, entries_begin + 0x10 * i);
        std::cout << "\t" << std::setw(8) << get_u32(buffer, entries_begin + 0x10 * i + 4);
        std::cout << "\t" << std::setw(8) << get_u32(buffer, entries_begin + 0x10 * i + 8);
        std::cout << "\t" << std::setw(4) << get_u16(buffer, entries_begin + 0x10 * i + 0xC);
        std::cout << "\t" << std::setw(4) << get_u16(buffer, entries_begin + 0x10 * i + 0xE) << std::endl;
        
    }
    return 0;
}

Fst::Fst(VBYTES const & buffer)
{
    LoadValuesFromBuffer(buffer);
}
