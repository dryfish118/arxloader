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




// ODA typedefs
#ifndef _RX_DEFS_
#define _RX_DEFS_

/** \details

    <group TD_Namespaces>
*/

// Deprecated: please use nullptr instead of NULLFCN
#define NULLFCN nullptr

#define ODRX_ULONG_MAX 0xFFFFFFFF

#define ODRX_ASCII_MAX 255  /* Same as UCHAR_MAX in <limits.h> */
#define ODRX_EOS 0          /* End of String Indicator */

struct OdRx
{
  static const OdUInt32 kNullDictId = OdUInt32(-1);

  typedef void(*FcnPtr) ();

  enum DictIterType
  {
    kDictSorted = 0,
    kDictCollated,
    kDictReversed
  };
  
  enum AppMsgCode
  {
    kNullMsg         = 0,
    kInitAppMsg      = 1,
    kUnloadAppMsg    = 2,
    kLoadDwgMsg      = 3,
    kUnloadDwgMsg    = 4,
    kInvkSubrMsg     = 5,
    kCfgMsg          = 6,
    kEndMsg          = 7,
    kQuitMsg         = 8,
    kSaveMsg         = 9,
    kDependencyMsg   = 10,
    kNoDependencyMsg = 11,
    kOleUnloadAppMsg = 12,
    kPreQuitMsg      = 13,
    kInitDialogMsg   = 14,
    kEndDialogMsg    = 15,
	kSuspendMsg      = 16,
	kInitTabGroupMsg = 17,
	kEndTabGroupMsg  = 18
  }; 
  
  enum AppRetCode
  {
    kRetOK = 0,
    kRetError = 3
  };

  enum Ordering
  {
    kLessThan = -1, // This object < Specified Object
    kEqual = 0, // This object == Specified Object
    kGreaterThan = 1, // This object > Specified Object
    kNotOrderable = 2  // These objects cannot be ordered.
  };

  enum MTSupport
  {
    kMTRender = 0x01, // worldDraw() or viewportDraw() calls from different threads are allowed
                              // for highest level (MS or PS), elsewhere they should always happen
                              // in one dedicated thread.
    kMTRenderInBlock = 0x02, // Calls to worldDraw() or viewportDraw() methods from different threads are allowed
                                                        // if the drawable is located inside a block (compound object).
    kMTRenderNested = 0x04, // worldDraw() or viewportDraw() from different threads are allowed for
                                                                                  // nested drawables of this compound object.
    kMTRenderReserved = 0x08, // Reserved for future use.
    kMTRenderMask = 0x0f, // Combination of all MTRender-dependent flags.
    kMTLoading = 0x80, // Multithread loading is supported for this object.
    kHistoryAware = 0x100 // The information written by the object to the undo filer can be saved in the history file (is valid between sessions)
  };
};

#ifndef kLoadADSMsg
#define kLoadADSMsg kLoadDwgMsg
#define kUnloadADSMsg kUnloadDwgMsg
#endif

//class OdRxClass;
//typedef void (*AppNameChangeFuncPtr)(const OdRxClass* classObj, char*& newAppName, int saveVer);

#endif // _RX_DEFS_

