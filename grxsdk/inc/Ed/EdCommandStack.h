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

#ifndef _ODEDCOMMANDSTACK_H_INCLUDED_
#define _ODEDCOMMANDSTACK_H_INCLUDED_



#define ODRX_COMMAND_DOCK      OD_T("ODRX_REGISTERED_COMMANDS")

typedef void (*OdRxFunctionPtr) ();

class OdEdCommand;
class OdEdCommandContext;

#include "../RxObject.h"
#include "rxresource.h"

class OdRxIterator;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdRxIterator object pointers. 
*/
typedef OdSmartPtr<OdRxIterator> OdRxIteratorPtr;

class OdRxDictionary;
class OdEdUIContext;

#include "../TD_PackPush.h"

class OdEdCommand;
class OdEdCommandReactor;
class OdEdCommandIterator;
typedef void (OdEdCommandFunction) (OdEdCommandContext* pCmdCtx);


/** \details
  This template class is a specialization of the OdSmartPtr class for OdEdCommand object pointers. 
*/
typedef OdSmartPtr<OdEdCommand> OdEdCommandPtr;

struct OdEdCommandStruc 
{
  OdRxFunctionPtr fcnAddr;
  long            flags;
  void	          *app;
  HINSTANCE       hResHandle;
  OdEdCommand		*cmd;
};
/** \details
    This class represents custom commands within a client application created with the ODA Platform. 
    
    \remarks
    A custom command is be created by deriving a class from OdEdCommand, and overriding
    the functions in that class. 
    
    The custom command is registered in the global command stack by calling 
    OdEdCommandStack::addCommand() on the global command stack, 
    which obtained via the odedRegCmds() external function.

    Corresponding C++ library: TD_Root
    
    <group OdEd_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdEdCommand : public OdRxObject 
{
protected:
  OdEdCommand();
public:
  ODRX_DECLARE_MEMBERS(OdEdCommand);

  ~OdEdCommand();

  enum
  {
    kModal            = 0x00000000,
    kTransparent      = 0x00000001,
    kUsePickset       = 0x00000002,
    kRedraw           = 0x00000004,
    kNoPerspective    = 0x00000008, // NOT allowed in perspective views
    kNoMultiple       = 0x00000010,
    kNoTilemode       = 0x00000020, // NOT allowed with TILEMODE == 1
    kNoPaperspace     = 0x00000040, // NOT allowed in Paperspace
    kPlotOnly         = 0x00000080,
    kNoOEM            = 0x00000100,
    kUndefined        = 0x00000200,
    kInProgress       = 0x00000400,
    kDefun            = 0x00000800,
    kLispAsCmd        = 0x00001000, // For Internal use only
    kPgpInit          = 0x00002000,
    kNoNewStack       = 0x00010000, // For internal use only
    kNoInternalLock   = 0x00020000,
    kDocReadLock      = 0x00080000, // not set = DOCWRITELOCK
    kDocExclusiveLock = 0x00100000, // not set = DOCSHAREDLOCK
    kSession          = 0x00200000, // Run cmd handler in the session fiber
    kInterruptible    = 0x00400000, // Supports OPM display of command properties
    kNoHistory        = 0x00800000, // Command does not become default
    kNoUndoMarker     = 0x01000000, // No Undo or Repeat presence.
    kNoBedit          = 0x02000000, // blocked during a bedit session
    kNoActionRecording= 0x04000000, // Disallow Action Recording
    kActionMacro      = 0x08000000, // Action Macro command
    KRelaxAssoc       = 0x10000000,  /* Allow relaxed network evaluation
                                       during drag operation */
    kCore             = 0x20000000, // For internal use only
    kNoInferConstraint= 0x40000000, // Disallow Inferring constraints
    kTempShowDyndim   = 0x80000000 // Temporarily show dynamic dimensions for selected entities during this command

    /*
    NOACTIONRECORDING  0x04000000 // Disallow Action Recording
    ACTIONMACRO        0x08000000 // Action Macro command
    RELAXASSOC         0x10000000 // Allow relaxed network evaluation during drag operation
    CORE               0x20000000 // For internal use only
    NOINFERCONSTRAINT  0x40000000 // Disallow Inferring constraints
    TEMPSHOWDYNDIM     0x80000000 // Temporarily show dynamic dimensions for selected entities during this command
    */
  };

  static OdEdCommandPtr createObject(
    const OdString& sGroupName,
    const OdString& sGlobalName,
    const OdString& sLocalName,
    OdUInt32 commandFlags,
    OdEdCommandFunction pFunction,
    OdRxModule *pModule = 0,
	  OdEdUIContext *pUIContext = NULL);

  static OdEdCommandPtr createObject(
    const OdString& sGroupName,
    const OdString& sGlobalName,
    const OdString& sLocalName,
    OdUInt32 flags,
    OdRxFunctionPtr pFunction,
    OdRxModule *pModule = 0,
    OdEdUIContext *pUIContext = NULL,
    HINSTANCE hResourceHandle = NULL);

  /** \details
    This function is for internal use only.

    \Remarks:
    This function is for internal use only.
  */
  virtual void* commandApp() const;

  /** \details
    Returns the group name of this command object. 
    
    \remarks
    This name is used to group sets of registered commands.
  */
  virtual const OdChar* groupName() const;

  /** \details
    Returns the global (untranslated) name of this command object.
    
    \remarks
    This name must be unique within the groupName of this command object.
  */
  virtual const OdChar* globalName() const = 0;

  /** \details
    Returns the local (translated) name of this command.
    
    \remarks
    This name must be unique within the groupName of this command object.
  */
    virtual const OdChar* localName() const;

  /** \details
    Called to execute this command object.
    
    \remarks
    The client's override of this function contains the body of the command.
    
    \param pCommandContext [in]  Pointer to the command context.
    
    \remarks
    The specified command context object is used to interact with the 
    calling application as part of an interactive command.  
            
    \sa
    OdEdCommandContext::userIO
  */
  virtual void execute(OdEdCommandContext* pCommandContext);

  virtual const OdRxModule* module() const;

  virtual void commandUndef(bool undefIt);

  virtual OdInt32 commandFlags() const;

  virtual const HINSTANCE resourceHandle() const;

  virtual OdEdUIContext*  UIContext() const {return NULL;}

  virtual OdRxFunctionPtr functionAddr() const;
  virtual void            functionAddr(OdRxFunctionPtr fhdl);  
  
  virtual int             functionCode() const;
  virtual void            functionCode(int fcode);

  virtual const OdRxResourceInstance& resourceInstance() const = 0;
  void addReactor(OdEdCommandReactor* pReactor);
  void removeReactor(OdEdCommandReactor* pReactor);

  OdUInt8 defaultCommandVersion() const;
};

