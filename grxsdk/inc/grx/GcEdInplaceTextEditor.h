#pragma once
#include "gcadstd.h"
#include "dbtexteditor.h"

class IPE_Editor;
class GcEdInplaceTextEditor;
class IGcEdInplaceTextEditorHost;
class GcEdInplaceTextEditorSettingsImp;
class GcEdInplaceTextEditorImp;

class GcEdInplaceTextEditorSettings
{
public:
  GCED_DLL_DECL GcEdInplaceTextEditorSettings();
  GCED_DLL_DECL ~GcEdInplaceTextEditorSettings();

  enum EntityType
  {
    kDefault,
    kTableCell,
    kMultiAttribute
  };

  enum EditFlags
  {
    kForceOpaqueBackground = 1 << 0,
    kSelectAll = 1 << 1,
    kCursorAtEnd = 1 << 2,
  };

public:
  GCED_DLL_DECL int               editFlags() const;
  GCED_DLL_DECL Gcad::ErrorStatus setEditFlags(int flags);

  GCED_DLL_DECL EntityType        sourceEntityType() const;
  GCED_DLL_DECL Gcad::ErrorStatus setSourceEntityType(EntityType type);

  GCED_DLL_DECL bool              tabSupported() const;
  GCED_DLL_DECL Gcad::ErrorStatus setSupportTab(bool bTab);

  GCED_DLL_DECL bool              simpleMText() const;
  GCED_DLL_DECL Gcad::ErrorStatus setSimpleMText(bool bSimpleMText);

  GCED_DLL_DECL double            definedHeight() const;
  GCED_DLL_DECL Gcad::ErrorStatus setDefinedHeight(double height);
protected:
  GcEdInplaceTextEditorSettingsImp* m_pImp;
private:
  GcEdInplaceTextEditorSettings(const GcEdInplaceTextEditorSettings& editor);
  GcEdInplaceTextEditorSettings& operator=(const GcEdInplaceTextEditorSettings& editor);
};

class GcEdInplaceTextEditor : public GcDbTextEditor
{
public:
  GCED_DLL_DECL static GcEdInplaceTextEditor* current();

  GCED_DLL_DECL void setHost(IGcEdInplaceTextEditorHost* pHost);

  GCED_DLL_DECL static Gcad::ErrorStatus invoke(GcDbMText* pMtext, const GcEdInplaceTextEditorSettings* pSettings);
  GCED_DLL_DECL static Gcad::ErrorStatus invoke(GcDbText* pText, GcDbObjectIdArray* appendedEntities);

public:
  enum TextUndoType {
    kUndoTyping = 1,
    kUndoBoldOn,
    kUndoBoldOff,
    kUndoItalicOn,
    kUndoItalicOff,
    kUndoUnderlineOn,
    kUndoUnderlineOff,
    kUndoOverlineOn,
    kUndoOverlineOff,
    kUndoFont,
    kUndoHeight,
    kUndoColor,
    kUndoObliqueAngle,
    kUndoWidthScale,
    kUndoTrackingFactor,
    kUndoLanguage,
    kUndoBackspace,
    kUndoDelete,
    kUndoPaste,
    kUndoCut,
    kUndoStack,
    kUndoUnstack,
    kUndoStackProperties,
    kUndoFieldInsert,
    kUndoFieldConvert,
    kUndoFieldUpdate,
    kUndoSymbolInsert,
    kUndoAutoField,
    kUndoAutoStack,
    kUndoAutoSymbol,
    kUndoAutoDTextEscape,
    kUndoAutoMifOrCif,
    kUndoAutoDimension,
    kUndoAutoDimBreak,
    kUndoAutoSpell,
    kUndoStyle,
    kUndoAttachment,
    kUndoChangeCase,
    kUndoImportText,
    kUndoCombineParagraphs,
    kUndoRemoveCharFormatting,
    kUndoRemoveParaFormatting,
    kUndoRemoveAllFormatting,
    kUndoReplaceAll,
    kUndoReplace,
    kUndoParagraphAttributes,
    kUndoSetDefinedWidth,
    kUndoSetDefinedHeight,
    kUndoCharAttributes,
    kUndoWipeout,
    kUndoDimensionInsert,
    kUndoDimBreakInsert,
    kUndoCustomConvert,
    kUndoDeleteAndMoveSelection,
    kUndoParagraphNumbering,
    kUndoCursorAttributes,
    kUndoColumns,
    kUndoAnnoState,
    kUndoDimensionTweak,
    kUndoDimensionSymbol,
    kUndoDimensionTemplate,
  };

  GCED_DLL_DECL bool canUndo() const;

  GCED_DLL_DECL Gcad::ErrorStatus undo();

  GCED_DLL_DECL bool canRedo() const;

  GCED_DLL_DECL Gcad::ErrorStatus redo();

  GCED_DLL_DECL Gcad::ErrorStatus  addUndoMarker(TextUndoType type);

  GCED_DLL_DECL bool              canCut() const;
  GCED_DLL_DECL bool              canCopy() const;
  GCED_DLL_DECL bool              canPaste() const;

