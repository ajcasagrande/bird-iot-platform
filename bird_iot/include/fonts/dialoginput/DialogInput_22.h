#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t DialogInput_plain_22Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xDB,0x6D,0xB6,0xDB,0x01,0xB6, // '!'
	0xCD,0x9B,0x36,0x6C,0xD9,0x80, // '"'
	0x06,0x20,0x19,0x80,0x66,0x01,0x18,0x7F,0xF9,0xFF,0xE0,0xCC,0x02,0x30,0x18,0x83,0xFF,0xCF,0xFF,0x04,0x60,0x31,0x00,0xCC,0x02,0x30,0x00, // '#'
	0x08,0x01,0x00,0x20,0x1F,0x87,0xF9,0xD1,0x32,0x06,0x40,0xE8,0x0F,0x80,0x7E,0x04,0xE0,0x8C,0x11,0xA2,0x77,0xFC,0x7E,0x01,0x00,0x20,0x04,0x00, // '$'
	0x38,0x01,0xB0,0x0C,0x60,0x31,0x80,0xC6,0x01,0xB0,0x43,0x87,0x00,0xE0,0x0E,0x01,0xC3,0x80,0x1B,0x00,0xC6,0x03,0x18,0x0C,0x60,0x1B,0x00,0x38, // '%'
	0x0F,0x00,0x7E,0x03,0x88,0x0C,0x00,0x30,0x00,0xE0,0x01,0x80,0x0F,0x00,0x6E,0x1B,0x1C,0x6C,0x39,0xB0,0x7C,0xE0,0xF1,0xC3,0x87,0xFB,0x07,0xCE, // '&'
	0xDB,0x6D,0x80, // '''
	0x18,0xC3,0x18,0x61,0x8C,0x30,0xC3,0x0C,0x30,0xC3,0x06,0x18,0x60,0xC3,0x06, // '('
	0xC1,0x86,0x0C,0x30,0xC1,0x86,0x18,0x61,0x86,0x18,0x63,0x0C,0x31,0x86,0x30, // ')'
	0x08,0x02,0x08,0x89,0xAC,0x1C,0x07,0x06,0xB2,0x22,0x08,0x02,0x00, // '*'
	0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x7F,0xFB,0xFF,0xC0,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00, // '+'
	0x73,0x9C,0xCE,0x60, // ','
	0xFD,0xF8, // '-'
	0xEE,0xE0, // '.'
	0x00,0xC0,0x30,0x06,0x01,0x80,0x30,0x06,0x01,0x80,0x30,0x0C,0x01,0x80,0x60,0x0C,0x03,0x00,0x60,0x0C,0x03,0x00,0x60,0x18,0x00, // '/'
	0x1E,0x07,0xE1,0xCE,0x30,0xCC,0x0D,0x81,0xB0,0x36,0x76,0xCE,0xD8,0x1B,0x03,0x60,0x66,0x18,0xE7,0x0F,0xC0,0xF0, // '0'
	0x3C,0x3F,0x0C,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x07,0xF9,0xFE, // '1'
	0x7E,0x1F,0xF3,0x07,0x00,0x60,0x0C,0x01,0x80,0x70,0x0C,0x03,0x80,0xE0,0x38,0x0E,0x03,0x00,0xC0,0x3F,0xF7,0xFE, // '2'
	0x3E,0x1F,0xF2,0x07,0x00,0x60,0x0C,0x01,0x80,0x60,0xF8,0x1F,0x00,0x30,0x03,0x00,0x60,0x0D,0x03,0xBF,0xE3,0xF0, // '3'
	0x03,0x80,0x78,0x07,0x80,0xD8,0x09,0x81,0x98,0x31,0x82,0x18,0x61,0x8C,0x18,0xFF,0xEF,0xFE,0x01,0x80,0x18,0x01,0x80,0x18, // '4'
	0x7F,0x8F,0xF1,0x80,0x30,0x06,0x00,0xFC,0x1F,0xE2,0x1C,0x01,0xC0,0x18,0x03,0x00,0x60,0x1D,0x07,0x3F,0xC3,0xF0, // '5'
	0x1F,0x07,0xF1,0xC2,0x30,0x0E,0x01,0x80,0x33,0xC7,0xFC,0xE1,0xD8,0x1B,0x03,0x60,0x64,0x0C,0xC3,0x8F,0xE0,0xF8, // '6'
	0xFF,0xDF,0xF8,0x06,0x00,0xC0,0x38,0x06,0x00,0xC0,0x30,0x06,0x00,0xC0,0x30,0x06,0x01,0xC0,0x30,0x06,0x01,0x80, // '7'
	0x3F,0x0F,0xF3,0x87,0x60,0x6C,0x0D,0x81,0x98,0x61,0xF8,0x3F,0x0C,0x33,0x03,0x60,0x6C,0x0D,0xC3,0x9F,0xE1,0xF8, // '8'
	0x3E,0x0F,0xE3,0x86,0x60,0x4C,0x0D,0x81,0xB0,0x37,0x0E,0x7F,0xC7,0x98,0x03,0x00,0xE0,0x18,0x87,0x1F,0xC1,0xF0, // '9'
	0xEE,0xE0,0x00,0x00,0xEE,0xE0, // ':'
	0x73,0x9C,0x00,0x00,0x00,0x73,0x9C,0xCE,0x60, // ';'
	0x00,0x20,0x1E,0x07,0xC1,0xE0,0xF8,0x0C,0x00,0xF8,0x01,0xE0,0x07,0xC0,0x1E,0x00,0x20, // '<'
	0xFF,0xEF,0xFE,0x00,0x00,0x00,0x00,0x0F,0xFE,0xFF,0xE0, // '='
	0x80,0x0F,0x00,0x7C,0x00,0xF0,0x03,0xE0,0x06,0x03,0xE0,0xF0,0x7C,0x0F,0x00,0x80,0x00, // '>'
	0x7E,0x3F,0xC8,0x18,0x06,0x03,0x81,0xC0,0xE0,0x70,0x18,0x06,0x01,0x80,0x00,0x00,0x06,0x01,0x80,0x60, // '?'
	0x07,0x80,0xFF,0x0E,0x18,0xE0,0xE6,0x03,0x71,0xDB,0x0F,0xD8,0xC6,0xC6,0x36,0x31,0xB1,0x8D,0x87,0xEE,0x3B,0x30,0x01,0xC0,0x07,0x00,0x1F,0xC0,0x3E,0x00, // '@'
	0x0E,0x00,0xE0,0x0E,0x01,0xB0,0x1B,0x01,0xB0,0x1B,0x03,0x18,0x31,0x83,0x18,0x7F,0xC7,0xFC,0x60,0xC6,0x0C,0xC0,0x6C,0x06, // 'A'
	0xFE,0x1F,0xE3,0x0E,0x60,0xCC,0x19,0x83,0x30,0xE7,0xF8,0xFF,0x18,0x33,0x03,0x60,0x6C,0x0D,0x83,0xBF,0xE7,0xF8, // 'B'
	0x0F,0x87,0xF9,0xC1,0x30,0x0E,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x70,0x06,0x00,0xE0,0x8F,0xF0,0x7C, // 'C'
	0xFC,0x1F,0xE3,0x0E,0x60,0xCC,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x19,0x87,0x3F,0xC7,0xE0, // 'D'
	0xFF,0xDF,0xFB,0x00,0x60,0x0C,0x01,0x80,0x30,0x07,0xFC,0xFF,0x98,0x03,0x00,0x60,0x0C,0x01,0x80,0x3F,0xF7,0xFE, // 'E'
	0xFF,0xDF,0xFB,0x00,0x60,0x0C,0x01,0x80,0x30,0x07,0xFC,0xFF,0x98,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00, // 'F'
	0x0F,0x83,0xFC,0x70,0x46,0x00,0xE0,0x0C,0x00,0xC0,0x0C,0x1E,0xC1,0xEC,0x06,0xC0,0x6E,0x06,0x60,0x67,0x06,0x3F,0xE0,0xF8, // 'G'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x37,0xFE,0xFF,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06, // 'H'
	0xFF,0x7F,0x86,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC3,0xFD,0xFE, // 'I'
	0x1F,0x87,0xE0,0x18,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x06,0x81,0xB0,0xEF,0xF1,0xF8, // 'J'
	0xC0,0xE6,0x0E,0x30,0xE1,0x8E,0x0C,0xE0,0x66,0x03,0x60,0x1F,0x80,0xEC,0x06,0x30,0x31,0xC1,0x86,0x0C,0x18,0x60,0xE3,0x03,0x18,0x0C, // 'K'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x3F,0xF7,0xFE, // 'L'
	0xE0,0xEE,0x0E,0xF1,0xEF,0x1E,0xD1,0x6D,0xB6,0xDB,0x6C,0xA6,0xCE,0x6C,0xE6,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06, // 'M'
	0xE0,0xDC,0x1B,0xC3,0x78,0x6D,0x0D,0xB1,0xB6,0x36,0x66,0xCC,0xD8,0xDB,0x1B,0x61,0x6C,0x3D,0x87,0xB0,0x76,0x0E, // 'N'
	0x1F,0x03,0xF8,0x71,0xC6,0x0C,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0x60,0xC7,0x1C,0x3F,0x81,0xF0, // 'O'
	0xFE,0x1F,0xF3,0x07,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x0E,0xFF,0x9F,0xC3,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00, // 'P'
	0x1F,0x03,0xF8,0x71,0xC6,0x0C,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0x60,0xC7,0x1C,0x3F,0x81,0xF0,0x03,0x80,0x1C,0x00,0x80, // 'Q'
	0xFE,0x07,0xFC,0x30,0x71,0x81,0x8C,0x0C,0x60,0x63,0x06,0x1F,0xF0,0xFF,0x06,0x1C,0x30,0x61,0x83,0x8C,0x0C,0x60,0x73,0x01,0x98,0x0E, // 'R'
	0x1F,0x0F,0xF3,0x82,0x60,0x0C,0x01,0x80,0x38,0x03,0xF0,0x1F,0x80,0x38,0x03,0x00,0x60,0x0D,0x03,0xBF,0xE3,0xF0, // 'S'
	0xFF,0xF7,0xFF,0x81,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0, // 'T'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0xC3,0x9F,0xE0,0xF0, // 'U'
	0xC0,0x6C,0x06,0x60,0xC6,0x0C,0x60,0xC7,0x1C,0x31,0x83,0x18,0x31,0x81,0xB0,0x1B,0x01,0xB0,0x1B,0x00,0xE0,0x0E,0x00,0xE0, // 'V'
	0xC0,0x1B,0x00,0x6C,0x01,0x98,0x0C,0x67,0x31,0x9C,0xC6,0x53,0x19,0x4C,0x6D,0xB1,0xB6,0xC3,0xDE,0x0E,0x38,0x38,0xE0,0xE3,0x83,0x8E,0x0C,0x18, // 'W'
	0xE0,0xE6,0x0C,0x71,0xC3,0x18,0x1B,0x01,0xF0,0x0E,0x00,0xE0,0x0E,0x01,0xF0,0x1B,0x03,0xB8,0x31,0x87,0x1C,0x60,0xCE,0x0E, // 'X'
	0xE0,0x73,0x03,0x1C,0x38,0x61,0x81,0x98,0x0C,0xC0,0x3C,0x01,0xE0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0, // 'Y'
	0xFF,0xEF,0xFE,0x00,0xC0,0x1C,0x01,0x80,0x30,0x07,0x00,0x60,0x0C,0x01,0xC0,0x18,0x03,0x00,0x70,0x06,0x00,0xFF,0xEF,0xFE, // 'Z'
	0xFB,0xEC,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0F,0xBE, // '['
	0xC0,0x0C,0x01,0x80,0x18,0x03,0x00,0x60,0x06,0x00,0xC0,0x0C,0x01,0x80,0x18,0x03,0x00,0x30,0x06,0x00,0xC0,0x0C,0x01,0x80,0x18, // '\'
	0xFB,0xE1,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x6F,0xBE, // ']'
	0x06,0x00,0x78,0x06,0x60,0x61,0x86,0x06,0x60,0x18, // '^'
	0xFF,0xFB,0xFF,0xE0, // '_'
	0xC1,0x83,0x06, // '`'
	0x3F,0x0F,0xF1,0x07,0x00,0x63,0xFC,0xFF,0xB8,0x36,0x06,0xC1,0xDC,0x79,0xFB,0x1E,0x60, // 'a'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0xBC,0x3F,0xE7,0x0C,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB8,0x67,0xFC,0xDE,0x00, // 'b'
	0x1F,0x0F,0xE7,0x0B,0x80,0xC0,0x30,0x0C,0x03,0x00,0xE0,0x1C,0x23,0xF8,0x7C, // 'c'
	0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x3D,0x9F,0xF3,0x0E,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0x98,0x73,0xFE,0x1E,0xC0, // 'd'
	0x1F,0x07,0xF1,0x86,0x60,0x6C,0x0D,0xFF,0xBF,0xF6,0x00,0xC0,0x0C,0x08,0xFF,0x0F,0xC0, // 'e'
	0x07,0x83,0xE1,0x80,0x60,0x18,0x3F,0xEF,0xF8,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x00, // 'f'
	0x1E,0xCF,0xF9,0x87,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xCC,0x39,0xFF,0x0F,0x60,0x0C,0x01,0x90,0x63,0xFC,0x3E,0x00, // 'g'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x9E,0x37,0xE7,0x0E,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xC0, // 'h'
	0x0C,0x01,0x80,0x30,0x00,0x00,0x00,0xF8,0x1F,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x07,0xFE,0xFF,0xC0, // 'i'
	0x0C,0x18,0x30,0x00,0x0F,0x9F,0x06,0x0C,0x18,0x30,0x60,0xC1,0x83,0x06,0x0C,0x18,0x30,0xEF,0x9E,0x00, // 'j'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x87,0x31,0xC6,0x70,0xDC,0x1F,0x03,0xE0,0x76,0x0C,0xE1,0x8E,0x30,0xC6,0x0C,0xC1,0xC0, // 'k'
	0xFC,0x1F,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x80,0x3E,0x03,0xC0, // 'l'
	0xDC,0xE7,0xFF,0xB1,0x8D,0x8C,0x6C,0x63,0x63,0x1B,0x18,0xD8,0xC6,0xC6,0x36,0x31,0xB1,0x8D,0x8C,0x60, // 'm'
	0xCF,0x1B,0xF3,0x87,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x60, // 'n'
	0x1E,0x0F,0xF1,0x86,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xCC,0x31,0xFE,0x0F,0x00, // 'o'
	0xDE,0x1F,0xF3,0x86,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xDC,0x33,0xFE,0x6F,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x00, // 'p'
	0x1E,0xCF,0xF9,0x87,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xCC,0x39,0xFF,0x0F,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0, // 'q'
	0xCF,0x37,0xEF,0x0B,0x80,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00, // 'r'
	0x3F,0x0F,0xF3,0x82,0x60,0x0F,0x00,0xFE,0x07,0xF0,0x06,0x00,0xD0,0x3B,0xFE,0x3F,0x80, // 's'
	0x18,0x06,0x01,0x83,0xFE,0xFF,0x86,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x07,0xE0,0xF8, // 't'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xDC,0x39,0xFB,0x1E,0x60, // 'u'
	0xC0,0xDC,0x39,0x86,0x30,0xC7,0x38,0x66,0x0C,0xC1,0xF8,0x1E,0x03,0xC0,0x78,0x06,0x00, // 'v'
	0xC0,0x1B,0x00,0x66,0x03,0x18,0x0C,0x62,0x31,0x9C,0xC7,0x57,0x0D,0x58,0x3D,0xE0,0xE3,0x83,0x8E,0x06,0x30, // 'w'
	0xE1,0xCC,0x30,0xCC,0x1F,0x81,0xE0,0x18,0x03,0x00,0xF0,0x3F,0x06,0x61,0x86,0x70,0xE0, // 'x'
	0xC0,0xCC,0x31,0x86,0x30,0xC3,0x30,0x66,0x0C,0xC0,0xF0,0x1E,0x03,0xC0,0x38,0x06,0x00,0xC0,0x38,0x06,0x03,0xC0,0x70,0x00, // 'y'
	0xFF,0xDF,0xF8,0x06,0x01,0x80,0x70,0x1C,0x07,0x01,0xC0,0x70,0x0C,0x03,0xFF,0x7F,0xE0, // 'z'
	0x0F,0x0F,0x86,0x03,0x01,0x80,0xC0,0x60,0x30,0x38,0x78,0x3C,0x07,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x07,0xC1,0xE0, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0x80, // '|'
	0xF0,0x7C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x1C,0x07,0x83,0xC3,0x81,0x80,0xC0,0x60,0x30,0x18,0x0C,0x3E,0x1E,0x00 // '}'
};
const GFXglyph DialogInput_plain_22Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,  14,    0,    0 }, // ' '
	  {     1,   3,  16,  14,    6,  -16 }, // '!'
	  {     7,   7,   6,  14,    4,  -16 }, // '"'
	  {    13,  14,  15,  14,    0,  -15 }, // '#'
	  {    40,  11,  20,  14,    2,  -17 }, // '$'
	  {    68,  14,  16,  14,    0,  -16 }, // '%'
	  {    96,  14,  16,  14,    1,  -16 }, // '&'
	  {   124,   3,   6,  14,    6,  -16 }, // '''
	  {   127,   6,  20,  14,    5,  -17 }, // '('
	  {   142,   6,  20,  14,    4,  -17 }, // ')'
	  {   157,  10,  10,  14,    2,  -16 }, // '*'
	  {   170,  13,  12,  14,    1,  -13 }, // '+'
	  {   190,   5,   6,  14,    4,   -3 }, // ','
	  {   194,   7,   2,  14,    4,   -7 }, // '-'
	  {   196,   4,   3,  14,    5,   -3 }, // '.'
	  {   198,  11,  18,  14,    1,  -16 }, // '/'
	  {   223,  11,  16,  14,    1,  -16 }, // '0'
	  {   245,  10,  16,  14,    2,  -16 }, // '1'
	  {   265,  11,  16,  14,    2,  -16 }, // '2'
	  {   287,  11,  16,  14,    1,  -16 }, // '3'
	  {   309,  12,  16,  14,    1,  -16 }, // '4'
	  {   333,  11,  16,  14,    1,  -16 }, // '5'
	  {   355,  11,  16,  14,    1,  -16 }, // '6'
	  {   377,  11,  16,  14,    1,  -16 }, // '7'
	  {   399,  11,  16,  14,    1,  -16 }, // '8'
	  {   421,  11,  16,  14,    1,  -16 }, // '9'
	  {   443,   4,  11,  14,    5,  -11 }, // ':'
	  {   449,   5,  14,  14,    4,  -11 }, // ';'
	  {   458,  12,  11,  14,    1,  -12 }, // '<'
	  {   475,  12,   7,  14,    1,  -11 }, // '='
	  {   486,  12,  11,  14,    1,  -12 }, // '>'
	  {   503,  10,  16,  14,    2,  -16 }, // '?'
	  {   523,  13,  18,  14,    1,  -15 }, // '@'
	  {   553,  12,  16,  14,    1,  -16 }, // 'A'
	  {   577,  11,  16,  14,    1,  -16 }, // 'B'
	  {   599,  11,  16,  14,    1,  -16 }, // 'C'
	  {   621,  11,  16,  14,    1,  -16 }, // 'D'
	  {   643,  11,  16,  14,    1,  -16 }, // 'E'
	  {   665,  11,  16,  14,    1,  -16 }, // 'F'
	  {   687,  12,  16,  14,    1,  -16 }, // 'G'
	  {   711,  11,  16,  14,    1,  -16 }, // 'H'
	  {   733,   9,  16,  14,    3,  -16 }, // 'I'
	  {   751,  10,  16,  14,    1,  -16 }, // 'J'
	  {   771,  13,  16,  14,    1,  -16 }, // 'K'
	  {   797,  11,  16,  14,    1,  -16 }, // 'L'
	  {   819,  12,  16,  14,    1,  -16 }, // 'M'
	  {   843,  11,  16,  14,    1,  -16 }, // 'N'
	  {   865,  12,  16,  14,    1,  -16 }, // 'O'
	  {   889,  11,  16,  14,    1,  -16 }, // 'P'
	  {   911,  12,  19,  14,    1,  -16 }, // 'Q'
	  {   940,  13,  16,  14,    1,  -16 }, // 'R'
	  {   966,  11,  16,  14,    1,  -16 }, // 'S'
	  {   988,  13,  16,  14,    1,  -16 }, // 'T'
	  {  1014,  11,  16,  14,    1,  -16 }, // 'U'
	  {  1036,  12,  16,  14,    1,  -16 }, // 'V'
	  {  1060,  14,  16,  14,    0,  -16 }, // 'W'
	  {  1088,  12,  16,  14,    1,  -16 }, // 'X'
	  {  1112,  13,  16,  14,    1,  -16 }, // 'Y'
	  {  1138,  12,  16,  14,    1,  -16 }, // 'Z'
	  {  1162,   6,  20,  14,    5,  -17 }, // '['
	  {  1177,  11,  18,  14,    1,  -16 }, // '\'
	  {  1202,   6,  20,  14,    3,  -17 }, // ']'
	  {  1217,  13,   6,  14,    1,  -16 }, // '^'
	  {  1227,  14,   2,  14,    0,    3 }, // '_'
	  {  1231,   6,   4,  14,    3,  -18 }, // '`'
	  {  1234,  11,  12,  14,    1,  -12 }, // 'a'
	  {  1251,  11,  17,  14,    1,  -17 }, // 'b'
	  {  1275,  10,  12,  14,    1,  -12 }, // 'c'
	  {  1290,  11,  17,  14,    1,  -17 }, // 'd'
	  {  1314,  11,  12,  14,    1,  -12 }, // 'e'
	  {  1331,  10,  17,  14,    2,  -17 }, // 'f'
	  {  1353,  11,  17,  14,    1,  -12 }, // 'g'
	  {  1377,  11,  17,  14,    1,  -17 }, // 'h'
	  {  1401,  11,  17,  14,    2,  -17 }, // 'i'
	  {  1425,   7,  22,  14,    2,  -17 }, // 'j'
	  {  1445,  11,  17,  14,    1,  -17 }, // 'k'
	  {  1469,  11,  17,  14,    1,  -17 }, // 'l'
	  {  1493,  13,  12,  14,    1,  -12 }, // 'm'
	  {  1513,  11,  12,  14,    1,  -12 }, // 'n'
	  {  1530,  11,  12,  14,    1,  -12 }, // 'o'
	  {  1547,  11,  17,  14,    1,  -12 }, // 'p'
	  {  1571,  11,  17,  14,    1,  -12 }, // 'q'
	  {  1595,  10,  12,  14,    4,  -12 }, // 'r'
	  {  1610,  11,  12,  14,    1,  -12 }, // 's'
	  {  1627,  10,  15,  14,    2,  -15 }, // 't'
	  {  1646,  11,  12,  14,    1,  -12 }, // 'u'
	  {  1663,  11,  12,  14,    1,  -12 }, // 'v'
	  {  1680,  14,  12,  14,    0,  -12 }, // 'w'
	  {  1701,  11,  12,  14,    1,  -12 }, // 'x'
	  {  1718,  11,  17,  14,    1,  -12 }, // 'y'
	  {  1742,  11,  12,  14,    1,  -12 }, // 'z'
	  {  1759,   9,  20,  14,    3,  -17 }, // '{'
	  {  1782,   3,  22,  14,    6,  -17 }, // '|'
	  {  1791,   9,  20,  14,    3,  -17 } // '}'
};
const GFXfont DialogInput_plain_22 PROGMEM = {
(uint8_t  *)DialogInput_plain_22Bitmaps,(GFXglyph *)DialogInput_plain_22Glyphs,0x20, 0x7E, 27};