enum OdEdCommandStatusFlags
{
  kCmdStatusNone   = 0x00000,
  kCmdStatusCancel = 0x00001,
  kCmdStatusFailed = 0x00002,
};

FIRSTDLL_EXPORT OdEdCommandStatusFlags& operator|=(OdEdCommandStatusFlags& f, int i);
FIRSTDLL_EXPORT OdEdCommandStatusFlags& operator&=(OdEdCommandStatusFlags& f, int i);

class OdEdImpCommandEventArgs;
class OdEdCommandEventArgs
{
public:
  const OdChar* groupName() const;
  OdEdCommandStatusFlags status() const;
  void setStatus(OdEdCommandStatusFlags flags);

protected:
  friend class OdEdImpCommandEventArgs;
  OdEdImpCommandEventArgs* m_pImp;

  OdEdCommandEventArgs(OdEdImpCommandEventArgs* pImp);
  OdEdCommandEventArgs(const OdEdCommandEventArgs& other);
  OdEdCommandEventArgs& operator=(const OdEdCommandEventArgs& other);
};

class FIRSTDLL_EXPORT OdEdCommandReactor : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdEdCommandReactor);

  virtual void commandWillStart(OdEdCommand* pCmd, OdEdCommandEventArgs* data);
  virtual void     commandEnded(OdEdCommand* pCmd, OdEdCommandEventArgs* data);
  virtual void          goodbye(OdEdCommand* pCmd, OdEdCommandEventArgs* data);
};

/** \details
    This class is the base class for custom classes that receive notification
    of OdEdCommandStack events.
    
    \remarks
    Events consist of the addition and deletion, starting and ending,
    cancellation and failure, and non-recognition of registered commands. 
    
    The command stack consists of groups which contain their respective commands.
    Adding a command adds it to its group. If the group does not exist,
    the group is first created and pushed onto the top of the stack.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    Corresponding C++ library: TD_Root

    <group OdEd_Classes>
*/
class FIRSTDLL_EXPORT OdEdCommandStackReactor : public OdRxObject 
{ 
public:
  ODRX_DECLARE_MEMBERS(OdEdCommandStackReactor);

  virtual void commandRemoved(OdEdCommand* pCmd, OdEdCommandEventArgs* data);
  /** \details
    Notification function called whenevever a command has been added to the global command stack.
    
    \param pCommand [in]  Pointer to the command object.
    
	  \remarks
	  This function is called after the operation.
  */
  virtual void commandAdded(OdEdCommand* pCommand);
  virtual void commandAdded(OdEdCommand* pCmd, OdEdCommandEventArgs* data);

