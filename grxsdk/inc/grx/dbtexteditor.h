#pragma once

#include "gcadstrc.h"
#include "dbmtext.h"
#include "GcString.h"
#include "PAL/api/charset.h"

class TextEditor;
class TextEditorLocation;

class GcDbTextEditor;

class GcDbTextEditorColumn;
class GcDbTextEditorParagraph;
class GcDbTextEditorParagraphIterator;

class GcDbImpTextEditorParagraph;
class GcDbImpTextEditorParagraphIterator;
class GcDbImpTextEditorColumn;

class GcDbTextEditorParagraphTab;
class GcDbImpTextEditorParagraphTab;

class GcDbTextEditorStack;
class GcDbImpTextEditorStack;

class GcDbImpTextEditorSelectionBase;
class GcDbImpTextEditorCursor;
class GcDbImpTextEditorSelection;

class GcDbTextEditorLocation
{
public:
    GCDB_DLL_DECL void release();

private:
    ~GcDbTextEditorLocation();
    GcDbTextEditorLocation();
    bool operator==(const GcDbTextEditorLocation& other);

    friend class GcDbTextEditor;
    friend class GcDbTextEditorServices;
    friend class GcDbTextEditorCursor;

    TextEditorLocation* m_pImp;
};

class GcDbTextEditorSelectable
{
public:
    virtual ~GcDbTextEditorSelectable() { };

    virtual GcDbTextEditorLocation* startOfText() = 0;
    virtual GcDbTextEditorLocation* endOfText() = 0;
};

class GcDbTextEditorSelectionBase
{
public:
    enum FlowAlign
    {
        kFlowBase,
        kFlowCenter,
        kFlowTop
    };

    enum InsertTextType {
        kUnicodeMTextFormat,
        kMTextFormat,
        kRichTextFormat,
        kUnicodeDTextFormat,
        kDTextFormat,
        kUnicodeTextFormat,
        kMultibyteTextFormat
    };

    GCDB_DLL_DECL Gcad::ErrorStatus setLanguage(Charset charset);
    GCDB_DLL_DECL Charset               language() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setFont(const GcString& fontname, bool bTrueType);
    GCDB_DLL_DECL GcString          font() const;

    GCDB_DLL_DECL bool              isTrueType() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setHeight(double height);
    GCDB_DLL_DECL double            height() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setColor(const GcCmColor& color);
    GCDB_DLL_DECL GcCmColor         color() const;

    GCDB_DLL_DECL Gcad::ErrorStatus toggleBold();
    GCDB_DLL_DECL bool              bold() const;

    GCDB_DLL_DECL Gcad::ErrorStatus toggleItalic();
    GCDB_DLL_DECL bool              italic() const;

    GCDB_DLL_DECL Gcad::ErrorStatus toggleUnderline();
    GCDB_DLL_DECL bool              underline() const;

    GCDB_DLL_DECL Gcad::ErrorStatus toggleOverline();
    GCDB_DLL_DECL bool              overline() const;

    GCDB_DLL_DECL Gcad::ErrorStatus toggleStrikethrough();
    GCDB_DLL_DECL bool              strikethrough() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setObliqueAngle(double angle);

    GCDB_DLL_DECL double            obliqueAngle() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setTrackingFactor(double factor);

    GCDB_DLL_DECL double            trackingFactor() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setWidthScale(double scale);
    GCDB_DLL_DECL double            widthScale() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setFlowAlign(FlowAlign flowAlign);
    GCDB_DLL_DECL FlowAlign         flowAlign() const;

    GCDB_DLL_DECL static double     minObliqueAngle();
    GCDB_DLL_DECL static double     maxObliqueAngle();
    GCDB_DLL_DECL static double     minTrackingFactor();
    GCDB_DLL_DECL static double     maxTrackingFactor();
    GCDB_DLL_DECL static double     minWidthScale();
    GCDB_DLL_DECL static double     maxWidthScale();

    GCDB_DLL_DECL Gcad::ErrorStatus insertSymbol(GCHAR wch, Charset charset);

    GCDB_DLL_DECL Gcad::ErrorStatus insertString(const GcString& str);

    GCDB_DLL_DECL Gcad::ErrorStatus insertImportedText(InsertTextType insertType, void * pData);

    GCDB_DLL_DECL Gcad::ErrorStatus inputSpecialChar(Gsoft::UInt32 c);

