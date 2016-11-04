#pragma once

#include "types.h"
#include "utils.h"
#include "Tmd.h"

class Fst
{
    int LoadValuesFromBuffer(VBYTES const & buffer);

    u32 unknown;
    u32 num_contents;

public:
    Fst(VBYTES const & buffer);
};