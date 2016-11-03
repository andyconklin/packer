#pragma once

#include "types.h"
#include "utils.h"

class Ticket 
{
    int LoadValuesFromBuffer(VBYTES const & buffer);

    enum
    {
        SIGTYPE_RSA_4096_SHA1 = 0x010000,
        SIGTYPE_RSA_2048_SHA1 = 0x010001,
        SIGTYPE_ECDSA_SHA1 = 0x010002,
        SIGTYPE_RSA_4096_SHA256 = 0x010003,
        SIGTYPE_RSA_2048_SHA256 = 0x010004,
        SIGTYPE_ECDSA_SHA256 = 0x010005,
    };

    u32 signature_type;
    VBYTES signature;

    struct {
        VBYTES issuer;
        VBYTES ecc_public_key;
        u8 version;
        u8 ca_crl_version;
        u8 signer_crl_version;
        VBYTES title_key;
        u8 reserved1;
        u64 ticket_id;
        u32 console_id;
        u64 title_id;
        u16 reserved2;
        u16 ticket_title_version;
        u64 reserved3;
        u8 license_type;
        u8 index;
        VBYTES reserved4;
        u32 eshop_account_id;
        u8 reserved5;
        u8 audit;
        VBYTES reserved6;
        VBYTES limits;
        VBYTES content_index;
    } header;

public:
    Ticket(VBYTES const & buffer);
    VBYTES get_title_key() const;
    u64 get_title_id() const;
};