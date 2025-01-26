#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Mono_24Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xDB,0x6D,0xB6,0xDB,0x60,0x36,0xC0, // '!'
	0xCD,0x9B,0x36,0x6C,0xD9,0x80, // '"'
	0x06,0x20,0x11,0x80,0xC6,0x03,0x18,0x0C,0x61,0xFF,0xE7,0xFF,0x86,0x30,0x18,0xC0,0x62,0x0F,0xFF,0x3F,0xFC,0x31,0x80,0xC6,0x03,0x18,0x0C,0x40,0x23,0x00, // '#'
	0x06,0x00,0x60,0x0E,0x03,0xF8,0x71,0xC6,0x0C,0x60,0xE6,0x0E,0x60,0x07,0x80,0x3E,0x00,0xF8,0x03,0xC0,0x0E,0x00,0xEC,0x06,0xC0,0xE6,0x1C,0x7F,0x81,0xF0,0x04,0x00,0x40, // '$'
	0x70,0x03,0xE0,0x08,0xC4,0x23,0x30,0x8C,0x83,0xE6,0x07,0x90,0x00,0xC0,0x06,0x00,0x1B,0x80,0xDF,0x02,0x66,0x19,0x18,0xC4,0x60,0x11,0x80,0x7C,0x00,0xE0, // '%'
	0x0F,0x00,0xFE,0x03,0x18,0x0C,0x30,0x31,0x80,0xCE,0x01,0xF0,0x07,0x80,0x3E,0x01,0xD8,0x66,0x33,0x38,0xEC,0xC1,0xF3,0x83,0x86,0x0E,0x1F,0xFC,0x1F,0x38, // '&'
	0xDB,0x6D,0x00, // '''
	0x04,0x18,0x61,0x83,0x0C,0x18,0x30,0x61,0x83,0x06,0x0C,0x18,0x30,0x70,0x60,0xC1,0x81,0x83,0x03,0x03,0x02,0x04, // '('
	0x81,0x81,0x81,0x83,0x03,0x06,0x0C,0x1C,0x18,0x30,0x60,0xC1,0x83,0x0E,0x18,0x30,0x61,0x83,0x0C,0x18,0x60,0x80, // ')'
	0x0E,0x00,0x40,0x04,0x08,0x42,0xF4,0xE7,0xFE,0x0E,0x01,0xA0,0x1B,0x03,0x18,0x71,0xC0,0x10, // '*'
	0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x03,0xFF,0xDF,0xFE,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x00, // '+'
	0x73,0x9C,0xC6,0x61,0x00, // ','
	0xFF,0xBF,0xE0, // '-'
	0xEE,0xE0, // '.'
	0x01,0x80,0xC0,0x30,0x0C,0x06,0x01,0x80,0x60,0x30,0x0C,0x06,0x01,0x80,0x60,0x30,0x0C,0x06,0x01,0x80,0x60,0x30,0x00, // '/'
	0x1F,0x07,0xF8,0x61,0xCC,0x0C,0xC0,0xEC,0x0E,0xC1,0xEC,0x76,0xCE,0x6D,0x86,0xF0,0x6E,0x06,0xC0,0xEC,0x0C,0x61,0xC7,0xF8,0x1F,0x00, // '0'
	0x06,0x1E,0xFE,0xE6,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06, // '1'
	0x1F,0x03,0xFC,0x18,0x31,0x81,0xCC,0x06,0x00,0x70,0x03,0x00,0x38,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0xC0,0x1C,0x01,0xC0,0x1F,0xFE,0xFF,0xF0, // '2'
	0x1F,0x07,0xFC,0x60,0xCE,0x0E,0x00,0xE0,0x0E,0x00,0xC0,0xF8,0x0F,0x80,0x1C,0x00,0xE0,0x06,0xC0,0x6E,0x0E,0x60,0xC7,0xFC,0x1F,0x00, // '3'
	0x01,0xC0,0x0E,0x00,0xF0,0x0D,0x80,0x6C,0x06,0x60,0x63,0x03,0x18,0x30,0xC3,0x06,0x18,0x31,0xFF,0xEF,0xFF,0x00,0x60,0x03,0x00,0x18,0x00,0xC0, // '4'
	0x3F,0xC3,0xFC,0x60,0x06,0x00,0x60,0x06,0x00,0x7F,0x07,0xFC,0x61,0xC0,0x0E,0x00,0x60,0x06,0xC0,0x6E,0x0E,0x60,0xC3,0xFC,0x1F,0x00, // '5'
	0x07,0x03,0xE0,0xE0,0x30,0x06,0x01,0x9C,0x3F,0xE7,0x8E,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0xC1,0x98,0x73,0xFC,0x1F,0x00, // '6'
	0xFF,0xF7,0xFF,0x80,0x18,0x00,0xC0,0x0C,0x00,0x60,0x06,0x00,0x30,0x03,0x80,0x18,0x01,0xC0,0x0C,0x00,0x60,0x06,0x00,0x30,0x03,0x00,0x38,0x00, // '7'
	0x1F,0x07,0xF8,0x60,0xC6,0x0C,0xE0,0xE6,0x0C,0x71,0xC3,0xF8,0x3F,0x86,0x0C,0xE0,0xEC,0x06,0xC0,0x6E,0x0E,0x60,0xC7,0xFC,0x1F,0x00, // '8'
	0x1E,0x0F,0xF3,0x86,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xE1,0xCF,0xF8,0xFB,0x00,0x60,0x0C,0x03,0x00,0xE1,0xF8,0x3C,0x00, // '9'
	0xEE,0xE0,0x00,0x00,0x00,0xEE,0xE0, // ':'
	0xE7,0x38,0x00,0x00,0x00,0x00,0x1C,0xE7,0x31,0x98,0x40, // ';'
	0x00,0x40,0x38,0x1F,0x1F,0x0F,0x81,0x80,0x1E,0x00,0xF8,0x07,0xC0,0x38,0x01,0x00, // '<'
	0xFF,0xEF,0xFE,0x00,0x00,0x00,0x00,0x0F,0xFE,0xFF,0xE0, // '='
	0x80,0x1C,0x01,0xF0,0x0F,0x80,0x3C,0x01,0x81,0xF0,0xF8,0xF8,0x1C,0x02,0x00,0x00, // '>'
	0x1F,0x0F,0xF1,0x87,0x60,0x60,0x0C,0x01,0x80,0x70,0x1C,0x07,0x01,0xC0,0x30,0x06,0x00,0x00,0x00,0x03,0x00,0x60,0x0C,0x00, // '?'
	0x0F,0x80,0x7F,0x83,0x06,0x18,0xCC,0x47,0x93,0x32,0x4D,0x89,0xA6,0x26,0x98,0x9A,0x66,0x49,0x99,0x27,0xBC,0xCE,0xE1,0x00,0x06,0x00,0x0F,0xE0,0x0F,0x00, // '@'
	0x06,0x00,0x1C,0x00,0x70,0x03,0xC0,0x0D,0x80,0x36,0x01,0x98,0x06,0x30,0x18,0xC0,0xE3,0x03,0x0E,0x0F,0xF8,0x7F,0xE1,0x81,0xC6,0x03,0x38,0x0C,0xC0,0x38, // 'A'
	0xFF,0x0F,0xF8,0xC0,0xCC,0x0E,0xC0,0xEC,0x0E,0xC1,0xCF,0xF8,0xFF,0x8C,0x0C,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0xCF,0xFC,0xFF,0x00, // 'B'
	0x0F,0x81,0xFE,0x0C,0x18,0xC0,0xE6,0x03,0x70,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0xC0,0x06,0x03,0x30,0x38,0xC1,0x87,0xF8,0x0F,0x80, // 'C'
	0xFE,0x0F,0xF8,0xC1,0xCC,0x0C,0xC0,0xEC,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0xEC,0x0C,0xC1,0xCF,0xF8,0xFE,0x00, // 'D'
	0xFF,0xEF,0xFE,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0F,0xF8,0xFF,0x8C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0F,0xFE,0xFF,0xE0, // 'E'
	0xFF,0xEF,0xFE,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xFF,0xCF,0xFC,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x00, // 'F'
	0x0F,0x81,0xFE,0x0C,0x18,0xC0,0xE6,0x03,0x70,0x03,0x00,0x18,0x00,0xC1,0xF6,0x0F,0xB0,0x0D,0xC0,0x66,0x03,0x30,0x18,0xC1,0xC3,0xFC,0x0F,0x80, // 'G'
	0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6F,0xFE,0xFF,0xEC,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x60, // 'H'
	0xFF,0xDF,0xF8,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x07,0xFE,0xFF,0xC0, // 'I'
	0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0xC0,0x6E,0x06,0x70,0xC3,0xFC,0x1F,0x00, // 'J'
	0xC0,0xF6,0x06,0x30,0x71,0x87,0x0C,0x70,0x63,0x03,0x30,0x1B,0x80,0xFC,0x07,0xF0,0x39,0xC1,0x86,0x0C,0x38,0x60,0xE3,0x03,0x18,0x1C,0xC0,0x70, // 'K'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0F,0xFE,0xFF,0xE0, // 'L'
	0xE0,0xEE,0x0E,0xE1,0xEF,0x1E,0xF1,0x6F,0x36,0xDB,0x6D,0xA6,0xDE,0x6C,0xE6,0xCC,0x6C,0xC6,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x60, // 'M'
	0xC0,0x6E,0x06,0xE0,0x6F,0x06,0xF0,0x6F,0x86,0xD8,0xEC,0xCE,0xCC,0xEC,0x6E,0xC6,0xEC,0x3E,0xC3,0xEC,0x1E,0xC1,0xEC,0x0E,0xC0,0xE0, // 'N'
	0x0F,0x01,0xFE,0x0C,0x38,0xC0,0xC6,0x03,0x70,0x1B,0x00,0xD8,0x06,0xC0,0x36,0x01,0xB0,0x0D,0xC0,0x66,0x03,0x30,0x30,0xC3,0x87,0xF8,0x0F,0x80, // 'O'
	0xFF,0x0F,0xFC,0xC0,0xEC,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x0E,0xFF,0xCF,0xF0,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x00, // 'P'
	0x0F,0x80,0xFF,0x03,0x0E,0x18,0x18,0x60,0x33,0x00,0xCC,0x03,0x30,0x0C,0xC0,0x33,0x00,0xCC,0x03,0x30,0x0C,0x60,0x31,0x81,0x83,0x0E,0x0F,0xF0,0x0F,0xC0,0x01,0xC0,0x03,0x80,0x04, // 'Q'
	0xFF,0x0F,0xF8,0xC0,0xCC,0x0E,0xC0,0x6C,0x06,0xC0,0xEC,0x0C,0xFF,0x8F,0xF0,0xC3,0x0C,0x38,0xC1,0x8C,0x1C,0xC0,0xCC,0x0E,0xC0,0x60, // 'R'
	0x0F,0x81,0xFF,0x1C,0x18,0xC0,0x66,0x03,0x30,0x01,0xC0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x1C,0x00,0x6E,0x03,0x30,0x19,0xC1,0xC7,0xFC,0x0F,0x80, // 'S'
	0xFF,0xFB,0xFF,0xE0,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00, // 'T'
	0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0xEC,0x0C,0x61,0xC7,0xF8,0x1F,0x00, // 'U'
	0xC0,0x37,0x01,0x98,0x1C,0xC0,0xC6,0x06,0x18,0x30,0xC3,0x06,0x18,0x18,0xC0,0xCC,0x06,0x60,0x3B,0x00,0xF8,0x07,0x80,0x3C,0x00,0xE0,0x06,0x00, // 'V'
	0xC6,0x1B,0x1C,0x6C,0x71,0xB1,0xCC,0xC7,0x31,0x34,0xC6,0xD3,0x1B,0x6C,0x6D,0xB1,0xA6,0xC6,0x9B,0x1E,0x28,0x78,0xE0,0xE3,0x83,0x8E,0x0C,0x38,0x30,0xE0, // 'W'
	0xE0,0x39,0x81,0xC3,0x06,0x0E,0x38,0x18,0xC0,0x76,0x00,0xF8,0x01,0xC0,0x07,0x00,0x3C,0x00,0xD8,0x07,0x60,0x18,0xC0,0xE3,0x87,0x06,0x18,0x1C,0xE0,0x38, // 'X'
	0xC0,0x37,0x03,0x98,0x18,0xE1,0xC3,0x0C,0x1C,0xE0,0x66,0x03,0xB0,0x0F,0x00,0x78,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00, // 'Y'
	0xFF,0xE7,0xFF,0x00,0x38,0x01,0x80,0x1C,0x01,0xC0,0x0C,0x00,0xE0,0x06,0x00,0x60,0x07,0x00,0x30,0x03,0x80,0x38,0x01,0x80,0x1F,0xFE,0xFF,0xF0, // 'Z'
	0xFB,0xEC,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0xEF,0x80, // '['
	0xC0,0x30,0x06,0x01,0x80,0x60,0x0C,0x03,0x00,0x60,0x18,0x06,0x00,0xC0,0x30,0x04,0x01,0x80,0x60,0x0C,0x03,0x00,0xE0, // '\'
	0xF7,0x8C,0x63,0x18,0xC6,0x31,0x8C,0x63,0x18,0xC6,0x31,0x8C,0x63,0x7B,0xC0, // ']'
	0x18,0x07,0x03,0xC0,0xF0,0x36,0x19,0x86,0x33,0x0C,0xC3,0x80, // '^'
	0xFF,0xEF,0xFE, // '_'
	0xE1,0xC3,0x80, // '`'
	0x1F,0x07,0xF8,0xE1,0xCC,0x0C,0x00,0xC1,0xFC,0x7F,0xCE,0x0C,0xC0,0xCC,0x0C,0xE1,0xC7,0xFC,0x3E,0xE0, // 'a'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0xF0,0xFF,0x8E,0x1C,0xC0,0xCC,0x0E,0xC0,0x6C,0x06,0xC0,0x6C,0x0E,0xC0,0xCE,0x1C,0xFF,0x8C,0xF0, // 'b'
	0x1F,0x07,0xF8,0x60,0xCC,0x0C,0xC0,0x6C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x0E,0x60,0xC7,0xF8,0x1F,0x00, // 'c'
	0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x3D,0x9F,0xF3,0x0E,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x33,0x0E,0x7F,0xC3,0xD8, // 'd'
	0x1F,0x03,0xF8,0x61,0xCC,0x0C,0xC0,0x6F,0xFE,0xFF,0xEC,0x00,0xC0,0x0E,0x04,0x60,0xE7,0xFC,0x1F,0x00, // 'e'
	0x03,0xC0,0x7E,0x0E,0x01,0xC0,0x1C,0x01,0x80,0xFF,0xCF,0xFC,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x01,0x80,0x18,0x00, // 'f'
	0x1E,0xCF,0xF9,0x87,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x19,0x87,0x3F,0xE1,0xEC,0x01,0x90,0x37,0x0E,0x7F,0x83,0xC0, // 'g'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0xF0,0xDF,0xCE,0x0C,0xC0,0xCC,0x0C,0xC0,0xEC,0x0E,0xC0,0xEC,0x0E,0xC0,0xEC,0x0E,0xC0,0xEC,0x0E, // 'h'
	0x06,0x00,0xE0,0x06,0x00,0x00,0xFE,0x0F,0xE0,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x0F,0xFE,0xFF,0xE0, // 'i'
	0x03,0x03,0x80,0xC0,0x07,0xF3,0xF8,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x81,0xC0,0xC7,0xE7,0xC0, // 'j'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x1C,0xC3,0x8C,0x70,0xCE,0x0D,0xC0,0xD8,0x0F,0xC0,0xEE,0x0C,0x70,0xC3,0x8C,0x18,0xC1,0xCC,0x0E, // 'k'
	0xFE,0x0F,0xE0,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0xFF,0xEF,0xFE, // 'l'
	0xDC,0xE7,0xFF,0xB1,0x8D,0x8C,0x6C,0x63,0x63,0x1B,0x18,0xD8,0xC6,0xC6,0x36,0x31,0xB1,0x8D,0x8C,0x6C,0x63,0x00, // 'm'
	0xCF,0x1B,0xFB,0x83,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0C, // 'n'
	0x0F,0x81,0xFE,0x1C,0x38,0xC0,0xC6,0x03,0x70,0x1B,0x80,0xDC,0x06,0x60,0x33,0x03,0x1C,0x38,0x7F,0x80,0xF8,0x00, // 'o'
	0xDF,0x0F,0xF8,0xE1,0xCC,0x0C,0xC0,0xEC,0x06,0xC0,0x6C,0x06,0xC0,0xEC,0x0C,0xE1,0xCF,0xF8,0xDF,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00, // 'p'
	0x1E,0xCF,0xF9,0x87,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x19,0x87,0x3F,0xE1,0xEC,0x01,0x80,0x30,0x06,0x00,0xC0,0x18, // 'q'
	0xCF,0xBF,0xCE,0x03,0x80,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x00, // 'r'
	0x1F,0x07,0xFC,0x60,0xCE,0x0E,0x60,0x07,0x80,0x1F,0x80,0x3C,0x00,0xEC,0x0E,0xE0,0xC7,0xFC,0x1F,0x00, // 's'
	0x18,0x03,0x00,0x60,0x7F,0xEF,0xFC,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x38,0x03,0xF0,0x3E, // 't'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x19,0x87,0x3F,0xE3,0xEC, // 'u'
	0xE0,0x33,0x03,0x98,0x18,0x60,0xC3,0x0C,0x18,0x60,0x63,0x03,0x30,0x0D,0x80,0x68,0x03,0xC0,0x0E,0x00,0x60,0x00, // 'v'
	0xC6,0x1B,0x18,0x6C,0x71,0x31,0xCC,0xCF,0x31,0x34,0xC6,0xDB,0x1A,0x68,0x79,0xA0,0xE3,0x83,0x8E,0x0C,0x38,0x30,0xC0, // 'w'
	0xE0,0x71,0x83,0x0E,0x30,0x33,0x80,0xF8,0x07,0x80,0x1C,0x01,0xE0,0x0D,0x80,0xCE,0x0E,0x30,0xE0,0xCE,0x07,0x00, // 'x'
	0xC0,0x3B,0x80,0xC6,0x06,0x1C,0x18,0x30,0xE0,0xE3,0x01,0x8C,0x06,0x60,0x0D,0x80,0x3C,0x00,0xF0,0x01,0xC0,0x06,0x00,0x18,0x00,0xC0,0x07,0x00,0x78,0x01,0xC0,0x00, // 'y'
	0xFF,0xCF,0xFC,0x01,0xC0,0x38,0x07,0x00,0x60,0x0C,0x01,0xC0,0x38,0x07,0x00,0x60,0x0F,0xFE,0xFF,0xE0, // 'z'
	0x07,0x07,0x83,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x1C,0x3C,0x1C,0x03,0x00,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x80,0xC0,0x78,0x0C, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0x80, // '|'
	0xC0,0x70,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x38,0x0C,0x03,0xC1,0xE1,0xC0,0xC0,0xE0,0x60,0x30,0x18,0x0C,0x06,0x07,0x07,0x03,0x00 // '}'
};
const GFXglyph Roboto_Mono_24Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,  15,    0,    0 }, // ' '
	  {     1,   3,  17,  15,    6,  -17 }, // '!'
	  {     8,   7,   6,  15,    4,  -18 }, // '"'
	  {    14,  14,  17,  15,    1,  -17 }, // '#'
	  {    44,  12,  22,  15,    2,  -20 }, // '$'
	  {    77,  14,  17,  15,    1,  -17 }, // '%'
	  {   107,  14,  17,  15,    1,  -17 }, // '&'
	  {   137,   3,   6,  15,    6,  -18 }, // '''
	  {   140,   7,  25,  15,    4,  -19 }, // '('
	  {   162,   7,  25,  15,    4,  -19 }, // ')'
	  {   184,  12,  12,  15,    2,  -14 }, // '*'
	  {   202,  13,  13,  15,    1,  -15 }, // '+'
	  {   224,   5,   7,  15,    4,   -3 }, // ','
	  {   229,  10,   2,  15,    3,   -9 }, // '-'
	  {   232,   4,   3,  15,    6,   -3 }, // '.'
	  {   234,  10,  18,  15,    3,  -17 }, // '/'
	  {   257,  12,  17,  15,    2,  -17 }, // '0'
	  {   283,   8,  17,  15,    2,  -17 }, // '1'
	  {   300,  13,  17,  15,    1,  -17 }, // '2'
	  {   328,  12,  17,  15,    1,  -17 }, // '3'
	  {   354,  13,  17,  15,    1,  -17 }, // '4'
	  {   382,  12,  17,  15,    2,  -17 }, // '5'
	  {   408,  11,  17,  15,    2,  -17 }, // '6'
	  {   432,  13,  17,  15,    1,  -17 }, // '7'
	  {   460,  12,  17,  15,    2,  -17 }, // '8'
	  {   486,  11,  17,  15,    2,  -17 }, // '9'
	  {   510,   4,  13,  15,    7,  -13 }, // ':'
	  {   517,   5,  17,  15,    6,  -13 }, // ';'
	  {   528,  11,  11,  15,    2,  -13 }, // '<'
	  {   544,  12,   7,  15,    2,  -11 }, // '='
	  {   555,  11,  11,  15,    2,  -13 }, // '>'
	  {   571,  11,  17,  15,    2,  -17 }, // '?'
	  {   595,  14,  17,  15,    1,  -17 }, // '@'
	  {   625,  14,  17,  15,    1,  -17 }, // 'A'
	  {   655,  12,  17,  15,    2,  -17 }, // 'B'
	  {   681,  13,  17,  15,    1,  -17 }, // 'C'
	  {   709,  12,  17,  15,    2,  -17 }, // 'D'
	  {   735,  12,  17,  15,    2,  -17 }, // 'E'
	  {   761,  12,  17,  15,    2,  -17 }, // 'F'
	  {   787,  13,  17,  15,    1,  -17 }, // 'G'
	  {   815,  12,  17,  15,    2,  -17 }, // 'H'
	  {   841,  11,  17,  15,    2,  -17 }, // 'I'
	  {   865,  12,  17,  15,    1,  -17 }, // 'J'
	  {   891,  13,  17,  15,    2,  -17 }, // 'K'
	  {   919,  12,  17,  15,    2,  -17 }, // 'L'
	  {   945,  12,  17,  15,    2,  -17 }, // 'M'
	  {   971,  12,  17,  15,    2,  -17 }, // 'N'
	  {   997,  13,  17,  15,    1,  -17 }, // 'O'
	  {  1025,  12,  17,  15,    2,  -17 }, // 'P'
	  {  1051,  14,  20,  15,    1,  -17 }, // 'Q'
	  {  1086,  12,  17,  15,    2,  -17 }, // 'R'
	  {  1112,  13,  17,  15,    1,  -17 }, // 'S'
	  {  1140,  14,  17,  15,    1,  -17 }, // 'T'
	  {  1170,  12,  17,  15,    2,  -17 }, // 'U'
	  {  1196,  13,  17,  15,    1,  -17 }, // 'V'
	  {  1224,  14,  17,  15,    1,  -17 }, // 'W'
	  {  1254,  14,  17,  15,    1,  -17 }, // 'X'
	  {  1284,  13,  17,  15,    1,  -17 }, // 'Y'
	  {  1312,  13,  17,  15,    1,  -17 }, // 'Z'
	  {  1340,   6,  23,  15,    5,  -19 }, // '['
	  {  1358,  10,  18,  15,    3,  -17 }, // '\'
	  {  1381,   5,  23,  15,    5,  -19 }, // ']'
	  {  1396,  10,   9,  15,    3,  -17 }, // '^'
	  {  1408,  12,   2,  15,    2,    0 }, // '_'
	  {  1411,   6,   3,  15,    5,  -18 }, // '`'
	  {  1414,  12,  13,  15,    2,  -13 }, // 'a'
	  {  1434,  12,  18,  15,    2,  -18 }, // 'b'
	  {  1461,  12,  13,  15,    2,  -13 }, // 'c'
	  {  1481,  11,  18,  15,    2,  -18 }, // 'd'
	  {  1506,  12,  13,  15,    2,  -13 }, // 'e'
	  {  1526,  12,  19,  15,    2,  -19 }, // 'f'
	  {  1555,  11,  18,  15,    2,  -13 }, // 'g'
	  {  1580,  12,  18,  15,    2,  -18 }, // 'h'
	  {  1607,  12,  17,  15,    2,  -17 }, // 'i'
	  {  1633,   9,  22,  15,    2,  -17 }, // 'j'
	  {  1658,  12,  18,  15,    2,  -18 }, // 'k'
	  {  1685,  12,  18,  15,    2,  -18 }, // 'l'
	  {  1712,  13,  13,  15,    1,  -13 }, // 'm'
	  {  1734,  11,  13,  15,    2,  -13 }, // 'n'
	  {  1752,  13,  13,  15,    1,  -13 }, // 'o'
	  {  1774,  12,  18,  15,    2,  -13 }, // 'p'
	  {  1801,  11,  18,  15,    2,  -13 }, // 'q'
	  {  1826,  10,  13,  15,    4,  -13 }, // 'r'
	  {  1843,  12,  13,  15,    2,  -13 }, // 's'
	  {  1863,  11,  16,  15,    2,  -16 }, // 't'
	  {  1885,  11,  13,  15,    2,  -13 }, // 'u'
	  {  1903,  13,  13,  15,    1,  -13 }, // 'v'
	  {  1925,  14,  13,  15,    1,  -13 }, // 'w'
	  {  1948,  13,  13,  15,    1,  -13 }, // 'x'
	  {  1970,  14,  18,  15,    1,  -13 }, // 'y'
	  {  2002,  12,  13,  15,    2,  -13 }, // 'z'
	  {  2022,   9,  23,  15,    4,  -19 }, // '{'
	  {  2048,   3,  22,  15,    6,  -17 }, // '|'
	  {  2057,   9,  23,  15,    4,  -19 } // '}'
};
const GFXfont Roboto_Mono_24 PROGMEM = {
(uint8_t  *)Roboto_Mono_24Bitmaps,(GFXglyph *)Roboto_Mono_24Glyphs,0x20, 0x7E, 29};
