#include "types.h"
#include "utils.h"
#include "Tmd.h"

int main() {
    VBYTES tmdfile = ReadIntoBuffer("C:\\Users\\Andy\\Desktop"
        "\\JNUSTool\\tmp_000500301001620A\\title.tmd");
    Tmd tmd(tmdfile);
    return 0;
}