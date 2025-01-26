#pragma once

/*
	Copyright 2001, 2002 Georges Menie (www.menie.org)
	stdarg version contributed by Christian Ettinger

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Changes for the FreeRTOS ports:

	- The dot in "%-8.8s"
	- The specifiers 'l' (long) and 'L' (long long)
	- The specifier 'u' for unsigned
	- Dot notation for IP addresses:
	  sprintf("IP = %xip\n", 0xC0A80164);
      will produce "IP = 192.168.1.100\n"
*/

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <freertos/FreeRTOS.h>

#define PAD_RIGHT 1
#define PAD_ZERO 2

/* You can define you own version of this character-output function. */
void __attribute__((weak)) vOutputChar(char cChar, TickType_t xTicksToWait);

struct xPrintFlags
{
  int base;
  int width;
  int printLimit;
  unsigned
      pad : 8,
      letBase : 8,
      isSigned : 1,
      isNumber : 1,
      long32 : 1,
      long64 : 1;
};

struct SStringBuf
{
  char *str;
  const char *orgStr;
  const char *nulPos;
  int curLen;
  struct xPrintFlags flags;
};

void xstrbuf_init(struct SStringBuf *apStr, char *apBuf, const char *apMaxStr);
BaseType_t xstrbuf_printchar(struct SStringBuf *apStr, int c);
BaseType_t xstrbuf_printchar_inline(struct SStringBuf *apStr, int c);
int xi2hex(int aCh);

BaseType_t xprints(struct SStringBuf *apBuf, const char *apString);

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12 /* to print 4294967296 */

#if CONFIG_SPRINTF_LONG_LONG
BaseType_t x_printll(struct SStringBuf *apBuf, long long i);
#endif

BaseType_t xprinti(struct SStringBuf *apBuf, int i);
BaseType_t xprintIp(struct SStringBuf *apBuf, unsigned i);
void xprint(struct SStringBuf *apBuf, const char *format, va_list args);
int xprintf(const char *format, ...);
int xvsnprintf(char *apBuf, size_t aMaxLen, const char *apFmt, va_list args);
int xsnprintf(char *apBuf, size_t aMaxLen, const char *apFmt, ...);
int xsprintf(char *apBuf, const char *apFmt, ...);
int xvsprintf(char *apBuf, const char *apFmt, va_list args);
int xvprintf(const char* format, va_list args);
const char* xmksize(unsigned long long aSize, char *apBuf, int aLen);