    GCDB_DLL_DECL Gcad::ErrorStatus insertColumnBreak();

protected:
    GcDbTextEditorSelectionBase();
    virtual ~GcDbTextEditorSelectionBase();
    GcDbTextEditorSelectionBase(const GcDbTextEditorSelectionBase&);
    GcDbTextEditorSelectionBase& operator=(const GcDbTextEditorSelectionBase&);

    friend class GcDbTextEditor;
    GcDbImpTextEditorSelectionBase* m_pImp;
};

class GcDbTextEditorSelection : public GcDbTextEditorSelectionBase
{
public:
    GCDB_DLL_DECL bool languageSupported(Charset charset) const;
    GCDB_DLL_DECL bool fontSupported(const GcString& fontname, bool bTrueType) const;

    GCDB_DLL_DECL bool canStack() const;

    GCDB_DLL_DECL Gcad::ErrorStatus stack();

    GCDB_DLL_DECL bool canUnStack() const;
    GCDB_DLL_DECL Gcad::ErrorStatus    unStack();

    GCDB_DLL_DECL bool     singleStackSelected() const;

    GCDB_DLL_DECL Gcad::ErrorStatus    getStack(GcDbTextEditorStack& stack) const;
    GCDB_DLL_DECL Gcad::ErrorStatus    setStack(const GcDbTextEditorStack& stack);

    GCDB_DLL_DECL void paragraph(GcArray<GcDbTextEditorParagraph*>& paragraphs);

    GCDB_DLL_DECL Gcad::ErrorStatus combineParagraphs();

    GCDB_DLL_DECL Gcad::ErrorStatus removeCharacterFormatting();

    GCDB_DLL_DECL Gcad::ErrorStatus removeParagraphFormatting();

    GCDB_DLL_DECL Gcad::ErrorStatus removeAllFormatting();

    GCDB_DLL_DECL bool canChangeCase() const;
    GCDB_DLL_DECL bool changeToUppercase();

    GCDB_DLL_DECL bool changeToLowercase();

    GCDB_DLL_DECL Gcad::ErrorStatus getSelectionText(GcString& txt) const;

    GCDB_DLL_DECL bool     singleFieldSelected() const;

    GCDB_DLL_DECL GcDbField* field() const;

    GCDB_DLL_DECL Gcad::ErrorStatus  updateField();

    GCDB_DLL_DECL Gcad::ErrorStatus  convertToPlainText();
protected:
    GCDB_DLL_DECL GcDbTextEditorSelection(const TextEditor* pImp);
    GCDB_DLL_DECL ~GcDbTextEditorSelection();
    GcDbTextEditorSelection(const GcDbTextEditorSelection&);
    GcDbTextEditorSelection& operator=(const GcDbTextEditorSelection&);

    GcDbImpTextEditorSelection* m_pImpSelection;
    friend class TextEditor;
};

class GcDbTextEditorCursor : public GcDbTextEditorSelectionBase
{
public:
    GCDB_DLL_DECL GcDbTextEditorParagraph* paragraph();

    GCDB_DLL_DECL GcDbTextEditorColumn*    column();
    
    GCDB_DLL_DECL Gcad::ErrorStatus        setLocation(const GcDbTextEditorLocation& location);
    GCDB_DLL_DECL GcDbTextEditorLocation* location() const;

protected:
    GCDB_DLL_DECL GcDbTextEditorCursor(const TextEditor* pImp);
    GCDB_DLL_DECL ~GcDbTextEditorCursor();
    GcDbTextEditorCursor(const GcDbTextEditorCursor&);
    GcDbTextEditorCursor& operator=(const GcDbTextEditorCursor&);

    GcDbImpTextEditorCursor* m_pImpCursor;
    friend class TextEditor;
};

class GcDbTextEditorParagraphTab
{
public:
    enum ParagraphTabType
    {
        kLeftTab,
        kCenterTab,
        kRightTab,
        kDecimalTab,
    };

    GCDB_DLL_DECL  GcDbTextEditorParagraphTab();
    GCDB_DLL_DECL ~GcDbTextEditorParagraphTab();
    GCDB_DLL_DECL GcDbTextEditorParagraphTab(const GcDbTextEditorParagraphTab&);
    GCDB_DLL_DECL GcDbTextEditorParagraphTab& operator=(const GcDbTextEditorParagraphTab&);
    GCDB_DLL_DECL double            offset() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setOffset(double offdist);

    GCDB_DLL_DECL ParagraphTabType  type() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setType(ParagraphTabType type);

    GCDB_DLL_DECL wchar_t             decimalChar() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setDecimalChar(wchar_t decchar);

private:
    GcDbImpTextEditorParagraphTab* m_pImp;
};

