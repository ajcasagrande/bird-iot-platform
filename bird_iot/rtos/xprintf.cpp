/*
	Copyright 2001, 2002 Georges Menie (www.menie.org)
	stdarg version contributed by Christian Ettinger

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
*/
#include "xprintf.h"
#include "sdkconfig.h"
#if CONFIG_FORWARD_ESP_LOG_TO_WEBSOCKET
#include "streams/BufferedStreamJoiner.h"
#else
#include "HardwareSerial.h"
#endif

void __attribute__((weak)) vOutputChar(const char cChar) {
#if CONFIG_FORWARD_ESP_LOG_TO_WEBSOCKET
  BufferedStreamJoiner.write((uint8_t)cChar);
#else
  Serial.write(cChar);
#endif
}

void xstrbuf_init(struct SStringBuf *apStr, char *apBuf, const char *apMaxStr)
{
  apStr->str = apBuf;
  apStr->orgStr = apBuf;
  apStr->nulPos = apMaxStr - 1;
  apStr->curLen = 0;

  memset(&apStr->flags, '\0', sizeof apStr->flags);
}
/*-----------------------------------------------------------*/

BaseType_t xstrbuf_printchar(struct SStringBuf *apStr, int c)
{
  if (apStr->str == nullptr)
  {
    vOutputChar((char)c);
    apStr->curLen++;
    return pdTRUE;
  }
  if (apStr->str < apStr->nulPos)
  {
    *(apStr->str++) = c;
    apStr->curLen++;
    return pdTRUE;
  }
  if (apStr->str == apStr->nulPos)
  {
    *(apStr->str++) = '\0';
  }
  return pdFALSE;
}
/*-----------------------------------------------------------*/

BaseType_t __always_inline xstrbuf_printchar_inline(struct SStringBuf *apStr, int c)
{
  if (apStr->str == nullptr)
  {
    vOutputChar((char)c);
    if (c == 0)
    {
      return pdFALSE;
    }
    apStr->curLen++;
    return pdTRUE;
  }
  if (apStr->str < apStr->nulPos)
  {
    *(apStr->str++) = c;
    if (c == 0)
    {
      return pdFALSE;
    }
    apStr->curLen++;
    return pdTRUE;
  }
  if (apStr->str == apStr->nulPos)
  {
    *(apStr->str++) = '\0';
  }
  return pdFALSE;
}
/*-----------------------------------------------------------*/

int xi2hex(int aCh)
{
  int iResult;

  if (aCh < 10)
  {
    iResult = '0' + aCh;
  }
  else
  {
    iResult = 'A' + aCh - 10;
  }

  return iResult;
}
/*-----------------------------------------------------------*/

BaseType_t xprints(struct SStringBuf *apBuf, const char *apString)
{
  register int padchar = ' ';
  int i, len;

  if (apBuf->flags.width > 0)
  {
    register int len = 0;
    register const char *ptr;
    for (ptr = apString; *ptr; ++ptr)
    {
      ++len;
    }

    if (len >= apBuf->flags.width)
    {
      apBuf->flags.width = 0;
    }
    else
    {
      apBuf->flags.width -= len;
    }

    if (apBuf->flags.pad & PAD_ZERO)
    {
      padchar = '0';
    }
  }
  if ((apBuf->flags.pad & PAD_RIGHT) == 0)
  {
    for (; apBuf->flags.width > 0; --apBuf->flags.width)
    {
      if (xstrbuf_printchar(apBuf, padchar) == 0)
      {
        return pdFALSE;
      }
    }
  }
  if ((apBuf->flags.isNumber == pdTRUE) && (apBuf->flags.pad == pdTRUE))
  {
    /* The string to print represents an integer number.
		 * In this case, printLimit is the min number of digits to print
		 * If the length of the number to print is less than the min nb of i
		 * digits to display, we add 0 before printing the number
		 */
    len = strlen(apString);

    if (len < apBuf->flags.printLimit)
    {
      i = apBuf->flags.printLimit - len;
      for (; i; i--)
      {
        if (xstrbuf_printchar(apBuf, '0') == 0)
        {
          return pdFALSE;
        }
      }
    }
  }
  /* The string to print is not the result of a number conversion to ascii.
	 * For a string, printLimit is the max number of characters to display
	 */
  for (; apBuf->flags.printLimit && *apString; ++apString, --apBuf->flags.printLimit)
  {
    if (!xstrbuf_printchar(apBuf, *apString))
    {
      return pdFALSE;
    }
  }

  for (; apBuf->flags.width > 0; --apBuf->flags.width)
  {
    if (!xstrbuf_printchar(apBuf, padchar))
    {
      return pdFALSE;
    }
  }

  return pdTRUE;
}
/*-----------------------------------------------------------*/

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12 /* to print 4294967296 */

