#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Orbitron_Bold_22Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0x0E,0xEE, // '!'
	0xEE,0xEE,0xEE,0xEE, // '"'
	0x07,0x0E,0x03,0x87,0x01,0xC7,0x01,0xC3,0x8F,0xFF,0xF7,0xFF,0xF8,0x70,0xE0,0x38,0x70,0x1C,0x30,0x1C,0x38,0x3F,0xFF,0x9F,0xFF,0xC3,0x0E,0x03,0x87,0x01,0xC3,0x81,0xE3,0x80, // '#'
	0x03,0x80,0x03,0x80,0x7F,0xFC,0xFF,0xFE,0xFF,0xFE,0xE3,0x86,0xE3,0x80,0xE3,0x80,0xE3,0x80,0xFF,0xFE,0x7F,0xFE,0x1F,0xFE,0x03,0x86,0x03,0x86,0xE3,0x86,0xFF,0xFE,0xFF,0xFE,0x7F,0xFC,0x03,0x80,0x03,0x80, // '$'
	0x3C,0x00,0xC7,0xE0,0x1C,0xFF,0x03,0xCE,0x30,0x78,0xE3,0x0F,0x0E,0x33,0xE0,0xFF,0x7C,0x07,0xEF,0x80,0x01,0xE7,0x80,0x3C,0xFC,0x07,0x9F,0xE1,0xF1,0x8E,0x3E,0x18,0xE3,0x81,0x8E,0x30,0x1F,0xC2,0x00,0xFC, // '%'
	0x1F,0xFC,0x03,0xFF,0xE0,0x7F,0xFE,0x07,0x00,0xE0,0x70,0x0E,0x07,0x00,0x00,0x78,0x00,0x07,0xE0,0x00,0xFF,0x87,0x0E,0x7E,0x70,0xE1,0xFF,0x0E,0x07,0xF0,0xE0,0x1F,0x8F,0xFF,0xFE,0x7F,0xFE,0xE3,0xFF,0xE6, // '&'
	0xEE,0xEE, // '''
	0x33,0xBD,0xCE,0x73,0x9C,0xE7,0x39,0xCE,0x79,0xCE, // '('
	0xE7,0xBC,0x63,0x18,0xC6,0x31,0x8C,0x63,0x7B,0xDC, // ')'
	0x1C,0x03,0x83,0x76,0x7F,0xCF,0xFC,0x7E,0x0F,0x83,0xBC,0x77,0x04,0x40, // '*'
	0x1C,0x07,0x01,0xC3,0xFE,0xFF,0xBF,0xE1,0xC0,0x70,0x1C,0x00, // '+'
	0xEE,0xEE,0xEC, // ','
	0xFF,0xBF,0xEF,0xF8, // '-'
	0xEE,0xE0, // '.'
	0x00,0x20,0x02,0x00,0x60,0x0E,0x01,0xC0,0x3C,0x07,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x80,0xF0,0x0E,0x00,0xC0,0x08,0x00, // '/'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0xDC,0x03,0xEE,0x03,0xF7,0x03,0xFB,0x83,0xDD,0xC3,0xCE,0xE7,0xC7,0x77,0xC3,0xBF,0x81,0xDF,0x80,0xEF,0x80,0x77,0xFF,0xF9,0xFF,0xF8,0x7F,0xFC, // '0'
	0x07,0x07,0x87,0xC7,0xE7,0xF7,0xB8,0x1C,0x0E,0x07,0x03,0x81,0xC0,0xE0,0x70,0x38,0x1C,0x0E, // '1'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0xDC,0x00,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0xFF,0xFE,0x7F,0xFE,0x7F,0xFE,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0xFF,0xFB,0xFF,0xFD,0xFF,0xFE, // '2'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0x9C,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x38,0x3F,0xFC,0x1F,0xFF,0x00,0x03,0x80,0x01,0xC0,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xF8,0x7F,0xFC, // '3'
	0x00,0x38,0x00,0x78,0x00,0xF8,0x01,0xF8,0x07,0xF8,0x0F,0xB8,0x1F,0x38,0x3E,0x38,0x78,0x38,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38, // '4'
	0xFF,0xFF,0x7F,0xFF,0xBF,0xFF,0xDC,0x00,0x0E,0x00,0x07,0x00,0x03,0xFF,0xF1,0xFF,0xFC,0xFF,0xFF,0x00,0x03,0x80,0x01,0xC0,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0x7F,0xFC, // '5'
	0x3F,0xF8,0x3F,0xFC,0x3F,0xFE,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0xFF,0xF1,0xFF,0xFC,0xFF,0xFF,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0x7F,0xFC, // '6'
	0xFF,0xF3,0xFF,0xEF,0xFF,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0E, // '7'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xFF,0xFE,0xFF,0xFF,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0x7F,0xFC, // '8'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xFF,0xFE,0x7F,0xFF,0x1F,0xFF,0x80,0x01,0xC0,0x00,0xE0,0x00,0x77,0xFF,0xF9,0xFF,0xF8,0x7F,0xF8, // '9'
	0xEE,0xE0,0x00,0x00,0x00,0xEE,0xE0, // ':'
	0xEE,0xE0,0x00,0x00,0x00,0xEE,0xEE,0xE8, // ';'
	0x00,0x80,0xE0,0x78,0x7E,0x7E,0x3E,0x0F,0x03,0xE0,0x7E,0x07,0xE0,0x78,0x0E,0x00,0x80, // '<'
	0xFF,0xF7,0xFF,0xBF,0xFC,0x00,0x0F,0xFF,0x7F,0xFB,0xFF,0xC0, // '='
	0x80,0x1C,0x03,0xE0,0x3F,0x03,0xF0,0x1F,0x80,0xF0,0x7E,0x1F,0x0F,0xC3,0xE0,0x70,0x0C,0x00, // '>'
	0xFF,0xF3,0xFF,0xEF,0xFF,0x80,0x06,0x00,0x18,0x00,0x60,0x01,0x83,0xFE,0x3F,0xF8,0xFF,0xC3,0x80,0x0E,0x00,0x00,0x00,0xE0,0x03,0x80,0x0E,0x00, // '?'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0xDC,0x00,0xEE,0x3C,0x77,0x3F,0x3B,0xBF,0xDD,0xDC,0x6E,0xEE,0x37,0x77,0xFF,0xB9,0xFF,0xDC,0x7F,0xEE,0x00,0x07,0xFF,0xF9,0xFF,0xFC,0x7F,0xFE, // '@'
	0x3F,0xFC,0x3F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E,0xFF,0xFF,0x7F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E, // 'A'
	0xFF,0xFC,0x7F,0xFF,0x3F,0xFF,0x9C,0x00,0xEE,0x00,0x77,0x00,0x3B,0xFF,0xF9,0xFF,0xFC,0xFF,0xFF,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xFB,0xFF,0xFD,0xFF,0xFC, // 'B'
	0x3F,0xFF,0x3F,0xFF,0xBF,0xFF,0xDC,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0xFF,0xF9,0xFF,0xFC,0x7F,0xFE, // 'C'
	0xFF,0xFC,0x7F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E,0xE0,0x07,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xFB,0xFF,0xFD,0xFF,0xFC, // 'D'
	0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE, // 'E'
	0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00, // 'F'
	0x3F,0xFC,0x3F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x7E,0xE0,0x3F,0x70,0x1F,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0x7F,0xFC, // 'G'
	0xE0,0x03,0x70,0x01,0xB8,0x00,0xDC,0x00,0x6E,0x00,0x37,0x00,0x1B,0x80,0x0D,0xFF,0xFE,0xFF,0xFF,0x7F,0xFF,0xB8,0x00,0xDC,0x00,0x6E,0x00,0x37,0x00,0x1B,0x80,0x0D,0xC0,0x06, // 'H'
	0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE, // 'I'
	0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0xFF,0xFC, // 'J'
	0xE0,0x0F,0x70,0x0F,0x38,0x0F,0x1C,0x07,0x0E,0x07,0x87,0x07,0x83,0x87,0x81,0xFF,0x80,0xFF,0xC0,0x7F,0xF0,0x38,0x3C,0x1C,0x0E,0x0E,0x07,0x87,0x01,0xE3,0x80,0x79,0xC0,0x1E, // 'K'
	0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0xFF,0xFB,0xFF,0xFD,0xFF,0xFE, // 'L'
	0xF0,0x01,0xDF,0x00,0x7B,0xE0,0x1F,0x7E,0x07,0xEF,0xE1,0xFD,0xDE,0x7B,0xB9,0xEE,0x77,0x1F,0xCE,0xE1,0xF1,0xDC,0x3C,0x3B,0x83,0x07,0x70,0x20,0xEE,0x00,0x1D,0xC0,0x03,0xB8,0x00,0x77,0x00,0x0E, // 'M'
	0xF0,0x07,0x7C,0x03,0xBE,0x01,0xDF,0x80,0xEF,0xE0,0x77,0x78,0x3B,0x9E,0x1D,0xC7,0x8E,0xE1,0xC7,0x70,0xF3,0xB8,0x3D,0xDC,0x0F,0xEE,0x03,0xF7,0x00,0xFB,0x80,0x3D,0xC0,0x1E, // 'N'
	0x3F,0xFC,0x3F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E,0xE0,0x07,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0x7F,0xFC, // 'O'
	0xFF,0xFC,0x7F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E,0xFF,0xFF,0x7F,0xFF,0x3F,0xFF,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00, // 'P'
	0x3F,0xFC,0x0F,0xFF,0xE3,0xFF,0xFC,0x70,0x03,0x8E,0x00,0x71,0xC0,0x0E,0x38,0x01,0xC7,0x00,0x38,0xE0,0x07,0x1C,0x00,0xE3,0x80,0x1C,0x70,0x03,0x8E,0x00,0x71,0xFF,0xFF,0x9F,0xFF,0xF1,0xFF,0xFE, // 'Q'
	0xFF,0xFC,0x7F,0xFF,0xBF,0xFF,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E,0xFF,0xFF,0x7F,0xFF,0x3F,0xFF,0x1C,0x0F,0x0E,0x03,0xC7,0x00,0xF3,0x80,0x39,0xC0,0x1E, // 'R'
	0x3F,0xFC,0x3F,0xFF,0x3F,0xFF,0xDC,0x00,0xEE,0x00,0x07,0x00,0x03,0x80,0x01,0xFF,0xFC,0x7F,0xFF,0x0F,0xFF,0x80,0x01,0xC0,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0xFF,0xFC, // 'S'
	0xFF,0xFF,0x7F,0xFF,0xBF,0xFF,0xC0,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x03,0x80, // 'T'
	0xE0,0x07,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0x00,0x3B,0x80,0x1D,0xC0,0x0E,0xE0,0x07,0x70,0x03,0xB8,0x01,0xDC,0x00,0xEE,0x00,0x77,0xFF,0xF9,0xFF,0xFC,0x7F,0xFC, // 'U'
	0xE0,0x00,0x79,0xC0,0x01,0xC7,0x00,0x0E,0x0E,0x00,0x78,0x3C,0x01,0xC0,0x70,0x0F,0x01,0xE0,0x38,0x03,0x81,0xC0,0x07,0x07,0x00,0x1E,0x38,0x00,0x39,0xE0,0x00,0xF7,0x00,0x01,0xFC,0x00,0x07,0xE0,0x00,0x0F,0x00,0x00,0x1C,0x00, // 'V'
	0xE0,0x38,0x07,0x70,0x1E,0x03,0x9C,0x0F,0x03,0x8E,0x0F,0xC1,0xC7,0x07,0xE1,0xC1,0xC3,0xF0,0xE0,0xE3,0x9C,0x70,0x79,0xCE,0x70,0x1D,0xE7,0x38,0x0E,0xE1,0xDC,0x03,0xF0,0xFC,0x01,0xF0,0x7E,0x00,0xF8,0x1F,0x00,0x3C,0x0F,0x00,0x1C,0x07,0x80,0x0E,0x01,0x80, // 'W'
	0xE0,0x0F,0x78,0x07,0x1E,0x07,0x87,0x87,0x81,0xE7,0x80,0x7F,0x80,0x1F,0x80,0x07,0x80,0x03,0xC0,0x03,0xF0,0x03,0xFC,0x03,0xCF,0x03,0xC3,0xC3,0xC0,0xE1,0xC0,0x79,0xE0,0x1E, // 'X'
	0xF0,0x03,0xCF,0x00,0xF0,0xF0,0x1C,0x0E,0x07,0x00,0xE1,0xE0,0x1E,0x78,0x01,0xFE,0x00,0x1F,0xC0,0x01,0xF0,0x00,0x3C,0x00,0x03,0x80,0x00,0x70,0x00,0x0E,0x00,0x01,0xC0,0x00,0x38,0x00,0x07,0x00, // 'Y'
	0xFF,0xFF,0x7F,0xFF,0xBF,0xFF,0xC0,0x03,0xE0,0x03,0xE0,0x03,0xC0,0x03,0xC0,0x07,0xC0,0x07,0xC0,0x07,0xC0,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0xFF,0xFB,0xFF,0xFD,0xFF,0xFE, // 'Z'
	0xF7,0xBD,0xCE,0x73,0x9C,0xE7,0x39,0xCE,0x7B,0xDE, // '['
	0x80,0x0C,0x00,0xE0,0x0F,0x00,0x70,0x03,0x80,0x1C,0x00,0xE0,0x0F,0x00,0x78,0x03,0x80,0x1C,0x00,0xE0,0x06,0x00,0x60,0x02, // '\'
	0xF7,0xBC,0xE7,0x39,0xCE,0x73,0x9C,0xE7,0x7B,0xDE, // ']'
	0x00, // '^'
	0xFF,0xFF,0x7F,0xFF,0xBF,0xFF,0xC0, // '_'
	0xE7,0x38,0xE0, // '`'
	0xFF,0xE3,0xFF,0xEF,0xFF,0x80,0x0E,0x00,0x3B,0xFF,0xEF,0xFF,0xBF,0xFE,0xE0,0x3B,0x80,0xEF,0xFF,0x9F,0xFE,0x3F,0xF8, // 'a'
	0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xFF,0xE3,0xFF,0xEF,0xFF,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEF,0xFF,0xBF,0xFE,0xFF,0xF0, // 'b'
	0x3F,0xF9,0xFF,0xEF,0xFF,0xB8,0x00,0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x0F,0xFF,0x9F,0xFE,0x7F,0xF8, // 'c'
	0x00,0x30,0x01,0x80,0x0C,0x00,0x67,0xFF,0x7F,0xFB,0xFF,0xD8,0x06,0xC0,0x36,0x01,0xB0,0x0D,0x80,0x6C,0x03,0x60,0x1B,0xFF,0xDF,0xFE,0x7F,0xF0, // 'd'
	0x3F,0xE1,0xFF,0xEF,0xFF,0xB8,0x0E,0xE0,0x3B,0xFF,0xEF,0xFF,0xBF,0xFE,0xE0,0x03,0x80,0x0F,0xFF,0x9F,0xFE,0x7F,0xF8, // 'e'
	0x3F,0x3F,0xBF,0xDC,0x0F,0xF7,0xFB,0xFD,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x81,0xC0,0xE0,0x00, // 'f'
	0x3F,0xE3,0xFF,0xCF,0xFF,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEF,0xFF,0xBF,0xFE,0x7F,0xF8,0x00,0xE0,0x03,0x8F,0xFE,0x3F,0xF0,0xFF,0xC0, // 'g'
	0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xFF,0xE3,0xFF,0xEF,0xFF,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x38, // 'h'
	0xEE,0xE0,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xE0, // 'i'
	0x03,0x01,0x80,0xC0,0x00,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xDF,0xEF,0xF7,0xF0, // 'j'
	0xE0,0x03,0x80,0x0E,0x00,0x38,0x00,0xE0,0x3B,0x81,0xEE,0x0F,0x38,0x78,0xE3,0xC3,0xFE,0x0F,0xF0,0x3F,0xE0,0xE3,0xC3,0x87,0x0E,0x0E,0x38,0x1C,0xE0,0x78, // 'k'
	0xE1,0xC3,0x87,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0x87,0x0E,0x1C,0x3F,0x3E,0x3C, // 'l'
	0xFF,0xFF,0x8F,0xFF,0xFC,0xFF,0xFF,0xEE,0x0E,0x0E,0xE0,0xE0,0xEE,0x0E,0x0E,0xE0,0xE0,0xEE,0x0E,0x0E,0xE0,0xE0,0xEE,0x0E,0x0E,0xE0,0xE0,0xEE,0x0E,0x0E,0xE0,0xE0,0xE0, // 'm'
	0xFF,0xE3,0xFF,0xEF,0xFF,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x38, // 'n'
	0x3F,0xE1,0xFF,0xEF,0xFF,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEF,0xFF,0x9F,0xFE,0x7F,0xF0, // 'o'
	0xFF,0xE3,0xFF,0xEF,0xFF,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEF,0xFF,0xBF,0xFE,0xFF,0xF3,0x80,0x0E,0x00,0x38,0x00,0xE0,0x03,0x80,0x00, // 'p'
	0x3F,0xF9,0xFF,0xE7,0xFF,0xB8,0x06,0xE0,0x1B,0x80,0x6E,0x01,0xB8,0x06,0xE0,0x1B,0x80,0x6F,0xFF,0x9F,0xFE,0x3F,0xF8,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x60, // 'q'
	0x3F,0xCF,0xFB,0xFF,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x00, // 'r'
	0x3F,0xE1,0xFF,0xCF,0xFF,0xB8,0x0E,0xE0,0x03,0xFF,0x8F,0xFF,0x1F,0xFE,0x00,0x3B,0x80,0xEF,0xFF,0xBF,0xFE,0x7F,0xF0, // 's'
	0xE0,0x70,0x38,0x1C,0x0F,0xF7,0xFB,0xFD,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0xFC,0xFE,0x3F,0x00, // 't'
	0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEF,0xFF,0x9F,0xFE,0x3F,0xF0, // 'u'
	0xF0,0x03,0x9C,0x01,0xC3,0x80,0x70,0xF0,0x38,0x1C,0x0E,0x07,0x87,0x00,0xE3,0xC0,0x3C,0xE0,0x07,0x78,0x00,0xFC,0x00,0x3F,0x00,0x07,0x80,0x01,0xC0,0x00, // 'v'
	0xE0,0x70,0x3D,0xC0,0xF0,0x71,0xC3,0xE0,0xE3,0x87,0xE3,0x87,0x9F,0xC7,0x07,0x3B,0xCE,0x0E,0xF3,0xB8,0x0F,0xC7,0xF0,0x1F,0x87,0xC0,0x3F,0x0F,0x80,0x3C,0x1F,0x00,0x78,0x1C,0x00,0x60,0x38,0x00, // 'w'
	0xE0,0x3B,0xC1,0xE7,0x8F,0x0F,0x78,0x1F,0xC0,0x3E,0x00,0x70,0x03,0xE0,0x1F,0xC0,0xF7,0x87,0x8F,0x1C,0x1E,0xF0,0x38, // 'x'
	0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEE,0x03,0xB8,0x0E,0xE0,0x3B,0x80,0xEF,0xFF,0xBF,0xFE,0x7F,0xF8,0x00,0xE0,0x03,0x8F,0xFE,0x3F,0xF8,0xFF,0xC0, // 'y'
	0xFF,0xFB,0xFF,0xEF,0xFF,0x80,0x3E,0x01,0xF0,0x0F,0x00,0x78,0x07,0xC0,0x3E,0x01,0xE0,0x0F,0xFF,0xBF,0xFE,0xFF,0xF8, // 'z'
	0x39,0xE7,0xB8,0xE3,0x8E,0x38,0xE3,0x8E,0x38,0xE3,0xE7,0x8E, // '{'
	0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE, // '|'
	0xE3,0xCF,0x1C,0x71,0xC7,0x8E,0x39,0xE7,0x1C,0x73,0xCF,0x38 // '}'
};
const GFXglyph Orbitron_Bold_22Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   8,    0,    0 }, // ' '
	  {     1,   4,  16,   6,    1,  -16 }, // '!'
	  {     9,   8,   4,   9,    1,  -16 }, // '"'
	  {    13,  17,  16,  19,    1,  -16 }, // '#'
	  {    47,  16,  20,  18,    1,  -18 }, // '$'
	  {    87,  20,  16,  22,    1,  -16 }, // '%'
	  {   127,  20,  16,  22,    1,  -16 }, // '&'
	  {   167,   4,   4,   6,    1,  -16 }, // '''
	  {   169,   5,  16,   7,    1,  -16 }, // '('
	  {   179,   5,  16,   7,    1,  -16 }, // ')'
	  {   189,  11,  10,  12,    1,  -16 }, // '*'
	  {   203,  10,   9,  11,    0,  -11 }, // '+'
	  {   215,   4,   6,   6,    1,   -3 }, // ','
	  {   218,  10,   3,  12,    1,   -8 }, // '-'
	  {   222,   4,   3,   6,    1,   -3 }, // '.'
	  {   224,  12,  16,  12,    0,  -16 }, // '/'
	  {   248,  17,  16,  19,    1,  -16 }, // '0'
	  {   282,   9,  16,  10,    0,  -16 }, // '1'
	  {   300,  17,  16,  19,    1,  -16 }, // '2'
	  {   334,  17,  16,  19,    1,  -16 }, // '3'
	  {   368,  16,  16,  17,    0,  -16 }, // '4'
	  {   400,  17,  16,  19,    1,  -16 }, // '5'
	  {   434,  17,  16,  19,    1,  -16 }, // '6'
	  {   468,  14,  16,  16,    0,  -16 }, // '7'
	  {   496,  17,  16,  19,    1,  -16 }, // '8'
	  {   530,  17,  16,  19,    1,  -16 }, // '9'
	  {   564,   4,  13,   6,    1,  -13 }, // ':'
	  {   571,   4,  16,   6,    1,  -13 }, // ';'
	  {   579,  10,  13,  11,    0,  -13 }, // '<'
	  {   596,  13,   7,  15,    1,  -10 }, // '='
	  {   608,  11,  13,  11,    1,  -13 }, // '>'
	  {   626,  14,  16,  16,    1,  -16 }, // '?'
	  {   654,  17,  16,  19,    1,  -16 }, // '@'
	  {   688,  17,  16,  19,    1,  -16 }, // 'A'
	  {   722,  17,  16,  19,    1,  -16 }, // 'B'
	  {   756,  17,  16,  19,    1,  -16 }, // 'C'
	  {   790,  17,  16,  19,    1,  -16 }, // 'D'
	  {   824,  16,  16,  18,    1,  -16 }, // 'E'
	  {   856,  16,  16,  17,    1,  -16 }, // 'F'
	  {   888,  17,  16,  19,    1,  -16 }, // 'G'
	  {   922,  17,  16,  20,    1,  -16 }, // 'H'
	  {   956,   4,  16,   6,    1,  -16 }, // 'I'
	  {   964,  17,  16,  18,    0,  -16 }, // 'J'
	  {   998,  17,  16,  19,    1,  -16 }, // 'K'
	  {  1032,  17,  16,  18,    1,  -16 }, // 'L'
	  {  1066,  19,  16,  21,    1,  -16 }, // 'M'
	  {  1104,  17,  16,  19,    1,  -16 }, // 'N'
	  {  1138,  17,  16,  19,    1,  -16 }, // 'O'
	  {  1172,  17,  16,  18,    1,  -16 }, // 'P'
	  {  1206,  19,  16,  20,    1,  -16 }, // 'Q'
	  {  1244,  17,  16,  19,    1,  -16 }, // 'R'
	  {  1278,  17,  16,  19,    1,  -16 }, // 'S'
	  {  1312,  17,  16,  18,    0,  -16 }, // 'T'
	  {  1346,  17,  16,  19,    1,  -16 }, // 'U'
	  {  1380,  22,  16,  23,    1,  -16 }, // 'V'
	  {  1424,  25,  16,  27,    1,  -16 }, // 'W'
	  {  1474,  17,  16,  19,    1,  -16 }, // 'X'
	  {  1508,  19,  16,  19,    0,  -16 }, // 'Y'
	  {  1546,  17,  16,  19,    1,  -16 }, // 'Z'
	  {  1580,   5,  16,   7,    1,  -16 }, // '['
	  {  1590,  12,  16,  12,    0,  -16 }, // '\'
	  {  1614,   5,  16,   7,    1,  -16 }, // ']'
	  {  1624,   1,   1,   1,    0,    0 }, // '^'
	  {  1625,  17,   3,  19,    1,    0 }, // '_'
	  {  1632,   5,   4,   6,    1,  -21 }, // '`'
	  {  1635,  14,  13,  16,    1,  -13 }, // 'a'
	  {  1658,  14,  17,  16,    1,  -17 }, // 'b'
	  {  1688,  14,  13,  16,    1,  -13 }, // 'c'
	  {  1711,  13,  17,  16,    1,  -17 }, // 'd'
	  {  1739,  14,  13,  16,    1,  -13 }, // 'e'
	  {  1762,   9,  17,  11,    1,  -17 }, // 'f'
	  {  1782,  14,  18,  16,    1,  -13 }, // 'g'
	  {  1814,  14,  17,  16,    1,  -17 }, // 'h'
	  {  1844,   4,  17,   6,    1,  -17 }, // 'i'
	  {  1853,   9,  22,   6,   -4,  -17 }, // 'j'
	  {  1878,  14,  17,  15,    1,  -17 }, // 'k'
	  {  1908,   7,  17,   9,    1,  -17 }, // 'l'
	  {  1923,  20,  13,  23,    1,  -13 }, // 'm'
	  {  1956,  14,  13,  16,    1,  -13 }, // 'n'
	  {  1979,  14,  13,  16,    1,  -13 }, // 'o'
	  {  2002,  14,  18,  16,    1,  -13 }, // 'p'
	  {  2034,  14,  18,  16,    0,  -13 }, // 'q'
	  {  2066,  11,  13,  13,    1,  -13 }, // 'r'
	  {  2084,  14,  13,  16,    1,  -13 }, // 's'
	  {  2107,   9,  17,  11,    1,  -17 }, // 't'
	  {  2127,  14,  13,  16,    1,  -13 }, // 'u'
	  {  2150,  18,  13,  18,    0,  -13 }, // 'v'
	  {  2180,  23,  13,  24,    1,  -13 }, // 'w'
	  {  2218,  14,  13,  16,    1,  -13 }, // 'x'
	  {  2241,  14,  18,  16,    1,  -13 }, // 'y'
	  {  2273,  14,  13,  16,    1,  -13 }, // 'z'
	  {  2296,   6,  16,   7,    1,  -16 }, // '{'
	  {  2308,   4,  20,   6,    1,  -18 }, // '|'
	  {  2318,   6,  16,   7,    1,  -16 } // '}'
};
const GFXfont Orbitron_Bold_22 PROGMEM = {
(uint8_t  *)Orbitron_Bold_22Bitmaps,(GFXglyph *)Orbitron_Bold_22Glyphs,0x20, 0x7E, 23};