  /** \details
    Notification function called whenevever a command will be removed from the global command stack
    
    \param pCommand [in]  Pointer to the command object.
    
	  \remarks
	  This function is called after the operation.
  */
  virtual void commandWillBeRemoved(OdEdCommand* pCommand);
  
  /** \details
    Notification function called whenevever the execution of a command will start.
    
    \param pCommand [in]  Pointer to the command object.
    
	  \remarks
	  This function is called before the operation.
  */
  virtual void commandWillStart(OdEdCommand* pCommand, OdEdCommandContext* pCmdCtx);
  virtual void commandWillStart(OdEdCommand* pCmd, OdEdCommandEventArgs* data);

  /** \details
    Notification function called whenevever the execution of a command has ended.
    
    \param pCommand [in]  Pointer to the command object.
    
	  \remarks
	  This function is called after the operation.
  */
  virtual void commandEnded(OdEdCommand* pCommand, OdEdCommandContext* pCmdCtx);
  virtual void commandEnded(OdEdCommand* pCmd, OdEdCommandEventArgs* data);

  /** \details
    Notification function called whenevever the execution of a command has been canceled.
    
    \param pCommand [in]  Pointer to the command object.
    
	  \remarks
	  This function is called after the operation.
  */
  virtual void commandCancelled(OdEdCommand* pCommand, OdEdCommandContext* pCmdCtx);
  
  /** \details
    Notification function called whenevever the execution of a command has failed.
    
    \param pCommand [in]  Pointer to the command object.
    
	  \remarks
	  This function is called after the operation.
  */
  virtual void commandFailed(OdEdCommand* pCommand, OdEdCommandContext* pCmdCtx);
  
  /** \details
    Notification function called whenevever the execution of an unknown command has been attempted.
    
    \param commandName [in]  name of unknown command.
    
	  \remarks
	  This function is called after the operation.
  */
  virtual OdEdCommandPtr unknownCommand(const OdString& commandName, OdEdCommandContext* pCmdCtx);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdEdCommandStackReactor object pointers. 
*/
typedef OdSmartPtr<OdEdCommandStackReactor> OdEdCommandStackReactorPtr;

/** \details
    This template class is a specialization of the OdArray class for OdEdCommandStackReactor object SmartPointers.
*/
typedef OdArray<OdEdCommandStackReactorPtr> OdEdCommandStackReactorArray;

/** \details
    This exception class to be thrown from OdEdCommandStack::executeCommand(const OdString& cmdName, ...)
    if cmdName was not found.
    <group OdEd_Classes>
*/
class OdEdUnknownCommand {};

/** \details
    This class implements and manages the global command stack.

    \remarks
    The command stack consists of groups which contain their respective commands.
    Adding a command adds it to its group. If the group does not exist,
    the group is first created and pushed onto the top of the stack.
    
    The lookupCommand and executeCommand functions search for command names
    in the group order on the stack.
     
    In the case of duplicate command names, the most recent one added to the stack
    is the command that is returned or executed.
     
    The group order may be changed with popGroupToTop function. 
         
    Corresponding C++ library: TD_Root
    
    <group OdEd_Classes>
*/
class FIRSTDLL_EXPORT OdEdCommandStack : public OdRxObject 
{ 
public:
  ODRX_DECLARE_MEMBERS(OdEdCommandStack);

  //This function is for internal system use only.
  virtual bool atPut(const OdChar * cmdGroupName, OdRxDictionary*& cmdsGlobal, OdRxDictionary*& cmdsLocal) = 0;

   /** \details
    Adds the specified reactor to this object's reactor list.

    \param pReactor [in]  Pointer to the reactor object.
   */
  virtual void addReactor(OdEdCommandStackReactor* pReactor);

  /** \details
    Removes the specified transient reactor from this object's reactor list.

    \param pReactor [in]  Pointer to the reactor object.
  */
  virtual void removeReactor(OdEdCommandStackReactor* pReactor);

  /** \details
    Returns this object's transient reactors.
  */
  virtual OdEdCommandStackReactorArray getCommandStackReactors() const;

  /** \details
    Adds the specified command object to this Stack object.

    \param pCommand [in]  Pointer to the command object.
    
    \remarks
    If the group associated with the command does not exist, 
    the group is first created and pushed onto the top of the stack.
    
    The globalName and localName must be unique within the groupName of this command object.
  */
  virtual void addCommand(OdEdCommand* pCommand);

