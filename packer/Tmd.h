#pragma once

#include "types.h"
#include "utils.h"

class Tmd 
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

    struct header_t 
    {
        VBYTES signature_issuer;
        u8 version;
        u8 ca_crl_version;
        u8 signer_crl_version;
        u8 reserved1;
        u64 system_version;
        u64 title_id;
        u32 title_type;
        u16 group_id;
        u32 save_data_size; /* bytes */
        u32 srl_private_save_data_size; /* bytes */
        u32 reserved2;
        u8 srl_flag;
        VBYTES reserved3;
        u32 access_rights;
        u16 title_version;
        u16 content_count;
        u16 boot_content;
        VBYTES sha256_hash_of_content_info_records;
    } header;

    struct content_info_t 
    {
        u16 content_index_offset;
        u16 content_command_count;
        VBYTES sha256_hash_of_next_records;
    };

    std::vector<struct content_info_t> info_records;

    struct content_chunk_t 
    {
        u32 content_id;
        u16 content_index;
        u16 content_type;
        u64 content_size;
        VBYTES sha256_hash;
    };

    std::vector<struct content_chunk_t> chunk_records;

public:
    Tmd(VBYTES const & buffer);
};