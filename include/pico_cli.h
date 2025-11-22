#include <stdio.h>
#include <string.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#ifndef PICO_CLI
#define PICO_CLI
// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// #undef PICO_STDIO_SHORT_CIRCUIT_CLIB_FUNCS 
// #define PICO_STDIO_SHORT_CIRCUIT_CLIB_FUNCS  0
#ifndef LED_DELAY_MS
#define LED_DELAY_MS 500
#endif
#define PROBE_DAP_CONNECTED_LED 15

#define ILINE 80
//XModem
#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define PAD  0x1a

#define C_BS  0x08
#define C_ESC 0x1b
#define S_CLS F("\e[0H\e[2J")
#define S_CR  F("\r\n>")

/**************************************************/
/*! \brief Automatic generated enum- commands
    \defgroup token_parser
    \sa datetime_t */
/**************************************************/
enum eCmdSt {eNoToken=0,
      eAUTO, eCD, eCLS, eCONFIG, eCOPY, eDATE, eDEL, eDIR,
      eECHO, eFORMAT, eHELP, eMD, ePATH, eRD, eREN, eTEMP,
      eTIME, eTYPE, eVER, eVOL, eXREC, eXTRAN}; 

bool editLine(char*, char);
int fnSDOS_Parser(char*);
int func_MonParser(char*);

extern char sPath[];
extern bool bAuto;

#endif