#if CONFIG_SPRINTF_LONG_LONG
BaseType_t xprintll(struct SStringBuf *apBuf, long long i)
{
  char print_buf[2 * PRINT_BUF_LEN];
  register char *s;
  register int t, neg = 0;
  register unsigned long long u = i;
  lldiv_t lldiv_result;

  /* typedef struct
 * {
 * 	long long int quot; // quotient
 * 	long long int rem;  // remainder
 * } lldiv_t;
 */

  apBuf->flags.isNumber = pdTRUE; /* Parameter for prints */
  if (i == 0LL)
  {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return xprints(apBuf, print_buf);
  }

  if ((apBuf->flags.isSigned == pdTRUE) && (apBuf->flags.base == 10) && (i < 0LL))
  {
    neg = 1;
    u = -i;
  }

  s = print_buf + sizeof print_buf - 1;

  *s = '\0';
  /* 18446744073709551616 */
  while (u != 0)
  {
    lldiv_result = lldiv(u, (unsigned long long)apBuf->flags.base);
    t = lldiv_result.rem;
    if (t >= 10)
    {
      t += apBuf->flags.letBase - '0' - 10;
    }
    *(--s) = t + '0';
    u = lldiv_result.quot;
  }

  if (neg != 0)
  {
    if ((apBuf->flags.width != 0) && (apBuf->flags.pad & PAD_ZERO))
    {
      if (!xstrbuf_printchar(apBuf, '-'))
      {
        return pdFALSE;
      }
      --apBuf->flags.width;
    }
    else
    {
      *(--s) = '-';
    }
  }

  return xprints(apBuf, s);
}
#endif /* CONFIG_SPRINTF_LONG_LONG */
/*-----------------------------------------------------------*/

BaseType_t xprinti(struct SStringBuf *apBuf, int i)
{
  char print_buf[PRINT_BUF_LEN];
  register char *s;
  register int t, neg = 0;
  register unsigned int u = i;
  register unsigned base = apBuf->flags.base;

  apBuf->flags.isNumber = pdTRUE; /* Parameter for xprints */

  if (i == 0)
  {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return xprints(apBuf, print_buf);
  }

  if ((apBuf->flags.isSigned == pdTRUE) && (base == 10) && (i < 0))
  {
    neg = 1;
    u = -i;
  }

  s = print_buf + sizeof print_buf - 1;

  *s = '\0';
  switch (base)
  {
  case 16:
    while (u != 0)
    {
      t = u & 0xF;
      if (t >= 10)
      {
        t += apBuf->flags.letBase - '0' - 10;
      }
      *(--s) = t + '0';
      u >>= 4;
    }
    break;

  case 8:
  case 10:
    /* GCC compiles very efficient */
    while (u)
    {
      t = u % base;
      *(--s) = t + '0';
      u /= base;
    }
    break;
    /*
	// The generic case, not yet in use
	default:
		while( u )
		{
			t = u % base;
			if( t >= 10)
			{
				t += apBuf->flags.letBase - '0' - 10;
			}
			*( --s ) = t + '0';
			u /= base;
		}
		break;
*/
  }

  if (neg != 0)
  {
    if (apBuf->flags.width && (apBuf->flags.pad & PAD_ZERO))
    {
      if (xstrbuf_printchar(apBuf, '-') == 0)
      {
        return pdFALSE;
      }
      --apBuf->flags.width;
    }
    else
    {
      *(--s) = '-';
    }
  }

  return xprints(apBuf, s);
}
/*-----------------------------------------------------------*/

