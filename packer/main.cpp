#include "types.h"
#include "utils.h"
#include "Tmd.h"
#include "Ticket.h"
#include "Fst.h"

int main() 
{
    VBYTES tmdfile = ReadIntoBuffer("C:\\Users\\Andy\\Desktop"
        "\\JNUSTool\\tmp_000500301001620A\\title.tmd");
    Tmd tmd(tmdfile);

    VBYTES tikfile = ReadIntoBuffer("C:\\Users\\Andy\\Desktop"
        "\\JNUSTool\\tmp_000500301001620A\\title.tik");
    Ticket ticket(tikfile);

    VBYTES enc_title_key = ticket.get_title_key();
    VBYTES dec_title_key(enc_title_key);

    BYTE key[] = { 0xD7,0xB0,0x04,0x02,0x65,0x9B,0xA2,0xAB,
        0xD2,0xCB,0x0D,0xB2,0x7F,0xA2,0xB6,0x56 };
    u64 title_id = ticket.get_title_id();
    BYTE iv[16];
    for (int i = 0; i < 8; i++)
        iv[i] = (BYTE)((title_id >> (56 - (8 * i))) & 0xFF);
    for (int i = 8; i < 16; i++)
        iv[i] = 0;

    AES128_CBC_decrypt_buffer((uint8_t*)dec_title_key.data(), (uint8_t*)enc_title_key.data(),
        (uint32_t)enc_title_key.size(), (uint8_t*)key, (uint8_t*)iv);

    VBYTES enc_appfile = ReadIntoBuffer("C:\\Users\\Andy\\Desktop"
        "\\JNUSTool\\tmp_000500301001620A\\00000117.app");
    VBYTES dec_appfile(enc_appfile);

    for (int i = 0; i < 16; i++)
        iv[i] = 0;

    AES128_CBC_decrypt_buffer((uint8_t*)dec_appfile.data(), (uint8_t*)enc_appfile.data(),
        (uint32_t)enc_appfile.size(), (uint8_t*)dec_title_key.data(), (uint8_t*)iv);
    
    Fst fst(dec_appfile);

    system("pause");
    
    return 0;
}