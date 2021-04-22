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




#ifndef   _ODEDITORIMPL_H_INCLUDED_
#define   _ODEDITORIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "Editor.h"
#include "DbIdMapping.h"

/** \details

    <group OdRx_Classes> 
*/

#define RXEVENT_FIRE(method, inparams, params) \
inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    OdRxEventReactor* reactor = reactors[i]; \
    if (m_reactors.contains(reactor))\
      reactor->method params; \
  } \
}

#define EDEVENT_FIRE(method, inparams, params) \
inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    OdRxEventReactor* reactor = reactors[i]; \
    if (m_reactors.contains(reactor))\
    {\
      OdEditorReactorPtr edReactor = OdEditorReactor::ODSYSCALL1(cast, reactor); \
      if (edReactor.get()) edReactor->method params; \
    }\
  } \
}

#define DCEVENT_FIRE(method, inparams, params, IdMappingToDatabase) \
inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    OdRxEventReactor* reactor = reactors[i]; \
    if (m_reactors.contains(reactor))\
      reactor->method params; \
  } \
}

#define RXEVENT_FIRE_ABORT(method, inparams, params, abortmethod, abortparams) \
inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  OdArray<OdRxEventReactor*> firedReactors(reactors.length()); \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    if (m_reactors.contains(reactors[i])) \
    { \
      try \
      { \
        firedReactors.append(reactors[i]); \
        reactors[i]->method params; \
      } \
      catch(...) \
      { \
        for (unsigned j = 0; j < firedReactors.size(); ++j) \
        { \
          if (m_reactors.contains(firedReactors[j])) \
            firedReactors[j]->abortmethod abortparams; \
        } \
        throw; \
      } \
    } \
  } \
}

#define EDEVENT_FIRE_ABORT(method, inparams, params, abortmethod, abortparams) \
inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  OdArray<OdEditorReactorPtr> firedReactors(reactors.length()); \
  for (unsigned i = 0; i < reactors.size(); ++i) \
  { \
    if (m_reactors.contains(reactors[i])) \
    { \
      try \
      { \
        OdEditorReactorPtr pReactor = OdEditorReactor::ODSYSCALL1(cast, reactors[i]); \
        if (pReactor.get()) \
        { \
          firedReactors.append(pReactor); \
          pReactor->method params; \
        } \
      } \
      catch(...) \
      { \
        for (unsigned j = 0; j < firedReactors.size(); ++j) \
        { \
          if (m_reactors.contains(firedReactors[j])) \
            firedReactors[j]->abortmethod abortparams; \
        } \
        throw; \
      } \
    } \
  } \
}

#define EDEVENT_FIRE2(method, inparams, params) \
  inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  for (OdSize i = 0; i < reactors.length(); ++i) \
  { \
  if (m_reactors.contains(reactors[i]))\
    {\
    OdEditorReactor2* pReactor = OdEditorReactor2::ODSYSCALL1(cast, reactors[i]); \
    if (pReactor) pReactor->method params; \
    }\
  } \
}


#define EDEVENT_FIREEX(method, inparams, params) \
  inline void fire_##method inparams \
{ \
  OdArray<OdRxEventReactor*> reactors;\
  {TD_AUTOLOCK( m_mutex ); \
  reactors = m_reactors;} \
  for (OdSize i = 0; i < reactors.length(); ++i) \
  { \
  if (m_reactors.contains(reactors[i]))\
    {\
    OdEditorReactorEx* pReactor = OdEditorReactorEx::ODSYSCALL1(cast, reactors[i]); \
    if (pReactor) pReactor->method params; \
    }\
  } \
}


/** \details
    This class defines the events that trigger OdRxEventReactor instances. 
    Corresponding C++ library: TD_Db
    <group OdRx_Classes> 
*/
class TOOLKIT_EXPORT OdRxEventImpl : public OdEditor
{
protected:
  OdArray<OdRxEventReactor*> m_reactors;
  OdMutex m_mutex;
public:
  OdRxEventImpl() {}
  ODRX_DECLARE_MEMBERS(OdRxEventImpl);
  
  void addReactor(OdRxEventReactor* pReactor);
  void removeReactor(OdRxEventReactor* pReactor);

