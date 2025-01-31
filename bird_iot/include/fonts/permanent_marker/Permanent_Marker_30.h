#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Permanent_Marker_Regular_30Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0x06,0x07,0x83,0xC1,0xE1,0xF0,0xF8,0x78,0x3C,0x1E,0x0F,0x0F,0x87,0xC3,0xC1,0xE0,0xF0,0x00,0x00,0x10,0x1E,0x1F,0x0F,0x83,0xC0,0xC0, // '!'
	0x1C,0x30,0x7C,0xF8,0xF9,0xF1,0xF3,0xC7,0xCF,0x8F,0x9F,0x1F,0x3C,0x3C,0xF8,0x79,0xF0,0xF3,0xE3,0xE7,0x87,0x8F,0x07,0x1E,0x06,0x18,0x00, // '"'
	0x00,0x81,0x00,0x03,0x06,0x00,0x1C,0x38,0x00,0x78,0xF0,0x03,0xE7,0xC0,0x0F,0x1F,0x01,0xFF,0xFE,0x1F,0xFF,0xFC,0x7F,0xFF,0xF9,0xFF,0xFF,0x00,0x78,0xF0,0x03,0xC7,0x80,0x0F,0x1F,0x03,0xFF,0xFF,0x0F,0xFF,0xFE,0x3F,0xFF,0xE0,0xFE,0x3C,0x00,0xF1,0xE0,0x07,0xCF,0x80,0x1F,0x3E,0x00,0x78,0xF8,0x00,0xE1,0xC0,0x00, // '#'
	0x00,0x40,0x00,0x70,0x00,0x38,0x00,0x3C,0x00,0x1F,0xC0,0x3F,0xF0,0xFF,0xF9,0xFF,0xFE,0xFC,0x00,0x7F,0x80,0x3F,0xF0,0x07,0xF8,0x00,0x1E,0x00,0x07,0x00,0x07,0x80,0x07,0xC0,0x7F,0xC0,0x3F,0xC0,0x1F,0xC0,0x0F,0xC0,0x01,0xE0,0x00,0xF0,0x00,0x20,0x00, // '$'
	0x06,0x00,0x60,0xF0,0x0E,0x3F,0x01,0xC3,0xF0,0x3C,0x7B,0x87,0xC7,0x78,0xF0,0xFF,0x9E,0x07,0xF3,0xC0,0x7E,0x78,0x00,0x0F,0x00,0x01,0xE0,0x00,0x3C,0x40,0x07,0x8E,0x01,0xF3,0xE0,0x3E,0x7F,0x03,0xC7,0xF0,0x78,0xF7,0x07,0x8F,0xF8,0xF0,0xFF,0x0F,0x0F,0xE0,0x60,0x10,0x00, // '%'
	0x00,0x10,0x00,0x1C,0x00,0x07,0x80,0x23,0xE0,0x3E,0xF0,0x0F,0xFE,0x07,0xFF,0xE3,0xDF,0xFC,0xFF,0xFF,0x9F,0xFF,0xE3,0xFE,0x00,0x0F,0x80,0x03,0xE0,0x00,0xF8,0x00,0x3C,0x00,0x06,0x00, // '&'
	0x1C,0x3E,0x3E,0x3E,0x7C,0x7C,0x7C,0x78,0x78,0x78,0xF8,0xF0,0x70,0x30, // '''
	0x00,0x38,0x01,0xE0,0x0F,0x80,0x7E,0x03,0xF8,0x1F,0xC0,0xFC,0x03,0xE0,0x1F,0x00,0xFC,0x03,0xE0,0x0F,0x80,0x7C,0x01,0xF0,0x07,0xC0,0x1E,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3E,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3E,0x00,0xF8,0x01,0xF0,0x07,0x80,0x0E,0x00,0x1C,0x00,0x70,0x00, // '('
	0x00,0xC0,0x01,0xC0,0x03,0xC0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x3E,0x00,0x3E,0x00,0x7C,0x00,0xF8,0x01,0xE0,0x03,0xE0,0x07,0x80,0x0F,0x00,0x3E,0x00,0x7C,0x00,0xF0,0x03,0xE0,0x07,0xC0,0x1F,0x80,0x3E,0x00,0xFC,0x03,0xF0,0x0F,0xC0,0x3F,0x80,0xFE,0x01,0xF8,0x03,0xC0,0x07,0x00,0x1C,0x00,0x00, // ')'
	0x03,0x03,0x00,0x70,0xE0,0x0F,0x9E,0x00,0xFF,0xC0,0x07,0xFC,0x00,0x3F,0xF0,0x7F,0xFF,0xCF,0xFF,0xFE,0xFF,0xFF,0xC7,0xFF,0x80,0x07,0xFC,0x00,0xFB,0xC0,0x0F,0x1E,0x01,0xF1,0xC0,0x0E,0x0C,0x00, // '*'
	0x00,0xC0,0x00,0xE0,0x00,0x78,0x00,0x3C,0x00,0x3E,0x00,0x1F,0x01,0xFF,0xF1,0xFF,0xFE,0x7F,0xFF,0x3F,0xFE,0x09,0xF0,0x00,0xF8,0x00,0x78,0x00,0x3C,0x00,0x1E,0x00, // '+'
	0x38,0x3C,0x3E,0x3E,0x7C,0x7C,0xF8,0xF8,0x70, // ','
	0x7F,0xFC,0xFF,0xFE,0xFF,0xFE,0xFF,0xF8,0x40,0x00, // '-'
	0x21,0xEF,0xBE,0x78,0xC0, // '.'
	0x00,0x00,0x00,0x06,0x00,0x0E,0x00,0x1E,0x00,0x3E,0x00,0x3E,0x00,0x7C,0x00,0xF8,0x01,0xF0,0x03,0xE0,0x03,0xC0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x3E,0x00,0x7C,0x00,0x78,0x00,0xF8,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00, // '/'
	0x00,0x0C,0x00,0x01,0xE0,0x00,0x3E,0x00,0x07,0xF0,0x00,0xFF,0x00,0x1F,0xF0,0x03,0xFF,0x00,0x7F,0xF8,0x0F,0xFF,0x81,0xFC,0x78,0x1F,0x87,0xC3,0xF0,0x3C,0x3E,0x03,0xE7,0xE0,0x3E,0x7C,0x01,0xE7,0xC0,0x3E,0xF8,0x07,0xEF,0x81,0xFE,0xFF,0xFF,0xE7,0xFF,0xFC,0x7F,0xFF,0x83,0xFF,0xF0,0x1F,0xF8,0x00,0x78,0x00, // '0'
	0x30,0x38,0x3C,0x3C,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x7E,0x7C,0x7C,0xFC,0xFC,0xF8,0xF8,0xF8,0xF8,0x70, // '1'
	0x1F,0xC0,0x07,0xFF,0x80,0xFF,0xFC,0x0F,0xFF,0xC0,0xFF,0xFE,0x0F,0xFF,0xF0,0x00,0x7F,0x00,0x0F,0xF0,0x01,0xFE,0x00,0x3F,0xC0,0x0F,0xF8,0x01,0xFF,0x00,0x1F,0xC0,0x03,0xF8,0x00,0x7F,0x00,0x0F,0xE0,0x7C,0xFF,0xFF,0xEF,0xFF,0xFE,0xFF,0xFF,0xEF,0xFF,0xFC,0xFF,0xFC,0x03,0xF8,0x00, // '2'
	0x00,0x00,0x03,0xFF,0x87,0xFF,0xF3,0xFF,0xFC,0xFF,0xFF,0xBF,0xFF,0xCF,0xFF,0xE0,0xBF,0xF0,0x0F,0xF0,0x07,0xF8,0x01,0xFF,0x80,0x3F,0xF0,0x0F,0xFC,0x00,0x7F,0x80,0x03,0xE0,0x00,0xFC,0x21,0xFF,0x1F,0xFF,0x87,0xFF,0xC1,0xFF,0xE0,0x7F,0xE0,0x0F,0xC0,0x00, // '3'
	0x00,0x20,0x00,0x18,0x00,0x0E,0x08,0x07,0x06,0x07,0xC7,0x83,0xC1,0xC1,0xE0,0xF0,0xF0,0x78,0x7A,0x3C,0x3F,0x9F,0xFF,0xCF,0xFF,0xE3,0xFF,0xF1,0xFF,0xC0,0x3F,0x80,0x03,0xC0,0x03,0xE0,0x01,0xE0,0x00,0xF0,0x00,0x78,0x00,0x3E,0x00,0x0F,0x00,0x07,0x80,0x01,0xC0, // '4'
	0x01,0x00,0x00,0x38,0x00,0x0F,0xCF,0xC1,0xFF,0xFC,0x3F,0xFF,0xE7,0xFF,0xFE,0x7F,0xFF,0xE7,0xFF,0xC0,0xFF,0x00,0x07,0xF8,0x00,0x7F,0xC0,0x03,0xFE,0x00,0x0F,0xF0,0x00,0x3F,0x80,0x00,0xF8,0x00,0x07,0xC0,0x61,0xFC,0x0F,0xFF,0xC0,0x7F,0xF8,0x07,0xFF,0x80,0x3F,0xF0,0x00,0xF8,0x00, // '5'
	0x00,0xE0,0x07,0xC0,0x0F,0x80,0x3F,0x80,0xFF,0x01,0xF8,0x07,0xE0,0x0F,0x80,0x3E,0x00,0x7C,0x01,0xF0,0x03,0xE7,0x87,0xBF,0x9F,0x7F,0xBD,0xFF,0x7B,0xFE,0xF7,0xFD,0xFF,0xFB,0xFF,0xE7,0xFF,0x8F,0xFC,0x0F,0xC0,0x00,0x00,0x00, // '6'
	0x0E,0x00,0x07,0xFF,0x00,0x7F,0xF8,0x0F,0xFF,0xC0,0xFF,0xFE,0x07,0xFF,0xE0,0x00,0x3E,0x00,0x01,0xE0,0x00,0x1E,0x00,0x03,0xE0,0x00,0xFF,0xC1,0xFF,0xFE,0x3F,0xFF,0xE3,0xFF,0xFC,0x3F,0xFC,0x01,0xFF,0x00,0x03,0xE0,0x00,0x3E,0x00,0x07,0xC0,0x00,0x7C,0x00,0x07,0x80,0x00,0x78,0x00, // '7'
	0x0F,0x08,0x1F,0xC6,0x1F,0xF7,0x8F,0xFF,0xCF,0xFE,0xE7,0xCF,0xFB,0xC7,0xFD,0xF0,0xFC,0xFB,0xFC,0x3F,0xFC,0x1F,0xFC,0x07,0xF8,0x07,0xF8,0x03,0xFC,0x03,0xFF,0x01,0xE7,0x80,0xF1,0xC0,0x7F,0xF0,0x1F,0xF0,0x0F,0xF8,0x03,0xFC,0x00,0xF8,0x00, // '8'
	0x00,0xE0,0x07,0xF0,0x0F,0xF8,0x1F,0xF8,0x3F,0xFC,0x7F,0x3C,0x7C,0x7C,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0x7F,0xFC,0x7F,0xF8,0x00,0x78,0x00,0x70,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x01,0xE0,0x01,0xE0,0x01,0xE0, // '9'
	0x18,0x3E,0x3E,0x3E,0x1C,0x08,0x00,0x00,0x20,0x78,0xF8,0xF8,0x78,0x30, // ':'
	0x06,0x03,0xE0,0xF8,0x3E,0x07,0x00,0x80,0x00,0x00,0x00,0x07,0x01,0xE0,0x7C,0x3E,0x0F,0x83,0xE1,0xF0,0x7C,0x0E,0x00, // ';'
	0x00,0x03,0xC0,0x01,0xF8,0x01,0xFF,0x01,0xFF,0xC3,0xFF,0xE1,0xFF,0xE0,0x3F,0xE0,0x07,0xFC,0x00,0x3F,0xF0,0x03,0xFF,0x80,0x1F,0xF8,0x00,0x7F,0x80,0x00,0xF0, // '<'
	0x3F,0xFF,0x1F,0xFF,0xE7,0xFF,0xF0,0xFE,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xC3,0xFF,0xF8,0xFF,0xFC,0x1E,0x00,0x00, // '='
	0x3E,0x00,0x03,0xFC,0x00,0x3F,0xE0,0x03,0xFF,0x00,0x1F,0xF8,0x00,0x7F,0x80,0x1F,0xF0,0x1F,0xFE,0x1F,0xFE,0x0F,0xFE,0x03,0xFE,0x00,0x7F,0x00,0x0F,0x80,0x00, // '>'
	0x0F,0xF0,0x07,0xFF,0xC3,0xFF,0xF9,0xFF,0xFE,0x3F,0xFF,0x86,0x1F,0xE0,0x01,0xF8,0x00,0xFE,0x00,0xFF,0x00,0x7F,0x80,0x7F,0x80,0x3F,0xC0,0x1F,0xC0,0x07,0xC0,0x01,0xE0,0x00,0x10,0x00,0x00,0x00,0x08,0x00,0x07,0x80,0x01,0xE0,0x00,0xF8,0x00,0x1F,0x00,0x03,0x00,0x00, // '?'
	0x00,0x1E,0x00,0x00,0xFE,0x00,0x03,0xFC,0x00,0x1F,0xF0,0x00,0xFD,0xE0,0x07,0xC3,0x80,0x7E,0x0F,0x03,0xF0,0xDE,0x1F,0x1F,0x78,0xF8,0xFC,0xE7,0xCF,0xF3,0xBF,0x7F,0x8E,0xFB,0xEE,0x3B,0xCF,0x38,0xEF,0x3F,0xFF,0x38,0xFF,0xF8,0xE1,0xFF,0xC3,0xC0,0xC0,0x07,0xC0,0x08,0x0F,0xFF,0xE0,0x1F,0xFF,0xC0,0x1F,0xFF,0x00,0x03,0xF0,0x00, // '@'
	0x00,0x08,0x00,0x00,0x1E,0x00,0x00,0x7E,0x00,0x01,0xFC,0x00,0x1F,0xF8,0x00,0x3F,0xF0,0x00,0xFF,0xE0,0x01,0xFF,0xC0,0x07,0xFF,0xC0,0x0F,0xCF,0x80,0x3F,0x1F,0x00,0x7E,0x3F,0x81,0xF8,0xFF,0xC3,0xFF,0xFF,0x8F,0xFF,0xFE,0x1F,0x7F,0xF0,0x7E,0xFF,0xF0,0xF8,0x03,0xE1,0xF0,0x0F,0xC7,0xE0,0x3F,0x07,0x80,0x3E,0x06,0x00,0x78,0x00, // 'A'
	0x00,0xFF,0x00,0x3F,0xFE,0x03,0xFF,0xFE,0x1F,0xFF,0xF8,0xFF,0xF3,0xF1,0xFC,0x1F,0xC7,0xF8,0xFE,0x06,0xFF,0xF8,0x07,0xFF,0xC0,0x1F,0xFE,0x00,0x7F,0xF0,0x01,0xFF,0xF0,0x0F,0xFF,0xE0,0x3E,0x03,0xC0,0xF8,0x0F,0x07,0xE0,0x7E,0x1F,0x0F,0xF8,0x7C,0xFF,0xC1,0xFF,0xFE,0x0F,0xFF,0xF0,0x1F,0xFF,0x00,0x7F,0xF0,0x00,0x4C,0x00,0x00, // 'B'
	0x00,0x06,0x00,0x01,0xE0,0x00,0xFE,0x00,0x7F,0xE0,0x3F,0xFC,0x0F,0xFF,0x07,0xFF,0xC1,0xFF,0x80,0x3F,0xE0,0x0F,0xF0,0x03,0xF8,0x00,0x7E,0x00,0x0F,0x80,0x01,0xF0,0x00,0x3C,0x00,0x07,0xC0,0x00,0x7F,0x00,0x0F,0xFF,0xE0,0xFF,0xFE,0x0F,0xFF,0xC0,0xFF,0xF0,0x03,0xFC,0x00, // 'C'
	0x20,0x00,0x0F,0x00,0x03,0xF0,0x00,0xFF,0x00,0x3F,0xF0,0x0F,0xFE,0x03,0xCF,0xC0,0xF0,0xF8,0x3C,0x1F,0x0F,0x01,0xE3,0xC0,0x78,0xF0,0x1E,0x3C,0x0F,0x8F,0x07,0xE7,0xC7,0xF1,0xFF,0xFC,0x7F,0xFE,0x3F,0xFE,0x07,0xFF,0x01,0xFF,0x00,0x7E,0x00,0x1E,0x00,0x00, // 'D'
	0x00,0x00,0xC0,0x03,0xFF,0x01,0xFF,0xFC,0x3F,0xFF,0xC3,0xFF,0xFC,0x1F,0xFF,0x80,0xFF,0xC0,0x03,0xE0,0x00,0x1F,0x0C,0x00,0xFF,0xF0,0x07,0xFF,0xC0,0x7F,0xFE,0x03,0xFF,0xE0,0x3F,0xFC,0x01,0xF0,0x00,0x1F,0x80,0x00,0xF8,0x07,0x07,0xFF,0xFC,0x1F,0xFF,0xF0,0xFF,0xFF,0x07,0xFF,0xF0,0x1F,0xFC,0x00, // 'E'
	0x00,0x03,0xF0,0x00,0x7F,0xF0,0x07,0xFF,0xF0,0x7F,0xFF,0xE1,0xFF,0xFE,0x03,0xFF,0x00,0x07,0xF0,0x00,0x07,0xE0,0x00,0x07,0xC0,0x00,0x0F,0x80,0x00,0x1E,0x0C,0x03,0xFF,0xFC,0x0F,0xFF,0xF8,0x0F,0xFF,0xF0,0x1F,0xFF,0xC0,0x1F,0xE0,0x00,0x3E,0x00,0x00,0x7C,0x00,0x00,0xF0,0x00,0x01,0xE0,0x00,0x03,0xC0,0x00,0x03,0x80,0x00,0x00, // 'F'
	0x00,0x03,0x00,0x00,0x01,0xE0,0x00,0x01,0xFC,0x00,0x00,0xFF,0x80,0x00,0xFF,0xE0,0x00,0x7F,0xF0,0x00,0x3F,0xF0,0x00,0x1F,0xF0,0x00,0x0F,0xF0,0x00,0x07,0xF8,0x30,0x03,0xF8,0x1F,0x01,0xFC,0x0F,0xF0,0x7E,0x01,0xFE,0x3F,0x00,0x7F,0xCF,0xC0,0x0F,0xFB,0xE0,0x0F,0xFE,0xF8,0x7F,0xFF,0x1F,0xFF,0xFF,0x87,0xFF,0xFF,0x81,0xFF,0xFF,0x80,0x3F,0xFE,0x00,0x03,0xF0,0x00,0x00, // 'G'
	0x00,0x00,0xC0,0x40,0x06,0x07,0x00,0x78,0x3C,0x03,0xC1,0xF0,0x1F,0x0F,0x80,0xF8,0x7C,0x07,0xC3,0xE0,0x3E,0x1F,0x01,0xF1,0xF8,0x1F,0x8F,0x80,0xFC,0x7C,0x3F,0xE3,0xFF,0xFE,0x3F,0xFF,0xF1,0xFF,0xFF,0x8F,0xFF,0xFC,0xFF,0xE7,0xC7,0xF8,0x7E,0x3F,0x83,0xF1,0xF8,0x1F,0x8F,0xC0,0x78,0x3C,0x01,0x80, // 'H'
	0x00,0xFF,0xC0,0x3F,0xFF,0x03,0xFF,0xFC,0x1F,0xFF,0xE0,0x7F,0xFC,0x01,0xBE,0x00,0x01,0xF0,0x00,0x0F,0x00,0x00,0xF8,0x00,0x07,0xC0,0x00,0x3E,0x00,0x01,0xE0,0x00,0x1F,0x00,0x00,0xF8,0x00,0x0F,0x80,0x00,0x7C,0x00,0x07,0xC0,0x00,0xFF,0xC0,0x3F,0xFF,0x01,0xFF,0xF8,0x0F,0xFF,0xC0,0x3E,0x20,0x00, // 'I'
	0x01,0xFF,0xFE,0x03,0xFF,0xFF,0xC1,0xFF,0xFF,0xF8,0x7F,0xFF,0xFE,0x1F,0xFF,0xC7,0x03,0x81,0xF0,0x00,0x00,0x7C,0x00,0x00,0x1F,0x00,0x00,0x0F,0x80,0x00,0x03,0xE0,0x00,0x00,0xF8,0x00,0x00,0x3E,0x00,0x00,0x1F,0x00,0x00,0x07,0xC0,0x00,0x03,0xF0,0x01,0xC1,0xF8,0x00,0x7F,0xFE,0x00,0x3F,0xFF,0x00,0x07,0xFF,0x80,0x01,0xFF,0xC0,0x00,0x07,0xC0,0x00,0x00, // 'J'
	0x01,0x00,0x00,0x01,0xE0,0x08,0x01,0xF8,0x0E,0x00,0xFC,0x1F,0x80,0xFE,0x3F,0xE0,0x7E,0x3F,0xE0,0x3F,0x3F,0xE0,0x3F,0x7F,0xE0,0x1F,0xFF,0xC0,0x0F,0xFF,0xC0,0x0F,0xFF,0x80,0x07,0xFF,0x80,0x03,0xFF,0x80,0x03,0xFF,0xE0,0x01,0xFF,0xF8,0x00,0xFF,0xFF,0xF8,0xFF,0x9F,0xFE,0x7F,0x87,0xFF,0xBF,0x81,0xFF,0x8F,0x80,0x3F,0xC7,0xC0,0x01,0x81,0xC0,0x00,0x00, // 'K'
	0x06,0x00,0x00,0xF8,0x00,0x1F,0x00,0x07,0xE0,0x00,0xFC,0x00,0x1F,0x00,0x07,0xE0,0x00,0xFC,0x00,0x1F,0x00,0x07,0xE0,0x00,0xFC,0x00,0x1F,0x00,0x07,0xE0,0x00,0xF8,0x00,0x1F,0x00,0x07,0xE0,0x00,0xFC,0xFE,0x1F,0xFF,0xF1,0xFF,0xFF,0x3F,0xFF,0xE7,0xFF,0xFC,0x7F,0x00,0x00, // 'L'
	0x00,0xC0,0x00,0x00,0x07,0x80,0x03,0x80,0x1F,0x80,0x1F,0x00,0xFE,0x00,0xFC,0x07,0xFC,0x07,0xF8,0x1F,0xF0,0x3F,0xE0,0xFF,0xC1,0xFF,0x83,0xFF,0x1F,0xFC,0x1F,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xC1,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF,0x7C,0x3F,0x7F,0xF3,0xF1,0xF9,0xFF,0x0F,0xC7,0xE3,0xF0,0x3E,0x3F,0x80,0x00,0xF8,0xFC,0x00,0x03,0xE3,0xF0,0x00,0x1F,0x8F,0x80,0x00,0x7C,0x3E,0x00,0x00,0xF0,0x78,0x00,0x03,0x81,0xC0,0x00,0x04,0x00, // 'M'
	0x01,0x00,0x40,0x07,0x03,0x80,0x3E,0x0F,0x00,0xF8,0x3E,0x07,0xF1,0xF8,0x1F,0xC7,0xE0,0xFF,0x1F,0x03,0xF8,0x7C,0x1F,0xE1,0xF0,0x7F,0x8F,0xC3,0xFE,0x3E,0x0F,0xF8,0xF8,0x7F,0xE7,0xE1,0xFF,0xBF,0x8F,0xFF,0xFE,0x3F,0xFF,0xF0,0xFE,0xFF,0xC3,0xF3,0xFE,0x0F,0x87,0xF8,0x1E,0x0F,0xC0,0x78,0x1E,0x00,0xC0,0x00,0x00, // 'N'
	0x00,0x07,0x00,0x00,0x7E,0x00,0x03,0xF8,0x00,0x1F,0xF0,0x00,0xFF,0x80,0x07,0xFE,0x00,0x7F,0xFC,0x03,0xFF,0xF0,0x0F,0xE3,0xE0,0x7F,0x07,0x83,0xF8,0x1F,0x0F,0x80,0x3C,0x7E,0x00,0xF9,0xF0,0x01,0xEF,0xC0,0x0F,0xBE,0x00,0xFE,0xF8,0x1F,0xFB,0xFF,0xFF,0xE7,0xFF,0xFF,0x1F,0xFF,0xF0,0x3F,0xFF,0x00,0x7F,0xE0,0x00, // 'O'
	0x00,0xFE,0x00,0x1F,0xF8,0x07,0xFF,0x80,0x7F,0xFC,0x0F,0xFF,0xC0,0xFF,0xFE,0x1F,0x03,0xE1,0xF0,0x3E,0x7E,0x1F,0xE7,0xFF,0xFE,0xFF,0xFF,0xCF,0xFF,0xF8,0xFF,0xFF,0x0F,0xFF,0xC0,0x7F,0xC0,0x07,0xC0,0x00,0x7C,0x00,0x07,0xC0,0x00,0x7C,0x00,0x0F,0xC0,0x00,0xF8,0x00,0x07,0x80,0x00, // 'P'
	0x00,0x1E,0x00,0x00,0x3F,0x00,0x00,0x7F,0x00,0x01,0xFE,0x00,0x07,0xFE,0x00,0x1F,0xFC,0x00,0x7F,0xFC,0x03,0xFC,0x78,0x0F,0xF0,0xF8,0x3F,0xC0,0xF0,0xFE,0x01,0xF3,0xF9,0xE3,0xE7,0xE3,0xE7,0xDF,0x87,0xFF,0x3E,0x07,0xFE,0x7C,0x07,0xFC,0xF0,0x7F,0xF1,0xFF,0xFF,0xC3,0xFF,0xFF,0x87,0xFF,0xFF,0x07,0xFF,0xDF,0x03,0xFC,0x3E,0x00,0x00,0x3C,0x00,0x00,0x30, // 'Q'
	0x00,0x30,0x00,0x03,0xE0,0x00,0x3F,0x80,0x03,0xFE,0x00,0x3F,0xF0,0x03,0xFF,0xC0,0x7F,0x7E,0x03,0xF1,0xF0,0x3F,0x07,0xC1,0xF8,0xFE,0x0F,0xFF,0xE0,0x7F,0xFF,0x07,0xFF,0xF0,0x3F,0xFE,0x01,0xFF,0x80,0x0F,0xF8,0x00,0x7F,0xE0,0x03,0xFF,0xE0,0x3E,0xFF,0xF8,0xF3,0xFF,0xC7,0x87,0xFE,0x38,0x0F,0xF8,0x00,0x0F,0x80, // 'R'
	0x00,0x0F,0xC0,0x01,0xFF,0x80,0x7F,0xFF,0x07,0xFF,0xFC,0x3F,0xFF,0xF9,0xFF,0xCC,0x8F,0xF8,0x00,0x3F,0xF0,0x00,0xFF,0xF0,0x01,0xFF,0xE0,0x03,0xFF,0x80,0x00,0x3F,0x00,0x00,0x1E,0x00,0x00,0x78,0x00,0x03,0xE0,0x00,0x1F,0x80,0x01,0xFC,0x00,0x3F,0xF0,0x03,0xFF,0x80,0x0F,0xFC,0x00,0x3F,0xC0,0x00,0xFC,0x00,0x00, // 'S'
	0x00,0x21,0xF8,0x03,0xFF,0xFC,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFF,0xFE,0x7F,0xFC,0x00,0x3E,0xF8,0x00,0x00,0xF8,0x00,0x01,0xF0,0x00,0x01,0xF0,0x00,0x03,0xF0,0x00,0x03,0xE0,0x00,0x07,0xE0,0x00,0x07,0xC0,0x00,0x07,0xC0,0x00,0x0F,0x80,0x00,0x0F,0x80,0x00,0x0F,0x80,0x00,0x0F,0x00,0x00,0x07,0x80,0x00,0x07,0xC0,0x00,0x03,0xC0,0x00,0x01,0x00,0x00, // 'T'
	0x00,0x00,0x80,0x00,0x06,0x00,0x00,0x30,0xC0,0x03,0xC7,0x00,0x1E,0x78,0x00,0xF3,0xE0,0x0F,0xDF,0x00,0x7C,0xF8,0x03,0xE7,0xC0,0x3F,0x3E,0x01,0xF9,0xF0,0x1F,0x8F,0x81,0xFC,0x7C,0x1F,0xC3,0xE3,0xFC,0x1F,0xFF,0xC0,0xFF,0xFC,0x07,0xFF,0xC0,0x1F,0xFE,0x00,0xFF,0xC0,0x03,0xFC,0x00,0x0F,0x00,0x00, // 'U'
	0x40,0x03,0x1C,0x00,0xF3,0xC0,0x3F,0x78,0x07,0xEF,0x81,0xF9,0xF0,0x7F,0x3E,0x1F,0xC7,0xC3,0xF0,0xF8,0xFC,0x1F,0x3F,0x83,0xF7,0xE0,0x7F,0xF8,0x07,0xFE,0x00,0xFF,0xC0,0x1F,0xF0,0x03,0xFE,0x00,0x7F,0x80,0x0F,0xF0,0x00,0xFC,0x00,0x1F,0x00,0x03,0xE0,0x00,0x38,0x00,0x00, // 'V'
	0x00,0x00,0x00,0x10,0x1C,0x00,0x00,0x70,0x38,0x02,0x00,0xE0,0xF8,0x0E,0x03,0xE1,0xF0,0x3E,0x07,0xC7,0xE0,0x7C,0x1F,0x8F,0xC1,0xF8,0x3F,0x3F,0x07,0xF0,0x7C,0x7E,0x0F,0xE1,0xF8,0xF8,0x3F,0xC3,0xE1,0xF0,0x7F,0x0F,0xC7,0xE1,0xFE,0x1F,0x8F,0xC7,0xFC,0x7E,0x1F,0x1F,0xF8,0xFC,0x3E,0x7F,0xF7,0xF0,0x7D,0xFF,0xFF,0xE0,0xFF,0xFB,0xFF,0x81,0xFF,0xE3,0xFF,0x01,0xFF,0x87,0xFC,0x03,0xFE,0x07,0xF0,0x03,0xF8,0x07,0xC0,0x01,0x80,0x0F,0x00,0x00, // 'W'
	0x0E,0x00,0x30,0x3E,0x01,0xF0,0x3E,0x07,0xE0,0xFE,0x1F,0xE0,0xFE,0xFF,0x81,0xFF,0xFE,0x01,0xFF,0xF0,0x01,0xFF,0xC0,0x01,0xFE,0x00,0x03,0xF8,0x00,0x1F,0xF0,0x00,0x3F,0xE0,0x00,0xFF,0xE0,0x03,0xFF,0xE0,0x0F,0xEF,0xC0,0x3F,0x8F,0xC0,0x7E,0x0F,0x80,0xF8,0x1F,0x81,0xE0,0x1F,0x03,0xC0,0x3C,0x07,0x00,0x38,0x06,0x00,0x00,0x00, // 'X'
	0x60,0x06,0x1E,0x07,0xC7,0x81,0xF9,0xF0,0xFE,0x7C,0x7F,0x1F,0x3F,0x87,0xCF,0xC0,0xF7,0xE0,0x3F,0xF0,0x0F,0xFC,0x03,0xFE,0x00,0x7F,0x80,0x0F,0xC0,0x07,0xE0,0x01,0xF8,0x00,0xFC,0x00,0x3F,0x00,0x1F,0x80,0x07,0xE0,0x03,0xF0,0x00,0xF8,0x00,0x1E,0x00,0x03,0x00,0x00, // 'Y'
	0x00,0x80,0x00,0x3F,0xFF,0xC0,0xFF,0xFF,0x01,0xFF,0xFE,0x07,0xFF,0xF8,0x0F,0x9F,0xC0,0x00,0xFE,0x00,0x0F,0xF0,0x00,0x7F,0x80,0x03,0xFC,0x00,0x3F,0xE0,0x01,0xFF,0x00,0x1F,0xF0,0x00,0xFF,0x80,0x07,0xF8,0x00,0x3F,0xC0,0x60,0xFE,0x0F,0xC3,0xF1,0xFF,0x8F,0xFF,0xFE,0x3F,0xFF,0xE0,0xFF,0xFE,0x01,0xFF,0xC0,0x03,0xF8,0x00,0x00, // 'Z'
	0x00,0x3F,0xF0,0x03,0xFF,0xF0,0x07,0xFF,0xF0,0x0F,0xFF,0xE0,0x1F,0xC0,0x00,0x3C,0x00,0x00,0xF8,0x00,0x01,0xF0,0x00,0x03,0xC0,0x00,0x07,0x80,0x00,0x1F,0x00,0x00,0x3E,0x00,0x00,0x78,0x00,0x00,0xF0,0x00,0x03,0xE0,0x00,0x07,0xC0,0x00,0x0F,0x00,0x00,0x3E,0x00,0x00,0x7C,0x00,0x00,0xF8,0x00,0x01,0xE0,0x00,0x07,0xC0,0x00,0x0F,0x80,0x00,0x1E,0x00,0x00,0x7C,0x00,0x00,0xF8,0x00,0x01,0xF0,0x00,0x03,0xFF,0xC0,0x0F,0xFF,0xC0,0x1F,0xFF,0x80,0x1F,0xFE,0x00,0x38,0x00,0x00, // '['
	0xC0,0xE0,0xF0,0xF0,0xF0,0xF0,0x70,0x70,0x78,0x78,0x78,0x78,0x38,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x1E,0x1C,0x0C, // '\'
	0x00,0xFF,0xE0,0x0F,0xFF,0x80,0x7F,0xFC,0x03,0xFF,0xE0,0x1E,0x0F,0x00,0x00,0xF8,0x00,0x07,0xC0,0x00,0x3C,0x00,0x01,0xE0,0x00,0x1F,0x00,0x00,0xF8,0x00,0x07,0x80,0x00,0x3C,0x00,0x03,0xE0,0x00,0x1F,0x00,0x00,0xF0,0x00,0x07,0x80,0x00,0x7C,0x00,0x03,0xE0,0x00,0x1E,0x00,0x01,0xF0,0x00,0x0F,0x80,0x00,0x78,0x00,0x07,0xC0,0x00,0x3E,0x00,0x01,0xF0,0x00,0x0F,0x00,0xFF,0xF8,0x0F,0xFF,0xC0,0x7F,0xFC,0x03,0xFF,0xC0,0x0E,0x00,0x00, // ']'
	0x00,0x00,0x00,0xC0,0x03,0xC0,0x07,0x80,0x1F,0x80,0x3F,0x00,0xFE,0x03,0xFC,0x07,0xF8,0x1F,0xF0,0x7D,0xF1,0xF1,0xC3,0xE3,0x8F,0x87,0xBE,0x0F,0x7C,0x0E,0xF0,0x1C,0xC0,0x10, // '^'
	0x03,0xFF,0x80,0x7F,0xFF,0xFE,0x3F,0xFF,0xFF,0xCF,0xFF,0xFF,0xE3,0xF0,0x00,0x00, // '_'
	0x60,0x3C,0x0F,0x83,0xF0,0x7E,0x0F,0xC0,0xF8,0x1C,0x01,0x00, // '`'
	0x00,0x30,0x00,0x07,0xC0,0x00,0x7C,0x00,0x3F,0xC0,0x07,0xFC,0x00,0x7F,0xC0,0x0F,0xFE,0x00,0xF9,0xE0,0x0F,0x9E,0x01,0xF1,0xF8,0x1E,0xFF,0xE3,0xFF,0xFC,0x3F,0xFF,0x87,0xDF,0xF0,0x78,0x0F,0x8F,0x83,0xF8,0x78,0x1F,0x07,0x00,0xE0, // 'a'
	0x03,0xFC,0x0F,0xFF,0x87,0xFF,0xF3,0xFF,0x3E,0x7E,0x1F,0x1D,0xCF,0xC0,0x7F,0xE0,0x3F,0xF0,0x0F,0xFC,0x03,0xFF,0x80,0xFC,0xF0,0x7C,0x0E,0x1E,0x0F,0x87,0x87,0xE3,0xEF,0xF8,0xFF,0xFC,0x3F,0xFC,0x07,0xFC,0x00,0x98,0x00, // 'b'
	0x00,0x18,0x00,0x7C,0x01,0xFE,0x07,0xFE,0x0F,0xFC,0x1F,0xF0,0x3F,0x80,0x7F,0x00,0xFC,0x00,0xF8,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0x7C,0x00,0x7F,0xF8,0x3F,0xFC,0x1F,0xFC,0x07,0xF8, // 'c'
	0x30,0x00,0x78,0x00,0xFC,0x01,0xFE,0x07,0xFE,0x07,0x3E,0x0E,0x1E,0x1C,0x1E,0x38,0x1C,0x70,0x38,0xE0,0xF3,0xC7,0xE7,0xBF,0x8F,0xFE,0x3F,0xF8,0x3F,0xC0,0x7E,0x00,0xF0,0x00, // 'd'
	0x00,0x0E,0x01,0xFF,0x87,0xFF,0xC7,0xFF,0xE3,0xFF,0x81,0xFC,0x00,0x78,0x00,0x3F,0xE0,0x3F,0xF8,0x1F,0xFE,0x1F,0xFC,0x0F,0x80,0x0F,0x80,0x07,0xC0,0xC3,0xFF,0xF8,0xFF,0xFC,0x7F,0xFC,0x1F,0xF8,0x00, // 'e'
	0x00,0x1F,0x80,0x1F,0xFC,0x0F,0xFF,0xE3,0xFF,0xFC,0x3F,0xC0,0x01,0xF8,0x00,0x0F,0x80,0x00,0xF0,0x00,0x0F,0x04,0x07,0xFF,0xC0,0xFF,0xFE,0x07,0xFF,0xC0,0x7F,0xC0,0x03,0xC0,0x00,0x38,0x00,0x07,0x80,0x00,0x38,0x00,0x03,0x80,0x00, // 'f'
	0x00,0x08,0x00,0x00,0xF8,0x00,0x0F,0xF0,0x00,0x7F,0xC0,0x03,0xFC,0x00,0x1F,0xC0,0x01,0xFE,0x00,0x0F,0xE0,0x80,0x3F,0x0F,0x01,0xF8,0x3F,0x07,0xC0,0xFE,0x3E,0x01,0xFE,0xF0,0x07,0xFB,0xC3,0xFF,0xCF,0xFF,0xFE,0x1F,0xFF,0xE0,0x7F,0xFC,0x00,0x7F,0x80,0x00, // 'g'
	0x08,0x06,0x06,0x01,0x81,0x80,0x70,0xF0,0x1E,0x3E,0x0F,0x8F,0x83,0xE3,0xC0,0xF8,0xF0,0x3E,0x3C,0x0F,0x8F,0x1F,0xC7,0xFF,0xF1,0xFF,0xFC,0x7F,0xFE,0x3F,0xEF,0x8F,0xE3,0xE3,0xE0,0xF8,0xF8,0x1E,0x3C,0x07,0x00, // 'h'
	0x18,0x70,0xF1,0xE7,0xCF,0x9E,0x3C,0xF9,0xF3,0xC7,0x8F,0x1E,0x3C,0x78,0xF0,0xE0, // 'i'
	0x00,0x0F,0x80,0x7F,0xFF,0xC1,0xFF,0xFF,0x87,0xFF,0xFE,0x1F,0xFE,0x00,0x20,0x78,0x00,0x01,0xE0,0x00,0x0F,0x80,0x00,0x3C,0x00,0x00,0xF0,0x00,0x03,0xC0,0x00,0x1F,0x00,0x00,0x78,0x01,0x83,0xE0,0x07,0xFF,0x00,0x3F,0xFC,0x00,0x7F,0xE0,0x00,0xFE,0x00,0x00, // 'j'
	0x07,0x00,0x00,0x3C,0x0C,0x03,0xE0,0xF0,0x1F,0x1F,0xC1,0xF9,0xFE,0x0F,0x9F,0xC0,0x7F,0xFC,0x07,0xFF,0x80,0x3F,0xF8,0x01,0xFF,0x80,0x1F,0xF8,0x00,0xFF,0xE0,0x07,0xFF,0xE4,0x7F,0x3F,0xF3,0xF0,0xFF,0xCF,0x83,0xFE,0x78,0x03,0xC3,0x80,0x00,0x00, // 'k'
	0x0E,0x00,0x0F,0x00,0x0F,0x80,0x1F,0x00,0x1F,0x00,0x1E,0x00,0x3E,0x00,0x3E,0x00,0x3C,0x00,0x7C,0x00,0x7C,0x00,0x78,0x00,0xF8,0x00,0xF9,0xF8,0xFF,0xFE,0x7F,0xFE,0x7F,0xFE,0x3F,0x08, // 'l'
	0x01,0x80,0x08,0x01,0xE0,0x0E,0x01,0xF8,0x07,0x80,0xFE,0x07,0xE0,0xFF,0x0F,0xF0,0x7F,0x8F,0xF8,0x7F,0xCF,0xFC,0x3F,0xFF,0xFC,0x3F,0xFF,0xFE,0x1F,0xFF,0xEF,0x1F,0x7F,0xC7,0x8F,0x9F,0xC7,0xCF,0xC2,0x03,0xE7,0xC0,0x01,0xF3,0xE0,0x00,0xF1,0xE0,0x00,0x78,0xF0,0x00,0x38,0x38,0x00,0x08,0x08,0x00,0x00,0x00, // 'm'
	0x02,0x02,0x00,0xF0,0x70,0x1E,0x1E,0x07,0xE3,0xE0,0xFC,0x78,0x3F,0x1F,0x07,0xE3,0xE1,0xFC,0x78,0x3F,0x8F,0x0F,0xF3,0xE1,0xFE,0x7C,0x7F,0xDF,0x8F,0xFF,0xE1,0xF7,0xFC,0x3E,0x7F,0x07,0x87,0xE0,0x70,0x78,0x0E,0x04,0x00, // 'n'
	0x00,0x18,0x00,0x0F,0xC0,0x03,0xF8,0x00,0xFE,0x00,0x7F,0xE0,0x1F,0xFC,0x07,0xFB,0xC0,0xFC,0x78,0x3E,0x07,0x8F,0x80,0xF1,0xF0,0x0E,0x3C,0x01,0xEF,0x00,0xFD,0xE0,0x7F,0xBF,0xFF,0xE3,0xFF,0xF8,0x7F,0xFE,0x03,0xFE,0x00, // 'o'
	0x03,0xF8,0x03,0xFE,0x03,0xFF,0x83,0xFF,0xC1,0xFF,0xE1,0xE0,0x79,0xF0,0xFC,0xFF,0xFE,0xFF,0xFE,0x7F,0xFE,0x3F,0xFE,0x1F,0xF8,0x07,0x80,0x07,0xC0,0x03,0xE0,0x01,0xF0,0x00,0xF0,0x00,0x78,0x00,0x10,0x00,0x00, // 'p'
	0x00,0x78,0x00,0x0F,0x80,0x01,0xF8,0x00,0x7F,0x00,0x3F,0xF0,0x0F,0xFF,0x03,0xF9,0xE0,0xFC,0x1E,0x3F,0x03,0xCF,0xCE,0x7B,0xF3,0xEF,0x7C,0x3F,0xEF,0x03,0xF9,0xE1,0xFF,0x3F,0xFF,0xC7,0xFF,0xF8,0x7F,0xFF,0x07,0xF8,0xF0,0x20,0x1E,0x00,0x01,0x80, // 'q'
	0x00,0xE0,0x00,0xF8,0x00,0xFE,0x00,0xFF,0x80,0xFF,0xC1,0xF9,0xE0,0xF8,0xF8,0x7C,0x7C,0x3D,0xFE,0x3F,0xFE,0x1F,0xFE,0x0F,0xF8,0x07,0xF0,0x03,0xFC,0x03,0xFF,0xC1,0xFF,0xFE,0x71,0xFF,0x38,0x3F,0x80,0x07,0xC0, // 'r'
	0x00,0x7F,0x00,0xFF,0xC1,0xFF,0xF9,0xFF,0xFE,0x7F,0xD1,0x3F,0x80,0x0F,0xF8,0x01,0xFF,0x80,0x3F,0xE0,0x00,0x7C,0x00,0x07,0x00,0x01,0xE0,0x00,0xF0,0x00,0xFC,0x03,0xFE,0x01,0xFF,0x00,0x7F,0x80,0x0F,0x80,0x00, // 's'
	0x00,0xBF,0xC7,0xFF,0xFF,0x3F,0xFF,0xF9,0xFF,0xFF,0xC7,0xFE,0x00,0x00,0xF0,0x00,0x0F,0x80,0x00,0x78,0x00,0x07,0xC0,0x00,0x3C,0x00,0x03,0xE0,0x00,0x1E,0x00,0x00,0xF0,0x00,0x07,0x00,0x00,0x38,0x00,0x01,0xC0,0x00,0x0F,0x00,0x00,0x78,0x00,0x00,0x80,0x00, // 't'
	0x00,0x04,0x00,0x03,0x10,0x03,0xDC,0x01,0xEF,0x00,0xF7,0x80,0x7B,0xC0,0x3D,0xE0,0x3E,0xF0,0x1E,0x78,0x1F,0x3C,0x1F,0x1E,0x3F,0x8F,0xFF,0x87,0xFF,0x83,0xFF,0x80,0xFF,0x80,0x7F,0x80,0x1F,0x00,0x00, // 'u'
	0x40,0x0C,0xC0,0x1C,0xE0,0x3E,0xF0,0x7C,0xF0,0xFC,0xF0,0xF8,0xF1,0xF0,0xFB,0xF0,0xFB,0xE0,0xFF,0xC0,0x7F,0x80,0x7F,0x80,0x7F,0x00,0x7F,0x00,0x7E,0x00,0x7C,0x00,0x3C,0x00,0x1C,0x00,0x00,0x00, // 'v'
	0x08,0x00,0x02,0x07,0x00,0x01,0xC1,0xE0,0x60,0x78,0xF8,0x38,0x1E,0x3C,0x1F,0x0F,0x9F,0x07,0xC3,0xE7,0xC3,0xF1,0xF1,0xE1,0xF8,0x7C,0x78,0x7E,0x1E,0x3E,0x3F,0x8F,0x8F,0x9F,0xE7,0xC3,0xC7,0xF9,0xF0,0xF7,0xFF,0xFC,0x3F,0xFB,0xFE,0x0F,0xFC,0xFF,0x01,0xFE,0x1F,0xC0,0x7F,0x03,0xE0,0x0F,0x00,0xF0,0x00, // 'w'
	0x10,0x00,0x03,0x80,0x70,0x78,0x1F,0x0F,0x87,0xE1,0xFB,0xF8,0x1F,0xFE,0x01,0xFF,0x80,0x3F,0xC0,0x03,0xF0,0x01,0xFE,0x00,0x3F,0xC0,0x0F,0xFC,0x03,0xF7,0xC0,0xFC,0xF8,0x1F,0x0F,0x83,0xC1,0xF0,0x70,0x1E,0x0E,0x01,0x80,0x80,0x00,0x00, // 'x'
	0x60,0x38,0xE0,0xF9,0xE3,0xF3,0xC7,0xE7,0x9F,0x0F,0x7E,0x1F,0xF8,0x1F,0xE0,0x3F,0x80,0x7F,0x00,0x7C,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x1F,0x00,0x3C,0x00,0xF8,0x00,0xE0,0x01,0xC0,0x00, // 'y'
	0x0F,0xFA,0x03,0xFF,0xC0,0xFF,0xF8,0x3F,0xFE,0x07,0x3F,0x80,0x1F,0xC0,0x0F,0xC0,0x07,0xE0,0x07,0xF0,0x03,0xF8,0x03,0xFC,0x01,0xFC,0x00,0xFE,0x00,0x3E,0x0F,0x8F,0x9F,0xF3,0xFF,0xF8,0xFF,0xFC,0x1F,0xF8,0x03,0xF0,0x00, // 'z'
	0x00,0x0F,0xFC,0x00,0x7F,0xFF,0x00,0x1F,0xFF,0xC0,0x0F,0xFF,0xC0,0x07,0xE0,0x00,0x07,0xC0,0x00,0x03,0xE0,0x00,0x01,0xE0,0x00,0x00,0xF0,0x00,0x00,0xF8,0x00,0x00,0x7C,0x00,0x00,0xFC,0x00,0x01,0xFE,0x00,0x03,0xFE,0x00,0x01,0xFC,0x00,0x00,0xFC,0x00,0x00,0x7F,0x00,0x00,0x1F,0xE0,0x00,0x07,0xF0,0x00,0x00,0xF0,0x00,0x00,0xF8,0x00,0x00,0x7C,0x00,0x00,0x3C,0x00,0x00,0x3E,0x00,0x00,0x1F,0x00,0x00,0x0F,0x80,0x00,0x07,0x80,0x00,0x07,0xFF,0xC0,0x03,0xFF,0xF0,0x01,0xFF,0xF0,0x00,0xFF,0xF0,0x00,0x38,0x00,0x00, // '{'
	0x01,0x80,0x30,0x0F,0x01,0xE0,0x3C,0x0F,0x01,0xE0,0x3C,0x0F,0x01,0xE0,0x38,0x0F,0x01,0xE0,0x3C,0x0F,0x01,0xE0,0x3C,0x0F,0x03,0xE0,0x78,0x0F,0x01,0xE0,0x08,0x00, // '|'
	0x00,0x7F,0xF0,0x01,0xFF,0xF8,0x00,0xFF,0xF8,0x01,0xFF,0xF8,0x00,0xF0,0xF8,0x00,0x00,0xF0,0x00,0x00,0xF0,0x00,0x00,0xF0,0x00,0x01,0xF0,0x00,0x01,0xF0,0x00,0x01,0xE0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x03,0xF0,0x00,0x03,0xF8,0x00,0x01,0xFC,0x00,0x00,0x7E,0x00,0x01,0xFE,0x00,0x07,0xFE,0x00,0x0F,0xF0,0x00,0x0F,0xC0,0x00,0x0F,0x80,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x3F,0xFE,0x00,0xFF,0xFC,0x00,0xFF,0xFC,0x00,0x7F,0xF8,0x00,0x78,0x00,0x00 // '}'
};
const GFXglyph Permanent_Marker_Regular_30Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,  12,    0,    0 }, // ' '
	  {     1,   9,  23,   9,    0,  -22 }, // '!'
	  {    27,  15,  14,  16,    2,  -22 }, // '"'
	  {    54,  22,  22,  22,    1,  -22 }, // '#'
	  {   115,  17,  23,  16,    1,  -22 }, // '$'
	  {   164,  20,  21,  20,    1,  -21 }, // '%'
	  {   217,  18,  16,  19,    0,  -17 }, // '&'
	  {   253,   8,  14,   9,    2,  -22 }, // '''
	  {   267,  14,  30,  12,    1,  -25 }, // '('
	  {   320,  15,  30,  12,   -4,  -25 }, // ')'
	  {   377,  20,  15,  21,    2,  -22 }, // '*'
	  {   415,  17,  15,  18,    0,  -16 }, // '+'
	  {   447,   8,   9,   7,   -3,   -4 }, // ','
	  {   456,  16,   5,  19,    1,  -10 }, // '-'
	  {   466,   6,   6,   8,   -1,   -5 }, // '.'
	  {   471,  16,  22,  13,   -1,  -22 }, // '/'
	  {   515,  20,  24,  22,    0,  -23 }, // '0'
	  {   575,   8,  22,  11,    1,  -22 }, // '1'
	  {   597,  20,  22,  21,    2,  -22 }, // '2'
	  {   652,  18,  22,  18,    0,  -22 }, // '3'
	  {   702,  17,  24,  18,    1,  -23 }, // '4'
	  {   753,  20,  22,  18,    1,  -22 }, // '5'
	  {   808,  15,  23,  16,    0,  -22 }, // '6'
	  {   852,  20,  22,  18,    0,  -22 }, // '7'
	  {   907,  17,  22,  17,    2,  -22 }, // '8'
	  {   954,  16,  22,  17,    1,  -22 }, // '9'
	  {   998,   8,  14,   8,   -1,  -13 }, // ':'
	  {  1012,  10,  18,   8,   -3,  -13 }, // ';'
	  {  1035,  19,  13,  20,    0,  -14 }, // '<'
	  {  1066,  18,  10,  19,    0,  -13 }, // '='
	  {  1089,  19,  13,  20,   -1,  -14 }, // '>'
	  {  1120,  18,  23,  18,    1,  -22 }, // '?'
	  {  1172,  22,  23,  23,    0,  -22 }, // '@'
	  {  1236,  23,  22,  22,   -1,  -22 }, // 'A'
	  {  1300,  22,  23,  22,   -1,  -22 }, // 'B'
	  {  1364,  19,  22,  19,    0,  -22 }, // 'C'
	  {  1417,  18,  22,  19,    0,  -22 }, // 'D'
	  {  1467,  21,  22,  20,    0,  -22 }, // 'E'
	  {  1525,  23,  22,  18,   -1,  -22 }, // 'F'
	  {  1589,  26,  22,  25,    0,  -22 }, // 'G'
	  {  1661,  21,  22,  22,    0,  -22 }, // 'H'
	  {  1719,  21,  22,  16,   -1,  -22 }, // 'I'
	  {  1777,  26,  21,  21,   -1,  -21 }, // 'J'
	  {  1846,  25,  22,  24,    0,  -22 }, // 'K'
	  {  1915,  19,  22,  20,    0,  -22 }, // 'L'
	  {  1968,  30,  22,  30,    0,  -22 }, // 'M'
	  {  2051,  22,  22,  22,    0,  -22 }, // 'N'
	  {  2112,  22,  22,  23,    0,  -22 }, // 'O'
	  {  2173,  20,  22,  20,    1,  -22 }, // 'P'
	  {  2228,  23,  24,  23,    0,  -22 }, // 'Q'
	  {  2297,  21,  23,  20,    0,  -22 }, // 'R'
	  {  2358,  22,  22,  18,    0,  -22 }, // 'S'
	  {  2419,  24,  23,  19,    0,  -22 }, // 'T'
	  {  2488,  21,  22,  22,    2,  -22 }, // 'U'
	  {  2546,  19,  22,  19,    2,  -22 }, // 'V'
	  {  2599,  31,  22,  31,    1,  -22 }, // 'W'
	  {  2685,  23,  22,  20,   -1,  -21 }, // 'X'
	  {  2749,  18,  23,  16,    1,  -22 }, // 'Y'
	  {  2801,  22,  23,  21,    0,  -22 }, // 'Z'
	  {  2865,  23,  32,  13,   -1,  -27 }, // '['
	  {  2957,   8,  23,  12,    2,  -22 }, // '\'
	  {  2980,  21,  32,  13,   -8,  -27 }, // ']'
	  {  3064,  15,  18,  17,    0,  -23 }, // '^'
	  {  3098,  25,   5,  22,   -3,   -4 }, // '_'
	  {  3114,  10,   9,  24,    9,  -22 }, // '`'
	  {  3126,  20,  18,  18,   -1,  -18 }, // 'a'
	  {  3171,  18,  19,  18,   -1,  -18 }, // 'b'
	  {  3214,  16,  18,  16,    0,  -18 }, // 'c'
	  {  3250,  15,  18,  16,    0,  -18 }, // 'd'
	  {  3284,  17,  18,  17,    0,  -18 }, // 'e'
	  {  3323,  20,  18,  15,   -1,  -18 }, // 'f'
	  {  3368,  22,  18,  21,    0,  -18 }, // 'g'
	  {  3418,  18,  18,  18,    0,  -18 }, // 'h'
	  {  3459,   7,  18,  11,    2,  -18 }, // 'i'
	  {  3475,  22,  18,  17,   -1,  -18 }, // 'j'
	  {  3525,  21,  18,  20,    0,  -18 }, // 'k'
	  {  3573,  16,  18,  17,    0,  -18 }, // 'l'
	  {  3609,  25,  19,  25,    0,  -18 }, // 'm'
	  {  3669,  19,  18,  18,    0,  -18 }, // 'n'
	  {  3712,  19,  18,  20,    0,  -18 }, // 'o'
	  {  3755,  17,  19,  17,    1,  -18 }, // 'p'
	  {  3796,  19,  20,  20,    0,  -18 }, // 'q'
	  {  3844,  17,  19,  17,    0,  -18 }, // 'r'
	  {  3885,  18,  18,  15,    0,  -18 }, // 's'
	  {  3926,  21,  19,  15,    0,  -18 }, // 't'
	  {  3976,  17,  18,  19,    2,  -18 }, // 'u'
	  {  4015,  16,  19,  16,    2,  -18 }, // 'v'
	  {  4053,  26,  18,  26,    1,  -18 }, // 'w'
	  {  4112,  19,  19,  16,   -1,  -18 }, // 'x'
	  {  4158,  15,  19,  13,    1,  -18 }, // 'y'
	  {  4194,  18,  19,  17,    0,  -18 }, // 'z'
	  {  4237,  25,  32,  14,    0,  -27 }, // '{'
	  {  4337,  11,  23,  11,    0,  -22 }, // '|'
	  {  4369,  24,  32,  15,   -9,  -27 } // '}'
};
const GFXfont Permanent_Marker_Regular_30 PROGMEM = {
(uint8_t  *)Permanent_Marker_Regular_30Bitmaps,(GFXglyph *)Permanent_Marker_Regular_30Glyphs,0x20, 0x7E, 45};
