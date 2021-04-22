#pragma once

#ifndef  GCCOREDEFS_H
#define GCCOREDEFS_H

#ifndef GCCORE_PORT
#ifdef GCCORE_API
    #define GCCORE_PORT __declspec(dllexport)
    #define GCCORE_DATA_PORT __declspec(dllexport)
    #define GCCORE_STATIC_DATA_PORT __declspec(dllexport) static
#else
    #define GCCORE_PORT
    #define GCCORE_DATA_PORT __declspec(dllimport)
    #define GCCORE_STATIC_DATA_PORT __declspec(dllimport) static
#endif
#endif


#endif 