#pragma once

#ifndef  GCBASEDEFS_H
#define GCBASEDEFS_H


#ifdef _GSOFT_STATIC_LINKING_
    #define GCBASE_PORT
#else
    #if defined(_MSC_VER) 
        #ifdef GCBASE_API
            #define GCBASE_PORT _declspec(dllexport)
        #else
            #define GCBASE_PORT _declspec(dllimport)
        #endif 
    #elif defined(__clang__)
        #define GCBASE_PORT
    #else
        #error Visual C++ or Clang compiler is required.
    #endif
#endif 


#endif 