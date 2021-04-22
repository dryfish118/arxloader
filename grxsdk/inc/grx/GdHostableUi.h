#pragma once

#ifndef GDHOSTABLEUI_H
#define GDHOSTABLEUI_H
#include "gsoft.h"

#ifdef  GDHOSTABLE_API
#define GDHOSTABLE_PORT __declspec(dllexport)
#else
#define GDHOSTABLE_PORT
#endif


#endif 