class GcDbTextEditorParagraph : public GcDbTextEditorSelectable
{
public:
    enum AlignmentType
    {
        kAlignmentDefault,
        kAlignmentLeft,
        kAlignmentCenter,
        kAlignmentRight,
        kAlignmentJustify,
        kAlignmentDistribute
    };

    enum LineSpacingStyle{
        kLineSpacingDefault,
        kLineSpacingExactly,
        kLineSpacingAtLeast,
        kLineSpacingMultiple,
    };

    enum NumberingType{
        kOff = 0,
        kBullet,
        kNumber,
        kLetterLower,
        kLetterUpper,
        kNumberWide,
        kLetterLowerWide,
        kLetterUpperWide,
    };

    GCDB_DLL_DECL Gcad::ErrorStatus setAlignment(AlignmentType AlignmentType);

    GCDB_DLL_DECL AlignmentType alignment() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setFirstIndent(double firstIndent);

    GCDB_DLL_DECL double firstIndent() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setLeftIndent(double leftIndent);

    GCDB_DLL_DECL double leftIndent() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setRightIndent(double rightIndent);

    GCDB_DLL_DECL double rightIndent() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setLineSpacingStyle(LineSpacingStyle lineSpacingStyle);
    GCDB_DLL_DECL LineSpacingStyle  lineSpacingStyle() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setLineSpacingFactor(double lineSpacingFactor);
    GCDB_DLL_DECL double            lineSpacingFactor() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setSpaceBefore(double spaceBefore);
    GCDB_DLL_DECL double            spaceBefore() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setSpaceAfter(double spaceAfter);
    GCDB_DLL_DECL double            spaceAfter() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setNumberingType(NumberingType type);
    GCDB_DLL_DECL NumberingType     numberingType() const;

    GCDB_DLL_DECL Gcad::ErrorStatus restartNumbering();
    GCDB_DLL_DECL Gcad::ErrorStatus continueNumbering();

    GCDB_DLL_DECL int               tabsCount() const;

    GCDB_DLL_DECL Gcad::ErrorStatus addTab(const GcDbTextEditorParagraphTab& tab);

    GCDB_DLL_DECL Gcad::ErrorStatus removeTab(const GcDbTextEditorParagraphTab& tab);

    GCDB_DLL_DECL Gcad::ErrorStatus getTab(int i, GcDbTextEditorParagraphTab& tab);

    GCDB_DLL_DECL virtual GcDbTextEditorLocation* startOfText() GSOFT_OVERRIDE;
    GCDB_DLL_DECL virtual GcDbTextEditorLocation* endOfText() GSOFT_OVERRIDE;

    GCDB_DLL_DECL double     minLineSpacingFactor() const;
    GCDB_DLL_DECL double     maxLineSpacingFactor() const;

    GCDB_DLL_DECL double     minSpaceValue() const;
    GCDB_DLL_DECL double     maxSpaceValue() const;

    GCDB_DLL_DECL void             release();

private:
    friend class GcDbTextEditorParagraphIterator;
    friend class GcDbTextEditorServices;
    GcDbImpTextEditorParagraph* m_pImp; 

    GcDbTextEditorParagraph() {}
    virtual ~GcDbTextEditorParagraph();
    GcDbTextEditorParagraph(const GcDbTextEditorParagraph&);
    GcDbTextEditorParagraph& operator=(const GcDbTextEditorParagraph&);
};

class GcDbTextEditorParagraphIterator
{
public:
    GCDB_DLL_DECL GcDbTextEditorParagraphIterator(const GcDbTextEditor& textEditor);
    GCDB_DLL_DECL ~GcDbTextEditorParagraphIterator();

    GCDB_DLL_DECL bool done();

    GCDB_DLL_DECL GcDbTextEditorParagraph* current();

    GCDB_DLL_DECL void next();
private:
    GcDbImpTextEditorParagraphIterator* m_pImp;
};

class GcDbTextEditorColumn : public GcDbTextEditorSelectable
{
public:
    GCDB_DLL_DECL double height();
    GCDB_DLL_DECL Gcad::ErrorStatus setHeight(double height);

    GCDB_DLL_DECL void              release();

    GCDB_DLL_DECL virtual GcDbTextEditorLocation* startOfText() GSOFT_OVERRIDE;
    GCDB_DLL_DECL virtual GcDbTextEditorLocation* endOfText() GSOFT_OVERRIDE;
private:
    GcDbImpTextEditorColumn* m_pImp;
    friend class GcDbTextEditorServices;