BaseType_t xprintIp(struct SStringBuf *apBuf, unsigned i)
{
  char print_buf[16];

  xsprintf(print_buf, "%u.%u.%u.%u",
           i >> 24,
           (i >> 16) & 0xff,
           (i >> 8) & 0xff,
           i & 0xff);
  apBuf->flags.isNumber = pdTRUE; /* Parameter for xprints */
  xprints(apBuf, print_buf);

  return pdTRUE;
}
/*-----------------------------------------------------------*/

void xprint(struct SStringBuf *apBuf, const char *format, va_list args)
{
  char scr[2];

  for (;;)
  {
    int ch = *(format++);

    if (ch != '%')
    {
      do
      {
        /* Put the most like flow in a small loop */
        if (xstrbuf_printchar_inline(apBuf, ch) == 0)
        {
          return;
        }
        ch = *(format++);
      } while (ch != '%');
    }
    ch = *(format++);
    /* Now ch has character after '%', format pointing to next */

    if (ch == '\0')
    {
      break;
    }
    if (ch == '%')
    {
      if (xstrbuf_printchar(apBuf, ch) == 0)
      {
        return;
      }
      continue;
    }
    memset(&apBuf->flags, '\0', sizeof apBuf->flags);

    if (ch == '-')
    {
      ch = *(format++);
      apBuf->flags.pad = PAD_RIGHT;
    }
    while (ch == '0')
    {
      ch = *(format++);
      apBuf->flags.pad |= PAD_ZERO;
    }
    if (ch == '*')
    {
      ch = *(format++);
      apBuf->flags.width = va_arg(args, int);
    }
    else
    {
      while (ch >= '0' && ch <= '9')
      {
        apBuf->flags.width *= 10;
        apBuf->flags.width += ch - '0';
        ch = *(format++);
      }
    }
    if (ch == '.')
    {
      ch = *(format++);
      if (ch == '*')
      {
        apBuf->flags.printLimit = va_arg(args, int);
        ch = *(format++);
      }
      else
      {
        while (ch >= '0' && ch <= '9')
        {
          apBuf->flags.printLimit *= 10;
          apBuf->flags.printLimit += ch - '0';
          ch = *(format++);
        }
      }
    }
    if (apBuf->flags.printLimit == 0)
    {
      apBuf->flags.printLimit--; /* -1: make it unlimited */
    }
    if (ch == 's')
    {
      register char *s = (char *)va_arg(args, int);
      if (xprints(apBuf, s ? s : "(null)") == 0)
      {
        break;
      }
      continue;
    }
    if (ch == 'c')
    {
      /* char are converted to int then pushed on the stack */
      scr[0] = (char)va_arg(args, int);

      if (xstrbuf_printchar(apBuf, scr[0]) == 0)
      {
        return;
      }

      continue;
    }
    if (ch == 'l')
    {
      ch = *(format++);
      apBuf->flags.long32 = 1;
      /* Makes not difference as u32 == long */
    }
    if (ch == 'L')
    {
      ch = *(format++);
      apBuf->flags.long64 = 1;
      /* Does make a difference */
    }
    apBuf->flags.base = 10;
    apBuf->flags.letBase = 'a';

    if (ch == 'd' || ch == 'u')
    {
      apBuf->flags.isSigned = (ch == 'd');
#if CONFIG_SPRINTF_LONG_LONG
      if (apBuf->flags.long64 != pdFALSE)
      {
        if (xprintll(apBuf, va_arg(args, long long)) == 0)
        {
          break;
        }
      }
      else
#endif /* SPRINTF_LONG_LONG */
          if (xprinti(apBuf, va_arg(args, int)) == 0)
      {
        break;
      }
      continue;
    }

    apBuf->flags.base = 16; /* From here all hexadecimal */

    if (ch == 'x' && format[0] == 'i' && format[1] == 'p')
    {
      format += 2; /* eat the "xi" of "xip" */
      /* Will use base 10 again */
      if (xprintIp(apBuf, va_arg(args, int)) == 0)
      {
        break;
      }
      continue;
    }
    if (ch == 'x' || ch == 'X' || ch == 'p' || ch == 'o')
    {
      if (ch == 'X')
      {
        apBuf->flags.letBase = 'A';
      }
      else if (ch == 'o')
      {
        apBuf->flags.base = 8;
      }
#if CONFIG_SPRINTF_LONG_LONG
      if (apBuf->flags.long64 != pdFALSE)
      {
        if (xprintll(apBuf, va_arg(args, long long)) == 0)
        {
          break;
        }
      }
      else
#endif /* SPRINTF_LONG_LONG */
          if (xprinti(apBuf, va_arg(args, int)) == 0)
      {
        break;
      }
      continue;
    }
  }
  xstrbuf_printchar(apBuf, '\0');
}
/*-----------------------------------------------------------*/

