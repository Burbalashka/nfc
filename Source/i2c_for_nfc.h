//
// Created by Egor on 11.03.2018.
//

#ifndef NFC_I2C_FOR_NFC_H
#define NFC_I2C_FOR_NFC_H

#include <stdint.h>

extern void write_nfc_data(uint16_t address, uint8_t *data, uint16_t length);

#endif //NFC_I2C_FOR_NFC_H