    GcDbTextEditorColumn();
    virtual ~GcDbTextEditorColumn();
    GcDbTextEditorColumn(const GcDbTextEditorColumn&);
    GcDbTextEditorColumn& operator=(const GcDbTextEditorColumn&);
};

class GcDbTextEditorColumns
{
public:
    GCDB_DLL_DECL static int maxCount();

    GCDB_DLL_DECL int count() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setCount(int count);

    GCDB_DLL_DECL GcDbTextEditorColumn* getAt(int i);
    
    GCDB_DLL_DECL Gcad::ErrorStatus setColumnType(GcDbMText::ColumnType type);

    GCDB_DLL_DECL GcDbMText::ColumnType columnType() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setAutoHeight(bool bAutoHeight);

    GCDB_DLL_DECL bool autoHeight() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setWidth(double value);

    GCDB_DLL_DECL double width() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setGutter(double value);

    GCDB_DLL_DECL double gutter() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setTotalWidth(double value);

    GCDB_DLL_DECL double totalWidth() const;

    GCDB_DLL_DECL bool   isFlowReversed() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setIsFlowReversed(bool isFlowReversed);

private:
    friend class TextEditor;
    GcDbTextEditorColumns();
    ~GcDbTextEditorColumns();
    GcDbTextEditorColumns(const GcDbTextEditorColumns&);
    GcDbTextEditorColumns& operator=(const GcDbTextEditorColumns&);

    TextEditor* m_pImp;
};

class GcDbTextEditorWipeout
{
public:
    GCDB_DLL_DECL static double     minBackgroundScaleFactor();
    GCDB_DLL_DECL static double     maxBackgroundScaleFactor();

    GCDB_DLL_DECL bool              enableBackgroundFill() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setEnableBackgroundFill(bool bEnable);

    GCDB_DLL_DECL GcCmColor         getBackgroundFillColor() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setBackgroundFillColor(GcCmColor color);

    GCDB_DLL_DECL bool              useBackgroundColor() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setUseBackgroundColor(bool bUse);

    GCDB_DLL_DECL double            getBackgroundScaleFactor()const;
    GCDB_DLL_DECL Gcad::ErrorStatus setBackgroundScaleFactor(double factor);

private:
    GcDbTextEditorWipeout();
    ~GcDbTextEditorWipeout();
    GcDbTextEditorWipeout(const GcDbTextEditorWipeout&);
    GcDbTextEditorWipeout& operator=(const GcDbTextEditorWipeout&);

    TextEditor* m_pEditor;
    friend class TextEditor;
};

class GcDbTextEditorStack
{
public:
    enum StackType
    {
        kHorizontalStack,
        kDiagonalStack,
        kToleranceStack,
        kDecimalStack,
    };

    GCDB_DLL_DECL GcDbTextEditorStack();
    GCDB_DLL_DECL ~GcDbTextEditorStack();
    GCDB_DLL_DECL GcDbTextEditorStack(const GcDbTextEditorStack&);
    GCDB_DLL_DECL GcDbTextEditorStack& operator=(const GcDbTextEditorStack&);

    GCDB_DLL_DECL StackType        type() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setType(StackType type);

    GCDB_DLL_DECL GcDbTextEditorSelectionBase::FlowAlign alignType() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setAlignType(GcDbTextEditorSelectionBase::FlowAlign align);

    GCDB_DLL_DECL GcString top() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setTop(const GcString& top);

    GCDB_DLL_DECL GcString           bottom() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setBottom(const GcString& bottom);

    GCDB_DLL_DECL double            scale() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setScale(double scale);

    GCDB_DLL_DECL wchar_t             decimalChar() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setDecimalChar(wchar_t decimalChar);

    GCDB_DLL_DECL static double       minStackScale();
    GCDB_DLL_DECL static double       maxStackScale();

private:
    GcDbImpTextEditorStack*   m_pImpStack;
};

class GcDbTextEditor : public GcDbTextEditorSelectable
{
public:
    enum TextFindFlags {
        kFindMatchCase = 1 << 0,
        kFindWholeWord = 1 << 1,
        kFindHalfFullForm = 1 << 2,
        kFindIgnoreAccent = 1 << 3,
        kFindUseWildcards = 1 << 4,
    };

    enum ExitStatus
    {
        kExitQuit = 0,
        kExitSave,
    };
    GCDB_DLL_DECL static GcDbTextEditor* createDbTextEditor(GcDbMText* pMText);

    GCDB_DLL_DECL virtual void  close(ExitStatus stat);

