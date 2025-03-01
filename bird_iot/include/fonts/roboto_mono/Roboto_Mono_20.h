#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Mono_20Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xDB,0x6D,0xB6,0xD8,0x01,0xB0, // '!'
	0xCB,0x2C,0xB2,0xC8, // '"'
	0x08,0x80,0x88,0x19,0x81,0x98,0xFF,0xEF,0x10,0x11,0x01,0x30,0x33,0x03,0x3C,0xFF,0xC2,0x20,0x22,0x06,0x60,0x66,0x00, // '#'
	0x08,0x02,0x01,0xC1,0xF8,0x63,0x30,0xCC,0x1B,0x00,0x60,0x0F,0x01,0xE0,0x0C,0x01,0xA0,0x6C,0x1B,0x0C,0x7E,0x06,0x01,0x80, // '$'
	0x78,0x03,0xC0,0x33,0x21,0x99,0x04,0xD0,0x3D,0x80,0x48,0x00,0xC0,0x04,0x80,0x6F,0x02,0xC8,0x36,0x61,0x33,0x00,0xF0,0x07,0x80, // '%'
	0x1E,0x03,0xE0,0x63,0x06,0x30,0x62,0x03,0xE0,0x3C,0x03,0x80,0x6C,0x4C,0x6C,0xC6,0xCC,0x38,0xC1,0x87,0xFC,0x3C,0xE0, // '&'
	0xAA,0x80, // '''
	0x0C,0x30,0x41,0x82,0x0C,0x18,0x20,0x41,0x83,0x02,0x04,0x0C,0x18,0x30,0x20,0x60,0x60,0x60,0x40, // '('
	0x81,0x06,0x0C,0x30,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x84,0x30,0x86,0x30,0x80, // ')'
	0x18,0x06,0x00,0x83,0x26,0xFF,0x86,0x03,0xC0,0x98,0x63,0x08,0x80, // '*'
	0x0C,0x01,0x80,0x30,0x06,0x00,0xC1,0xFF,0xBF,0x00,0x60,0x0C,0x01,0x80,0x30,0x00, // '+'
	0x66,0x66,0xC4, // ','
	0xFF,0x7F,0x80, // '-'
	0xCE,0xC0, // '.'
	0x03,0x01,0x01,0x80,0xC0,0x40,0x60,0x30,0x10,0x18,0x08,0x0C,0x06,0x02,0x03,0x03,0x00, // '/'
	0x1E,0x07,0xE1,0x86,0x20,0x4C,0x0D,0x83,0xB1,0xF6,0x66,0xD8,0xDE,0x1B,0x03,0x20,0x46,0x18,0x7E,0x07,0x80, // '0'
	0x04,0x3B,0xF6,0x60,0xC1,0x83,0x06,0x0C,0x18,0x30,0x60,0xC1,0x83,0x00, // '1'
	0x3E,0x1F,0xCC,0x33,0x06,0xC1,0x80,0x60,0x30,0x18,0x06,0x03,0x01,0x80,0xC0,0x60,0x3F,0xEF,0xF8, // '2'
	0x3E,0x1F,0xCC,0x13,0x06,0x01,0x80,0xC0,0xF0,0x78,0x03,0x00,0x60,0x1B,0x06,0xC1,0x9F,0xC3,0xE0, // '3'
	0x03,0x00,0xE0,0x1C,0x07,0x81,0xB0,0x26,0x0C,0xC1,0x18,0x63,0x18,0x63,0xFF,0x7F,0xE0,0x30,0x06,0x00,0xC0, // '4'
	0x7F,0x18,0x04,0x01,0x00,0x40,0x12,0x0F,0xE3,0x0C,0x01,0x80,0x60,0x1B,0x06,0xC3,0x1F,0xC3,0xE0, // '5'
	0x0E,0x07,0x83,0x01,0x80,0x60,0x11,0x0D,0xF3,0x8E,0xC1,0xB0,0x2C,0x09,0x86,0x61,0x8F,0xC1,0xE0, // '6'
	0xFF,0xDF,0xF0,0x06,0x00,0xC0,0x30,0x06,0x00,0x80,0x30,0x06,0x01,0x80,0x30,0x0C,0x01,0x80,0x20,0x0C,0x00, // '7'
	0x3C,0x1F,0xCC,0x33,0x04,0xC1,0x30,0xC7,0xE0,0xF8,0x63,0x30,0x6C,0x1B,0x06,0xC3,0x1F,0xC3,0xE0, // '8'
	0x1E,0x0F,0xC6,0x19,0x06,0xC0,0xB0,0x24,0x09,0x86,0x7F,0x87,0xA0,0x18,0x06,0x03,0x07,0x83,0xC0, // '9'
	0xCE,0xC0,0x00,0x00,0x0C,0xEC, // ':'
	0x63,0x98,0x00,0x00,0x00,0x00,0x18,0xC6,0x33,0x08, // ';'
	0x01,0x03,0x87,0x8F,0x0C,0x07,0x80,0xF0,0x1E,0x01,0x00, // '<'
	0xFF,0x7F,0x80,0x00,0x0F,0xF7,0xF8, // '='
	0x80,0x70,0x1E,0x03,0xC0,0x30,0x78,0xF1,0xC0,0x80,0x00, // '>'
	0x3C,0x3F,0xB0,0xD8,0x60,0x30,0x18,0x18,0x1C,0x1C,0x0C,0x06,0x00,0x00,0x00,0xC0,0x60, // '?'
	0x1F,0x07,0xF1,0x82,0x22,0x2C,0xF5,0x34,0xA4,0x95,0x92,0xB2,0x56,0x4A,0x7F,0x4C,0xC4,0x00,0xFC,0x07,0xC0, // '@'
	0x0C,0x01,0x80,0x38,0x0F,0x01,0xA0,0x26,0x0C,0xC1,0x98,0x31,0x0F,0xF1,0xFE,0x30,0x44,0x0D,0x81,0xB0,0x30, // 'A'
	0xFC,0x33,0xCC,0x33,0x06,0xC1,0xB0,0xCC,0xE3,0xF8,0xC3,0x30,0x6C,0x1B,0x06,0xC3,0xB3,0xCF,0xE0, // 'B'
	0x1E,0x07,0xF1,0x86,0x20,0x6C,0x0D,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x03,0x20,0x66,0x18,0x7F,0x07,0x80, // 'C'
	0xF8,0x27,0x88,0x32,0x0C,0x81,0xA0,0x68,0x1A,0x06,0x81,0xA0,0x68,0x1A,0x0C,0x83,0x27,0x8F,0x80, // 'D'
	0xFF,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0xFC,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x3F,0xEF,0xF8, // 'E'
	0xFF,0xB0,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0xFC,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x00, // 'F'
	0x1E,0x07,0xF1,0x86,0x20,0x6C,0x01,0x80,0x30,0x06,0x3E,0xC7,0xD8,0x1B,0x03,0x20,0x66,0x0C,0x7F,0x07,0xC0, // 'G'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x37,0xFE,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x30, // 'H'
	0xFF,0x7C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xFB,0xFC, // 'I'
	0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x1B,0x06,0xC1,0x9F,0xC3,0xE0, // 'J'
	0xC1,0x98,0x63,0x18,0x67,0x0C,0xC1,0xB0,0x3C,0x07,0xC0,0xFC,0x19,0x83,0x18,0x63,0x0C,0x31,0x87,0x30,0x70, // 'K'
	0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x3F,0xEF,0xF8, // 'L'
	0xE1,0xDC,0x3B,0x87,0x79,0xED,0x3D,0xA5,0xB7,0xB6,0xF6,0xCC,0xD9,0x9B,0x33,0x60,0x6C,0x0D,0x81,0xB0,0x30, // 'M'
	0xC0,0xDC,0x1B,0x83,0x78,0x6D,0x0D,0xB1,0xB2,0x36,0x66,0xC4,0xD8,0xDB,0x0B,0x61,0xEC,0x1D,0x83,0xB0,0x30, // 'N'
	0x1E,0x07,0xE1,0x86,0x20,0x4C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x20,0x46,0x18,0x7E,0x07,0x80, // 'O'
	0xFE,0x33,0xCC,0x1B,0x06,0xC1,0xB0,0x6C,0x1B,0x3C,0xFE,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x00, // 'P'
	0x1E,0x07,0xE1,0x86,0x60,0x4C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x66,0x18,0x7E,0x07,0xC0,0x0E,0x00,0xC0, // 'Q'
	0xFC,0x33,0xCC,0x33,0x06,0xC1,0xB0,0x6C,0x33,0x3C,0xFC,0x31,0x8C,0x63,0x08,0xC3,0x30,0x4C,0x18, // 'R'
	0x1E,0x07,0xF1,0x87,0x20,0x66,0x00,0xC0,0x0E,0x00,0xF8,0x07,0x80,0x38,0x03,0x60,0x66,0x0C,0xFF,0x07,0xC0, // 'S'
	0xFF,0xDF,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00, // 'T'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x20,0x46,0x18,0x7E,0x07,0x80, // 'U'
	0xC0,0xD8,0x1B,0x02,0x30,0xC6,0x18,0xC3,0x0C,0xC1,0x98,0x33,0x02,0xC0,0x78,0x0F,0x01,0xE0,0x18,0x03,0x00, // 'V'
	0x8C,0x6C,0xC4,0xCC,0x4C,0xEC,0xCE,0xCD,0xEC,0xDA,0xC5,0xAC,0x52,0xC5,0x38,0x53,0x87,0x38,0x71,0x87,0x18,0x61,0x80, // 'W'
	0xC0,0xCC,0x31,0x86,0x19,0x83,0xB0,0x3C,0x03,0x80,0x60,0x0E,0x03,0xC0,0xCC,0x19,0x86,0x18,0xC3,0xB0,0x30, // 'X'
	0xC0,0xD8,0x31,0x86,0x30,0xC3,0x30,0x66,0x07,0x80,0xF0,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00, // 'Y'
	0xFF,0x9F,0xF0,0x06,0x01,0x80,0x60,0x0C,0x03,0x00,0x60,0x18,0x03,0x00,0xC0,0x30,0x06,0x01,0xFF,0xBF,0xF0, // 'Z'
	0xF7,0xB1,0x8C,0x63,0x18,0xC6,0x31,0x8C,0x63,0x18,0xC6,0x3D,0xE0, // '['
	0xC0,0x20,0x18,0x04,0x03,0x01,0x80,0x40,0x30,0x08,0x06,0x03,0x00,0x80,0x60,0x30,0x0C, // '\'
	0xF7,0x8C,0x63,0x18,0xC6,0x31,0x8C,0x63,0x18,0xC6,0x31,0x8D,0xE0, // ']'
	0x18,0x0C,0x0F,0x07,0x82,0x43,0x31,0x99,0x86, // '^'
	0xFF,0x7F,0x80, // '_'
	0xE1,0x80, // '`'
	0x3C,0x3F,0xCC,0x30,0x0C,0x3F,0x3E,0xCC,0x32,0x0C,0xC3,0x3F,0xC7,0x98, // 'a'
	0xC0,0x30,0x0C,0x03,0x00,0xFC,0x3F,0xCC,0x33,0x04,0xC1,0xB0,0x6C,0x1B,0x04,0xC3,0x3F,0xCB,0xC0, // 'b'
	0x1E,0x07,0xF1,0x86,0x20,0x6C,0x01,0x80,0x30,0x02,0x06,0x61,0x87,0xF0,0x78,0x00, // 'c'
	0x01,0x80,0x60,0x18,0x06,0x1F,0x8F,0xE6,0x19,0x06,0xC1,0xB0,0x6C,0x19,0x06,0x61,0x8F,0xE1,0xE8, // 'd'
	0x1E,0x07,0xF1,0x86,0x20,0x4C,0x0D,0xFF,0xB0,0x02,0x00,0x60,0xC7,0xF0,0x7C,0x00, // 'e'
	0x01,0x01,0xF8,0x30,0x0C,0x01,0x81,0xFF,0x3E,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0, // 'f'
	0x1E,0x9F,0xE6,0x19,0x06,0xC1,0xB0,0x6C,0x19,0x06,0x61,0x8F,0xE1,0xF8,0x06,0x41,0x9F,0xC1,0xE0, // 'g'
	0xC0,0x60,0x30,0x18,0x0D,0xE7,0xFB,0x0D,0x82,0xC1,0x60,0xB0,0x58,0x2C,0x16,0x0B,0x04, // 'h'
	0x18,0x07,0x00,0x00,0x00,0xF8,0x3E,0x00,0x80,0x20,0x08,0x02,0x00,0x80,0x20,0x08,0x03,0xEF,0xF8, // 'i'
	0x0C,0x18,0x00,0x07,0xCF,0x83,0x06,0x0C,0x18,0x30,0x60,0xC1,0x83,0x06,0x0D,0x7B,0xC0, // 'j'
	0xC0,0x30,0x0C,0x03,0x00,0xC3,0x31,0x8C,0xC3,0x60,0xF0,0x3E,0x0D,0xC3,0x30,0xC6,0x30,0xCC,0x38, // 'k'
	0xF8,0x3E,0x00,0x80,0x20,0x08,0x02,0x00,0x80,0x20,0x08,0x02,0x00,0x80,0x20,0x08,0x03,0xEF,0xF8, // 'l'
	0xFB,0x9F,0xFB,0x33,0x66,0x6C,0xCD,0x99,0xB3,0x36,0x66,0xCC,0xD9,0x9B,0x33,0x00, // 'm'
	0x9E,0x5F,0xB0,0xD8,0x2C,0x16,0x0B,0x05,0x82,0xC1,0x60,0xB0,0x40, // 'n'
	0x1E,0x07,0xE1,0x86,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0x61,0x87,0xE0,0x78,0x00, // 'o'
	0xBC,0x3F,0xCC,0x33,0x04,0xC1,0xB0,0x6C,0x1B,0x04,0xC3,0x3F,0x8F,0xC3,0x00,0xC0,0x30,0x0C,0x00, // 'p'
	0x1E,0x9F,0xE6,0x19,0x06,0xC1,0xB0,0x6C,0x19,0x06,0x61,0x8F,0xE1,0xF8,0x06,0x01,0x80,0x60,0x18, // 'q'
	0xDE,0xFE,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0, // 'r'
	0x3E,0x1F,0xCC,0x33,0x00,0x60,0x0F,0x80,0x73,0x06,0xC1,0x3F,0xC3,0xE0, // 's'
	0x18,0x06,0x01,0x83,0xFE,0xF8,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x0F,0x81,0xE0, // 't'
	0xC3,0x61,0xB0,0xD8,0x6C,0x36,0x1B,0x0D,0x86,0xC3,0x7F,0x9F,0x40, // 'u'
	0xC0,0xC8,0x11,0x86,0x30,0xC2,0x10,0x66,0x04,0x80,0xF0,0x1E,0x01,0x80,0x30,0x00, // 'v'
	0xC6,0x32,0x31,0x19,0x88,0xCC,0xC6,0xF6,0x14,0xB0,0xA5,0x05,0x28,0x39,0xC1,0xC6,0x04,0x20, // 'w'
	0xE0,0xCC,0x30,0xCC,0x0F,0x01,0xE0,0x18,0x07,0x80,0xD8,0x33,0x0C,0x33,0x83,0x00, // 'x'
	0xC0,0xD8,0x19,0x86,0x30,0xC3,0x10,0x66,0x04,0x80,0xF0,0x1E,0x01,0x80,0x30,0x04,0x01,0x80,0xE0,0x38,0x00, // 'y'
	0xFF,0x3F,0xC0,0x60,0x38,0x0C,0x06,0x03,0x01,0x80,0xE0,0x3F,0xEF,0xF8, // 'z'
	0x02,0x0E,0x18,0x18,0x18,0x18,0x18,0x18,0x30,0xF0,0xE0,0x30,0x18,0x18,0x18,0x18,0x18,0x18,0x0E,0x06, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x00, // '|'
	0x80,0xE0,0x20,0x30,0x30,0x30,0x30,0x30,0x10,0x1E,0x0E,0x18,0x30,0x30,0x30,0x30,0x30,0x30,0xE0,0xC0 // '}'
};
const GFXglyph Roboto_Mono_20Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,  13,    0,    0 }, // ' '
	  {     1,   3,  15,  13,    5,  -15 }, // '!'
	  {     7,   6,   5,  13,    3,  -15 }, // '"'
	  {    11,  12,  15,  13,    1,  -15 }, // '#'
	  {    34,  10,  19,  13,    2,  -17 }, // '$'
	  {    58,  13,  15,  13,    0,  -15 }, // '%'
	  {    83,  12,  15,  13,    1,  -15 }, // '&'
	  {   106,   2,   5,  13,    5,  -15 }, // '''
	  {   108,   7,  21,  13,    3,  -16 }, // '('
	  {   127,   6,  21,  13,    3,  -16 }, // ')'
	  {   143,  10,  10,  13,    2,  -12 }, // '*'
	  {   156,  11,  11,  13,    1,  -12 }, // '+'
	  {   172,   4,   6,  13,    3,   -2 }, // ','
	  {   175,   9,   2,  13,    2,   -8 }, // '-'
	  {   178,   4,   3,  13,    5,   -3 }, // '.'
	  {   180,   9,  15,  13,    2,  -15 }, // '/'
	  {   197,  11,  15,  13,    1,  -15 }, // '0'
	  {   218,   7,  15,  13,    2,  -15 }, // '1'
	  {   232,  10,  15,  13,    1,  -15 }, // '2'
	  {   251,  10,  15,  13,    1,  -15 }, // '3'
	  {   270,  11,  15,  13,    1,  -15 }, // '4'
	  {   291,  10,  15,  13,    2,  -15 }, // '5'
	  {   310,  10,  15,  13,    1,  -15 }, // '6'
	  {   329,  11,  15,  13,    1,  -15 }, // '7'
	  {   350,  10,  15,  13,    2,  -15 }, // '8'
	  {   369,  10,  15,  13,    1,  -15 }, // '9'
	  {   388,   4,  12,  13,    5,  -12 }, // ':'
	  {   394,   5,  16,  13,    4,  -12 }, // ';'
	  {   404,   9,   9,  13,    2,  -11 }, // '<'
	  {   415,   9,   6,  13,    2,  -10 }, // '='
	  {   422,   9,   9,  13,    2,  -11 }, // '>'
	  {   433,   9,  15,  13,    2,  -15 }, // '?'
	  {   450,  11,  15,  13,    1,  -15 }, // '@'
	  {   471,  11,  15,  13,    1,  -15 }, // 'A'
	  {   492,  10,  15,  13,    2,  -15 }, // 'B'
	  {   511,  11,  15,  13,    1,  -15 }, // 'C'
	  {   532,  10,  15,  13,    2,  -15 }, // 'D'
	  {   551,  10,  15,  13,    2,  -15 }, // 'E'
	  {   570,  10,  15,  13,    2,  -15 }, // 'F'
	  {   589,  11,  15,  13,    1,  -15 }, // 'G'
	  {   610,  11,  15,  13,    1,  -15 }, // 'H'
	  {   631,   9,  15,  13,    2,  -15 }, // 'I'
	  {   648,  10,  15,  13,    1,  -15 }, // 'J'
	  {   667,  11,  15,  13,    2,  -15 }, // 'K'
	  {   688,  10,  15,  13,    2,  -15 }, // 'L'
	  {   707,  11,  15,  13,    1,  -15 }, // 'M'
	  {   728,  11,  15,  13,    1,  -15 }, // 'N'
	  {   749,  11,  15,  13,    1,  -15 }, // 'O'
	  {   770,  10,  15,  13,    2,  -15 }, // 'P'
	  {   789,  11,  17,  13,    1,  -15 }, // 'Q'
	  {   813,  10,  15,  13,    2,  -15 }, // 'R'
	  {   832,  11,  15,  13,    1,  -15 }, // 'S'
	  {   853,  11,  15,  13,    1,  -15 }, // 'T'
	  {   874,  11,  15,  13,    1,  -15 }, // 'U'
	  {   895,  11,  15,  13,    1,  -15 }, // 'V'
	  {   916,  12,  15,  13,    1,  -15 }, // 'W'
	  {   939,  11,  15,  13,    1,  -15 }, // 'X'
	  {   960,  11,  15,  13,    1,  -15 }, // 'Y'
	  {   981,  11,  15,  13,    1,  -15 }, // 'Z'
	  {  1002,   5,  20,  13,    4,  -17 }, // '['
	  {  1015,   9,  15,  13,    2,  -15 }, // '\'
	  {  1032,   5,  20,  13,    4,  -17 }, // ']'
	  {  1045,   9,   8,  13,    2,  -15 }, // '^'
	  {  1054,   9,   2,  13,    2,   -1 }, // '_'
	  {  1057,   5,   2,  13,    4,  -15 }, // '`'
	  {  1059,  10,  11,  13,    2,  -11 }, // 'a'
	  {  1073,  10,  15,  13,    2,  -15 }, // 'b'
	  {  1092,  11,  11,  13,    1,  -11 }, // 'c'
	  {  1108,  10,  15,  13,    1,  -15 }, // 'd'
	  {  1127,  11,  11,  13,    1,  -11 }, // 'e'
	  {  1143,  11,  16,  13,    1,  -16 }, // 'f'
	  {  1165,  10,  15,  13,    1,  -11 }, // 'g'
	  {  1184,   9,  15,  13,    2,  -15 }, // 'h'
	  {  1201,  10,  15,  13,    2,  -15 }, // 'i'
	  {  1220,   7,  19,  13,    2,  -15 }, // 'j'
	  {  1237,  10,  15,  13,    2,  -15 }, // 'k'
	  {  1256,  10,  15,  13,    2,  -15 }, // 'l'
	  {  1275,  11,  11,  13,    1,  -11 }, // 'm'
	  {  1291,   9,  11,  13,    2,  -11 }, // 'n'
	  {  1304,  11,  11,  13,    1,  -11 }, // 'o'
	  {  1320,  10,  15,  13,    2,  -11 }, // 'p'
	  {  1339,  10,  15,  13,    1,  -11 }, // 'q'
	  {  1358,   8,  11,  13,    3,  -11 }, // 'r'
	  {  1369,  10,  11,  13,    2,  -11 }, // 's'
	  {  1383,  10,  14,  13,    1,  -14 }, // 't'
	  {  1401,   9,  11,  13,    2,  -11 }, // 'u'
	  {  1414,  11,  11,  13,    1,  -11 }, // 'v'
	  {  1430,  13,  11,  13,    0,  -11 }, // 'w'
	  {  1448,  11,  11,  13,    1,  -11 }, // 'x'
	  {  1464,  11,  15,  13,    1,  -11 }, // 'y'
	  {  1485,  10,  11,  13,    2,  -11 }, // 'z'
	  {  1499,   8,  20,  13,    3,  -16 }, // '{'
	  {  1519,   3,  19,  13,    5,  -15 }, // '|'
	  {  1527,   8,  20,  13,    3,  -16 } // '}'
};
const GFXfont Roboto_Mono_20 PROGMEM = {
(uint8_t  *)Roboto_Mono_20Bitmaps,(GFXglyph *)Roboto_Mono_20Glyphs,0x20, 0x7E, 24};