  /** \details
    Adds the specified command object to this Stack object.

    \param pCommand [in]  Pointer to the command object.
    
    \remarks
    If the group associated with the command does not exist, 
    the group is first created and pushed onto the top of the stack.
    
    The globalName and localName must be unique within the groupName of this command object.
  */
  virtual OdEdCommand* addCommand(
    const OdString& sGroupName,
    const OdString& sGlobalName,
    const OdString& sLocalName,
    OdUInt32 commandFlags,
    OdEdCommandFunction pFunction,
    OdRxModule *pModule = 0,
	OdEdUIContext *pUIContext = NULL);
  
  virtual OdEdCommand* addCommand(
    const OdString& sGroupName,
    const OdString& sGlobalName,
    const OdString& sLocalName,
    OdUInt32 commandFlags,
    OdRxFunctionPtr pFunction,
    OdRxModule *pModule = 0,
		OdEdUIContext *pUIContext = NULL,
		HINSTANCE hResourceHandle = NULL);

  virtual OdResult addCommand(
    const OdChar* cmdGroupName,
    const OdChar* cmdGlobalName,
    const OdChar* cmdLocalName,
    OdInt32 commandFlags,
		OdRxFunctionPtr FunctionAddr,
    OdEdUIContext* UIContext = NULL,
    int fcode = -1,
    const OdRxResourceInstance& hResourceHandle = OdRxResourceInstance::empty(),
    OdEdCommand** cmdPtrRet = NULL);
  /** \details
    Returns an Iterator object that can be 
    used to traverse the OdEdCommand objects in this Stack object.
    
    \remarks
    The traversal is by global name in group order.
  */
  virtual OdRxIteratorPtr newIterator();

  /** \details
    Returns an Iterator object that can be 
    used to traverse the OdEdCommand objects in this Stack object.

    \param groupName [in]  Group name.

    \remarks
    If groupName is specified, only OdEdCommand objects in the specified
    group will be traversed.
  */
  virtual OdRxIteratorPtr newIterator(const OdString& groupName);


	virtual OdEdCommandIterator* iterator() = 0;
  /** \details
    Returns an Iterator object that can be used to traverse the 
    group objects in this Stack object.

    \remarks
    Each group is an OdRxDictionary object.
  */
  virtual OdRxIteratorPtr newGroupIterator();
  
  enum LookupFlags
  {
    kGlobal       = 0x01, // Search global (untranslated) names.
    kLocal        = 0x02, // Search local (translated) names.
    kSpecifedGroup= 0x04, // Search in specified group only.
    kUndefed      = 0x08, // Do not fire unknownCommand() event.
    kUndefined    = 0x10  // Throw OdEdUnknownCommand exception if command was not found.
  };
  /** \details
    Returns the OdEdCommand object with the specified name in this Stack object. 

    \param commandName [in]  Name of the command to find.
    \param lookupFlags [in]  Specified where command lookup is to look.
    \param groupName [in]  Group name.
    
    \returns
    Returns a SmartPointer to the OdEdCommand object if successful, otherwise a null SmartPointer.
\remarks
    This function searches for command names in the group order on the stack.
    
    If groupName is specified, only that group will be searched.

    lookupFlags must be a combination of one or more of the following:
    
    <table>
    Name              Value     Description
    kGlobal           0x01      Search global (untranslated) names.
    kLocal            0x02      Search local (translated) names.
    kSpecifedGroup    0x04      Search in specified group only.
    kUndefed          0x08      Indicates whether or not to return commands that are currently marked as undefined.
    </table>
    
  */
  virtual OdEdCommandPtr lookupCmd(
    const OdChar * commandName,
    int lookupFlags = kGlobal|kLocal,
    const OdString& groupName = OdString::kEmpty);

   /** Description:
    Returns the OdEdCommand object with the specified name in this Stack object. 

    Arguments:
    cmdName       (I) Name of the command to find.
    globalFlag    (I) Input Boolean flag which specifies if the command lookup is to be performed on global and untranslated or local and translated command names 
    allGroupsFlag (I) Input Boolean flag indicating whether to search only the command group at the top of the CommandStack, or all command groups 
    skipUndefed   (I) Input Boolean flag indicating whether or not to skip past commands that are currently marked as undefined 

    Remarks:
    Returns a SmartPointer to the OdEdCommand object if successful, otherwise a null SmartPointer.
  */
  virtual OdEdCommand* lookupGlobalCmd(const OdChar * cmdName) = 0;
  virtual OdEdCommand* lookupLocalCmd(const OdChar * cmdName) = 0;
  virtual OdEdCommand* lookupCmd(const OdChar * cmdName, bool globalFlag) = 0;
  virtual OdEdCommand* lookupCmd(const OdChar * cmdName, bool globalFlag, bool allGroupsFlag) = 0;
  virtual OdEdCommand* lookupCmd(const OdChar * cmdName, bool globalFlag, bool allGroupsFlag, bool skipUndefed) = 0;

