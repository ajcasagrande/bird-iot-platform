#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Mono_28Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xC0,0x00,0x0C,0xEC, // '!'
	0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6, // '"'
	0x03,0x18,0x03,0x18,0x06,0x18,0x06,0x18,0x06,0x18,0x06,0x30,0x7F,0xFE,0x7F,0xFE,0x0C,0x30,0x0C,0x30,0x0C,0x60,0x0C,0x60,0xFF,0xFC,0xFF,0xFC,0x18,0x60,0x18,0xC0,0x18,0xC0,0x30,0xC0,0x30,0xC0,0x30,0xC0, // '#'
	0x03,0x00,0x0C,0x00,0x30,0x03,0xF0,0x3F,0xE0,0xE1,0xC7,0x03,0x1C,0x0E,0x70,0x39,0xC0,0x07,0x80,0x0F,0x00,0x1F,0x80,0x1F,0x80,0x1F,0x00,0x1C,0x00,0x3B,0x80,0xEE,0x03,0x98,0x0E,0x70,0x70,0xFF,0xC1,0xFC,0x00,0xC0,0x03,0x00,0x0C,0x00, // '$'
	0x78,0x00,0xFC,0x00,0xCE,0x00,0xC6,0x30,0x86,0x30,0xC6,0x60,0xCE,0x60,0xFC,0xC0,0x79,0x80,0x01,0x80,0x03,0x00,0x03,0x38,0x06,0x7C,0x0C,0xC6,0x0C,0xC6,0x18,0xC6,0x08,0xC6,0x00,0xC6,0x00,0xFC,0x00,0x38, // '%'
	0x07,0x80,0x1F,0xC0,0x1C,0xE0,0x38,0x60,0x38,0x60,0x38,0x60,0x38,0xE0,0x1D,0xC0,0x0F,0x80,0x0E,0x00,0x1F,0x00,0x3B,0x8E,0x71,0xCE,0x61,0xCC,0xE0,0xEC,0x60,0x7C,0x60,0x38,0x70,0xFC,0x3F,0xFC,0x0F,0x8E, // '&'
	0xDB,0x6D,0xB0, // '''
	0x06,0x0E,0x1C,0x18,0x30,0x30,0x70,0x60,0x60,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0x60,0x60,0x70,0x30,0x30,0x18,0x1C,0x0E,0x06, // '('
	0xC0,0x30,0x0C,0x07,0x01,0x80,0xE0,0x30,0x1C,0x0E,0x03,0x01,0x80,0xC0,0x70,0x38,0x1C,0x0E,0x06,0x03,0x01,0x81,0xC0,0xE0,0x60,0x70,0x30,0x38,0x18,0x18,0x18,0x00, // ')'
	0x03,0x00,0x0C,0x00,0x30,0x00,0xC0,0x63,0x1B,0xEF,0xE3,0xFF,0x01,0xC0,0x0F,0x80,0x37,0x01,0x8C,0x0E,0x3C,0x10,0x60, // '*'
	0x07,0x00,0x1C,0x00,0x70,0x01,0xC0,0x07,0x00,0x1C,0x0F,0xFF,0xBF,0xFE,0x07,0x00,0x1C,0x00,0x70,0x01,0xC0,0x07,0x00,0x1C,0x00, // '+'
	0x73,0x9C,0xE6,0x73,0x08, // ','
	0xFF,0xDF,0xF8, // '-'
	0xE7,0xBD,0xC0, // '.'
	0x00,0x60,0x0C,0x00,0xC0,0x1C,0x01,0x80,0x18,0x03,0x80,0x30,0x07,0x00,0x60,0x06,0x00,0xE0,0x0C,0x00,0xC0,0x18,0x01,0x80,0x38,0x03,0x00,0x30,0x07,0x00,0xE0,0x00, // '/'
	0x0F,0x80,0xFF,0x87,0x8F,0x18,0x1C,0xE0,0x33,0x80,0xEE,0x03,0xB8,0x3E,0xE1,0xFB,0x8E,0xEE,0xF3,0xBF,0x0E,0xF8,0x3B,0x80,0xEE,0x03,0xB8,0x0C,0x60,0x71,0xC3,0xC3,0xFE,0x03,0xE0, // '0'
	0x01,0x07,0x9F,0xDF,0xEC,0x70,0x38,0x1C,0x0E,0x07,0x03,0x81,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x81,0xC0,0xE0, // '1'
	0x0F,0x80,0x7F,0xC1,0xE3,0xC3,0x01,0x8E,0x03,0x9C,0x07,0x00,0x0E,0x00,0x18,0x00,0x70,0x01,0xC0,0x03,0x00,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x01,0xFF,0xF3,0xFF,0xE0, // '2'
	0x0F,0x80,0xFF,0x87,0x87,0x1C,0x0C,0x60,0x3A,0x00,0xE0,0x03,0x80,0x1C,0x00,0xF0,0x3F,0x00,0xFE,0x00,0x1C,0x00,0x38,0x00,0xE0,0x03,0xB8,0x0E,0x60,0x39,0xE1,0xC3,0xFE,0x03,0xE0, // '3'
	0x00,0x70,0x01,0xE0,0x07,0xC0,0x0F,0x80,0x37,0x00,0xEE,0x01,0x9C,0x06,0x38,0x1C,0x70,0x30,0xE0,0xC1,0xC3,0x83,0x86,0x07,0x1F,0xFF,0xBF,0xFF,0x00,0x38,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x80, // '4'
	0x7F,0xF3,0xFF,0x98,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0F,0xF0,0xFF,0xC7,0x07,0x00,0x1C,0x00,0xE0,0x07,0x00,0x18,0x01,0xD8,0x0E,0xE0,0x73,0x87,0x1F,0xF0,0x3F,0x00, // '5'
	0x03,0xC0,0x3F,0x01,0xE0,0x0E,0x00,0x70,0x01,0x80,0x0E,0x00,0x3B,0xE0,0xFF,0xE3,0xE3,0x8E,0x07,0x38,0x0C,0xC0,0x33,0x80,0xEE,0x03,0x38,0x0C,0x70,0x71,0xE3,0x83,0xFE,0x03,0xE0, // '6'
	0xFF,0xFB,0xFF,0xE0,0x03,0x00,0x0C,0x00,0x70,0x01,0x80,0x0E,0x00,0x30,0x01,0xC0,0x06,0x00,0x38,0x00,0xE0,0x03,0x00,0x1C,0x00,0x60,0x03,0x80,0x0C,0x00,0x70,0x01,0x80,0x0E,0x00, // '7'
	0x0F,0x80,0xFF,0x83,0x8F,0x1C,0x1C,0x70,0x39,0x80,0xE7,0x03,0x9C,0x0C,0x38,0xF0,0x7F,0x81,0xFE,0x0E,0x1C,0x70,0x39,0x80,0xEE,0x01,0xB8,0x0E,0x70,0x39,0xE1,0xC3,0xFE,0x03,0xF0, // '8'
	0x0F,0x80,0xFF,0x07,0x8E,0x18,0x1C,0xE0,0x73,0x80,0xCE,0x03,0x38,0x0E,0xE0,0x39,0x81,0xE7,0x0F,0x8F,0xFC,0x1F,0x30,0x00,0xC0,0x07,0x00,0x18,0x00,0xE0,0x0F,0x01,0xF8,0x07,0x80, // '9'
	0xE7,0xBD,0xC0,0x00,0x00,0x00,0x00,0x0E,0x7B,0xDC, // ':'
	0x71,0xE7,0x9C,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xC7,0x1C,0x71,0x8E,0x30,0x40, // ';'
	0x00,0x10,0x07,0x80,0xFC,0x1F,0x83,0xE0,0x7C,0x03,0xC0,0x0F,0x80,0x1F,0x80,0x1F,0x80,0x3C,0x00,0x60, // '<'
	0xFF,0xFB,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xBF,0xFE, // '='
	0xC0,0x03,0xC0,0x0F,0xC0,0x07,0xE0,0x03,0xE0,0x03,0xE0,0x07,0x80,0xFC,0x0F,0x81,0xF8,0x0F,0x80,0x30,0x00, // '>'
	0x1F,0x07,0xFC,0xF1,0xEC,0x0E,0xC0,0x60,0x06,0x00,0x60,0x0E,0x01,0xC0,0x38,0x07,0x00,0xE0,0x0E,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xC0,0x0E,0x00,0xE0, // '?'
	0x03,0xE0,0x0F,0xF0,0x1C,0x38,0x30,0x0C,0x61,0xCC,0x67,0xE4,0x46,0x66,0xCC,0x66,0xCC,0x66,0xCC,0x66,0xC8,0x46,0xC8,0x46,0xC8,0x44,0xCC,0xCC,0xCF,0xFC,0x67,0x38,0x60,0x00,0x38,0x20,0x1F,0xE0,0x0F,0xC0, // '@'
	0x03,0x80,0x03,0x80,0x03,0x80,0x07,0xC0,0x06,0xC0,0x06,0xC0,0x0E,0xE0,0x0E,0x60,0x0C,0x60,0x1C,0x70,0x1C,0x30,0x18,0x30,0x38,0x38,0x3F,0xF8,0x3F,0xF8,0x30,0x1C,0x70,0x1C,0x60,0x0C,0x60,0x0C,0xE0,0x0E, // 'A'
	0xFF,0x83,0xFF,0x8E,0x0F,0x38,0x0C,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0C,0xE0,0xF3,0xFF,0x0F,0xFE,0x38,0x1C,0xE0,0x3B,0x80,0x6E,0x01,0xB8,0x06,0xE0,0x3B,0x81,0xCF,0xFE,0x3F,0xF0, // 'B'
	0x07,0xC0,0x3F,0xE0,0xF1,0xE1,0x80,0xC7,0x01,0xCC,0x01,0x98,0x00,0x30,0x00,0xE0,0x01,0xC0,0x03,0x80,0x07,0x00,0x06,0x00,0x0C,0x00,0x18,0x03,0x38,0x0E,0x30,0x18,0x78,0x70,0x7F,0xC0,0x3E,0x00, // 'C'
	0xFF,0x01,0xFF,0x83,0x87,0x87,0x03,0x8E,0x03,0x1C,0x07,0x38,0x06,0x70,0x0C,0xE0,0x19,0xC0,0x3B,0x80,0x77,0x00,0xCE,0x01,0x9C,0x03,0x38,0x0E,0x70,0x1C,0xE0,0x71,0xC3,0xC3,0xFF,0x07,0xF8,0x00, // 'D'
	0xFF,0xFB,0xFF,0xEE,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0xFF,0x8F,0xFE,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0F,0xFF,0xBF,0xFE, // 'E'
	0xFF,0xF7,0xFF,0xB0,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x07,0xFE,0x3F,0xF1,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x00, // 'F'
	0x07,0xC0,0x3F,0xE0,0xF0,0xE1,0x80,0xE7,0x01,0xCC,0x01,0x98,0x00,0x70,0x00,0xE0,0x01,0xC0,0x03,0x83,0xF7,0x07,0xEE,0x00,0xCC,0x01,0x9C,0x03,0x38,0x06,0x38,0x0C,0x78,0x78,0x7F,0xE0,0x3F,0x00, // 'G'
	0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x3B,0xFF,0xEF,0xFF,0xB0,0x0E,0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E, // 'H'
	0xFF,0xF7,0xFF,0x81,0xC0,0x0E,0x00,0x70,0x03,0x80,0x1C,0x00,0xE0,0x07,0x00,0x38,0x01,0xC0,0x0E,0x00,0x70,0x03,0x80,0x1C,0x00,0xE0,0x07,0x00,0x38,0x3F,0xFD,0xFF,0xE0, // 'I'
	0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x6E,0x01,0x98,0x0E,0x70,0x38,0xE1,0xC3,0xFE,0x03,0xE0, // 'J'
	0xE0,0x3D,0xC0,0x73,0x81,0xC7,0x07,0x0E,0x1C,0x1C,0x70,0x38,0xE0,0x73,0x80,0xEE,0x01,0xFC,0x03,0xFC,0x07,0xDC,0x0F,0x38,0x1C,0x38,0x38,0x38,0x70,0x70,0xE0,0x71,0xC0,0x73,0x80,0xE7,0x00,0xE0, // 'K'
	0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x3F,0xFD,0xFF,0xE0, // 'L'
	0xE0,0x3B,0xC1,0xEF,0x07,0xBC,0x1E,0xF8,0xFB,0x63,0x6D,0x8D,0xB7,0x76,0xCD,0x9B,0x36,0x6C,0xF1,0xB1,0xC6,0xC7,0x1B,0x18,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06, // 'M'
	0xE0,0x3B,0x80,0xEF,0x03,0xBC,0x0E,0xF8,0x3B,0xE0,0xEF,0xC3,0xBB,0x0E,0xEE,0x3B,0x98,0xEE,0x73,0xB8,0xCE,0xE3,0xBB,0x87,0xEE,0x1F,0xB8,0x3E,0xE0,0xFB,0x81,0xEE,0x07,0xB8,0x0E, // 'N'
	0x07,0xC0,0x3F,0xE0,0xF1,0xC1,0x81,0xC7,0x01,0xCC,0x03,0x98,0x03,0x30,0x06,0xE0,0x0D,0xC0,0x1B,0x80,0x37,0x00,0x66,0x00,0xCC,0x01,0x98,0x07,0x38,0x0E,0x30,0x38,0x78,0xE0,0x7F,0xC0,0x3E,0x00, // 'O'
	0xFF,0x83,0xFF,0x8C,0x0F,0x30,0x1C,0xC0,0x33,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x73,0x03,0xCF,0xFE,0x3F,0xE0,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00, // 'P'
	0x07,0xC0,0x1F,0xF0,0x3C,0x78,0x30,0x38,0x70,0x1C,0x60,0x1C,0x60,0x0C,0xE0,0x0C,0xE0,0x0C,0xE0,0x0E,0xE0,0x0E,0xE0,0x0C,0xE0,0x0C,0x60,0x0C,0x60,0x1C,0x70,0x1C,0x30,0x38,0x3C,0x78,0x1F,0xF0,0x07,0xF8,0x00,0x3C,0x00,0x1E,0x00,0x0C, // 'Q'
	0xFF,0x81,0xFF,0xC3,0x83,0xC7,0x01,0xCE,0x03,0x9C,0x07,0x38,0x0E,0x70,0x1C,0xE0,0x39,0xC1,0xE3,0xFF,0x87,0xFC,0x0E,0x1C,0x1C,0x18,0x38,0x38,0x70,0x30,0xE0,0x71,0xC0,0x63,0x80,0xE7,0x00,0xE0, // 'R'
	0x0F,0x80,0xFF,0x87,0x87,0x18,0x0E,0xE0,0x3B,0x80,0x6E,0x00,0x1C,0x00,0x3C,0x00,0x7E,0x00,0x7E,0x00,0x3C,0x00,0x38,0x00,0xEC,0x01,0xB8,0x06,0xE0,0x39,0xE1,0xE3,0xFF,0x03,0xF0, // 'S'
	0xFF,0xFE,0xFF,0xFE,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80, // 'T'
	0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0E,0xC0,0x3B,0x00,0xEC,0x03,0xB8,0x0E,0x60,0x71,0xE3,0xC3,0xFE,0x03,0xE0, // 'U'
	0xE0,0x0E,0xE0,0x0C,0x60,0x1C,0x70,0x1C,0x70,0x18,0x30,0x38,0x38,0x38,0x38,0x30,0x18,0x30,0x18,0x70,0x1C,0x60,0x0C,0x60,0x0C,0xE0,0x0E,0xE0,0x06,0xC0,0x07,0xC0,0x07,0xC0,0x07,0x80,0x03,0x80,0x03,0x80, // 'V'
	0xC3,0x86,0xE3,0x86,0xE3,0x8E,0xE3,0x8E,0x63,0x8E,0x67,0xCE,0x66,0xCC,0x66,0xCC,0x66,0xCC,0x66,0xCC,0x66,0x6C,0x7C,0x6C,0x3C,0x7C,0x3C,0x7C,0x3C,0x78,0x3C,0x78,0x3C,0x38,0x38,0x38,0x38,0x38,0x38,0x38, // 'W'
	0xF0,0x0E,0x70,0x1C,0x38,0x38,0x38,0x38,0x1C,0x70,0x0C,0x70,0x0E,0xE0,0x06,0xC0,0x07,0xC0,0x03,0x80,0x03,0x80,0x07,0xC0,0x06,0xE0,0x0E,0xE0,0x1C,0x70,0x1C,0x70,0x38,0x38,0x38,0x18,0x70,0x1C,0xE0,0x0E, // 'X'
	0xE0,0x0E,0x60,0x1C,0x70,0x18,0x30,0x38,0x38,0x30,0x18,0x70,0x1C,0x60,0x0C,0xE0,0x0E,0xC0,0x07,0xC0,0x07,0xC0,0x07,0x80,0x03,0x80,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00, // 'Y'
	0xFF,0xF3,0xFF,0xC0,0x07,0x00,0x18,0x00,0xE0,0x07,0x00,0x1C,0x00,0xE0,0x07,0x00,0x1C,0x00,0xE0,0x03,0x00,0x1C,0x00,0xE0,0x03,0x80,0x1C,0x00,0x60,0x03,0x80,0x0F,0xFF,0xBF,0xFE, // 'Z'
	0xFB,0xEC,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0xEF,0x80, // '['
	0xE0,0x06,0x00,0x60,0x03,0x00,0x30,0x03,0x80,0x18,0x01,0x80,0x1C,0x00,0xC0,0x0C,0x00,0x60,0x06,0x00,0x70,0x03,0x00,0x30,0x01,0x80,0x18,0x01,0xC0,0x0C,0x00,0xE0, // '\'
	0xFB,0xE1,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x1B,0xEF,0x80, // ']'
	0x0C,0x00,0xE0,0x1E,0x01,0xF0,0x1B,0x03,0xB8,0x31,0x87,0x18,0x61,0xCE,0x0E, // '^'
	0xFF,0xFB,0xFF,0xE0, // '_'
	0xE1,0xC3,0x80, // '`'
	0x0F,0x80,0xFF,0x87,0x0F,0x18,0x1C,0x80,0x30,0x00,0xC1,0xFF,0x1F,0xFC,0x70,0x33,0x80,0xCE,0x03,0x38,0x1C,0x70,0xF1,0xFE,0xC1,0xF3,0x80, // 'a'
	0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x78,0x3F,0xF8,0xF8,0xF3,0x81,0xCE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x81,0xCF,0x8F,0x3F,0xF8,0xE7,0x80, // 'b'
	0x0F,0x80,0xFF,0x87,0x8F,0x1C,0x0C,0xE0,0x3B,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x03,0x9C,0x0C,0x78,0x70,0xFF,0x80,0xF8,0x00, // 'c'
	0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x7C,0xC7,0xFE,0x78,0xF3,0x83,0xB8,0x0D,0xC0,0x6C,0x03,0x60,0x1B,0x00,0xDC,0x06,0xE0,0x33,0x03,0x9E,0x3C,0x7F,0xE0,0xF3,0x00, // 'd'
	0x0F,0x80,0xFF,0x87,0x8F,0x1C,0x0C,0xE0,0x3B,0x80,0xEF,0xFF,0xBF,0xFE,0xC0,0x03,0x80,0x0E,0x00,0x1C,0x04,0x78,0x78,0xFF,0xC0,0xFC,0x00, // 'e'
	0x01,0xF8,0x1F,0xE0,0x70,0x03,0x80,0x0E,0x00,0x38,0x0F,0xFF,0x3F,0xFC,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00, // 'f'
	0x1F,0x31,0xFF,0x9E,0x3C,0xE0,0xEE,0x03,0x70,0x1B,0x00,0xD8,0x06,0xC0,0x37,0x01,0xB8,0x0C,0xC0,0xE7,0x8F,0x1F,0xF8,0x3C,0xC0,0x06,0x00,0x33,0x03,0x9C,0x38,0x7F,0xC0,0xF8,0x00, // 'g'
	0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x7C,0x3B,0xF8,0xF8,0x73,0xC0,0xCE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x38, // 'h'
	0x06,0x00,0x78,0x01,0x80,0x00,0x00,0x00,0x7F,0x03,0xF8,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x3F,0xFD,0xFF,0xE0, // 'i'
	0x03,0x00,0xE0,0x30,0x00,0x00,0x1F,0xE7,0xF8,0x0E,0x03,0x80,0xE0,0x38,0x0E,0x03,0x80,0xE0,0x38,0x0E,0x03,0x80,0xE0,0x38,0x0E,0x03,0x80,0xC0,0x70,0x3C,0xFE,0x3E,0x00, // 'j'
	0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x07,0xB8,0x38,0xE1,0xC3,0x8E,0x0E,0x70,0x3B,0x80,0xFE,0x03,0xFC,0x0F,0x70,0x38,0xE0,0xE1,0xC3,0x83,0x8E,0x0E,0x38,0x1C,0xE0,0x38, // 'k'
	0xFE,0x07,0xF0,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x81,0xFF,0xEF,0xFF,0x00, // 'l'
	0xEE,0x78,0xFF,0xFC,0xE3,0x8C,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E,0xE3,0x8E, // 'm'
	0xE7,0xC3,0xBF,0x8F,0x87,0x3C,0x0C,0xE0,0x33,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0x80, // 'n'
	0x0F,0x80,0xFF,0x87,0x8F,0x18,0x1C,0xE0,0x3B,0x00,0xEC,0x01,0xB0,0x06,0xC0,0x1B,0x00,0xEE,0x03,0x98,0x1C,0x78,0xF0,0xFF,0x80,0xF8,0x00, // 'o'
	0xEF,0x83,0xFF,0x8F,0x8F,0x38,0x1C,0xE0,0x33,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0x38,0x1C,0xF0,0xF3,0xFF,0x8E,0x78,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x00, // 'p'
	0x1F,0x31,0xFF,0x9E,0x3C,0xE0,0xEE,0x03,0x70,0x1B,0x00,0xD8,0x06,0xC0,0x37,0x01,0xB8,0x0C,0xE0,0xE7,0x8F,0x1F,0xF8,0x3C,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00, // 'q'
	0xCF,0xDB,0xF3,0xC0,0x70,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x00, // 'r'
	0x0F,0x80,0xFF,0x87,0x87,0x1C,0x0C,0x60,0x39,0xC0,0x03,0xE0,0x07,0xF0,0x01,0xF0,0x00,0xCE,0x03,0x98,0x0E,0x78,0x70,0xFF,0x80,0xFC,0x00, // 's'
	0x0C,0x00,0x30,0x00,0xC0,0x03,0x00,0xFF,0xF3,0xFF,0xC0,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00,0xC0,0x03,0x80,0x0E,0x08,0x1F,0xC0,0x3F,0x80, // 't'
	0xE0,0x37,0x01,0xB8,0x0D,0xC0,0x6E,0x03,0x70,0x1B,0x80,0xDC,0x06,0xE0,0x37,0x01,0x98,0x0C,0xC0,0xE7,0x0F,0x1F,0xF8,0x7C,0xC0, // 'u'
	0xE0,0x0C,0xC0,0x39,0xC0,0x61,0x81,0xC3,0x83,0x83,0x06,0x06,0x1C,0x0E,0x30,0x0C,0x60,0x19,0xC0,0x1B,0x00,0x36,0x00,0x78,0x00,0x70,0x00,0xE0,0x00, // 'v'
	0xC1,0x06,0xC3,0x86,0xC3,0x86,0xE3,0x8E,0x62,0x8C,0x66,0xCC,0x66,0xCC,0x66,0xCC,0x64,0x4C,0x3C,0x78,0x3C,0x78,0x3C,0x78,0x38,0x38,0x38,0x30,0x18,0x30, // 'w'
	0xE0,0x38,0xE0,0xE0,0xC1,0xC1,0xC7,0x01,0xDC,0x01,0xF0,0x03,0xE0,0x03,0x80,0x0F,0x80,0x1B,0x00,0x77,0x01,0xC7,0x07,0x07,0x0E,0x06,0x38,0x0F,0x00, // 'x'
	0xE0,0x0E,0x60,0x1C,0x70,0x1C,0x70,0x18,0x38,0x38,0x38,0x30,0x18,0x70,0x1C,0x70,0x0C,0x60,0x0E,0xE0,0x06,0xC0,0x07,0xC0,0x07,0x80,0x03,0x80,0x03,0x80,0x03,0x00,0x07,0x00,0x06,0x00,0x1E,0x00,0x7C,0x00,0x78,0x00, // 'y'
	0xFF,0xF3,0xFF,0xC0,0x07,0x00,0x38,0x01,0xC0,0x0E,0x00,0x78,0x01,0xC0,0x0E,0x00,0x70,0x03,0x80,0x1E,0x00,0x70,0x03,0xFF,0xEF,0xFF,0x80, // 'z'
	0x01,0x80,0x78,0x1C,0x03,0x00,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x06,0x01,0xC1,0xF0,0x3E,0x00,0xE0,0x0C,0x01,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80,0x30,0x07,0x00,0x78,0x06,0x00, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xD8, // '|'
	0x60,0x1E,0x00,0xE0,0x0C,0x01,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80,0x70,0x06,0x00,0xE0,0x0F,0x81,0xF0,0x70,0x0C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0xC0,0x38,0x1E,0x01,0x80,0x00 // '}'
};
const GFXglyph Roboto_Mono_28Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,  18,    0,    0 }, // ' '
	  {     1,   4,  20,  18,    7,  -20 }, // '!'
	  {    11,   8,   7,  18,    5,  -21 }, // '"'
	  {    18,  16,  20,  18,    1,  -20 }, // '#'
	  {    58,  14,  26,  18,    2,  -23 }, // '$'
	  {   104,  16,  20,  18,    1,  -20 }, // '%'
	  {   144,  16,  20,  18,    1,  -20 }, // '&'
	  {   184,   3,   7,  18,    7,  -21 }, // '''
	  {   187,   8,  28,  18,    5,  -22 }, // '('
	  {   215,   9,  28,  18,    4,  -22 }, // ')'
	  {   247,  14,  13,  18,    2,  -17 }, // '*'
	  {   270,  14,  14,  18,    2,  -16 }, // '+'
	  {   295,   5,   8,  18,    5,   -3 }, // ','
	  {   300,  11,   2,  18,    3,  -10 }, // '-'
	  {   303,   5,   4,  18,    7,   -4 }, // '.'
	  {   306,  12,  21,  18,    3,  -20 }, // '/'
	  {   338,  14,  20,  18,    2,  -20 }, // '0'
	  {   373,   9,  20,  18,    3,  -20 }, // '1'
	  {   396,  15,  20,  18,    1,  -20 }, // '2'
	  {   434,  14,  20,  18,    1,  -20 }, // '3'
	  {   469,  15,  20,  18,    1,  -20 }, // '4'
	  {   507,  13,  20,  18,    3,  -20 }, // '5'
	  {   540,  14,  20,  18,    2,  -20 }, // '6'
	  {   575,  14,  20,  18,    2,  -20 }, // '7'
	  {   610,  14,  20,  18,    2,  -20 }, // '8'
	  {   645,  14,  20,  18,    2,  -20 }, // '9'
	  {   680,   5,  16,  18,    8,  -16 }, // ':'
	  {   690,   6,  21,  18,    7,  -16 }, // ';'
	  {   706,  13,  12,  18,    2,  -15 }, // '<'
	  {   726,  14,   8,  18,    2,  -13 }, // '='
	  {   740,  14,  12,  18,    2,  -15 }, // '>'
	  {   761,  12,  20,  18,    3,  -20 }, // '?'
	  {   791,  16,  20,  18,    1,  -20 }, // '@'
	  {   831,  16,  20,  18,    1,  -20 }, // 'A'
	  {   871,  14,  20,  18,    2,  -20 }, // 'B'
	  {   906,  15,  20,  18,    1,  -20 }, // 'C'
	  {   944,  15,  20,  18,    2,  -20 }, // 'D'
	  {   982,  14,  20,  18,    2,  -20 }, // 'E'
	  {  1017,  13,  20,  18,    3,  -20 }, // 'F'
	  {  1050,  15,  20,  18,    1,  -20 }, // 'G'
	  {  1088,  14,  20,  18,    2,  -20 }, // 'H'
	  {  1123,  13,  20,  18,    2,  -20 }, // 'I'
	  {  1156,  14,  20,  18,    1,  -20 }, // 'J'
	  {  1191,  15,  20,  18,    2,  -20 }, // 'K'
	  {  1229,  13,  20,  18,    3,  -20 }, // 'L'
	  {  1262,  14,  20,  18,    2,  -20 }, // 'M'
	  {  1297,  14,  20,  18,    2,  -20 }, // 'N'
	  {  1332,  15,  20,  18,    1,  -20 }, // 'O'
	  {  1370,  14,  20,  18,    3,  -20 }, // 'P'
	  {  1405,  16,  23,  18,    1,  -20 }, // 'Q'
	  {  1451,  15,  20,  18,    2,  -20 }, // 'R'
	  {  1489,  14,  20,  18,    2,  -20 }, // 'S'
	  {  1524,  16,  20,  18,    1,  -20 }, // 'T'
	  {  1564,  14,  20,  18,    2,  -20 }, // 'U'
	  {  1599,  16,  20,  18,    1,  -20 }, // 'V'
	  {  1639,  16,  20,  18,    1,  -20 }, // 'W'
	  {  1679,  16,  20,  18,    1,  -20 }, // 'X'
	  {  1719,  16,  20,  18,    1,  -20 }, // 'Y'
	  {  1759,  14,  20,  18,    2,  -20 }, // 'Z'
	  {  1794,   6,  27,  18,    6,  -23 }, // '['
	  {  1815,  12,  21,  18,    3,  -20 }, // '\'
	  {  1847,   6,  27,  18,    6,  -23 }, // ']'
	  {  1868,  12,  10,  18,    3,  -20 }, // '^'
	  {  1883,  14,   2,  18,    2,    0 }, // '_'
	  {  1887,   6,   3,  18,    6,  -21 }, // '`'
	  {  1890,  14,  15,  18,    2,  -15 }, // 'a'
	  {  1917,  14,  21,  18,    2,  -21 }, // 'b'
	  {  1954,  14,  15,  18,    2,  -15 }, // 'c'
	  {  1981,  13,  21,  18,    2,  -21 }, // 'd'
	  {  2016,  14,  15,  18,    2,  -15 }, // 'e'
	  {  2043,  14,  21,  18,    2,  -21 }, // 'f'
	  {  2080,  13,  21,  18,    2,  -15 }, // 'g'
	  {  2115,  14,  21,  18,    2,  -21 }, // 'h'
	  {  2152,  13,  20,  18,    3,  -20 }, // 'i'
	  {  2185,  10,  26,  18,    3,  -20 }, // 'j'
	  {  2218,  14,  21,  18,    2,  -21 }, // 'k'
	  {  2255,  13,  21,  18,    3,  -21 }, // 'l'
	  {  2290,  16,  15,  18,    1,  -15 }, // 'm'
	  {  2320,  14,  15,  18,    2,  -15 }, // 'n'
	  {  2347,  14,  15,  18,    2,  -15 }, // 'o'
	  {  2374,  14,  21,  18,    2,  -15 }, // 'p'
	  {  2411,  13,  21,  18,    2,  -15 }, // 'q'
	  {  2446,  11,  15,  18,    5,  -15 }, // 'r'
	  {  2467,  14,  15,  18,    2,  -15 }, // 's'
	  {  2494,  14,  19,  18,    2,  -19 }, // 't'
	  {  2528,  13,  15,  18,    2,  -15 }, // 'u'
	  {  2553,  15,  15,  18,    1,  -15 }, // 'v'
	  {  2582,  16,  15,  18,    1,  -15 }, // 'w'
	  {  2612,  15,  15,  18,    2,  -15 }, // 'x'
	  {  2641,  16,  21,  18,    1,  -15 }, // 'y'
	  {  2683,  14,  15,  18,    2,  -15 }, // 'z'
	  {  2710,  11,  27,  18,    4,  -22 }, // '{'
	  {  2748,   3,  26,  18,    7,  -20 }, // '|'
	  {  2758,  11,  27,  18,    4,  -22 } // '}'
};
const GFXfont Roboto_Mono_28 PROGMEM = {
(uint8_t  *)Roboto_Mono_28Bitmaps,(GFXglyph *)Roboto_Mono_28Glyphs,0x20, 0x7E, 33};
