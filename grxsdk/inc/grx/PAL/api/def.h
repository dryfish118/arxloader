#pragma once

#ifndef GCPAL_DEF_H
#define GCPAL_DEF_H

#ifdef _GSOFT_STATIC_LINKING_
#define GCPAL_SUPPRESS_IMPEXP_DIRECTIVES 1
#endif


#if GCPAL_SUPPRESS_IMPEXP_DIRECTIVES 
    #define   GCPAL_PORT
#else
    #if defined(_MSC_VER) 
        #ifdef  GCPAL_API
            #define   GCPAL_PORT _declspec(dllexport)
        #else
            #define   GCPAL_PORT _declspec(dllimport)
            //#pragma comment(lib, "gcpal.lib")
        #endif
    #elif defined(__clang__)
        #ifdef  GCPAL_API
            #define   GCPAL_PORT
        #else
            #define   GCPAL_PORT
            //#pragma comment(lib, "gcpal.lib")
        #endif
    #else
        #error Visual C++ or Clang compiler is required.
    #endif
#endif

#if defined(GCPAL_API) || !defined(_GSOFT_CROSS_PLATFORM_) || defined(GCPAL_TEST)
#define GC_NON_CROSS_PLATFORM_API
#endif



#endif