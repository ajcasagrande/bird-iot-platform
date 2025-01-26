#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t DialogInput_bold_24Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xE0,0x0E,0xEE, // '!'
	0xE3,0xB8,0xEE,0x3B,0x8E,0xE3,0xB8,0xEE,0x38, // '"'
	0x07,0x38,0x0E,0x70,0x18,0xC0,0x33,0x87,0xFF,0xCF,0xFF,0x9F,0xFF,0x06,0x30,0x1C,0xE0,0x39,0x83,0xFF,0xE7,0xFF,0xCF,0xFF,0x87,0x38,0x0C,0x60,0x18,0xC0,0x73,0x80, // '#'
	0x06,0x00,0x30,0x01,0x80,0x3F,0x87,0xFE,0x7F,0xF3,0x98,0x9C,0xC0,0xF6,0x03,0xF8,0x1F,0xF0,0x1F,0xC0,0x6F,0x03,0x3B,0x1B,0xDF,0xFE,0xFF,0xE1,0xFC,0x01,0x80,0x0C,0x00,0x60,0x03,0x00, // '$'
	0x38,0x00,0xF8,0x03,0x18,0x06,0x30,0x0C,0x60,0x0F,0x81,0x0E,0x0E,0x00,0x70,0x01,0x80,0x0C,0x00,0x60,0x03,0x83,0x84,0x0F,0x80,0x31,0x80,0x63,0x00,0xC6,0x00,0xF8,0x00,0xE0, // '%'
	0x0F,0xC0,0x3F,0xC0,0xFF,0x81,0xC1,0x03,0x80,0x07,0x80,0x07,0x00,0x0F,0x00,0x3F,0x00,0xEF,0x3B,0x9E,0x77,0x1E,0xEE,0x1F,0xDC,0x1F,0x3C,0x3C,0x3F,0xFC,0x3F,0xF8,0x3F,0x78, // '&'
	0xEE,0xEE,0xEE,0xE0, // '''
	0x1C,0x70,0xE3,0x87,0x0E,0x38,0x70,0xE1,0xC3,0x87,0x0E,0x1C,0x38,0x38,0x70,0xE0,0xE1,0xC1,0xC0, // '('
	0xE0,0xE1,0xC1,0x83,0x87,0x07,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0x87,0x1C,0x38,0x71,0xC3,0x8E,0x00, // ')'
	0x06,0x00,0x30,0x11,0x89,0xED,0xE7,0xFE,0x0F,0xC0,0x7E,0x0F,0xFC,0xF6,0xF2,0x31,0x01,0x80,0x0C,0x00, // '*'
	0x07,0x00,0x1C,0x00,0x70,0x01,0xC0,0x07,0x03,0xFF,0xEF,0xFF,0xBF,0xFE,0x07,0x00,0x1C,0x00,0x70,0x01,0xC0,0x07,0x00, // '+'
	0x79,0xE7,0x9E,0x79,0xCF,0x38, // ','
	0xFE,0xFE,0xFE, // '-'
	0xF7,0xBD,0xE0, // '.'
	0x00,0x70,0x07,0x00,0x38,0x03,0x80,0x1C,0x00,0xE0,0x0E,0x00,0x70,0x07,0x00,0x38,0x03,0x80,0x1C,0x01,0xC0,0x0E,0x00,0xE0,0x07,0x00,0x38,0x03,0x80,0x1C,0x01,0xC0,0x00, // '/'
	0x0F,0x01,0xFE,0x1F,0xF8,0xE1,0xCF,0x0E,0x70,0x3B,0x81,0xDC,0xEE,0xE7,0x77,0x3B,0xB8,0x1D,0xC0,0xEE,0x07,0x38,0x71,0xC3,0x8F,0xFC,0x3F,0xC0,0x78,0x00, // '0'
	0x3E,0x0F,0xE0,0xFE,0x0C,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x0F,0xFE,0xFF,0xEF,0xFE, // '1'
	0x3F,0x87,0xFE,0x3F,0xF9,0x81,0xE0,0x07,0x00,0x38,0x01,0xC0,0x1C,0x01,0xC0,0x1E,0x01,0xE0,0x1E,0x01,0xE0,0x1E,0x01,0xE0,0x1F,0xFE,0xFF,0xF7,0xFF,0x80, // '2'
	0x1F,0x83,0xFF,0x1F,0xF8,0x81,0xE0,0x07,0x00,0x38,0x03,0xC3,0xFC,0x1F,0x80,0xFF,0x00,0x3C,0x00,0xE0,0x07,0x00,0x3B,0x03,0xDF,0xFC,0xFF,0xE1,0xFC,0x00, // '3'
	0x03,0xC0,0x1E,0x01,0xF0,0x1F,0x80,0xDC,0x0E,0xE0,0xE7,0x07,0x38,0x71,0xC3,0x0E,0x38,0x71,0xFF,0xEF,0xFF,0x7F,0xF8,0x07,0x00,0x38,0x01,0xC0,0x0E,0x00, // '4'
	0x7F,0xE3,0xFF,0x1F,0xF8,0xE0,0x07,0x00,0x38,0x01,0xFE,0x0F,0xF8,0x7F,0xE2,0x0F,0x80,0x1C,0x00,0xE0,0x07,0x00,0x3A,0x07,0xDF,0xFC,0xFF,0xC1,0xF8,0x00, // '5'
	0x0F,0xC0,0xFF,0x0F,0xF8,0xF0,0x47,0x00,0x70,0x03,0xBE,0x1F,0xFC,0xFF,0xE7,0x87,0xB8,0x1D,0xC0,0xEE,0x07,0x70,0x39,0xC3,0xCF,0xFC,0x3F,0xC0,0x7C,0x00, // '6'
	0xFF,0xF7,0xFF,0xBF,0xFC,0x01,0xE0,0x0E,0x00,0xF0,0x07,0x00,0x38,0x03,0x80,0x1C,0x01,0xE0,0x0E,0x00,0xF0,0x07,0x00,0x38,0x03,0x80,0x1C,0x01,0xC0,0x00, // '7'
	0x1F,0x83,0xFF,0x1F,0xF9,0xE1,0xEE,0x07,0x70,0x3B,0xC3,0xCF,0xFC,0x1F,0x83,0xFF,0x3C,0x39,0xC0,0xEE,0x07,0x70,0x3B,0xC3,0xCF,0xFC,0x7F,0xE0,0xFC,0x00, // '8'
	0x1F,0x01,0xFE,0x1F,0xF9,0xE1,0xCE,0x07,0x70,0x3B,0x81,0xDC,0x0E,0xF0,0xF3,0xFF,0x9F,0xFC,0x3E,0xE0,0x07,0x00,0x71,0x07,0x8F,0xF8,0x7F,0x81,0xF8,0x00, // '9'
	0xF7,0xBD,0xE0,0x00,0x00,0xF7,0xBD,0xE0, // ':'
	0x79,0xE7,0x9E,0x00,0x00,0x00,0x79,0xE7,0x9E,0x79,0xCF,0x38, // ';'
	0x00,0x10,0x07,0x80,0xFC,0x1F,0xC7,0xF0,0x7E,0x03,0x80,0x1F,0x80,0x7F,0x00,0x7F,0x00,0xFC,0x01,0xE0,0x01,0x00, // '<'
	0xFF,0xF7,0xFF,0xBF,0xFC,0x00,0x00,0x00,0x00,0x03,0xFF,0xDF,0xFE,0xFF,0xF0, // '='
	0x80,0x07,0x80,0x3F,0x00,0xFE,0x00,0xFE,0x01,0xF8,0x01,0xC0,0x7E,0x0F,0xE3,0xF8,0x3F,0x01,0xE0,0x08,0x00,0x00, // '>'
	0x7F,0x1F,0xF3,0xFF,0x40,0xE0,0x1C,0x03,0x80,0xE0,0x38,0x0F,0x03,0x80,0xE0,0x1C,0x03,0x80,0x70,0x00,0x01,0xC0,0x38,0x07,0x00, // '?'
	0x07,0xE0,0x1F,0xE0,0xF0,0xE1,0x80,0xE7,0x00,0xCC,0x3D,0xB9,0xFF,0x63,0x0E,0xCC,0x0D,0x98,0x1B,0x30,0x36,0x60,0x6C,0x61,0xDC,0xFF,0x98,0x7B,0x38,0x00,0x38,0x00,0x38,0x10,0x3F,0xF0,0x1F,0xC0, // '@'
	0x07,0x80,0x1F,0x80,0x3F,0x00,0x7E,0x00,0xFC,0x03,0x9C,0x07,0x38,0x0E,0x70,0x1C,0xE0,0x79,0xE0,0xE1,0xC1,0xFF,0x87,0xFF,0x8F,0xFF,0x1C,0x0E,0x38,0x1C,0xF0,0x3D,0xE0,0x78, // 'A'
	0xFF,0x07,0xFE,0x3F,0xF9,0xC3,0xCE,0x0E,0x70,0x73,0x87,0x9F,0xF8,0xFF,0x07,0xFF,0x38,0x39,0xC0,0xEE,0x07,0x70,0x3B,0x83,0xDF,0xFE,0xFF,0xE7,0xFC,0x00, // 'B'
	0x0F,0xC1,0xFE,0x3F,0xE7,0x86,0x70,0x2F,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xF0,0x07,0x02,0x78,0x63,0xFE,0x1F,0xE0,0xFC, // 'C'
	0xFE,0x07,0xFC,0x3F,0xF1,0xC3,0xCE,0x0E,0x70,0x7B,0x81,0xDC,0x0E,0xE0,0x77,0x03,0xB8,0x1D,0xC0,0xEE,0x0F,0x70,0x73,0x87,0x9F,0xF8,0xFF,0x87,0xF0,0x00, // 'D'
	0xFF,0xEF,0xFE,0xFF,0xEE,0x00,0xE0,0x0E,0x00,0xE0,0x0F,0xFC,0xFF,0xCF,0xFC,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0F,0xFE,0xFF,0xEF,0xFE, // 'E'
	0xFF,0xEF,0xFE,0xFF,0xEE,0x00,0xE0,0x0E,0x00,0xE0,0x0F,0xFC,0xFF,0xCF,0xFC,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00, // 'F'
	0x0F,0xC0,0xFF,0x0F,0xF8,0xF0,0xC7,0x00,0x78,0x03,0x80,0x1C,0x00,0xE1,0xF7,0x0F,0xB8,0x7D,0xC0,0xEF,0x07,0x38,0x39,0xE1,0xC7,0xFE,0x1F,0xF0,0x7E,0x00, // 'G'
	0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEF,0xFE,0xFF,0xEF,0xFE,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E, // 'H'
	0xFF,0xBF,0xEF,0xF8,0x70,0x1C,0x07,0x01,0xC0,0x70,0x1C,0x07,0x01,0xC0,0x70,0x1C,0x07,0x01,0xC3,0xFE,0xFF,0xBF,0xE0, // 'I'
	0x0F,0xE0,0xFE,0x0F,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE8,0x0E,0xC1,0xEF,0xFC,0xFF,0xC3,0xF0, // 'J'
	0xE0,0xF3,0x87,0x8E,0x1C,0x38,0xF0,0xE7,0x83,0xBC,0x0F,0xE0,0x3F,0x80,0xFF,0x03,0xFC,0x0F,0x78,0x39,0xE0,0xE3,0xC3,0x8F,0x0E,0x1E,0x38,0x78,0xE0,0xF3,0x83,0xC0, // 'K'
	0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0F,0xFE,0xFF,0xEF,0xFE, // 'L'
	0xF0,0xF7,0x87,0xBE,0x7D,0xF3,0xEF,0x9F,0x7C,0xFB,0xBD,0xDD,0xEE,0xEF,0x77,0x7B,0xBB,0xDD,0xCC,0xEE,0x07,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x77,0x03,0x80, // 'M'
	0xF0,0xEF,0x0E,0xF0,0xEF,0x8E,0xF8,0xEF,0x8E,0xEC,0xEE,0xCE,0xEC,0xEE,0x6E,0xE6,0xEE,0x6E,0xE3,0xEE,0x3E,0xE3,0xEE,0x1E,0xE1,0xEE,0x1E, // 'N'
	0x0F,0x01,0xFE,0x1F,0xF8,0xE1,0xC7,0x0E,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x77,0x03,0xB8,0x1D,0xC0,0xEE,0x07,0x38,0x71,0xC3,0x8F,0xFC,0x3F,0xC0,0x78,0x00, // 'O'
	0xFF,0x0F,0xFC,0xFF,0xCE,0x1E,0xE0,0xEE,0x0E,0xE0,0xEE,0x1E,0xFF,0xCF,0xFC,0xFF,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00, // 'P'
	0x0F,0x01,0xFE,0x1F,0xF8,0xE1,0xC7,0x0E,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x77,0x03,0xB8,0x1D,0xC0,0xEE,0x07,0x38,0x79,0xC3,0x8F,0xFC,0x3F,0xC0,0x7E,0x00,0x78,0x01,0xC0,0x04,0x00, // 'Q'
	0xFF,0x03,0xFF,0x0F,0xFC,0x38,0x78,0xE0,0xE3,0x83,0x8E,0x0E,0x38,0x78,0xFF,0xC3,0xFC,0x0F,0xF8,0x38,0xF0,0xE3,0xC3,0x87,0x8E,0x1E,0x38,0x3C,0xE0,0xF3,0x81,0xE0, // 'R'
	0x1F,0x87,0xFC,0x7F,0xCF,0x0C,0xE0,0x4E,0x00,0xF0,0x07,0xE0,0x7F,0x81,0xFC,0x07,0xE0,0x1E,0x00,0xE8,0x0E,0xE1,0xEF,0xFC,0xFF,0xC7,0xF0, // 'S'
	0xFF,0xEF,0xFE,0xFF,0xE0,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0, // 'T'
	0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xF1,0xE7,0xFC,0x7F,0xC1,0xF0, // 'U'
	0xF0,0x7B,0xC1,0xE7,0x07,0x1C,0x1C,0x70,0x71,0xE3,0xC7,0x8F,0x0E,0x38,0x38,0xE0,0xE3,0x83,0xDE,0x07,0x70,0x1D,0xC0,0x77,0x01,0xDC,0x03,0xE0,0x0F,0x80,0x3E,0x00, // 'V'
	0xE0,0x1D,0xC0,0x3B,0x80,0x77,0x00,0xE6,0x01,0xCE,0xF3,0x1D,0xEE,0x3B,0xDC,0x77,0xB8,0xEF,0x71,0xDF,0xE3,0xE7,0xC7,0xCF,0x87,0x9F,0x0F,0x3C,0x1E,0x78,0x38,0x70,0x70,0xE0, // 'W'
	0xF0,0x3C,0xE0,0x71,0xE1,0xE1,0xE7,0x81,0xCE,0x03,0xFC,0x03,0xF0,0x07,0xE0,0x07,0x80,0x0F,0x00,0x3F,0x00,0x7E,0x01,0xFE,0x03,0x9C,0x0F,0x3C,0x3C,0x3C,0x70,0x39,0xE0,0x78, // 'X'
	0xF0,0x79,0xC1,0xC7,0x8F,0x0E,0x38,0x3D,0xE0,0x77,0x01,0xDC,0x07,0xF0,0x0F,0x80,0x3E,0x00,0x70,0x01,0xC0,0x07,0x00,0x1C,0x00,0x70,0x01,0xC0,0x07,0x00,0x1C,0x00, // 'Y'
	0xFF,0xF7,0xFF,0xBF,0xFC,0x01,0xE0,0x1E,0x01,0xE0,0x0F,0x00,0xF0,0x0F,0x00,0x78,0x07,0x80,0x78,0x03,0xC0,0x3C,0x03,0xC0,0x1F,0xFE,0xFF,0xF7,0xFF,0x80, // 'Z'
	0xFD,0xFB,0x87,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0x87,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0x87,0xEF,0xC0, // '['
	0xE0,0x03,0x00,0x1C,0x00,0x60,0x03,0x80,0x0C,0x00,0x70,0x01,0x80,0x0E,0x00,0x70,0x01,0xC0,0x0E,0x00,0x30,0x01,0xC0,0x06,0x00,0x38,0x00,0xC0,0x07,0x00,0x18,0x00,0xE0, // '\'
	0xFD,0xF8,0x70,0xE1,0xC3,0x87,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0x87,0x0E,0x1C,0x38,0x77,0xEF,0xC0, // ']'
	0x07,0x00,0x3E,0x01,0xFC,0x07,0x70,0x38,0xE1,0xC1,0xCE,0x03,0x80, // '^'
	0xFF,0xFD,0xFF,0xF8, // '_'
	0x70,0x38,0x1C,0x0E, // '`'
	0x3F,0x83,0xFF,0x1F,0xF8,0xC1,0xE0,0x07,0x1F,0xF9,0xFF,0xDF,0xFE,0xE0,0x77,0x07,0xBF,0xFC,0xFF,0xE3,0xE7,0x00, // 'a'
	0xE0,0x07,0x00,0x38,0x01,0xC0,0x0E,0x00,0x73,0xC3,0xBF,0x1F,0xFC,0xF0,0xF7,0x03,0xB8,0x1D,0xC0,0xEE,0x07,0x70,0x3B,0xC3,0xDF,0xFC,0xEF,0xC7,0x3C,0x00, // 'b'
	0x0F,0xC3,0xFE,0x7F,0xE7,0x82,0xF0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x07,0x82,0x7F,0xE3,0xFE,0x0F,0xC0, // 'c'
	0x00,0x70,0x03,0x80,0x1C,0x00,0xE0,0x07,0x0F,0x38,0xFD,0xCF,0xFE,0xF0,0xF7,0x03,0xB8,0x1D,0xC0,0xEE,0x07,0x70,0x3B,0xC3,0xCF,0xFE,0x3F,0x70,0xF3,0x80, // 'd'
	0x1F,0x81,0xFE,0x1F,0xF8,0xE1,0xEE,0x07,0x7F,0xFB,0xFF,0xDF,0xFE,0xE0,0x07,0x81,0x1F,0xF8,0x7F,0xC1,0xFC,0x00, // 'e'
	0x0F,0xC3,0xF8,0x7F,0x0E,0x01,0xC1,0xFF,0xBF,0xF7,0xFE,0x1C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80, // 'f'
	0x1E,0x71,0xFF,0x9F,0xFD,0xE1,0xEE,0x07,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x77,0x87,0x9F,0xFC,0x7F,0xE1,0xF7,0x00,0x39,0x03,0xCF,0xFC,0x7F,0xE1,0xFC,0x00, // 'g'
	0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x78,0xFF,0xCF,0xFE,0xF1,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E, // 'h'
	0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x00,0x00,0x00,0x00,0x07,0xE0,0x7E,0x07,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x00,0xE0,0x0E,0x0F,0xFE,0xFF,0xEF,0xFE, // 'i'
	0x07,0x03,0x81,0xC0,0xE0,0x00,0x00,0x00,0x7E,0x3F,0x1F,0x81,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x81,0xC0,0xE0,0x70,0x7B,0xFD,0xFC,0xFC,0x00, // 'j'
	0xE0,0x07,0x00,0x38,0x01,0xC0,0x0E,0x00,0x70,0xF3,0x8F,0x1C,0xF0,0xEF,0x07,0xF0,0x3F,0x81,0xFE,0x0F,0x70,0x73,0xC3,0x8F,0x1C,0x38,0xE1,0xE7,0x07,0x80, // 'k'
	0xFC,0x0F,0xC0,0xFC,0x01,0xC0,0x1C,0x01,0xC0,0x1C,0x01,0xC0,0x1C,0x01,0xC0,0x1C,0x01,0xC0,0x1C,0x01,0xC0,0x1E,0x01,0xFE,0x0F,0xE0,0x7E, // 'l'
	0xEE,0xF3,0xFB,0xCF,0xFF,0xB9,0xCE,0xE7,0x3B,0x9C,0xEE,0x73,0xB9,0xCE,0xE7,0x3B,0x9C,0xEE,0x73,0xB9,0xCE,0xE7,0x38, // 'm'
	0xE7,0x8F,0xFC,0xFF,0xEF,0x1E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xE0, // 'n'
	0x1F,0x81,0xFE,0x1F,0xF9,0xE1,0xCE,0x07,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x73,0x87,0x1F,0xF8,0x7F,0x81,0xF8,0x00, // 'o'
	0xE7,0x87,0x7E,0x3F,0xF9,0xE1,0xEE,0x07,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x77,0x87,0xBF,0xF9,0xDF,0x8E,0x78,0x70,0x03,0x80,0x1C,0x00,0xE0,0x07,0x00,0x00, // 'p'
	0x1E,0x71,0xFB,0x9F,0xFD,0xE1,0xEE,0x07,0x70,0x3B,0x81,0xDC,0x0E,0xE0,0x77,0x87,0x9F,0xFC,0x7E,0xE1,0xE7,0x00,0x38,0x01,0xC0,0x0E,0x00,0x70,0x03,0x80, // 'q'
	0xE7,0x9D,0xFB,0xFF,0x7C,0x2F,0x01,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x00, // 'r'
	0x3F,0x87,0xFC,0xFF,0xCE,0x04,0xF8,0x0F,0xF8,0x7F,0xC0,0xFE,0x00,0xEC,0x0E,0xFF,0xEF,0xFC,0x3F,0x80, // 's'
	0x1C,0x03,0x80,0x70,0x0E,0x0F,0xFD,0xFF,0xBF,0xF0,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0xF0,0x7E,0x07,0xC0, // 't'
	0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEE,0x0E,0xE0,0xEF,0x1E,0xFF,0xE7,0xFE,0x3C,0xE0, // 'u'
	0xF0,0xF7,0x87,0x9C,0x38,0xE1,0xC7,0x9E,0x1C,0xE0,0xE7,0x07,0x38,0x1F,0x80,0xFC,0x07,0xE0,0x1E,0x00,0xF0,0x00, // 'v'
	0xE0,0x1D,0xC0,0x3B,0x80,0x73,0x18,0xC7,0x7B,0x8E,0xF7,0x1D,0xEE,0x3B,0xDC,0x34,0xB0,0x79,0xE0,0xF3,0xC1,0xE7,0x83,0xCF,0x00, // 'w'
	0xF0,0xF3,0xCF,0x0E,0x70,0x7F,0x81,0xF8,0x07,0x80,0x3C,0x03,0xF0,0x1F,0x81,0xFE,0x0E,0x70,0xF3,0xCF,0x0F,0x00, // 'x'
	0xF0,0xF3,0x87,0x1C,0x38,0xF3,0xC3,0x9C,0x1C,0xE0,0xF7,0x03,0xF0,0x1F,0x80,0x7C,0x03,0xC0,0x1E,0x00,0xF0,0x07,0x00,0x38,0x0F,0xC0,0x7C,0x03,0xC0,0x00, // 'y'
	0xFF,0xEF,0xFE,0xFF,0xE0,0x3C,0x07,0x80,0xF0,0x1F,0x01,0xE0,0x3C,0x07,0x80,0xFF,0xEF,0xFE,0xFF,0xE0, // 'z'
	0x07,0xC1,0xF8,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x03,0xC3,0xF0,0x7E,0x01,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0xFC,0x0F,0x80, // '{'
	0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE, // '|'
	0xF8,0x1F,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x03,0xC0,0x3F,0x07,0xE1,0xE0,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x0F,0xC1,0xF0,0x00 // '}'
};
const GFXglyph DialogInput_bold_24Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,  15,    0,    0 }, // ' '
	  {     1,   4,  18,  15,    6,  -18 }, // '!'
	  {    10,  10,   7,  15,    3,  -18 }, // '"'
	  {    19,  15,  17,  15,    0,  -17 }, // '#'
	  {    51,  13,  22,  15,    1,  -18 }, // '$'
	  {    87,  15,  18,  15,    0,  -18 }, // '%'
	  {   121,  15,  18,  15,    1,  -18 }, // '&'
	  {   155,   4,   7,  15,    6,  -18 }, // '''
	  {   159,   7,  21,  15,    4,  -18 }, // '('
	  {   178,   7,  21,  15,    4,  -18 }, // ')'
	  {   197,  13,  12,  15,    1,  -18 }, // '*'
	  {   217,  14,  13,  15,    1,  -14 }, // '+'
	  {   240,   6,   8,  15,    4,   -4 }, // ','
	  {   246,   8,   3,  15,    4,   -8 }, // '-'
	  {   249,   5,   4,  15,    5,   -4 }, // '.'
	  {   252,  13,  20,  15,    1,  -18 }, // '/'
	  {   285,  13,  18,  15,    1,  -18 }, // '0'
	  {   315,  12,  18,  15,    2,  -18 }, // '1'
	  {   342,  13,  18,  15,    1,  -18 }, // '2'
	  {   372,  13,  18,  15,    1,  -18 }, // '3'
	  {   402,  13,  18,  15,    1,  -18 }, // '4'
	  {   432,  13,  18,  15,    1,  -18 }, // '5'
	  {   462,  13,  18,  15,    1,  -18 }, // '6'
	  {   492,  13,  18,  15,    1,  -18 }, // '7'
	  {   522,  13,  18,  15,    1,  -18 }, // '8'
	  {   552,  13,  18,  15,    1,  -18 }, // '9'
	  {   582,   5,  12,  15,    5,  -12 }, // ':'
	  {   590,   6,  16,  15,    4,  -12 }, // ';'
	  {   602,  13,  13,  15,    1,  -14 }, // '<'
	  {   624,  13,   9,  15,    1,  -12 }, // '='
	  {   639,  13,  13,  15,    1,  -14 }, // '>'
	  {   661,  11,  18,  15,    3,  -18 }, // '?'
	  {   686,  15,  20,  15,    0,  -16 }, // '@'
	  {   724,  15,  18,  15,    0,  -18 }, // 'A'
	  {   758,  13,  18,  15,    1,  -18 }, // 'B'
	  {   788,  12,  18,  15,    2,  -18 }, // 'C'
	  {   815,  13,  18,  15,    2,  -18 }, // 'D'
	  {   845,  12,  18,  15,    2,  -18 }, // 'E'
	  {   872,  12,  18,  15,    2,  -18 }, // 'F'
	  {   899,  13,  18,  15,    1,  -18 }, // 'G'
	  {   929,  12,  18,  15,    2,  -18 }, // 'H'
	  {   956,  10,  18,  15,    3,  -18 }, // 'I'
	  {   979,  12,  18,  15,    1,  -18 }, // 'J'
	  {  1006,  14,  18,  15,    1,  -18 }, // 'K'
	  {  1038,  12,  18,  15,    3,  -18 }, // 'L'
	  {  1065,  13,  18,  15,    1,  -18 }, // 'M'
	  {  1095,  12,  18,  15,    1,  -18 }, // 'N'
	  {  1122,  13,  18,  15,    1,  -18 }, // 'O'
	  {  1152,  12,  18,  15,    2,  -18 }, // 'P'
	  {  1179,  13,  21,  15,    1,  -18 }, // 'Q'
	  {  1214,  14,  18,  15,    2,  -18 }, // 'R'
	  {  1246,  12,  18,  15,    2,  -18 }, // 'S'
	  {  1273,  12,  18,  15,    2,  -18 }, // 'T'
	  {  1300,  12,  18,  15,    1,  -18 }, // 'U'
	  {  1327,  14,  18,  15,    1,  -18 }, // 'V'
	  {  1359,  15,  18,  15,    0,  -18 }, // 'W'
	  {  1393,  15,  18,  15,    0,  -18 }, // 'X'
	  {  1427,  14,  18,  15,    1,  -18 }, // 'Y'
	  {  1459,  13,  18,  15,    1,  -18 }, // 'Z'
	  {  1489,   7,  21,  15,    5,  -18 }, // '['
	  {  1508,  13,  20,  15,    1,  -18 }, // '\'
	  {  1541,   7,  21,  15,    3,  -18 }, // ']'
	  {  1560,  14,   7,  15,    1,  -18 }, // '^'
	  {  1573,  15,   2,  15,    0,    4 }, // '_'
	  {  1577,   8,   4,  15,    2,  -19 }, // '`'
	  {  1581,  13,  13,  15,    1,  -13 }, // 'a'
	  {  1603,  13,  18,  15,    1,  -18 }, // 'b'
	  {  1633,  12,  13,  15,    2,  -13 }, // 'c'
	  {  1653,  13,  18,  15,    1,  -18 }, // 'd'
	  {  1683,  13,  13,  15,    1,  -13 }, // 'e'
	  {  1705,  11,  18,  15,    2,  -18 }, // 'f'
	  {  1730,  13,  18,  15,    1,  -13 }, // 'g'
	  {  1760,  12,  18,  15,    2,  -18 }, // 'h'
	  {  1787,  12,  20,  15,    2,  -20 }, // 'i'
	  {  1817,   9,  25,  15,    2,  -20 }, // 'j'
	  {  1846,  13,  18,  15,    2,  -18 }, // 'k'
	  {  1876,  12,  18,  15,    2,  -18 }, // 'l'
	  {  1903,  14,  13,  15,    1,  -13 }, // 'm'
	  {  1926,  12,  13,  15,    2,  -13 }, // 'n'
	  {  1946,  13,  13,  15,    1,  -13 }, // 'o'
	  {  1968,  13,  18,  15,    1,  -13 }, // 'p'
	  {  1998,  13,  18,  15,    1,  -13 }, // 'q'
	  {  2028,  11,  13,  15,    3,  -13 }, // 'r'
	  {  2046,  12,  13,  15,    2,  -13 }, // 's'
	  {  2066,  11,  17,  15,    2,  -17 }, // 't'
	  {  2090,  12,  13,  15,    2,  -13 }, // 'u'
	  {  2110,  13,  13,  15,    1,  -13 }, // 'v'
	  {  2132,  15,  13,  15,    0,  -13 }, // 'w'
	  {  2157,  13,  13,  15,    1,  -13 }, // 'x'
	  {  2179,  13,  18,  15,    1,  -13 }, // 'y'
	  {  2209,  12,  13,  15,    1,  -13 }, // 'z'
	  {  2229,  11,  22,  15,    2,  -18 }, // '{'
	  {  2260,   4,  24,  15,    6,  -18 }, // '|'
	  {  2272,  11,  22,  15,    3,  -18 } // '}'
};
const GFXfont DialogInput_bold_24 PROGMEM = {
(uint8_t  *)DialogInput_bold_24Bitmaps,(GFXglyph *)DialogInput_bold_24Glyphs,0x20, 0x7E, 29};