  RXEVENT_FIRE(unknownCommand,(const OdChar* cmdStr, OdDbVoidPtrArray *al),(cmdStr,al))
  RXEVENT_FIRE(commandWillStart,(const OdChar* cmdStr),(cmdStr))
  RXEVENT_FIRE(commandEnded,(const OdChar* cmdStr),(cmdStr))
  RXEVENT_FIRE(commandCancelled,(const OdChar* cmdStr),(cmdStr))
  RXEVENT_FIRE(commandFailed,(const OdChar* cmdStr),(cmdStr))
  // notifiers
  RXEVENT_FIRE(dwgFileOpened, (OdDbDatabase* db, OdChar* filename),(db, filename))
  RXEVENT_FIRE(initialDwgFileOpenComplete, (OdDbDatabase* db), (db))
  RXEVENT_FIRE(databaseConstructed, (OdDbDatabase* db), (db))
  RXEVENT_FIRE(databaseToBeDestroyed, (OdDbDatabase* db), (db))
  RXEVENT_FIRE_ABORT(beginSave, (OdDbDatabase* db, const OdChar* pIntendedName), (db, pIntendedName), abortSave, (db))
  RXEVENT_FIRE(saveComplete, (OdDbDatabase* db, const OdChar* pActualName), (db, pActualName))
  RXEVENT_FIRE(abortSave, (OdDbDatabase* db), (db))
  // DXF In/Out Events.
  RXEVENT_FIRE_ABORT(beginDxfIn, (OdDbDatabase* db), (db), abortDxfIn, (db))
  RXEVENT_FIRE(abortDxfIn, (OdDbDatabase* db), (db))
  RXEVENT_FIRE(dxfInComplete, (OdDbDatabase* db), (db))
  //
  RXEVENT_FIRE_ABORT(beginDxfOut, (OdDbDatabase* db), (db), abortDxfOut, (db))
  RXEVENT_FIRE(abortDxfOut, (OdDbDatabase* db), (db))
  RXEVENT_FIRE(dxfOutComplete, (OdDbDatabase* db), (db))
  // Insert Events.
  RXEVENT_FIRE_ABORT(beginInsert, (OdDbDatabase* pTo, const OdChar* pBlockName, OdDbDatabase* pFrom), (pTo, pBlockName, pFrom), abortInsert, (pTo))
  RXEVENT_FIRE_ABORT(beginInsert, (OdDbDatabase* pTo, const OdGeMatrix3d& xform, OdDbDatabase* pFrom), (pTo, xform, pFrom), abortInsert, (pTo))
  RXEVENT_FIRE_ABORT(otherInsert, (OdDbDatabase* pTo, OdDbIdMapping& idMap, OdDbDatabase* pFrom), (pTo, idMap, pFrom), abortInsert, (pTo))
  RXEVENT_FIRE(abortInsert, (OdDbDatabase* pTo), (pTo))
  RXEVENT_FIRE(endInsert, (OdDbDatabase* pTo), (pTo))

  // Wblock Events.
  RXEVENT_FIRE(wblockNotice, (OdDbDatabase* pDb), (pDb))
  RXEVENT_FIRE_ABORT(beginWblock, (OdDbDatabase* pTo, OdDbDatabase* pFrom, const OdGePoint3d*& insertionPoint), (pTo, pFrom, insertionPoint), abortWblock, (pTo))
  RXEVENT_FIRE_ABORT(beginWblock, (OdDbDatabase* pTo, OdDbDatabase* pFrom, OdDbObjectId blockId), (pTo, pFrom, blockId), abortWblock, (pTo))
  RXEVENT_FIRE_ABORT(beginWblock, (OdDbDatabase* pTo, OdDbDatabase* pFrom), (pTo, pFrom), abortWblock, (pTo))
  RXEVENT_FIRE_ABORT(otherWblock, (OdDbDatabase* pTo, OdDbIdMapping& m, OdDbDatabase* pFrom), (pTo, m, pFrom), abortWblock, (pTo))
  RXEVENT_FIRE(abortWblock, (OdDbDatabase* pTo), (pTo))
  RXEVENT_FIRE(endWblock, (OdDbDatabase* pTo), (pTo))
  RXEVENT_FIRE(beginWblockObjects, (OdDbDatabase* pDb, OdDbIdMapping& m), (pDb, m))

