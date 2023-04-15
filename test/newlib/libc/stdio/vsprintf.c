/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * and/or other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/* doc in vfprintf.c */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <_ansi.h>
#include <reent.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>

#include "local.h"

#ifndef _REENT_ONLY

int
vsprintf (char *__restrict str,
       const char *__restrict fmt,
       va_list ap)
{
  return _vsprintf_r (_REENT, str, fmt, ap);
}

#ifdef _NANO_FORMATTED_IO
int
vsiprintf (char *, const char *, __VALIST)
       _ATTRIBUTE ((__alias__("vsprintf")));
#endif

#endif /* !_REENT_ONLY */

int
_vsprintf_r (struct _reent *ptr,
       char *__restrict str,
       const char *__restrict fmt,
       va_list ap)
{
  int ret;
  FILE f;

  f._flags = __SWR | __SSTR;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._w = INT_MAX;
  f._file = -1;  /* No file. */
  ret = _svfprintf_r (ptr, &f, fmt, ap);
  *f._p = 0;
  return ret;
}

#ifdef _NANO_FORMATTED_IO
int
_vsiprintf_r (struct _reent *, char *, const char *, __VALIST)
       _ATTRIBUTE ((__alias__("_vsprintf_r")));
#endif
