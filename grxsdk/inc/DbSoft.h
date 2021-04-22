#ifndef _DBOFT_H_
#define _DBOFT_H_

#include "OdaCommon.h"
#include "StringArray.h"
#include "gchar.h"

#define Gsoft_Boolean_is_bool 1
#define Gsoft_Int32_is_int 1

#pragma pack (push, 8)

#define _GCAD_WINDOWS_ 1
#define _GRX_CUSTOM_DRAG_N_DROP_




#if defined(_MSC_VER)
#ifndef _GSOFT_CROSS_PLATFORM_
#define _GSOFT_WINDOWS_ 1
#endif
#elif defined(__clang__)
#if defined(_GSOFT_MAC_)
#define __w64
#endif

#endif

#if (defined(_MSC_VER) && defined(_WIN64)) || (defined(__clang__) && defined(__LP64__))
#define _GC64 1
#endif

namespace OdGsoft
{
  typedef OdInt8    Int8;
  typedef OdInt16   Int16;
  typedef OdInt32   Int32;
  typedef OdSize    size_type;
  typedef OdUInt8   UInt8;
  typedef OdUInt16  UInt16;
  typedef OdUInt32  UInt32;
  typedef OdInt64   Int64;
  typedef OdUInt64  UInt64;

  typedef unsigned char  uchar;
  typedef unsigned short ushort;
  typedef unsigned int   uint;
  typedef unsigned long  ulong;

  typedef OdBool Boolean;
  enum
  {
    kFalse = ::kFalse,
    kTrue = ::kTrue,
  };

#ifdef _WIN64
  typedef unsigned __int64    Size_t;
  typedef __int64             SSize_t;
#else
  typedef unsigned long       Size_t;
  typedef long                SSize_t;
#endif

  typedef __w64 OdLongPtr     LongPtr;
  typedef __w64 OdULongPtr    ULongPtr;

  typedef __w64 OdIntPtr      IntPtr;
  typedef __w64 OdUIntPtr     UIntPtr;

  typedef LongPtr             IntDbId;
  typedef IntPtr              GsMarker;

  using Time64 = int64_t;
};

#ifndef NULL
#define NULL 0
#endif

#pragma pack (pop)

typedef char                  LEGACY_CHAR;
typedef char*                 LEGACY_STRING;
typedef const                 char* LEGACY_STRING_CONST;
typedef unsigned short        WIDE_CHAR;
typedef unsigned short*       WIDE_STRING;
typedef const unsigned short* WIDE_STRING_CONST;
typedef char*                 MEMORY_POINTER;
typedef const char*           MEMORY_POINTER_CONST;
typedef unsigned char         GC_BYTE;

//For Internal Use Only
typedef OdGsoft::Int8        GINT8;
typedef OdGsoft::Int16       GINT16;
typedef OdGsoft::Int32       GINT32;
typedef OdGsoft::Int64       GINT64;

typedef OdGsoft::UInt8       GUINT8;
typedef OdGsoft::UInt16      GUINT16;
typedef OdGsoft::UInt32      GUINT32;
typedef OdGsoft::UInt64      GUINT64;

typedef OdGsoft::UInt8       GBYTE;
typedef OdGsoft::UInt16      GWORD;
typedef OdGsoft::UInt32      GDWORD;
typedef OdGsoft::UInt64      GQWORD;

typedef OdGsoft::size_type   GSIZE;
typedef OdGsoft::Boolean     GBOOL;

#define GC_PI  OdaPI
#define GC_PI2 OdaPI2
#define GC_PI4 OdaPI4
#define GC_2PI (OdaPI + OdaPI)

#ifdef _GSOFT_MAC_
#ifdef nil
#undef nil
#endif
#define nil __DARWIN_NULL
#endif

#if defined(_MSC_VER)
#define GSOFT_NO_VTABLE           __declspec(novtable)
#define GSOFT_STDCALL             __stdcall
#define GSOFT_DEPRECATED          __declspec(deprecated)
#define GSOFT_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
#define GSOFT_DATA_IMPORT         __declspec(dllimport)
#define GSOFT_PACK_BEGIN __pragma(pack(push,1))
#define GSOFT_PACK_END __pragma(pack(pop))
#else 
#define GSOFT_NO_VTABLE

#if defined(__LP64__) || defined(__clang__)
#define GSOFT_STDCALL
#else
#define GSOFT_STDCALL         __attribute__((stdcall))   
#endif 

#define GSOFT_DEPRECATED          __attribute__((__deprecated__))
#define GSOFT_DEPRECATED_MSG(MSG) __attribute__((__deprecated__))
#define GSOFT_DATA_IMPORT         extern

#define __declspec(method) __declspec_##method
#define _declspec(method) __declspec_##method

#define __declspec_selectany      __attribute__ ((__weak__))

#define __declspec_dllexport      __attribute__ ((__visibility__("default")))
#define __declspec_dllimport      

#define __declspec_noinline       __attribute__ ((__noinline__))
#define __declspec_noreturn       __attribute__ ((__noreturn__))
#define __declspec_deprecated     __attribute__ ((__deprecated__))
#define __declspec_novtable
#define __declspec_allocate(name) __attribute__ ((section("__DATA," name)))
#define GSOFT_PACK_BEGIN
#define GSOFT_PACK_END __attribute__((packed))

#endif 

#if defined(_MSC_EXTENSIONS) || defined (__clang__)
#define GSOFT_OVERRIDE  override
#if defined(_MSC_VER) && (_MSC_VER <= 1600) 
#define GSOFT_SEALED sealed
#else
#define GSOFT_SEALED final
#endif
#else 
#define GSOFT_OVERRIDE
#define GSOFT_SEALED 
#endif 

#define MIGRATION_ERRORS

#if defined(_MSC_VER) && defined (MIGRATION_ERRORS) || defined(__clang__)
#define GSOFT_SEALED_VIRTUAL virtual
#if !defined(GSOFT_SEALED)
#define GSOFT_SEALED sealed
#endif 
#else 
#define GSOFT_SEALED_VIRTUAL 
#if !defined(GSOFT_SEALED)
#define GSOFT_SEALED sealed
#endif 
#endif 

#if defined(__INTEL_COMPILER) || defined (_MSC_VER)
#define GSOFT_FORCE_INLINE __forceinline
#else 
#define GSOFT_FORCE_INLINE inline
#endif 

#ifdef _GSOFT_WINDOWS_
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, wchar_t)
#else
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, int)
#endif

#ifdef _GSOFT_UNITTEST_
#ifdef GSOFT_SEALED
#undef GSOFT_SEALED
#endif
#define GSOFT_SEALED
#endif

#ifdef _MSC_VER
#define GSOFT_UNREFED_PARAM(x) x
#elif defined(__clang__)
#define GSOFT_UNREFED_PARAM(x) (void)(x);
#else
#error Unknown compiler.
#endif

#ifdef _MSC_VER
#define GSOFT_UNREACHABLE __assume(false)
#elif defined(__clang__)
#define GSOFT_UNREACHABLE __builtin_unreachable()
#else
#error Unknown compiler.
#endif

#endif