#pragma once

#ifndef GCAPWINDOW_H
#define GCAPWINDOW_H

#include "IGdHostWindow.h"
class GcApWindowImp;

class GcApWindow : public IGdHostWindow
{
public:
    GCCORE_PORT bool  preRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LONG_PTR& lResult);

    GCCORE_PORT bool     routeMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LONG_PTR& lResult);

    GCCORE_PORT bool postRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LONG_PTR& lResult);

protected:
    GCCORE_PORT GcApWindow();

    GCCORE_PORT virtual ~GcApWindow();

    GCCORE_PORT virtual bool subPreRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LONG_PTR& lResult);

    GCCORE_PORT virtual bool subRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LONG_PTR& lResult);

    GCCORE_PORT virtual bool subPostRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LONG_PTR& lResult);

    friend class GcApWindowImp;
    GcApWindowImp* m_pImp;
};

#endif 