    GCDB_DLL_DECL void   redraw();

    GCDB_DLL_DECL GcDbTextEditorColumns* columns();

    GCDB_DLL_DECL GcDbTextEditorWipeout* wipeout();

    GCDB_DLL_DECL GcDbTextEditorParagraphIterator* newParagraphsIterator();

    GCDB_DLL_DECL virtual GcDbTextEditorSelection* selection();

    GCDB_DLL_DECL virtual GcDbTextEditorCursor*    cursor();

    GCDB_DLL_DECL Gcad::ErrorStatus clearSelection();

    GCDB_DLL_DECL Gcad::ErrorStatus makeSelection(const GcDbTextEditorLocation* pStart,
        const GcDbTextEditorLocation* pEnd);

    GCDB_DLL_DECL Gcad::ErrorStatus findText(const GCHAR* text, int flags,
        GcDbTextEditorLocation*& pStart,
        GcDbTextEditorLocation*& pEnd);

    GCDB_DLL_DECL Gcad::ErrorStatus setAttachment(GcDbMText::AttachmentPoint attachment);

    GCDB_DLL_DECL GcDbMText::AttachmentPoint attachment() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setStyle(int index);

    GCDB_DLL_DECL Gcad::ErrorStatus setStyle(GcDbObjectId styleId);
    GCDB_DLL_DECL int               getIndexFromStyleName(const GcString& styleName);

    GCDB_DLL_DECL int               getStyleCount() const;

    GCDB_DLL_DECL GcString           getStyleName(int index) const;

    GCDB_DLL_DECL GcDbObjectId      style(int index) const;

    GCDB_DLL_DECL int               currentStyleIndex() const;

    GCDB_DLL_DECL bool              isAnnotativeStyle(int index) const;

    GCDB_DLL_DECL bool             isVerticalSHX() const;

    GCDB_DLL_DECL bool             isVerticalTTF() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setDefinedWidth(double width);

    GCDB_DLL_DECL double            definedWidth() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setDefinedHeight(double height);

    GCDB_DLL_DECL double            definedHeight() const;

    GCDB_DLL_DECL double            textHeight() const;
    GCDB_DLL_DECL Gcad::ErrorStatus setTextHeight(double textHeight);

    GCDB_DLL_DECL double            actualWidth() const;

    GCDB_DLL_DECL double            actualHeight() const;

    GCDB_DLL_DECL Gcad::ErrorStatus selectAll(); 

    GCDB_DLL_DECL Gcad::ErrorStatus setAutoCAPS(bool autoCAPS);

    GCDB_DLL_DECL bool              autoCAPS();

    GCDB_DLL_DECL Gcad::ErrorStatus setEnableNumbering(bool bEnable);
    GCDB_DLL_DECL bool              numberingEnabled() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setAutolistEnabled(bool enabled);
    GCDB_DLL_DECL bool              autolistEnabled() const;

    GCDB_DLL_DECL Gcad::ErrorStatus setTabOnlyDelimiter(bool tabOnlyDelimiter);
    GCDB_DLL_DECL bool              tabOnlyDelimiter() const;

    GCDB_DLL_DECL int               getFontCount() const;
    GCDB_DLL_DECL GcString          getFontName(int index) const;
    GCDB_DLL_DECL bool              isTrueTypeFont(int index) const;

    GCDB_DLL_DECL int               stackCount() const;

    GCDB_DLL_DECL double             defaultStackScale() const;
    GCDB_DLL_DECL Gcad::ErrorStatus    setDefaultStackScale(double scale);

    GCDB_DLL_DECL GcDbTextEditorSelectionBase::FlowAlign defaultStackAlignment() const;
    GCDB_DLL_DECL Gcad::ErrorStatus    setDefaultStackAlignment(GcDbTextEditorSelectionBase::FlowAlign alignment);

    GCDB_DLL_DECL virtual GcDbTextEditorLocation* startOfText() GSOFT_OVERRIDE;

    GCDB_DLL_DECL virtual GcDbTextEditorLocation* endOfText() GSOFT_OVERRIDE;

protected:
    GCDB_DLL_DECL GcDbTextEditor():m_pImp(NULL) {};
    GCDB_DLL_DECL virtual ~GcDbTextEditor();

    friend class GcDbTextEditorLocation;
    friend class GcDbTextEditorParagraphIterator;
    TextEditor* m_pImp;

private:
    GcDbTextEditor(const GcDbTextEditor& editor);
    GcDbTextEditor& operator=(const GcDbTextEditor& editor);
};