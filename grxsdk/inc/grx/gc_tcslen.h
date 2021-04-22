﻿
#pragma once

#ifdef _tcslen
#undef _tcslen
#endif

#ifdef UNICODE
#define _tcslen gc_wcslen
#else
#define _tcslen gc_strlen
#endif

#ifdef wcslen
#undef wcslen
#endif
#define wcslen gc_wcslen
#ifdef strlen
#undef strlen
#endif
#define strlen gc_strlen

#if defined ASSERT
#define GcTcsLen_Assert ASSERT
#elif defined(assert)
#define GcTcsLen_Assert assert
#elif defined(_ASSERTE)
#define GcTcsLen_Assert _ASSERTE
#elif defined ATLASSERT
#define GcTcsLen_Assert ATLASSERT
#else
#define GcTcsLen_Assert(x)
#endif

__declspec(noinline) inline unsigned __stdcall gc_wcslen(const wchar_t * s)
{
    unsigned n = 0;
    while (*s != L'\0') {
        s++;
        n++;
        GcTcsLen_Assert(n < 0x7FFFFFFE);
    }
    return n;
}

__declspec(noinline) inline unsigned __stdcall gc_strlen(const char * s)
{
    unsigned n = 0;
    while (*s != '\0') {
        s++;
        n++;
        GcTcsLen_Assert(n < 0x7FFFFFFE);
    }
    return n;
}

