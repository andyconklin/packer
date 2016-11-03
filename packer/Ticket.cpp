#include "Ticket.h"

int Ticket::LoadValuesFromBuffer(VBYTES const & buffer)
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

    header.issuer = VBYTES(buffer.begin() + header_offset, buffer.begin() + header_offset + 0x40);
    header.ecc_public_key = VBYTES(buffer.begin() + header_offset + 0x40, buffer.begin() + header_offset + 0x7C);
    header.version = get_u8(buffer, header_offset + 0x7C);
    header.ca_crl_version = get_u8(buffer, header_offset + 0x7D);
    header.signer_crl_version = get_u8(buffer, header_offset + 0x7E);
    header.title_key = VBYTES(buffer.begin() + header_offset + 0x7F, buffer.begin() + header_offset + 0x8F);
    header.reserved1 = get_u8(buffer, header_offset + 0x8F);
    header.ticket_id = get_u64(buffer, header_offset + 0x90);
    header.console_id = get_u32(buffer, header_offset + 0x98);
    header.title_id = get_u64(buffer, header_offset + 0x9C);
    header.reserved2 = get_u16(buffer, header_offset + 0xA4);
    header.ticket_title_version = get_u16(buffer, header_offset + 0xA6);
    header.reserved3 = get_u64(buffer, header_offset + 0xA8);
    header.license_type = get_u8(buffer, header_offset + 0xB0);
    header.index = get_u8(buffer, header_offset + 0xB1);
    header.reserved4 = VBYTES(buffer.begin() + header_offset + 0xB2, buffer.begin() + header_offset + 0xDC);
    header.eshop_account_id = get_u32(buffer, header_offset + 0xDC);
    header.reserved5 = get_u8(buffer, header_offset + 0xE0);
    header.audit = get_u8(buffer, header_offset + 0xE1);
    header.reserved6 = VBYTES(buffer.begin() + header_offset + 0xE2, buffer.begin() + header_offset + 0x124);
    header.limits = VBYTES(buffer.begin() + header_offset + 0x124, buffer.begin() + header_offset + 0x164);
    header.content_index = VBYTES(buffer.begin() + header_offset + 0x164, buffer.begin() + header_offset + 0x210);

    return 0;
}

Ticket::Ticket(VBYTES const & buffer)
{
    LoadValuesFromBuffer(buffer);
}

VBYTES Ticket::get_title_key() const
{
    return VBYTES(header.title_key);
}

u64 Ticket::get_title_id() const
{
    return header.title_id;
}
