#ifndef GC_GEDLL_H
#define GC_GEDLL_H

#include "gsoft.h"
#if defined(_MSC_VER)
#pragma warning(disable:4251)
#pragma warning(disable:4273)
#pragma warning(disable:4275)
#endif

#ifdef _GSOFT_STATIC_LINKING_
#define GE_DLLEXPIMPORT
#define GX_DLLEXPIMPORT
#else

#ifdef  GCGE_INTERNAL
#define GE_DLLEXPIMPORT __declspec(dllexport)
#else
#define GE_DLLEXPIMPORT __declspec(dllimport)
#endif  //GCGE_INTERNAL

#ifdef  GCGX_INTERNAL
#define GX_DLLEXPIMPORT __declspec(dllexport)
#else
#define GX_DLLEXPIMPORT __declspec(dllimport)
#endif  //GCGX_INTERNAL

#endif  //_GSOFT_STATIC_LINKING_

#endif  //GC_GEDLL_H