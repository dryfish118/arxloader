/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef _OdResult_h_Included_
#define _OdResult_h_Included_

namespace Oda
{

#define OD_ERROR_CODEVAL_DEF(code, string, val)  code = val,
#define OD_ERROR_DEF(code, string)  code,
enum OdResult
{
#include "ErrorDefs.h"
  eDummyLastError
};
#undef OD_ERROR_DEF
#undef OD_ERROR_CODEVAL_DEF

typedef OdResult ErrorStatus;

#define OD_MESSAGE_DEF(code, string)  code,
enum OdMessage
{
  sidDummyFirstMessage = eDummyLastError -1,
#include "MessageDefs.h"
  sidDummyLastMessage
};
#undef OD_MESSAGE_DEF

// PointHistory
enum PointHistory
{
  eTablet = 0x0001,
  eNotDigitizer = 0x0002,
  eLastPt = 0x0004,
  eGripped = 0x0008,
  eCartSnapped = 0x0010,
  eOrtho = 0x0020,
  eCyclingPt = 0x0040,
  eOsnapped = 0x0080,
  ePolarAngle = 0x0100,
  eAligned = 0x0400,

  eAppFiltered = 0x0800,

  eForcedPick = 0x1000,
  ePickMask = 0xE000,
  eDidNotPick = 0x0000,

  eUsedPickBox = 0x2000,
  eUsedOsnapBox = 0x4000,
  ePickAborted = 0x8000,
  eXPending = 0x10000,
  eYPending = 0x20000,
  eZPending = 0x40000,
  eCoordPending = 0x70000,
  eFromKeyboard = 0x80000,
  eNotInteractive = 0x100000,
  eDirectDistance = 0x200000,
  eGizmoConstrainted = 0x400000
};

// PromptStatus
enum PromptStatus
{
  eNone = 5000,
  eModeless = 5027,
  eNormal = 5100,
  eError = -5001,
  eCancel = -5002,
  eRejected = -5003,
  eFailed = -5004,
  eKeyword = -5005,
  eDirect = -5999
};
typedef OdResult OdWarning;

}; //namespace Oda

using namespace Oda;

#endif //_OdResult_h_Included_
