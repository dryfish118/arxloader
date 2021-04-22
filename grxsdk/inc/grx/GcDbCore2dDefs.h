#pragma once

#if defined (GCDBCORE2D_API)
    #define   GCDBCORE2D_PORT _declspec(dllexport)
    #define   GCDBCORE2D_DATA_PORT _declspec(dllexport)
#else
#if defined (GCDBCORE2D_STATIC)
    #define   GCDBCORE2D_PORT 
    #define   GCDBCORE2D_DATA_PORT
#else
    #define GCDBCORE2D_PORT
    #define GCDBCORE2D_DATA_PORT _declspec(dllimport)
#endif
#endif