  // Deep Clone Events.
  DCEVENT_FIRE(beginDeepClone, (OdDbDatabase* pTo, OdDbIdMapping& m), (pTo, m), &m)
  RXEVENT_FIRE_ABORT(beginDeepCloneXlation, (OdDbIdMapping& m, OdResult* pResult), (m, pResult), abortDeepClone, (m))
  DCEVENT_FIRE(abortDeepClone, (OdDbIdMapping& m), (m), 0)
  DCEVENT_FIRE(endDeepClone, (OdDbIdMapping& m), (m), 0)

  // Partial Open Events.
  RXEVENT_FIRE(partialOpenNotice, (OdDbDatabase* pDb), (pDb))

  RXEVENT_FIRE_ABORT(xrefSubCommandStart,   (OdDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths, bool& vetoOp),
                                            (pHostDb, subCmd, btrIds, btrNames, paths, vetoOp), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))

  RXEVENT_FIRE_ABORT(xrefSubCommandEnd,     (OdDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths),
                                            (pHostDb, subCmd, btrIds, btrNames, paths), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))

  RXEVENT_FIRE_ABORT(xrefSubCommandAborted, (OdDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths),
                                            (pHostDb, subCmd, btrIds, btrNames, paths), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))
  //
  // OdEditorReactor events.
  //
  // file events
  EDEVENT_FIRE(beginDwgOpen, (OdChar* filename), (filename))
  EDEVENT_FIRE(endDwgOpen, (const OdChar* filename, OdDbDatabase* pDb), (filename, pDb))
  EDEVENT_FIRE(beginClose,   (OdDbDatabase* pDb), (pDb))

  // xref events
  EDEVENT_FIRE_ABORT(beginAttach,  (OdDbDatabase* pToDb, const OdChar* filename, OdDbDatabase* pFromDb), (pToDb, filename, pFromDb), abortAttach, (pToDb))
  EDEVENT_FIRE_ABORT(otherAttach,  (OdDbDatabase* pToDb, OdDbDatabase* pFromDb), (pToDb, pFromDb), abortAttach, (pToDb))
  EDEVENT_FIRE(abortAttach,  (OdDbDatabase* pFromDb), (pFromDb))
  EDEVENT_FIRE(endAttach,    (OdDbDatabase* pToDb), (pToDb))
  EDEVENT_FIRE(redirected,   (OdDbObjectId newId, OdDbObjectId oldId), (newId, oldId))
  EDEVENT_FIRE(comandeered,  (OdDbDatabase* pToDb, OdDbObjectId id, OdDbDatabase* pFromDb), (pToDb, id, pFromDb))
  EDEVENT_FIRE_ABORT(beginRestore, (OdDbDatabase* pToDb, const OdChar* filename, OdDbDatabase* pFromDb), (pToDb, filename, pFromDb), abortRestore, (pToDb))
  EDEVENT_FIRE(abortRestore, (OdDbDatabase* pToDb), (pToDb))
  EDEVENT_FIRE(endRestore,   (OdDbDatabase* pToDb), (pToDb))

  // xref subcommand events
  EDEVENT_FIRE_ABORT(xrefSubCommandStart,       (OdDbDatabase* pHostDb, OdXrefSubCommand subCmd, const OdDbObjectIdArray& btrIds, const OdStringArray& btrNames, const OdStringArray& paths),
                                                (pHostDb, subCmd, btrIds, btrNames, paths), xrefSubCommandAborted, (pHostDb, subCmd, btrIds, btrNames, paths))
  EDEVENT_FIRE(xrefSubcommandBindItem,    (int activity, OdDbObjectId blockId), (activity, blockId))
  EDEVENT_FIRE(xrefSubcommandBindItem,    (OdDbDatabase* pHost, int activity, OdDbObjectId blockId), (pHost, activity, blockId))
  EDEVENT_FIRE(xrefSubcommandAttachItem,  (int activity, const OdString& xrefPath), (activity, xrefPath))
  EDEVENT_FIRE(xrefSubcommandOverlayItem, (int activity, const OdString& xrefPath), (activity, xrefPath))
  EDEVENT_FIRE(xrefSubcommandDetachItem,  (int activity, OdDbObjectId blockId), (activity, blockId))
  EDEVENT_FIRE(xrefSubcommandPathItem,    (int activity, OdDbObjectId blockId, const OdString& newPath), (activity, blockId, newPath))
  EDEVENT_FIRE(xrefSubcommandReloadItem,  (int activity, OdDbObjectId blockId), (activity, blockId))
  EDEVENT_FIRE(xrefSubcommandUnloadItem,  (int activity, OdDbObjectId blockId), (activity, blockId))

  // command undo events
  EDEVENT_FIRE(undoSubcommandAuto,   (int activity, bool state), (activity, state))
  EDEVENT_FIRE(undoSubcommandControl,(int activity, int option), (activity, option))
  EDEVENT_FIRE(undoSubcommandBegin,  (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandEnd,    (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandMark,   (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandBack,   (int activity), (activity))
  EDEVENT_FIRE(undoSubcommandNumber, (int activity, int num), (activity, num))

  // pickfirst selection event
  EDEVENT_FIRE(pickfirstModified, (), ())
  EDEVENT_FIRE(lispWillStart, (const OdChar* firstLine), (firstLine))
  EDEVENT_FIRE(lispEnded, (), ())
  EDEVENT_FIRE(lispCancelled, (), ())

  // layout event
  EDEVENT_FIRE(layoutSwitched, (const OdString& newLayoutName), (newLayoutName))

  // window events
  EDEVENT_FIRE(docFrameMovedOrResized, (OdHWnd hwndDocFrame, bool moved), (hwndDocFrame, moved))
  EDEVENT_FIRE(mainFrameMovedOrResized, (OdHWnd hwndMainFrame, bool moved), (hwndMainFrame, moved))

  // mouse events
  EDEVENT_FIRE(beginDoubleClick, (const OdGePoint3d& clickPoint), (clickPoint))
  EDEVENT_FIRE(beginRightClick, (const OdGePoint3d& clickPoint), (clickPoint))

  // toolbar events
  EDEVENT_FIRE(toolbarBitmapSizeWillChange, (bool largeBitmaps), (largeBitmaps))
  EDEVENT_FIRE(toolbarBitmapSizeChanged, (bool largeBitmaps), (largeBitmaps))

  // partial open events
  EDEVENT_FIRE(objectsLazyLoaded, (const OdDbObjectIdArray& objectIds), (objectIds))

  // quit events
  EDEVENT_FIRE_ABORT(beginQuit,       (), (), quitAborted, ())
  EDEVENT_FIRE(quitAborted,     (), ())
  EDEVENT_FIRE(quitWillStart,   (), ())

  // modeless operation events
  EDEVENT_FIRE(modelessOperationWillStart, (const OdString& contextString), (contextString))
  EDEVENT_FIRE(modelessOperationEnded, (const OdString& contextString), (contextString))

  // SysVar events
  EDEVENT_FIRE(sysVarChanged, (const OdChar* varName, OdBool success), (varName, success))
  EDEVENT_FIRE(sysVarWillChange, (const OdChar* varName), (varName))

  EDEVENT_FIRE(viewChanged, (), ())

  //OdEditorReactor2
  EDEVENT_FIRE2(beginDocClose, (OdDbDatabase* pDwg), (pDwg))
  EDEVENT_FIRE2(docCloseAborted, (OdDbDatabase* pDwg), (pDwg))
  EDEVENT_FIRE2(docCloseWillStart, (OdDbDatabase* pDwg), (pDwg))
  EDEVENT_FIRE2(layoutToBeSwitched, (const OdChar *oldLayoutName, const OdChar *newLayoutName), (oldLayoutName, newLayoutName))
  EDEVENT_FIRE2(dwgViewResized, (OdLongPtr hwndDwgView), (hwndDwgView))
  EDEVENT_FIREEX(customModeBegin, (), ())
  EDEVENT_FIREEX(customModeEnd, (), ())

};

typedef OdSmartPtr<OdRxEventImpl> OdRxEventImplPtr;

/** \details
    This class defines the events that trigger OdRxEventReactor instances. 
    <group Other_Classes>
*/
class TOOLKIT_EXPORT OdEditorImpl : public OdRxEventImpl
{
public:
  OdEditorImpl() {}
  ODRX_DECLARE_MEMBERS(OdEditorImpl);

  void enableVeto(bool bEnable);
  bool vetoed();
};

typedef OdSmartPtr<OdEditorImpl> OdEditorImplPtr;

#include "TD_PackPop.h"

#endif // _ODEDITORIMPL_H_INCLUDED_

