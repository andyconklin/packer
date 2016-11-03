#include "Tmd.h"

int Tmd::LoadValuesFromBuffer(VBYTES const & buffer)
{
    u32 signature_size;
    u32 signature_padding;
    u32 header_offset;
    u32 info_offset;
    u32 chunk_offset;

    this->signature_type = get_u32(buffer, 0);

    switch (this->signature_type) 
    {
    case SIGTYPE_RSA_4096_SHA1:
    case SIGTYPE_RSA_4096_SHA256:
        signature_size = 0x200;
        signature_padding = 0x3C;
        break;
    case SIGTYPE_RSA_2048_SHA1:
    case SIGTYPE_RSA_2048_SHA256:
        signature_size = 0x100;
        signature_padding = 0x3C;
        break;
    case SIGTYPE_ECDSA_SHA1:
    case SIGTYPE_ECDSA_SHA256:
        signature_size = 0x3C;
        signature_padding = 0x40;
        break;
    default:
        return -1;
    }

    this->signature = VBYTES(buffer.begin() + 4, buffer.begin() + 4 + 
        signature_size);

    header_offset = 4 + signature_size + signature_padding;

    header.signature_issuer = VBYTES(buffer.begin() + header_offset, 
        buffer.begin() + header_offset + 0x40);
    header.version = get_u8(buffer, header_offset + 0x40);
    header.ca_crl_version = get_u8(buffer, header_offset + 0x41);
    header.signer_crl_version = get_u8(buffer, header_offset + 0x42);
    header.reserved1 = get_u8(buffer, header_offset + 0x43);
    header.system_version = get_u64(buffer, header_offset + 0x44);
    header.title_id = get_u64(buffer, header_offset + 0x4C);
    header.title_type = get_u32(buffer, header_offset + 0x54);
    header.group_id = get_u16(buffer, header_offset + 0x58);
    header.save_data_size = get_u32(buffer, header_offset + 0x5A);
    header.srl_private_save_data_size = get_u32(buffer, header_offset + 0x5E);
    header.reserved2 = get_u32(buffer, header_offset + 0x62);
    header.srl_flag = get_u8(buffer, header_offset + 0x66);
    header.reserved3 = VBYTES(buffer.begin() + header_offset + 0x67, 
        buffer.begin() + header_offset + 0x67 + 0x31);
    header.access_rights = get_u32(buffer, header_offset + 0x98);
    header.title_version = get_u16(buffer, header_offset + 0x9C);
    header.content_count = get_u16(buffer, header_offset + 0x9E);
    header.boot_content = get_u16(buffer, header_offset + 0xA0);
    header.sha256_hash_of_content_info_records = VBYTES(buffer.begin() + 
        header_offset + 0xA4, buffer.begin() + header_offset + 0xA4 + 0x20);

    info_offset = header_offset + 0xC4;

    for (u32 i = 0; i < 64; i++) 
    {
        info_records.push_back({
            get_u16(buffer, info_offset + (0x24 * i)),
            get_u16(buffer, info_offset + (0x24 * i) + 0x2),
            VBYTES(buffer.begin() + info_offset + (0x24 * i) + 0x4,
                buffer.begin() + info_offset + (0x24 * i) + 0x24),
        });
    }

    chunk_offset = header_offset + 0x9C4;

    for (u32 i = 0; i < header.content_count; i++) 
    {
        chunk_records.push_back({
            get_u32(buffer, chunk_offset + (0x30 * i)),
            get_u16(buffer, chunk_offset + (0x30 * i) + 0x4),
            get_u16(buffer, chunk_offset + (0x30 * i) + 0x6),
            get_u64(buffer, chunk_offset + (0x30 * i) + 0x8),
            VBYTES(buffer.begin() + chunk_offset + (0x30 * i) + 0x10, 
                buffer.begin() + chunk_offset + (0x30 * i) + 0x30),
        });
    }

    return 0;
}

Tmd::Tmd(VBYTES const & buffer)
{
    if (LoadValuesFromBuffer(buffer))
        throw "a fit";
}
