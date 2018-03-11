//
// Created by Egor on 11.03.2018.
//

#ifndef NFC_NDEF_H
#define NFC_NDEF_H

#include <stdint.h>

#define NDEF_START_ADDRESS  ((uint16_t)0x0000)

#define NDEF_MSG_SIZE       ((uint16_t)3037)
#define NDEF_DEF_MSG_SIZE   ((uint8_t)26)

#define NDEF_MSG_FLG_MB     ((uint8_t)128)
#define NDEF_MSG_FLG_ME     ((uint8_t)64)
#define NDEF_MSG_FLG_CF     ((uint8_t)32)
#define NDEF_MSG_FLG_SR     ((uint8_t)16)
#define NDEF_MSG_FLG_IL     ((uint8_t)8)
#define NDEF_MSG_FLG_TNF    ((uint8_t)7)

#define FLG_TNF_UNKNOWN     ((uint8_t)5) /* Unknown tnf (0x05) */

#define NDEF_DATA_PSTN      ((uint16_t)28)
#define NDEF_LNG_PSTN       ((uint16_t)26) /* 2 bytes of ndef length */

#define NDEF_HDR_SIZE       ((uint8_t)6) /* message flags (1 byte),
                                          * message type length (1 byte),
                                          * payload size (4 byte)
                                          * */
#define NDEF_SHRT_REC       ((uint8_t)3)

#pragma pack(push,1)
typedef struct {
    uint16_t ndef_crnt_length;
    uint16_t ndef_crnt_addr;
    uint16_t ndef_ttl_records;
} Nfc_ndef;
#pragma pack(pop)

#endif //NFC_NDEF_H
