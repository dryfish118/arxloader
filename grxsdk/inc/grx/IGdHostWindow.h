#pragma once

#ifndef  GDHOSTWINDOW_H
#define GDHOSTWINDOW_H

#include "GdHostableUi.h"

class IGdHostWindow  
{
public:

    virtual HWND windowHandle() = 0;

};

#endif 