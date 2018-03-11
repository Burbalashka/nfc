//
// Created by Egor on 11.03.2018.
//

#include "Ndef.h"
#include "i2c_for_nfc.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint8_t ndef_memory_buffer[NDEF_MSG_SIZE];

const uint8_t ndef_default_header[] = {
    /* NDEF Tag Application name */
    0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01,
    /* Capability Container ID */
    0xE1, 0x03, /* NDEF Id */
    0x00, 0x0F, /* CCLEN */
    0x20,       /* Map version 2.0 */
    0x00, 0xF9, /* MLe */
    0x00, 0xF6, /* MLc */

    0x04,       /* Tag, File control TLV (4 - NDEF) */
    0x06,       /* Length, File control TLV (6 - bytes of data for tag)*/
    0xE1, 0x04, /* File Id */
    0x0B, 0xDF, /* Max file size */
    0x00,       /* Read access */
    0x00,       /* Write access */

    0xE1, 0x04, /* NDEF file id */
};

void set_def_ndef(Nfc_ndef *nfc)
{
    /* write ndef default header */
    write_nfc_data(NDEF_START_ADDRESS, ndef_default_header, sizeof(ndef_default_header));

    nfc->ndef_crnt_addr = NDEF_DATA_PSTN;
    nfc->ndef_crnt_length = 0;
    nfc->ndef_ttl_records = 0;
}

void set_ndef_length(uint16_t length)
{
    uint8_t buf[2] = {0x00};

    buf[0] = length >> 8;
    buf[1] = length & 0xFF;
    write_nfc_data(NDEF_LNG_PSTN, buf, 2);
}

void add_record(Nfc_ndef *nfc, uint8_t  ndef_flags, uint8_t *record, uint16_t length)
{
    uint8_t buf[NDEF_HDR_SIZE] = {0x00};

    buf[0] = ndef_flags;
    buf[1] = 0x00;

    if ((ndef_flags & NDEF_MSG_FLG_TNF) != FLG_TNF_UNKNOWN) {
        printf("Error record type");
        return;
    }
    /* writing record header and payload */
    if (length >= 0 && length <= 255) {
        buf[0] |= NDEF_MSG_FLG_SR;
        buf[2] = length & 0xFF;

        write_nfc_data(nfc->ndef_crnt_addr, buf, NDEF_SHRT_REC);
        nfc->ndef_crnt_addr += NDEF_SHRT_REC;
        nfc->ndef_crnt_length += NDEF_SHRT_REC;

        write_nfc_data(nfc->ndef_crnt_addr, record, length);
        nfc->ndef_crnt_addr += length;
        nfc->ndef_crnt_length += length;
    } else if (length > 255){
        buf[4] = length >> 8;
        buf[5] = length & 0xFF;

        write_nfc_data(NDEF_DATA_PSTN, buf, NDEF_HDR_SIZE);
        nfc->ndef_crnt_addr += NDEF_HDR_SIZE;
        nfc->ndef_crnt_length += NDEF_HDR_SIZE;

        write_nfc_data(NDEF_DATA_PSTN + NDEF_HDR_SIZE, record, length);
        nfc->ndef_crnt_addr += length;
        nfc->ndef_crnt_length += length;
    }
    nfc->ndef_ttl_records += 1;

    set_ndef_length(nfc->ndef_crnt_length);
}