  GCED_DLL_DECL Gcad::ErrorStatus cut();
  GCED_DLL_DECL Gcad::ErrorStatus copy();
  GCED_DLL_DECL Gcad::ErrorStatus paste();
  GCED_DLL_DECL Gcad::ErrorStatus pasteWithoutFormats();

  GCED_DLL_DECL bool              undoRecordingDisabled();
  GCED_DLL_DECL Gcad::ErrorStatus setUndoRecordingDisable(bool disabled);

  GCED_DLL_DECL Gcad::ErrorStatus setAnnotative(bool bSet);

  GCED_DLL_DECL bool              annotative() const;

  GCED_DLL_DECL bool   isTableCell() const;
  GCED_DLL_DECL bool   isSimpleMtext() const;
  GCED_DLL_DECL bool   isText() const;

  GCED_DLL_DECL bool   isMultiAttribute() const;

  GCED_DLL_DECL bool   isParagraphSupported() const;

  GCED_DLL_DECL void   replaceAllMatchItems(int findFlags, const GcString& findStr, const GcString& replaceStr) const;
  GCED_DLL_DECL void   replaceCurrentMatchItem(int findFlags, const GcString& findStr, const GcString& replaceStr) const;
  GCED_DLL_DECL void   findMatchItem(int findFlags, const GcString& findStr) const;

  GCED_DLL_DECL void   setCanExitInplaceEditor(bool bCanExit);
  GCED_DLL_DECL bool   canExitInplaceEditor();

  GCED_DLL_DECL void   removeHightlight();
  GCED_DLL_DECL void   drawHighlight();

  GCED_DLL_DECL GcDbTextEditorParagraph::AlignmentType getAlignmentFromAttachment() const;

  GCED_DLL_DECL COLORREF layerColor() const;

  GCED_DLL_DECL bool     spellerEnabled() const;
  GCED_DLL_DECL void     toggleSpelling();

  GCED_DLL_DECL void     insertFile(const GcString& fileName);

  GCED_DLL_DECL bool     rulerSupported() const;
  GCED_DLL_DECL void   setRulerHidden(bool hideRuler);
  GCED_DLL_DECL bool   rulerHidden() const;

  GCED_DLL_DECL void   setOpaqueBackground(bool opaqueBackground);

  GCED_DLL_DECL bool   opaqueBackground();

  GCED_DLL_DECL bool   forcedOpaqueBackground();

  GCED_DLL_DECL bool   wysiwyg();
  GCED_DLL_DECL void   enableWysiwyg();

  GCED_DLL_DECL virtual void  close(ExitStatus stat);

  GCED_DLL_DECL void   otherSymbol();

  GCED_DLL_DECL void   setToolbarHidden(bool bHideToolbar);
  GCED_DLL_DECL bool   toolbarHidden() const;

  GCED_DLL_DECL void   setToolbarOptionHidden(bool bHideOption);
  GCED_DLL_DECL bool   toolbarOptionHidden() const;

  GCED_DLL_DECL Gcad::ErrorStatus columnMenusInput(GcGePoint2d* menuPt, HWND parentHandle);
  GCED_DLL_DECL Gcad::ErrorStatus attachmentMenusInput(GcGePoint2d* menuPt, HWND parentHandle);
  GCED_DLL_DECL Gcad::ErrorStatus lineSpaceMenusInput(GcGePoint2d* menuPt, HWND parentHandle);
  GCED_DLL_DECL Gcad::ErrorStatus numberingMenusInput(GcGePoint2d* menuPt, HWND parentHandle);
  GCED_DLL_DECL Gcad::ErrorStatus symbolMenusInput(GcGePoint2d* menuPt, HWND parentHandle);
  GCED_DLL_DECL Gcad::ErrorStatus contextMenusInput(GcGePoint2d* menuPt, HWND parentHandle);

  GCED_DLL_DECL Gcad::ErrorStatus invokeParagraphDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeWipeoutDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeColumnsDialog(int iStaticColumnCount = 0);
  GCED_DLL_DECL Gcad::ErrorStatus invokeFindReplaceDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeImportTextDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeFieldDialog(GcDbField* pField = NULL);
  GCED_DLL_DECL Gcad::ErrorStatus invokeSpellSettingDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeSpellerDictinaryDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeHightlightColorDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeHelpDialog();
  GCED_DLL_DECL Gcad::ErrorStatus invokeNewFeatureWorkshop();
  GCED_DLL_DECL Gcad::ErrorStatus invokeStackPropertyDialog();
  GCED_DLL_DECL Gcad::ErrorStatus setStaticColumnsWithCount(int columnCount);
protected:
  GcEdInplaceTextEditor();
  ~GcEdInplaceTextEditor();
  GcEdInplaceTextEditor(const GcEdInplaceTextEditor&);
  GcEdInplaceTextEditor& operator=(const GcEdInplaceTextEditor&);

protected:
  friend class GcEdInplaceTextEditorImp;
  GcEdInplaceTextEditorImp* m_pEditorImp;
  IPE_Editor*               m_pIPEEditorImp;
};