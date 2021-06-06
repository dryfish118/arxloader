#include "pch.h"
#include "util.h"

ACRX_DEFINE_MEMBERS_WORKER(CGlobalUtil, ACBASE_PORT)

class CDebugerImpl : public CDebuger
{
public:
  CDebugerImpl() {}
  virtual ~CDebugerImpl() {}

public:
  virtual void printInfo(const AcString& msg, MessageLevel = kInfo);
  virtual void printError(Acad::ErrorStatus es, const AcString& prefex = L"");

  virtual void failure_eq(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void failure_ne(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void failure_le(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void failure_lt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void failure_ge(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void failure_gt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void assert_eq(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void assert_ne(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void assert_le(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void assert_lt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void assert_ge(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
  virtual void assert_gt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line);
};

CGlobalUtilImpl::CGlobalUtilImpl()
{
  m_debuger = std::make_unique<CDebugerImpl>();
}

CDebuger* CGlobalUtilImpl::debuger() const
{
  return m_debuger.get();
}

AcDbObjectId CGlobalUtilImpl::addToModelSpace(AcDbEntity* pEntity)
{
  AcDbObjectId objId;
  if (pEntity)
  {
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (pDb)
    {
      AcDbBlockTableRecordPointer pBTR(ACDB_MODEL_SPACE, pDb, AcDb::kForWrite);
      if (Acad::eOk == pBTR.openStatus())
      {
        pBTR->appendAcDbEntity(objId, pEntity);
      }
    }
  }

  return objId;
}

void CDebugerImpl::printInfo(const AcString& msg, MessageLevel)
{
  acutPrintf(msg);
}

void CDebugerImpl::printError(Acad::ErrorStatus es, const AcString& prefex)
{
  AcString strOut;
  switch (es)
  {
  case Acad::eOk:
    break;
  case Acad::eNotImplementedYet:
    break;
  case Acad::eNotApplicable:
    break;
  case Acad::eInvalidInput:
    break;
  case Acad::eAmbiguousInput:
    break;
  case Acad::eAmbiguousOutput:
    break;
  case Acad::eOutOfMemory:
    break;
  case Acad::eBufferTooSmall:
    break;
  case Acad::eInvalidOpenState:
    break;
  case Acad::eEntityInInactiveLayout:
    break;
  case Acad::eHandleExists:
    break;
  case Acad::eNullHandle:
    break;
  case Acad::eBrokenHandle:
    break;
  case Acad::eUnknownHandle:
    break;
  case Acad::eHandleInUse:
    break;
  case Acad::eNullObjectPointer:
    break;
  case Acad::eNullObjectId:
    break;
  case Acad::eNullBlockName:
    break;
  case Acad::eContainerNotEmpty:
    break;
  case Acad::eNullEntityPointer:
    break;
  case Acad::eIllegalEntityType:
    break;
  case Acad::eKeyNotFound:
    break;
  case Acad::eDuplicateKey:
    break;
  case Acad::eInvalidIndex:
    break;
  case Acad::eDuplicateIndex:
    break;
  case Acad::eAlreadyInDb:
    break;
  case Acad::eOutOfDisk:
    break;
  case Acad::eDeletedEntry:
    break;
  case Acad::eNegativeValueNotAllowed:
    break;
  case Acad::eInvalidExtents:
    break;
  case Acad::eInvalidAdsName:
    break;
  case Acad::eInvalidSymbolTableName:
    break;
  case Acad::eInvalidKey:
    break;
  case Acad::eWrongObjectType:
    break;
  case Acad::eWrongDatabase:
    break;
  case Acad::eObjectToBeDeleted:
    break;
  case Acad::eInvalidDwgVersion:
    break;
  case Acad::eAnonymousEntry:
    break;
  case Acad::eIllegalReplacement:
    break;
  case Acad::eEndOfObject:
    break;
  case Acad::eEndOfFile:
    break;
  case Acad::eIsReading:
    break;
  case Acad::eIsWriting:
    break;
  case Acad::eNotOpenForRead:
    break;
  case Acad::eNotOpenForWrite:
    break;
  case Acad::eNotThatKindOfClass:
    strOut = L"eNotThatKindOfClass";
    break;
  case Acad::eInvalidBlockName:
    break;
  case Acad::eMissingDxfField:
    break;
  case Acad::eDuplicateDxfField:
    break;
  case Acad::eInvalidDxfCode:
    break;
  case Acad::eInvalidResBuf:
    break;
  case Acad::eBadDxfSequence:
    break;
  case Acad::eFilerError:
    break;
  case Acad::eVertexAfterFace:
    break;
  case Acad::eInvalidFaceVertexIndex:
    break;
  case Acad::eInvalidMeshVertexIndex:
    break;
  case Acad::eOtherObjectsBusy:
    break;
  case Acad::eMustFirstAddBlockToDb:
    break;
  case Acad::eCannotNestBlockDefs:
    break;
  case Acad::eDwgRecoveredOK:
    break;
  case Acad::eDwgNotRecoverable:
    break;
  case Acad::eDxfPartiallyRead:
    break;
  case Acad::eDxfReadAborted:
    break;
  case Acad::eDxbPartiallyRead:
    break;
  case Acad::eDwgCRCDoesNotMatch:
    break;
  case Acad::eDwgSentinelDoesNotMatch:
    break;
  case Acad::eDwgObjectImproperlyRead:
    break;
  case Acad::eNoInputFiler:
    break;
  case Acad::eDwgNeedsAFullSave:
    break;
  case Acad::eDxbReadAborted:
    break;
  case Acad::eFileLockedByACAD:
    break;
  case Acad::eFileAccessErr:
    break;
  case Acad::eFileSystemErr:
    break;
  case Acad::eFileInternalErr:
    break;
  case Acad::eFileTooManyOpen:
    break;
  case Acad::eFileNotFound:
    break;
  case Acad::eDwkLockFileFound:
    break;
  case Acad::eWasErased:
    break;
  case Acad::ePermanentlyErased:
    break;
  case Acad::eWasOpenForRead:
    break;
  case Acad::eWasOpenForWrite:
    break;
  case Acad::eWasOpenForUndo:
    break;
  case Acad::eWasNotifying:
    break;
  case Acad::eWasOpenForNotify:
    break;
  case Acad::eOnLockedLayer:
    break;
  case Acad::eMustOpenThruOwner:
    break;
  case Acad::eSubentitiesStillOpen:
    break;
  case Acad::eAtMaxReaders:
    break;
  case Acad::eIsWriteProtected:
    break;
  case Acad::eIsXRefObject:
    break;
  case Acad::eNotAnEntity:
    break;
  case Acad::eHadMultipleReaders:
    break;
  case Acad::eDuplicateRecordName:
    break;
  case Acad::eXRefDependent:
    break;
  case Acad::eSelfReference:
    break;
  case Acad::eMissingSymbolTable:
    break;
  case Acad::eMissingSymbolTableRec:
    break;
  case Acad::eWasNotOpenForWrite:
    break;
  case Acad::eCloseWasNotifying:
    break;
  case Acad::eCloseModifyAborted:
    break;
  case Acad::eClosePartialFailure:
    break;
  case Acad::eCloseFailObjectDamaged:
    break;
  case Acad::eCannotBeErasedByCaller:
    break;
  case Acad::eCannotBeResurrected:
    break;
  case Acad::eWasNotErased:
    break;
  case Acad::eInsertAfter:
    break;
  case Acad::eFixedAllErrors:
    break;
  case Acad::eLeftErrorsUnfixed:
    break;
  case Acad::eUnrecoverableErrors:
    break;
  case Acad::eNoDatabase:
    break;
  case Acad::eXdataSizeExceeded:
    break;
  case Acad::eRegappIdNotFound:
    break;
  case Acad::eRepeatEntity:
    break;
  case Acad::eRecordNotInTable:
    break;
  case Acad::eIteratorDone:
    break;
  case Acad::eNullIterator:
    break;
  case Acad::eNotInBlock:
    break;
  case Acad::eOwnerNotInDatabase:
    break;
  case Acad::eOwnerNotOpenForRead:
    break;
  case Acad::eOwnerNotOpenForWrite:
    break;
  case Acad::eExplodeBeforeTransform:
    break;
  case Acad::eCannotScaleNonUniformly:
    break;
  case Acad::eNotInDatabase:
    break;
  case Acad::eNotCurrentDatabase:
    break;
  case Acad::eIsAnEntity:
    break;
  case Acad::eCannotChangeActiveViewport:
    break;
  case Acad::eNotInPaperspace:
    break;
  case Acad::eCommandWasInProgress:
    break;
  case Acad::eGeneralModelingFailure:
    break;
  case Acad::eOutOfRange:
    break;
  case Acad::eNonCoplanarGeometry:
    break;
  case Acad::eDegenerateGeometry:
    break;
  case Acad::eInvalidAxis:
    break;
  case Acad::ePointNotOnEntity:
    break;
  case Acad::eSingularPoint:
    break;
  case Acad::eInvalidOffset:
    break;
  case Acad::eNonPlanarEntity:
    break;
  case Acad::eCannotExplodeEntity:
    break;
  case Acad::eStringTooLong:
    break;
  case Acad::eInvalidSymTableFlag:
    break;
  case Acad::eUndefinedLineType:
    break;
  case Acad::eInvalidTextStyle:
    break;
  case Acad::eTooFewLineTypeElements:
    break;
  case Acad::eTooManyLineTypeElements:
    break;
  case Acad::eExcessiveItemCount:
    break;
  case Acad::eIgnoredLinetypeRedef:
    break;
  case Acad::eBadUCS:
    break;
  case Acad::eBadPaperspaceView:
    break;
  case Acad::eSomeInputDataLeftUnread:
    break;
  case Acad::eNoInternalSpace:
    break;
  case Acad::eInvalidDimStyle:
    break;
  case Acad::eInvalidLayer:
    break;
  case Acad::eUserBreak:
    break;
  case Acad::eUserUnloaded:
    break;
  case Acad::eDwgNeedsRecovery:
    break;
  case Acad::eDeleteEntity:
    break;
  case Acad::eInvalidFix:
    break;
  case Acad::eFSMError:
    break;
  case Acad::eBadLayerName:
    break;
  case Acad::eLayerGroupCodeMissing:
    break;
  case Acad::eBadColorIndex:
    break;
  case Acad::eBadLinetypeName:
    break;
  case Acad::eBadLinetypeScale:
    break;
  case Acad::eBadVisibilityValue:
    break;
  case Acad::eProperClassSeparatorExpected:
    break;
  case Acad::eBadLineWeightValue:
    break;
  case Acad::eBadColor:
    break;
  case Acad::eBadMaterialName:
    break;
  case Acad::ePagerError:
    break;
  case Acad::eOutOfPagerMemory:
    break;
  case Acad::ePagerWriteError:
    break;
  case Acad::eWasNotForwarding:
    break;
  case Acad::eInvalidIdMap:
    break;
  case Acad::eInvalidOwnerObject:
    break;
  case Acad::eOwnerNotSet:
    break;
  case Acad::eWrongSubentityType:
    break;
  case Acad::eTooManyVertices:
    break;
  case Acad::eTooFewVertices:
    break;
  case Acad::eNoActiveTransactions:
    break;
  case Acad::eNotTopTransaction:
    break;
  case Acad::eTransactionOpenWhileCommandEnded:
    break;
  case Acad::eInProcessOfCommitting:
    break;
  case Acad::eNotNewlyCreated:
    break;
  case Acad::eLongTransReferenceError:
    break;
  case Acad::eNoWorkSet:
    break;
  case Acad::eAlreadyInGroup:
    break;
  case Acad::eNotInGroup:
    break;
  case Acad::eAlreadyInferred:
    break;
  case Acad::eInvalidREFIID:
    break;
  case Acad::eInvalidNormal:
    break;
  case Acad::eInvalidStyle:
    break;
  case Acad::eCannotRestoreFromAcisFile:
    break;
  case Acad::eMakeMeProxy:
    break;
  case Acad::eNLSFileNotAvailable:
    break;
  case Acad::eNotAllowedForThisProxy:
    break;
  case Acad::eNotClonedPrimaryProxy:
    break;
  case Acad::eNotSupportedInDwgApi:
    break;
  case Acad::ePolyWidthLost:
    break;
  case Acad::eNullExtents:
    break;
  case Acad::eBadDwgHeader:
    break;
  case Acad::eLockViolation:
    break;
  case Acad::eLockConflict:
    break;
  case Acad::eDatabaseObjectsOpen:
    break;
  case Acad::eLockChangeInProgress:
    break;
  case Acad::eVetoed:
    break;
  case Acad::eNoDocument:
    break;
  case Acad::eNotFromThisDocument:
    break;
  case Acad::eLISPActive:
    break;
  case Acad::eTargetDocNotQuiescent:
    break;
  case Acad::eDocumentSwitchDisabled:
    break;
  case Acad::eInvalidContext:
    break;
  case Acad::eCreateFailed:
    break;
  case Acad::eCreateInvalidName:
    break;
  case Acad::eSetFailed:
    break;
  case Acad::eDelDoesNotExist:
    break;
  case Acad::eDelIsModelSpace:
    break;
  case Acad::eDelLastLayout:
    break;
  case Acad::eDelUnableToSetCurrent:
    break;
  case Acad::eDelUnableToFind:
    break;
  case Acad::eRenameDoesNotExist:
    break;
  case Acad::eRenameIsModelSpace:
    break;
  case Acad::eRenameInvalidLayoutName:
    break;
  case Acad::eRenameLayoutAlreadyExists:
    break;
  case Acad::eRenameInvalidName:
    break;
  case Acad::eCopyDoesNotExist:
    break;
  case Acad::eCopyIsModelSpace:
    break;
  case Acad::eCopyFailed:
    break;
  case Acad::eCopyInvalidName:
    break;
  case Acad::eCopyNameExists:
    break;
  case Acad::eProfileDoesNotExist:
    break;
  case Acad::eInvalidFileExtension:
    break;
  case Acad::eInvalidProfileName:
    break;
  case Acad::eFileExists:
    break;
  case Acad::eProfileIsInUse:
    break;
  case Acad::eCantOpenFile:
    break;
  case Acad::eNoFileName:
    break;
  case Acad::eRegistryAccessError:
    break;
  case Acad::eRegistryCreateError:
    break;
  case Acad::eBadDxfFile:
    break;
  case Acad::eUnknownDxfFileFormat:
    break;
  case Acad::eMissingDxfSection:
    break;
  case Acad::eInvalidDxfSectionName:
    break;
  case Acad::eNotDxfHeaderGroupCode:
    break;
  case Acad::eUndefinedDxfGroupCode:
    break;
  case Acad::eNotInitializedYet:
    break;
  case Acad::eInvalidDxf2dPoint:
    break;
  case Acad::eInvalidDxf3dPoint:
    break;
  case Acad::eBadlyNestedAppData:
    break;
  case Acad::eIncompleteBlockDefinition:
    break;
  case Acad::eIncompleteComplexObject:
    break;
  case Acad::eBlockDefInEntitySection:
    break;
  case Acad::eNoBlockBegin:
    break;
  case Acad::eDuplicateLayerName:
    break;
  case Acad::eBadPlotStyleName:
    break;
  case Acad::eDuplicateBlockName:
    break;
  case Acad::eBadPlotStyleType:
    break;
  case Acad::eBadPlotStyleNameHandle:
    break;
  case Acad::eUndefineShapeName:
    break;
  case Acad::eDuplicateBlockDefinition:
    break;
  case Acad::eMissingBlockName:
    break;
  case Acad::eBinaryDataSizeExceeded:
    break;
  case Acad::eObjectIsReferenced:
    break;
  case Acad::eNoThumbnailBitmap:
    break;
  case Acad::eGuidNoAddress:
    break;
  case Acad::eMustBe0to2:
    break;
  case Acad::eMustBe0to3:
    break;
  case Acad::eMustBe0to4:
    break;
  case Acad::eMustBe0to5:
    break;
  case Acad::eMustBe0to8:
    break;
  case Acad::eMustBe1to8:
    break;
  case Acad::eMustBe1to15:
    break;
  case Acad::eMustBePositive:
    break;
  case Acad::eMustBeNonNegative:
    break;
  case Acad::eMustBeNonZero:
    break;
  case Acad::eMustBe1to6:
    break;
  case Acad::eNoPlotStyleTranslationTable:
    break;
  case Acad::ePlotStyleInColorDependentMode:
    break;
  case Acad::eMaxLayouts:
    break;
  case Acad::eNoClassId:
    break;
  case Acad::eUndoOperationNotAvailable:
    break;
  case Acad::eUndoNoGroupBegin:
    break;
  case Acad::eHatchTooDense:
    break;
  case Acad::eOpenFileCancelled:
    break;
  case Acad::eNotHandled:
    break;
  case Acad::eMakeMeProxyAndResurrect:
    break;
  case Acad::eFileSharingViolation:
    break;
  case Acad::eUnsupportedFileFormat:
    break;
  case Acad::eObsoleteFileFormat:
    break;
  case Acad::eFileMissingSections:
    break;
  case Acad::eRepeatedDwgRead:
    break;
  case Acad::eSilentOpenFileCancelled:
    break;
  case Acad::eWrongCellType:
    break;
  case Acad::eCannotChangeColumnType:
    break;
  case Acad::eRowsMustMatchColumns:
    break;
  case Acad::eNullNodeId:
    break;
  case Acad::eNoNodeActive:
    break;
  case Acad::eGraphContainsProxies:
    break;
  case Acad::eDwgShareDemandLoad:
    break;
  case Acad::eDwgShareReadAccess:
    break;
  case Acad::eDwgShareWriteAccess:
    break;
  case Acad::eLoadFailed:
    break;
  case Acad::eDeviceNotFound:
    break;
  case Acad::eNoCurrentConfig:
    break;
  case Acad::eNullPtr:
    break;
  case Acad::eNoLayout:
    break;
  case Acad::eIncompatiblePlotSettings:
    break;
  case Acad::eNonePlotDevice:
    break;
  case Acad::eNoMatchingMedia:
    break;
  case Acad::eInvalidView:
    break;
  case Acad::eInvalidWindowArea:
    break;
  case Acad::eInvalidPlotArea:
    break;
  case Acad::eCustomSizeNotPossible:
    break;
  case Acad::ePageCancelled:
    break;
  case Acad::ePlotCancelled:
    break;
  case Acad::eInvalidEngineState:
    break;
  case Acad::ePlotAlreadyStarted:
    break;
  case Acad::eNoErrorHandler:
    break;
  case Acad::eInvalidPlotInfo:
    break;
  case Acad::eNumberOfCopiesNotSupported:
    break;
  case Acad::eLayoutNotCurrent:
    break;
  case Acad::eGraphicsNotGenerated:
    break;
  case Acad::eCannotPlotToFile:
    break;
  case Acad::eMustPlotToFile:
    break;
  case Acad::eNotMultiPageCapable:
    break;
  case Acad::eBackgroundPlotInProgress:
    break;
  case Acad::eNotShownInPropertyPalette:
    break;
  case Acad::eSubSelectionSetEmpty:
    break;
  case Acad::eNoIntersections:
    break;
  case Acad::eEmbeddedIntersections:
    break;
  case Acad::eNoOverride:
    break;
  case Acad::eNoStoredOverrides:
    break;
  case Acad::eUnableToRetrieveOverrides:
    break;
  case Acad::eUnableToStoreOverrides:
    break;
  case Acad::eUnableToRemoveOverrides:
    break;
  case Acad::eNoStoredReconcileStatus:
    break;
  case Acad::eUnableToStoreReconcileStatus:
    break;
  case Acad::eInvalidObjectId:
    break;
  case Acad::eInvalidXrefObjectId:
    break;
  case Acad::eNoViewAssociation:
    break;
  case Acad::eNoLabelBlock:
    break;
  case Acad::eUnableToSetViewAssociation:
    break;
  case Acad::eUnableToGetViewAssociation:
    break;
  case Acad::eUnableToSetLabelBlock:
    break;
  case Acad::eUnableToGetLabelBlock:
    break;
  case Acad::eUnableToRemoveAssociation:
    break;
  case Acad::eUnableToSyncModelView:
    break;
  case Acad::eDataLinkAdapterNotFound:
    break;
  case Acad::eDataLinkInvalidAdapterId:
    break;
  case Acad::eDataLinkNotFound:
    break;
  case Acad::eDataLinkBadConnectionString:
    break;
  case Acad::eDataLinkNotUpdatedYet:
    break;
  case Acad::eDataLinkSourceNotFound:
    break;
  case Acad::eDataLinkConnectionFailed:
    break;
  case Acad::eDataLinkSourceUpdateNotAllowed:
    break;
  case Acad::eDataLinkSourceIsWriteProtected:
    break;
  case Acad::eDataLinkExcelNotFound:
    break;
  case Acad::eDataLinkOtherError:
    break;
  case Acad::eXrefReloaded:
    break;
  case Acad::eXrefReloadImpossibleAtThisTime:
    break;
  case Acad::eSecInitializationFailure:
    break;
  case Acad::eSecErrorReadingFile:
    break;
  case Acad::eSecErrorWritingFile:
    break;
  case Acad::eSecInvalidDigitalID:
    break;
  case Acad::eSecErrorGeneratingTimestamp:
    break;
  case Acad::eSecErrorComputingSignature:
    break;
  case Acad::eSecErrorWritingSignature:
    break;
  case Acad::eSecErrorEncryptingData:
    break;
  case Acad::eSecErrorCipherNotSupported:
    break;
  case Acad::eSecErrorDecryptingData:
    break;
  case Acad::eNoAcDbHostApplication:
    break;
  case Acad::eNoUnderlayHost:
    break;
  case Acad::ePCUnknown:
    break;
  case Acad::ePCLargeData:
    break;
  case Acad::ePCUnknownFileType:
    break;
  case Acad::ePCFileNotFound:
    break;
  case Acad::ePCFileNotCreated:
    break;
  case Acad::ePCFileNotOpened:
    break;
  case Acad::ePCFileNotClosed:
    break;
  case Acad::ePCFileNotWritten:
    break;
  case Acad::ePCFileWrongFormat:
    break;
  case Acad::ePCFileDataSelectorInvalid:
    break;
  case Acad::ePCCoordSysReprojectFail:
    break;
  case Acad::ePCDiskSpaceTooSmall:
    break;
  case Acad::ePCThreadTerminated:
    break;
  case Acad::ePCFileNotErased:
    break;
  case Acad::ePCCoordSysAssignFail:
    break;
  case Acad::ePCLastImporterUnfinished:
    break;
  case Acad::ePCNoEngineInfo:
    break;
  case Acad::ePCInProgress:
    break;
  case Acad::eInetBase:
    break;
    //   case Acad::eInetOk:
    //     break;
  case Acad::eInetInCache:
    break;
  case Acad::eInetFileNotFound:
    break;
  case Acad::eInetBadPath:
    break;
  case Acad::eInetTooManyOpenFiles:
    break;
  case Acad::eInetFileAccessDenied:
    break;
  case Acad::eInetInvalidFileHandle:
    break;
  case Acad::eInetDirectoryFull:
    break;
  case Acad::eInetHardwareError:
    break;
  case Acad::eInetSharingViolation:
    break;
  case Acad::eInetDiskFull:
    break;
  case Acad::eInetFileGenericError:
    break;
  case Acad::eInetValidURL:
    break;
  case Acad::eInetNotAnURL:
    break;
  case Acad::eInetNoWinInet:
    break;
  case Acad::eInetOldWinInet:
    break;
  case Acad::eInetNoAcadInet:
    break;
  case Acad::eInetNotImplemented:
    break;
  case Acad::eInetProtocolNotSupported:
    break;
  case Acad::eInetCreateInternetSessionFailed:
    break;
  case Acad::eInetInternetSessionConnectFailed:
    break;
  case Acad::eInetInternetSessionOpenFailed:
    break;
  case Acad::eInetInvalidAccessType:
    break;
  case Acad::eInetFileOpenFailed:
    break;
  case Acad::eInetHttpOpenRequestFailed:
    break;
  case Acad::eInetUserCancelledTransfer:
    break;
  case Acad::eInetHttpBadRequest:
    break;
  case Acad::eInetHttpAccessDenied:
    break;
  case Acad::eInetHttpPaymentRequired:
    break;
  case Acad::eInetHttpRequestForbidden:
    break;
  case Acad::eInetHttpObjectNotFound:
    break;
  case Acad::eInetHttpBadMethod:
    break;
  case Acad::eInetHttpNoAcceptableResponse:
    break;
  case Acad::eInetHttpProxyAuthorizationRequired:
    break;
  case Acad::eInetHttpTimedOut:
    break;
  case Acad::eInetHttpConflict:
    break;
  case Acad::eInetHttpResourceGone:
    break;
  case Acad::eInetHttpLengthRequired:
    break;
  case Acad::eInetHttpPreconditionFailure:
    break;
  case Acad::eInetHttpRequestTooLarge:
    break;
  case Acad::eInetHttpUriTooLong:
    break;
  case Acad::eInetHttpUnsupportedMedia:
    break;
  case Acad::eInetHttpServerError:
    break;
  case Acad::eInetHttpNotSupported:
    break;
  case Acad::eInetHttpBadGateway:
    break;
  case Acad::eInetHttpServiceUnavailable:
    break;
  case Acad::eInetHttpGatewayTimeout:
    break;
  case Acad::eInetHttpVersionNotSupported:
    break;
  case Acad::eInetInternetError:
    break;
  case Acad::eInetGenericException:
    break;
  case Acad::eInetUnknownError:
    break;
  case Acad::eAlreadyActive:
    break;
  case Acad::eAlreadyInactive:
    break;
  case Acad::eGraphEdgeNotFound:
    break;
  case Acad::eGraphNodeNotFound:
    break;
  case Acad::eGraphNodeAlreadyExists:
    break;
  case Acad::eGraphEdgeAlreadyExists:
    break;
  case Acad::eGraphCyclesFound:
    break;
  case Acad::eAlreadyHasRepresentation:
    break;
  case Acad::eNoRepresentation:
    break;
  case Acad::eFailedToSetEdgeChamfers:
    break;
  case Acad::eNoConnectedBlendSet:
    break;
  case Acad::eFailedToBlend:
    break;
  case Acad::eFailedToSetEdgeRounds:
    break;
  case Acad::eFailedToSetVertexRounds:
    break;
  case Acad::eVSNotFound:
    break;
  case Acad::eVSTrue:
    break;
  case Acad::eVSFalse:
    break;
  case Acad::eVSAlreadyExists:
    break;
  case Acad::eVSOneOffCreated:
    break;
  case Acad::eVSAPIOnlyValues:
    break;
  case Acad::eVSIsInUse:
    break;
  case Acad::eVSIsAcadDefault:
    break;
  case Acad::eEmptyOperand:
    break;
  case Acad::eNoEntitiesFromPersistentIds:
    break;
  case Acad::eFailedCurveCheck:
    break;
  case Acad::eMaxNodes:
    break;
  case Acad::eFailedToEvaluate:
    break;
  case Acad::eFailedToEvaluateDependents:
    break;
  case Acad::eInvalidExpression:
    break;
  case Acad::eCyclicDependency:
    break;
  case Acad::eInconsistentConstraint:
    break;
  case Acad::eOverDefinedConstraint:
    break;
  case Acad::eAllInSameRigidSet:
    break;
  case Acad::eInvalidParameterName:
    break;
  case Acad::eReferencedInEquation:
    break;
  case Acad::eEntityRestricedInDOF:
    break;
  case Acad::eDataTooLarge:
    break;
  case Acad::eNearSizeLimit:
    break;
  case Acad::eStringNotAllowedInExpression:
    break;
  case Acad::eTooManyActiveCommands:
    break;
  case Acad::eUnableToTrimLastPiece:
    break;
  case Acad::eUnableToTrimSurface:
    break;
  case Acad::eModifyingAssociativeEntity:
    break;
  case Acad::eModifyingDimensionWithExpression:
    break;
  case Acad::eDependentOnObjectErased:
    break;
  case Acad::eSelfIntersecting:
    break;
  case Acad::eNotOnBoundary:
    break;
  case Acad::eNotConnected:
    break;
  case Acad::eNoInputPath:
    break;
  case Acad::eNotAssociative:
    break;
  case Acad::eNotG1Continuous:
    break;
  case Acad::eOwnerToBeTransformed:
    break;
  case Acad::eMustBeInteger:
    break;
  case Acad::eMustBePositiveInteger:
    break;
  case Acad::eChangedAgainstAssociativity:
    break;
  case Acad::eItemCountChanged:
    break;
  case Acad::eGetAdIntImgServicesFailed:
    break;
  case Acad::eReadImageBufferFailed:
    break;
  case Acad::eWriteImageBufferFailed:
    break;
  case Acad::eGetImageBytesFailed:
    break;
  case Acad::eGetImageDIBFailed:
    break;
  case Acad::eConvertImageFormatFailed:
    break;
  case Acad::eGetPreviewImageFailed:
    break;
  case Acad::eInvalidPreviewImage:
    break;
  case Acad::eDelayMore:
    break;
  case Acad::ePreviewFailed:
    break;
  case Acad::eAbortPreview:
    break;
  case Acad::eEndPreview:
    break;
  case Acad::eNoPreviewContext:
    break;
  case Acad::eFileNotInCloud:
    break;
  default:
    break;
  }

  if (!strOut.isEmpty())
  {
    AcString msg;
    if (prefex.isEmpty())
    {
      msg.format(L"\n\tReturn error status(%d): %s", es, strOut.constPtr());
    }
    else
    {
      msg.format(L"\n\tprefex(%d): %s", prefex.constPtr(), es, strOut.constPtr());
    }
    printInfo(msg);
  }
}

void CDebugerImpl::failure_eq(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::failure_ne(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::failure_le(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::failure_lt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::failure_ge(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::failure_gt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::assert_eq(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::assert_ne(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::assert_le(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::assert_lt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::assert_ge(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}

void CDebugerImpl::assert_gt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line)
{

}