  //This function is for internal system use only.
  virtual OdEdCommand* lookupCmd2(const OdChar * cmdName, bool globalFlag, bool allGroupsFlag, int skipFlags, bool match = false) = 0;

  /** \details
    Executes the specified command in this Stack object. 
    
    \remarks
    OdEdCommandStackReactor objects in the reactor list of this Stack object will be notified.

    \param pCommand [in]  Pointer to the command object to execute.
    \param pCmdCtx [in]  Pointer to the command context.

    \remarks
    The specified command context object is used to interact with the 
    calling application as part of an interactive command.  

    This function searches for both global and local command names in the group order on the stack.

    \sa
    OdEdCommand::execute.
  */
  virtual void executeCommand(OdEdCommand* pCmd, OdEdCommandContext* pCmdCtx);

  /** \details
    Executes the specified command in this Stack object. 

    \param cmdName [in]  Name of the command to find.
    \param pCmdCtx [in]  Pointer to the command *context*.
    \param lookupFlags [in]  Specified where command lookup is to look.
    \param groupName [in]  Group *name*.
    
    \remarks
    Lookups a command object registred in this Stack object by a cpecified cmdName,
    lookupFlags and groupName and executes it. If command was not found then method fires
    OdEdCommandStackReactor::unknownCommand() event that may provide back a command object
    for the given name. So if a command object was provided by one of the reactors then
    implementation of this method executs it. If one was provided by neither of the reactors and
    kThrowUnknown flag was specified in lookupFlags then OdEdUnknownCommand would be thrown.
    If kThrowUnknown flag was not specified the method just exits.
    
    If groupName is specified, only that group will be searched.

    lookupFlags must be a combination of one or more of the following:
    
    <table>
    Name              Value     Description
    kGlobal           0x01      Search global (untranslated) names.
    kLocal            0x02      Search local (translated) names.
    kSpecifedGroup    0x04      Search in specified group only.
    kUndefed          0x08      Indicates whether or not to return commands that are currently marked as undefined.
    kThrowUnknown     0x10      Throw OdEdUnknownCommand exception if command was not found.
    </table>   

    \sa
    OdEdCommandStack::lookupCmd,
    OdEdCommandStackReactor::unknownCommand,
    OdEdCommand::execute.
  */
  virtual void executeCommand(const OdString& cmdName,
                              OdEdCommandContext* pCmdCtx,
                              int lookupFlags = kGlobal|kLocal,
                              const OdString& groupName = OdString::kEmpty);

  /** \details
    Removes the command with the specified group and global names from this Stack object.

    \param groupName [in]  Group name.
    \param globalName [in]  Global (untranslated) name.
    
    \remarks
    If a group is emptied, it is removed from this Stack object.
    
    If the specified command is not found, this function does nothing but return.
  */
  virtual OdResult removeCmd(const OdChar* groupName, const OdChar* globalName) = 0;

  
  virtual OdResult removeCmd(const OdEdCommand* pCommand);

  /** \details
    Removes the specified group and its commands from this Stack object.

    \param groupName [in]  Group name.

    \remarks
    If the specified group is not found, this function does nothing but return.
  */
  virtual OdResult removeGroup(const OdChar* groupName) = 0;
  /** \details
    This function pops the cmdGroupName command group to the top of the 
    command stack making it the first group to be searched when resolving 
    application defined command names.

    \param cmdGroupName [in]  Name of the command group to pop to the top of the command stack.

    \remarks
    If the specified group is not found, this function returns eKeyNotFound.
  */
  virtual OdResult popGroupToTop(const OdChar* cmdGroupName) = 0;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdEdCommandStack object pointers. 
*/
typedef OdSmartPtr<OdEdCommandStack> OdEdCommandStackPtr;

/** \details
    Returns the global command stack.
*/
FIRSTDLL_EXPORT OdEdCommandStackPtr odedRegCmds();

class FIRSTDLL_EXPORT OdEdCommandIterator : public OdRxObject
{
public:
	ODRX_DECLARE_MEMBERS(OdEdCommandIterator);

	virtual bool               done() const = 0;
	virtual bool               next() = 0;
	virtual const OdEdCommand* command() const = 0;
	virtual const OdChar*      commandGroup() const = 0;
};

#include "../TD_PackPop.h"

#endif //#ifndef _ODEDCOMMANDSTACK_H_INCLUDED_
