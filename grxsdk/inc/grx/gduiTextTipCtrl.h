#pragma once
#include <afxpriv.h>
#include "gduiTextTip.h"

class GdToolTip;
class GdWthToolTip;

class GDUI_PORT CGdWthToolTipCtrl : public CGdToolTipCtrl
{
  DECLARE_DYNAMIC(CGdWthToolTipCtrl)
public:
  GdWthToolTip* GetWthToolTip();
};