int xprintf(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  struct SStringBuf strBuf;
  xstrbuf_init(&strBuf, nullptr, (const char *) nullptr);
  xprint(&strBuf, format, args);
  va_end(args);

  return strBuf.curLen;
}
/*-----------------------------------------------------------*/

int xvsnprintf(char *apBuf, size_t aMaxLen, const char *apFmt, va_list args)
{
  struct SStringBuf strBuf;
  xstrbuf_init(&strBuf, apBuf, (const char *) apBuf + aMaxLen);
  xprint(&strBuf, apFmt, args);

  return strBuf.curLen;
}
/*-----------------------------------------------------------*/

int xsnprintf(char *apBuf, size_t aMaxLen, const char *apFmt, ...)
{
  va_list args;

  va_start(args, apFmt);
  struct SStringBuf strBuf;
  xstrbuf_init(&strBuf, apBuf, (const char *) apBuf + aMaxLen);
  xprint(&strBuf, apFmt, args);
  va_end(args);

  return strBuf.curLen;
}
/*-----------------------------------------------------------*/

int xsprintf(char *apBuf, const char *apFmt, ...)
{
  va_list args;

  va_start(args, apFmt);
  struct SStringBuf strBuf;
  xstrbuf_init(&strBuf, apBuf, (const char *) apBuf + 1024);
  xprint(&strBuf, apFmt, args);
  va_end(args);

  return strBuf.curLen;
}
/*-----------------------------------------------------------*/

int xvsprintf(char *apBuf, const char *apFmt, va_list args)
{
  struct SStringBuf strBuf;
  xstrbuf_init(&strBuf, apBuf, (const char *) apBuf + 1024);
  xprint(&strBuf, apFmt, args);

  return strBuf.curLen;
}
/*-----------------------------------------------------------*/

int xvprintf(const char* format, va_list args)
{
  struct SStringBuf strBuf;
  xstrbuf_init(&strBuf, nullptr, (const char *) nullptr);
  xprint(&strBuf, format, args);

  return strBuf.curLen;
}
/*-----------------------------------------------------------*/

const char* xmksize(unsigned long long aSize, char *apBuf, int aLen)
{
  static char retString[33];
  size_t gb, mb, kb, sb;

  if (apBuf == nullptr)
  {
    apBuf = retString;
    aLen = sizeof retString;
  }
  gb = aSize / (1024 * 1024 * 1024);
  aSize -= gb * (1024 * 1024 * 1024);
  mb = aSize / (1024 * 1024);
  aSize -= mb * (1024 * 1024);
  kb = aSize / (1024);
  aSize -= kb * (1024);
  sb = aSize;
  if (gb)
  {
    xsnprintf(apBuf, aLen, "%u.%02u GB", (unsigned) gb, (unsigned) ((100 * mb) / 1024ul));
  }
  else if (mb)
  {
    xsnprintf(apBuf, aLen, "%u.%02u MB", (unsigned) mb, (unsigned) ((100 * kb) / 1024ul));
  }
  else if (kb != 0ul)
  {
    xsnprintf(apBuf, aLen, "%u.%02u KB", (unsigned) kb, (unsigned) ((100 * sb) / 1024ul));
  }
  else
  {
    xsnprintf(apBuf, aLen, "%u bytes", (unsigned) sb);
  }
  return apBuf;
}
