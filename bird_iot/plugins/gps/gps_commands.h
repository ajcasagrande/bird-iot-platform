#pragma once

// U-blox UBX binary commands
const unsigned char ubxRate1Hz[] PROGMEM =
    { 0x06,0x08,0x06,0x00,0xE8,0x03,0x01,0x00,0x01,0x00 };
const unsigned char ubxRate5Hz[] PROGMEM =
    { 0x06,0x08,0x06,0x00,200,0x00,0x01,0x00,0x01,0x00 };
const unsigned char ubxRate10Hz[] PROGMEM =
    { 0x06,0x08,0x06,0x00,100,0x00,0x01,0x00,0x01,0x00 };
const unsigned char ubxRate16Hz[] PROGMEM =
    { 0x06,0x08,0x06,0x00,50,0x00,0x01,0x00,0x01,0x00 };

// U-blox NMEA text commands
const char disableRMC[] PROGMEM = "PUBX,40,RMC,0,0,0,0,0,0";
const char disableGLL[] PROGMEM = "PUBX,40,GLL,0,0,0,0,0,0";
const char disableGSV[] PROGMEM = "PUBX,40,GSV,0,0,0,0,0,0";
const char disableGSA[] PROGMEM = "PUBX,40,GSA,0,0,0,0,0,0";
const char disableGGA[] PROGMEM = "PUBX,40,GGA,0,0,0,0,0,0";
const char disableVTG[] PROGMEM = "PUBX,40,VTG,0,0,0,0,0,0";
const char disableZDA[] PROGMEM = "PUBX,40,ZDA,0,0,0,0,0,0";

const char enableRMC[] PROGMEM = "PUBX,40,RMC,0,1,0,0,0,0";
const char enableGLL[] PROGMEM = "PUBX,40,GLL,0,1,0,0,0,0";
const char enableGSV[] PROGMEM = "PUBX,40,GSV,0,1,0,0,0,0";
const char enableGSA[] PROGMEM = "PUBX,40,GSA,0,1,0,0,0,0";
const char enableGGA[] PROGMEM = "PUBX,40,GGA,0,1,0,0,0,0";
const char enableVTG[] PROGMEM = "PUBX,40,VTG,0,1,0,0,0,0";
const char enableZDA[] PROGMEM = "PUBX,40,ZDA,0,1,0,0,0,0";

const char baud9600  [] PROGMEM = "PUBX,41,1,3,3,9600,0";
const char baud38400 [] PROGMEM = "PUBX,41,1,3,3,38400,0";
const char baud57600 [] PROGMEM = "PUBX,41,1,3,3,57600,0";
const char baud115200[] PROGMEM = "PUBX,41,1,3,3,115200,0";


