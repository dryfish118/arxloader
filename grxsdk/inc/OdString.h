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





#ifndef __ODSTRING_H__
#define __ODSTRING_H__

#include <stdarg.h>
#include <stdio.h>

#include "OdMutex.h"
#include "OdPlatformSettings.h"
#include "OdCodePage.h"
#include "OdAnsiString.h"
#include "OdHeap.h"

#define odaIsValidString(lpch)    (true)

#include "TD_PackPush.h"

class OdDbHandle;
class OdRxResourceInstance;

#ifdef sgi
#include <string>
using namespace std;  // va_XXXX items are in std namespace for newest SGI compiler
#endif

/** \details
    This structure contains string data used by OdString.

    \remarks
    An OdChar array (buffer) is allocated along with this structure, and
    is freed when this structure is freed.
    
    Corresponding C++ library: TD_Root
    <group !!RECORDS_TD_APIRef>
*/
struct OdStringData
{            
  /** \details
    Number of references to this string.
  */
  OdRefCounter nRefs;      

  /** \details
    String length in characters, omitting the 0 terminator.
  */
  int nDataLength; 

  /** \details
    String allocation length in characters, omitting the 0 terminator. 
  */
  int nAllocLength;       

  /** \details
    Underlying OdChar array (buffer) of this StringData object.
  */
  OdChar* unicodeBuffer;
  
  /** \details
    Underlying char array (buffer) of this StringData object.
  */
  char* ansiString;
};

/** \details
    This class implements character String objects in the ODA Platform.

    \remarks
    OdString objects use zero-based indices to access string elements.

    <group Other_Classes>
*/
class FIRSTDLL_EXPORT OdString : public OdHeapOperators
{
public:
  // Encoding type
  enum Encoding { Utf8 };

  FIRSTDLL_EXPORT_STATIC const static OdString kEmpty;

  OdString()
  { init(); }

  /** \param source [in]  Source.
  */
  OdString(const OdString& source);
  OdString(OdString && ods);

  enum eFormat {
    kSigned = 0x0002,
    kUnSigned = 0x0003,
    kHex = 0x0004
  };
  OdString(eFormat nCtorFlags, unsigned nArg);

#ifndef ODA_WINDOWS
  OdString(const OdChar16_t* lpch, OdCodePageId codepage = CP_CNT);
#endif
  /** \param ch [in]  Character to repeat.
    \param length [in]  Number of characters.
  */
  OdString(OdChar wch);
  OdString(OdChar ch, unsigned length);

  OdString(const OdChar* source);
  OdString(const OdChar* source, unsigned int length);

  OdString(const char *psz, Encoding encoding);
  OdString(const char* lpch, OdCodePageId codepage = CP_CNT);
  OdString(const char* lpch, int nLength, OdCodePageId codepage = CP_CNT);
  OdString(const OdAnsiString&);

  OdString(const OdDbHandle &h);
  OdString(const OdRxResourceInstance& hDll, unsigned int nId);

protected:
  explicit OdString(OdStringData* pData);
public:

  unsigned length() const;

  unsigned tcharLength() const
  {
    return this->length();
  }

  /** \details
    Returns the number of characters in this String object.
  */
  int getLength() const
  { 
    if (isUnicodeNotInSync())
      syncUnicode();
    return getData()->nDataLength; 
  }
  int getLengthA() const;

  bool isAscii() const;

  enum {
    kParseZero = 0,
    kParseMinus1 = 0x01,
    kParseAssert = 0x02,
    kParseExcept = 0x04,
    kParseNoEmpty = 0x08,
    kParseDefault = (kParseAssert | kParseZero)
  };

  int asDeci(int nFlags = kParseDefault) const;
  int asHex(int nFlags = kParseDefault) const;
  unsigned int asUDeci(int nFlags = kParseDefault) const;
  unsigned int asUHex(int nFlags = kParseDefault) const;
  int64_t asDeci64(int nFlags = kParseDefault) const;
  int64_t asHex64(int nFlags = kParseDefault) const;
  OdUInt64 asUDeci64(int nFlags = kParseDefault) const;
  OdUInt64 asUHex64(int nFlags = kParseDefault) const;
  OdDbHandle asOdDbHandle(int nFlags = kParseDefault) const;

  /** \details
    Returns true and only if this String object is empty.
  */
  bool isEmpty() const
  {
    return (getData()->nDataLength == 0 && 
      (getData()->ansiString == 0 || getAnsiString()->isEmpty()));
  }

  /** \details
    Sets this String object to the empty string.
  */
  void empty();
  OdString & setEmpty();

  bool loadString(const OdRxResourceInstance& hDll, unsigned nId);

  bool loadString(unsigned nId);
#if defined(_WINBASE_)
  // Set the string from a resource string
  // hDll : input windows handle to a loaded resource dll
  // nId : input id of the string resource in the specified resource dll
  bool loadString(HINSTANCE hDll, unsigned nId);
#endif

  /** \details
    Returns the single character of this String object at the specified position.
    \param charIndex [in]  Character index. 
  */
  OdChar getAt(int charIndex) const
  {
#ifdef TD_UNICODE
    if (isUnicodeNotInSync())
      syncUnicode();
#endif
    ODA_ASSERT(charIndex >= 0);
    ODA_ASSERT(charIndex < getData()->nDataLength);
    return getData()->unicodeBuffer[charIndex];
  }

  /** \details
    Indexing Operator
    
    \returns
    Returns the single character of this String object at the specified position.
    \param charIndex [in]  Character index. 
  */
  OdChar operator [] (int charIndex) const
  {
    return getAt(charIndex);

#ifndef ODA_WINDOWS
  OdString& operator=(const OdChar16_t* source);
#endif
  }

  /** \details
    Sets the single character of this String object at the specified position.
    \param charIndex [in]  Character index.
    \param ch [in]  Character.
    \remarks
    No range checking is performed.
  */
  OdString& setAt(int charIndex, OdChar ch);

#if defined(_MSC_VER) && defined(_WIN32) && defined(_DEBUG) && defined(ODA_LINT)
#define UPDATECONSTSTRINGDIAGNISTIC
private:
  void updateConstStringDiagnostic(const OdChar* pAddr) const;
public:
#else
  #define updateConstStringDiagnostic(pAddr)
#endif

  const char * utf8Ptr() const;
  const OdChar * kwszPtr() const;
  const OdChar *  constPtr() const;
  const OdChar * kTCharPtr() const;
  const OdChar* kOdCharPtr() const;

  /** \details
    Returns the underlying OdChar array (buffer) of this String object.
  */
  const OdChar* c_str() const
  { 
    if (isUnicodeNotInSync())
      syncUnicode();
    const OdChar* pRet = getData()->unicodeBuffer;
    updateConstStringDiagnostic(pRet);
    return pRet;
  }

  /** \details
    Returns the underlying character array (buffer) of this String object.
  */
  inline operator const OdChar*() const
  { 
    return c_str();
  }

  OdString & assign(OdChar wch);
  OdString & assign(const char *psz, Encoding encoding);
  OdString & assign(const OdChar *pwsz);
  OdString & assign(const OdString & ods);
  OdString & assign(const OdDbHandle & h);

  OdString& operator = (const OdString& source);
  OdString & operator = (OdString && ods);
  OdString& operator = (OdChar ch);
  
  OdString& operator = (const OdChar* source);

  OdString& operator = (const OdAnsiString& source);

  OdString& operator = (const char* source);
  OdString & operator = (const OdDbHandle & h);
  /** \details
    Concatenation-Equals Operator.
	
	\param string [in] Input value for concatenation
    \remarks
    Sets this object to the concatenation of this String object with the 
    value on the right, and returns a reference to this String object.
  */
  OdString& operator += (const OdString& string);

  /** \details
    Concatenation-Equals Operator.
	
	\param ch [in] Input value for concatenation
    \remarks
    Sets this object to the concatenation of this String object with the 
    value on the right, and returns a reference to this String object.
  */
  OdString& operator += (OdChar ch);

  /** \details
    Concatenation-Equals Operator.
	
	\param string [in] Input value for concatenation
    \remarks
    Sets this object to the concatenation of this String object with the 
    value on the right, and returns a reference to this String object.
  */
  OdString& operator += (const OdChar* string);

  /** \details
    Concatenation-Equals Operator.
	
	\param string [in] Input value for concatenation
    \remarks
    Sets this object to the concatenation of this String object with the 
    value on the right, and returns a reference to this String object.
  */
  OdString& operator += (const char* string);

  OdString & append(OdChar wch);
  OdString & append(const char *psz, Encoding encoding);
  OdString & append(const OdChar *pwsz);
  OdString & append(const OdString & ods);

  OdString operator + (OdChar wch) const;
  OdString operator + (const OdChar * pwsz) const;
  OdString operator + (const OdString & ods) const;

  OdString concat(OdChar wch) const;
  OdString concat(const char * psz, Encoding encoding) const;
  OdString concat(const OdChar * pwsz) const;
  OdString concat(const OdString & ods) const;

  OdString precat(OdChar ch) const;
  OdString precat(const char * psz, Encoding encoding) const;
  OdString precat(const OdChar * psz) const;

  /** \details
    Case sensitive string comparison.  
    
    \param otherString [in]  Other string.
    
    \remarks
    compare() returns one of the following:
    
    <table>
    Returns   Condition
    < 0       This String object < otherString. 
    0         This String object == otherString.
    > 0       This String object > otherString.
    </table>
  */
  int compare(const OdChar* otherString) const
  { 
    if (isUnicodeNotInSync())
      syncUnicode();
    return odStrCmp((const wchar_t*)getData()->unicodeBuffer, (const wchar_t*)otherString);
  }

  /** \details
    Case sensitive string comparison.  
    
    \param otherString [in]  Other string.
    
    \remarks
    compare() returns one of the following:
    
    <table>
    Returns   Condition
    < 0       This String object < otherString. 
    0         This String object == otherString.
    > 0       This String object > otherString.
    </table>
  */
  inline int compare(const OdString& otherString) const{ return compare(otherString.c_str());}

  /** \details
  Case sensitive string comparison.  

  \param otherString [in]  Other string.

  \remarks
  compare() returns one of the following:

  <table>
  Returns   Condition
  < 0       This String object < otherString. 
  0         This String object == otherString.
  > 0       This String object > otherString.
  </table>
  */
  int compare(const char* otherString) const;
  int  compare(OdChar wch) const;
  int  compare(const char *psz, Encoding encoding) const;

  /** \details
    Case insensitive string comparison.  
    
    \param otherString [in]  Other string.
    
    \remarks
    iCompare() returns one of the following:
    
    <table>
    Returns   Condition
    < 0       This String object < otherString. 
    0         This String object == otherString.
    > 0       This String object > otherString.
    </table>
  */
  int iCompare(const OdChar* otherString) const
  { 
    if (isUnicodeNotInSync())
      syncUnicode();
    return odStrICmp(getData()->unicodeBuffer, otherString); 
  }   
  
  /** \details
    Case insensitive string comparison.  
    
    \param otherString [in]  Other string.
    
    \remarks
    iCompare() returns one of the following:
    
    <table>
    Returns   Condition
    < 0       This String object < otherString. 
    0         This String object == otherString.
    > 0       This String object > otherString.
    </table>
  */
  inline int iCompare(const OdString& otherString) const{ return iCompare(otherString.c_str()); }

  int  collate(const OdChar *pwsz) const;
  int  collate(const OdString & ods) const;

  int  compareNoCase(OdChar wch) const;
  int  compareNoCase(const char *psz, Encoding encoding) const;
  int  compareNoCase(const OdChar *pwsz) const;
  int  compareNoCase(const OdString & ods) const;

  static bool equalsNoCase(const OdString& left, const OdString& right);
  int collateNoCase(const OdChar *psz) const;
  int collateNoCase(const OdString& ods) const;
  bool operator == (OdChar wch) const;
  bool operator == (const OdChar *pwsz) const;
  bool operator == (const OdString & ods) const;
  bool operator != (OdChar wch) const;
  bool operator != (const OdChar *pwsz) const;
  bool operator != (const OdString & ods) const;
  bool operator >  (OdChar wch) const;
  bool operator >  (const OdChar *pwsz) const;
  bool operator >  (const OdString & ods) const;
  bool operator >= (OdChar wch) const;
  bool operator >= (const OdChar *pwsz) const;
  bool operator >= (const OdString & ods) const;
  bool operator <  (OdChar wch) const;
  bool operator <  (const OdChar *pwsz) const;
  bool operator <  (const OdString & ods) const;
  bool operator <= (OdChar wch) const;
  bool operator <= (const OdChar *pwsz) const;
  bool operator <= (const OdString & ods) const;

  int  match(const char *psz, Encoding encoding) const;
  int  match(const OdChar *pwsz) const;
  int  match(const OdString & ods) const;
  int  matchNoCase(const char *psz, Encoding encoding) const;
  int  matchNoCase(const OdChar *pwsz) const;
  int  matchNoCase(const OdString & ods) const;

  /** \details
    Returns the substring specified by a start index and a length from this String object.
    \param startIndex [in]  Starting index.
    \param length [in]  Length of substring. 
    
  */
  OdString mid(int startIndex, int length) const;

  /** \details
    Returns the substring specified by a start index from this String object.
    \param startIndex [in]  Starting index.

  */
  OdString mid(int startIndex) const;

  OdString substr(int numChars) const;
  OdString substr(int nStart, int nNumChars) const;
  OdString substrRev(int numChars) const;

  /** \details
    Returns the leftmost substring of the specified length from this String object.
    \param length [in]  Length of substring. 
  */
  OdString left(int length) const;

  /** \details
    Returns the rightmost substring of the specified length from this String object.
    \param length [in]  Length of substring. 
  */
  OdString right(int length) const;

  /** \details
    Returns the longest leftmost substring of this String object 
    that consists solely of characters that are
    contained in the specified character set.

    \param charSet [in]  Character set.
    
    \remarks
    If the first character in this String object is not in the specified character set,
    an empty string is returned.
  */
  OdString spanIncluding(const OdChar* charSet) const;
  
  /** \details
    Returns the longest leftmost substring of this String object 
    that consists solely of characters that are
    contained in the specified character set.

    \param charSet [in]  Character set.
    
    \remarks
    If the first character in this String object is not in the specified character set,
    an empty string is returned.
  */
  inline OdString spanIncluding(const OdString& charSet) const { return spanIncluding(charSet.c_str()); }

  /** \details
    Returns the longest leftmost substring of this String object 
    that consists solely of characters that are
    not contained in the specified character set.

    \param charSet [in]  Character set.
    
    \remarks
    If the first character in this String object in the specified character set,
    an empty string is returned.
  */
  OdString spanExcluding(const OdChar* charSet) const;

  /** \details
    Returns the longest leftmost substring of this String object 
    that consists solely of characters that are
    not contained in the specified character set.

    \param charSet [in]  Character set.
    
    \remarks
    If the first character in this String object in the specified character set,
    an empty string is returned.
  */
  inline OdString spanExcluding(const OdString& charSet) const{ return spanExcluding(charSet.c_str());}
  
#if  defined(_AFX) || defined (__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)
  OdString(const CStringW &csw);
  OdString & operator = (const CStringW &csw);
  OdString & operator += (const CStringW &csw);
  int  compare(const CStringW & csw) const;
  int  compareNoCase(const CStringW & csw) const;
  bool operator == (const CStringW &) const;
  bool operator != (const CStringW &) const;
  bool operator <  (const CStringW &) const;
  bool operator <= (const CStringW &) const;
  bool operator >  (const CStringW &) const;
  bool operator >= (const CStringW &) const;
  int  match(const CStringW & csw) const;
  int  matchNoCase(const CStringW & csw) const;

#endif

  /** \details
    Converts this String object to upper case.

    \returns
    Returns a reference to this String object.  
  */
  OdString& makeUpper();

  /** \details
    Converts this String object to lower case.

    \returns
    Returns a reference to this String object.  
  */
  OdString& makeLower();

  /** \details
    Reverses this String object.

    \returns
    Returns a reference to this String object.  
  */
  OdString& makeReverse();


  /** \details
    Removes all whitespace from the right side of this String object.
   
    \returns
    Returns a reference to this String object.
    \remarks
    A space (' ') is used if no whitespace characters are specfied.  
  */
  OdString& trimRight();

  /** \details
    Removes all whitespace from the left side of this String object.
   
    \returns
    Returns a reference to this String object.  
    \remarks
    A space (' ') is used if no other whitespace characters are specfied.  
  */
  OdString& trimLeft();

  /** \details
    Removes all whitespace from the right side of this String object.
   
    \param whiteChar [in]  Whitespace character.
   
    \returns
    Returns a reference to this String object.
    \remarks
    A space (' ') is used if no whitespace characters are specfied.  
  */
  OdString& trimRight(OdChar whiteChar);

  /** \details
    Removes all whitespace from the right side of this String object.
   
    \param whiteChars [in]  Whitespace characters.
   
    \returns
    Returns a reference to this String object.
    \remarks
    A space (' ') is used if no whitespace characters are specfied.  
  */
  OdString& trimRight(const OdChar* whiteChars);

  /** \details
    Removes all whitespace from the right side of this String object.
   
    \param whiteChars [in]  Whitespace characters.
   
    \returns
    Returns a reference to this String object.
    \remarks
    A space (' ') is used if no whitespace characters are specfied.  
  */
  inline OdString& trimRight(const OdString& whiteChars){ return trimRight(whiteChars.c_str());}

  /** \details
    Removes all whitespace from the left side of this String object.
   
   \param whiteChar [in]  Whitespace character.
   
    \returns
    Returns a reference to this String object.  
    \remarks
    A space (' ') is used if no other whitespace characters are specfied.  
  */
  OdString& trimLeft(OdChar whiteChar);

  /** \details
    Removes all whitespace from the left side of this String object.
   
   \param whiteChars [in]  Whitespace characters.
   
    \returns
    Returns a reference to this String object.  
    \remarks
    A space (' ') is used if no other whitespace characters are specfied.  
  */
  OdString& trimLeft(const OdChar* whiteChars);
  
  /** \details
    Removes all whitespace from the left side of this String object.
   
   \param whiteChars [in]  Whitespace characters.
   
    \returns
    Returns a reference to this String object.  
    \remarks
    A space (' ') is used if no other whitespace characters are specfied.  
  */
  inline OdString& trimLeft(const OdString& whiteChars){ return trimLeft(whiteChars.c_str());}

  OdString & trim(OdChar wch);
  OdString & trim();
  OdString & trim(const OdChar *pwszChars);

  /** \details
    Replaces all occurrences of the specified character in this String object.

    \param oldChar [in]  Old character.
    \param newChar [in]  New character.
    
    \returns
    Returns the number of characters or strings replaced.
  */
  int replace(OdChar oldChar, OdChar newChar);

  /** \details
    Replaces all occurrences of the specified string in this String object.

    \param oldString [in]  Old string.
    \param newString [in]  New string.
    
    \returns
    Returns the number of characters or strings replaced.
  */
  int replace(const OdChar* oldString, const OdChar* newString);
  
  /** \details
    Replaces all occurrences of the specified string in this String object.

    \param oldString [in]  Old string.
    \param newString [in]  New string.
    
    \returns
    Returns the number of characters or strings replaced.
  */
  inline int replace(const OdString& oldString, const OdString& newString){ return replace(oldString.c_str(), newString.c_str());}

  int deleteAtIndex(int iIndex, int nCount = 1);
  OdString tokenize(const OdChar* pszTokens, int& iStart);

  /** \details
    Removes all occurrences of the specified character from this String object.

    \param removeChar [in]  Character to remove.

    \returns
    Returns the number of characters removed.
  */
  int remove(OdChar chRemove);

  /** \details
    Inserts the specified character into this String object.
    
	\param insertIndex [in]  Insertion index.
    \param insertChar [in]  Character to insert.

    \returns
    Returns the new length of this String object.
	
    \remarks
    If insertIndex exceeds the length of this String object, 
    this String object is lengthened as necessary to accommodate the insertion.
  */
  OdString& insert(int insertIndex, OdChar insertChar);

  /** \details
    \param insertString [in]  String to insert.
  */

  /** \details
    Inserts the specified string into this String object.
    
    \param insertIndex [in]  Insertion index.
	\param insertString [in]  String to insert.
  
    \returns
    Returns the new length of this String object.
    \remarks
    If insertIndex exceeds the length of this String object, 
    this String object is lengthened as necessary to accommodate the insertion.
  */
  OdString& insert(int insertIndex, const OdChar* insertString);
  
  /** \details
    Inserts the specified string into this String object.
    
    \param insertIndex [in]  Insertion index.
	\param insertString [in]  String to insert.
  
    \returns
    Returns the new length of this String object.
    \remarks
    If insertIndex exceeds the length of this String object, 
    this String object is lengthened as necessary to accommodate the insertion.
  */
  OdString& insert(int insertIndex, const OdString& insertString){return insert(insertIndex, insertString.c_str());}

  /** \details
    Deletes the specified number characters from this String object.

    \param deleteIndex [in]  Deletion index.
    \param count [in]  Number of characters to delete.
    \returns
    Returns the new length of this String object.
  */
  int deleteChars(int deleteIndex, int count = 1);


  /** \details
    Returns the first occurrence of the specified character in this String object.

    \param searchChar [in]  Search character.
     
    \remarks
    Returns -1 if not found.
  */
  int find(OdChar searchChar) const;

  /** \details
    Returns the last occurrence of the specified character in this String object.

    \param searchChar [in]  Search character.
     
    \remarks
    Returns -1 if not found.
  */
  int reverseFind(OdChar searchChar) const;

  /** \details
    Returns the last occurrence of the specified character in this String object.

    \param searchChar [in]  Search character.
    \param startIndex [in]  An index from which to start searching back.

    \remarks
    Returns -1 if not found.
  */
  int reverseFind(OdChar searchChar, int startIndex) const;

  /** 
  */
  /** \details
    Returns the first occurrence of the specified character in this String object.

    \param searchChar [in]  Search character.
	\param startIndex [in]  Start index of search.
	
    \remarks
    Returns -1 if not found.
  */
  int find(OdChar searchChar, int startIndex) const;

  /** \details
    Returns the first occurrence in this String object of any member of the specified character set. 

    \param charSet [in]  Character set.
     
    \remarks
    Returns -1 if not found.
  */
  int findOneOf(const OdChar* charSet) const;

  int findRev(OdChar ch) const;
  int findRev(const OdChar *psz) const;
  int findOneOfRev(const OdChar *psz) const;
  int findRev(const OdString & ods) const;

  /** \details
    Returns the first occurrence of the specified string in this String object.

    \param searchString [in]  Search string.
     
    \remarks
    Returns -1 if not found.
  */
  int find(const OdChar* searchString) const;

  /** \details
    Returns the first occurrence of the specified string in this String object.

    \param searchString [in]  Search string.
	\param startIndex [in]  Start index of search.
     
    \remarks
    Returns -1 if not found.
  */
  int find(const OdChar* searchString, int startIndex) const;

  int find(const OdString & ods) const;

  /** \details
    Assigns a value to this String object using a printf-style format string and 
    arguments.
    \param formatString [in]  Format string.
    \returns
    Returns a reference to this String Object.
  */
  OdString& format(const OdChar* formatString, ...);

  /** \details
    Assigns a value to this String object using a vsprintf-style format string and 
    argument list.
    \param formatString [in]  Format string.
    \param argList [in]  Argument list.   
    \returns
    Returns a reference to this String Object.
  */
  OdString& formatV(const OdChar* formatString, va_list argList); 
  OdString & appendFormat(const OdChar   *pszFmt, ...);
                                                     
  /** \details
    Returns a modifiable C style OdChar array (buffer) of the specified minimum length for this String object.
    \param minBufferLength [in]  Minimum buffer length.
    
    \remarks
    releaseBuffer() should be called before using any other OdString methods.
    
    The pointer returned by this function is not valid after releaseBuffer() is called.
  */
  OdChar* getBuffer(int minBufLength);

  /** \details
    Releases a buffer obtained by getBuffer() or getBufferSetLength(), and sets its length.
    \param newLength [in]  New buffer length.
    \remarks
    If newLength == -1, the buffer is treated as 0 terminated.  
  */
  bool releaseBuffer(int newLength = -1);

  /** \details
    Returns a modifiable C style OdChar array (buffer) of of the specified length for this String object.
    \param length [in]  buffer length.
    
    \remarks
    releaseBuffer() should be called before using any other OdString methods.
    
    The pointer returned by this function is not valid after releaseBuffer() is called.
  */
  OdChar* getBufferSetLength(int length);

  /** \details
    Releases any unused memory allocated by this String object.
  */
  void freeExtra();

  /** \details
    Enables reference counting for this String object.
  */
  OdChar* lockBuffer();

  /** \details
    Disables reference counting for this String object.
  */
  void unlockBuffer();

/*   disable wide char functionalities
   Constructor.  This OdString will receive a copy of the wide character string referenced
   by lpsz.
  OdString(const OdCharW* lpsz);

  Constructor. This OdString will receive a copy of the first nLength wide characters of
  the string referenced by lpch.
  OdString(const OdCharW* lpch, int nLength);

   Assignment operator.  This OdString is assigned the value of lpsz.
  const OdString& operator=(const OdCharW* lpsz);

*/

#ifdef NOT_IMPLEMENTED

  /*!DOM*/
  /** \details
    Case sensitive string comparison.  
    
    \param otherString [in]  Other string.
    
    \remarks
    collate() returns one of the following:
    
    <table>
    Returns   Condition
    < 0       This String object < otherString. 
    0         This String object == otherString.
    > 0       This String object > otherString.
    </table>
  */
  int collate(const OdChar* otherString) const;

  /*!DOM*/
  /** \details
    Case insensitive string comparison.  
    
    \param otherString [in]  Other string.
    
    \remarks
    icollate() returns one of the following:
    
    <table>
    Returns   Condition
    < 0       This String object < otherString. 
    0         This String object == otherString.
    > 0       This String object > otherString.
    </table>
  */
  int iCollate(const OdChar* otherString) const;

  /** \details
    Assigns a value to this String object using a printf-style format string and 
    arguments.
    \param formatID [in]  Format ID. 
    \returns
    Returns a reference to this String Object.
  */
  OdString& ODA_CDECL format(unsigned int formatID, ...);
#endif


public:
  ~OdString();

  /** \details
    Returns the number of characters allocated for the underlying OdChar array (buffer) in this String object.
  */
  int getAllocLength() const
  { return getData()->nAllocLength; }

  /** \details
  Assures the character buffer of this String object is at least the specified size.
  \param length [in]  New length of internal buffer.

  \remarks
  This function destroys the existing string contents if any. String length is set to 0.
*/
  inline void preallocate(int length)
  {
    allocBeforeWrite(length);
    m_pData->nDataLength = 0;
  }

protected:
  FIRSTDLL_EXPORT_STATIC static OdStringData kEmptyData;

  /** \details
    Pointer to the underlying OdChar array (buffer). 
  */
  OdStringData* m_pData;  
  
  /** \details
    Returns the StringData for this String object.
  */
  OdStringData* getData() const
    { ODA_ASSERT(m_pData!= NULL); return m_pData; }

  /** \details
    Initializes this String object to an empty string.
  */
  void init();

  /** \details
    Copies the specified number of characters from this String object to the destination String object.
    \param destString [out]  Destination string.
    \param copyLength [in]  Number of characters to copy.
    \param copyIndex [in]  First byte to copy.
    \param extraLength [in]  Extra characters to allocate.
    
    \remarks
    This function calls allocBuffer(copyLength + extraLength)
  */
  void allocCopy(OdString& destString, int copyLength, int copyIndex, int extraLength) const;

  /** \details
    Allocates the specified number of characters for the character buffer of this String object.
    \param length [in]  buffer length.
    allocAlways - if true, allocates new OdStringData even for 0 length unicode buffer (for ansi string constructors)
  */
  void allocBuffer(int length, bool allocAlways = false);

  /** \details
    Copies the specified string to this String object.
    
    \param sourceLength [in]  Number of characters to copy.
    \param source [in]  Source string.

    \remarks
    If getAllocLength() < sourceLength, this function calls allocBuffer(sourceLength).
  */
    void assignCopy(int sourceLength, const OdChar* source);

  /** \details
    Concatenates and copies the specified strings to this String object.
    
    \param sourceLength1 [in]  Number of characters in first string to copy.
    \param sourceLength2 [in]  Number of characters in second string to copy.
    \param source1 [in]  First source string.
    \param source2 [in]  Second source string.

    \remarks
    If getAllocLength() < (sourceLength1 + sourceLength2), this function calls allocBuffer(sourceLength1 + sourceLength2).
  */
    void concatCopy(int sourceLength1, const OdChar* source1, int sourceLength2, const OdChar* source2);

  /** \details
    Concatenates the string to this String object.
    
    \param sourceLength [in]  Number of characters to copy.
    \param source [in]  Source string.

    \remarks
    If getAllocLength() < getLength() + sourceLength, this function calls allocBuffer(getLength()+ sourceLength2).
  */
    void concatInPlace(int sourceLength, const OdChar* source);
 
  /** \details
    Assures there are no multiple references to the StringData associated with this String object. 
    
    \remarks
    If there is more than one reference to the StringData object, it is released, and
    replaced with a copy thereof 
  */
  void copyBeforeWrite();

  /** \details
    Assures the character buffer of this String object is at least the specified size.
    \param newLength [in]  New length of buffer.
    
    \remarks
    If getAllocLength() < newLength, this function calls allocBuffer(newLength).
  */
  void allocBeforeWrite(int newLength);

  /** \details
    Releases the reference to the specified StringData object.
    
    \param pStringData [in]  Pointer to the StringData object.
    
    \remarks
    If pStringData is not specified, the StringData associated with
    this String object is released.
    
    Decrements the reference count of the StringData object.
        
    When its reference count reaches zero, the StringData object is freed.
  */
  void release();

  static void release(OdStringData* pStringData);

  /** \details
    Returns the length of the specified string.
    \param string [in]  0 terminated string or NULL.
    \remarks
    Returns 0 if string == NULL.
  */
  static int safeStrlen(const OdChar* string)
  { return (string == NULL) ? (int)0 : (int)odStrLen((const wchar_t*)string); }

  /** \details
    Frees the specified StringData object.
    \param pStringData [in]  Pointer to the StringData object.
  */
  static void freeData(OdStringData* pStringData);

  bool isUnicodeNotInSync() const
  {
    return !getData()->unicodeBuffer && getData()->ansiString;
  }
  void syncUnicode() const;
  OdAnsiString* getAnsiString() const
  {
    if (getData()->ansiString)
      return reinterpret_cast<OdAnsiString*>(&getData()->ansiString);
    else 
      return 0;
  }
  void freeAnsiString()const;
  friend class OdAnsiString;
public:
  /** \details
    Functional object to do case-less string comparison e.g. in <algorithm> functions.
  */
  struct lessnocase { bool operator () (const OdString& x, const OdString& y) const { return x.iCompare(y) < 0; } };
};

typedef OdChar OdCharW;
typedef OdString OdWString;

bool operator == (OdChar wch, const OdString & ods);
bool operator == (const OdChar* pwsz, const OdString& ods);
bool operator != (OdChar wch, const OdString & ods);
bool operator != (const OdChar* pwsz, const OdString& ods);
bool operator < (OdChar wch, const OdString & ods);
bool operator < (const OdChar* pwsz, const OdString& ods);
bool operator > (OdChar wch, const OdString & ods);
bool operator > (const OdChar* wch, const OdString& ods);
bool operator <= (OdChar wch, const OdString & ods);
bool operator <= (const OdChar* wch, const OdString& ods);
bool operator >= (OdChar wch, const OdString & ods);
bool operator >= (const OdChar* wch, const OdString& ods);
OdString operator + (OdChar wch, const OdString & ods);
OdString operator + (const OdChar *pwsz, const OdString & ods);

inline const OdChar *  OdString::constPtr() const
{
  return this->kwszPtr();
}

inline const OdChar * OdString::kTCharPtr() const
{
  return this->kwszPtr();
}

inline const OdChar* OdString::kOdCharPtr() const
{
  return this->kwszPtr();
}

inline int OdString::find(OdChar ch) const
{
  const OdChar str[2] = { ch, '\0' };
  return this->findOneOf(str);
}

inline int OdString::findRev(OdChar ch) const
{
  const OdChar str[2] = { ch, '\0' };
  return this->findOneOfRev(str);
}

inline OdString OdString::mid(int nStart, int nNumChars) const
{
  return this->substr(nStart, nNumChars);
}

inline OdString OdString::mid(int nStart) const
{
  return this->mid(nStart, -1);
}

inline OdString OdString::substr(int nNumChars) const
{
  return this->substr(0, nNumChars);
}

inline OdString OdString::left(int nNumChars) const
{
  return this->substr(nNumChars);
}

inline OdString OdString::right(int nNumChars) const
{
  return this->substrRev(nNumChars);
}

inline OdString & OdString::trimLeft(OdChar wch)
{
  const OdChar wszChars[] = { wch, L'\0' };
  return this->trimLeft(wszChars);
}

inline OdString & OdString::trimLeft()
{
  return this->trimLeft(nullptr);
}

inline OdString & OdString::trimRight(OdChar wch)
{
  const OdChar wszChars[] = { wch, L'\0' };
  return this->trimRight(wszChars);
}

inline OdString & OdString::trimRight()
{
  return this->trimRight(nullptr);
}

inline OdString & OdString::trim(OdChar wch)
{
  const OdChar wszChars[] = { wch, L'\0' };
  return this->trim(wszChars);
}

inline OdString & OdString::trim()
{
  return this->trim(nullptr);
}

inline OdString & OdString::trim(const OdChar *pwszChars)
{
  return this->trimRight(pwszChars).trimLeft(pwszChars);
}

inline OdString & OdString::assign(OdChar wch)
{
  const OdChar wstr[2] = { wch, L'\0' };
  return this->assign(wstr);
}


inline OdString & OdString::operator = (OdChar wch)
{
  return this->assign(wch);
}

inline OdString & OdString::operator = (const OdChar *pwsz)
{
  return this->assign(pwsz);
}

inline OdString & OdString::operator = (const OdString & ods)
{
  return this->assign(ods);
}

inline OdString & OdString::operator = (const OdDbHandle & h)
{
  return this->assign(h);
}

inline OdString & OdString::operator += (OdChar wch)
{
  return this->append(wch);
}

inline OdString & OdString::operator += (const OdChar *pwsz)
{
  return this->append(pwsz);
}

inline OdString & OdString::operator += (const OdString & ods)
{
  return this->append(ods);
}

inline OdString & OdString::append(OdChar wch)
{
  const OdChar wstr[2] = { wch, L'\0' };
  return this->append(wstr);
}

inline OdString OdString::operator + (OdChar wch) const
{
  return this->concat(wch);
}

inline OdString OdString::operator + (const OdChar * pwsz) const
{
  return this->concat(pwsz);
}

inline OdString OdString::operator + (const OdString & ods) const
{
  return this->concat(ods);
}

inline OdString OdString::concat(OdChar wch) const
{
  const OdChar wstr[2] = { wch, L'\0' };
  return this->concat(wstr);
}

inline OdString OdString::precat(OdChar ch) const
{
  const OdChar str[2] = { ch, '\0' };
  return this->precat(str);
}

inline int OdString::compare(OdChar wch) const
{
  const OdChar wstr[2] = { wch, L'\0' };
  return this->compare(wstr);
}

inline int OdString::compareNoCase(OdChar wch) const
{
  const OdChar wstr[2] = { wch, L'\0' };
  return this->compareNoCase(wstr);
}

inline bool OdString::operator == (OdChar wch) const
{
  return this->compare(wch) == 0;
}

inline bool OdString::operator == (const OdChar *pwsz) const
{
  return this->compare(pwsz) == 0;
}

inline bool OdString::operator == (const OdString & ods) const
{
  return this->compare(ods) == 0;
}

inline bool OdString::operator != (OdChar wch) const
{
  return this->compare(wch) != 0;
}

inline bool OdString::operator != (const OdChar *pwsz) const
{
  return this->compare(pwsz) != 0;
}

inline bool OdString::operator != (const OdString & ods) const
{
  return this->compare(ods) != 0;
}

inline bool OdString::operator > (OdChar wch) const
{
  return this->compare(wch) > 0;
}

inline bool OdString::operator > (const OdChar *pwsz) const
{
  return this->compare(pwsz) > 0;
}

inline bool OdString::operator > (const OdString & ods) const
{
  return this->compare(ods) > 0;
}

inline bool OdString::operator >= (OdChar wch) const
{
  return this->compare(wch) >= 0;
}

inline bool OdString::operator >= (const OdChar *pwsz) const
{
  return this->compare(pwsz) >= 0;
}

inline bool OdString::operator >= (const OdString & ods) const
{
  return this->compare(ods) >= 0;
}

inline bool OdString::operator < (OdChar wch) const
{
  return this->compare(wch) < 0;
}

inline bool OdString::operator < (const OdChar *pwsz) const
{
  return this->compare(pwsz) < 0;
}

inline bool OdString::operator < (const OdString & ods) const
{
  return this->compare(ods) < 0;
}

inline bool OdString::operator <= (OdChar wch) const
{
  return this->compare(wch) <= 0;
}

inline bool OdString::operator <= (const OdChar *pwsz) const
{
  return this->compare(pwsz) <= 0;
}

inline bool OdString::operator <= (const OdString & ods) const
{
  return this->compare(ods) <= 0;
}

inline bool operator == (OdChar wch, const OdString & ods)
{
  return ods.compare(wch) == 0;
}

inline bool operator == (const OdChar *pwsz, const OdString & ods)
{
  return ods.compare(pwsz) == 0;
}

inline bool operator != (OdChar wch, const OdString & ods)
{
  return ods.compare(wch) != 0;
}

inline bool operator != (const OdChar *pwsz, const OdString & ods)
{
  return ods.compare(pwsz) != 0;
}

inline bool operator > (OdChar wch, const OdString & ods)
{
  return ods.compare(wch) < 0;
}

inline bool operator > (const OdChar *pwsz, const OdString & ods)
{
  return ods.compare(pwsz) < 0;
}

inline bool operator >= (OdChar wch, const OdString & ods)
{
  return ods.compare(wch) <= 0;
}

inline bool operator >= (const OdChar *pwsz, const OdString & ods)
{
  return ods.compare(pwsz) <= 0;
}

inline bool operator < (OdChar wch, const OdString & ods)
{
  return ods.compare(wch) > 0;
}

inline bool operator < (const OdChar *pwsz, const OdString & ods)
{
  return ods.compare(pwsz) > 0;
}

inline bool operator <= (OdChar wch, const OdString & ods)
{
  return ods.compare(wch) >= 0;
}

inline bool operator <= (const OdChar *pwsz, const OdString & ods)
{
  return ods.compare(pwsz) >= 0;
}

inline OdString operator + (OdChar ch, const OdString & ods)
{
  return ods.precat(ch);
}

inline OdString operator + (const OdChar *pwsz, const OdString & ods)
{
  return ods.precat(pwsz);
}

inline bool OdString::equalsNoCase(const OdString& left, const OdString& right)
{
  return left.compareNoCase(right) == 0;
}

#if defined(ODA_UNIXOS)
/** <group Other_Classes>
*/
class OdW2US
{
  OdUInt16* _buf;
public:
  OdW2US(const wchar_t* pStr)
  {
    size_t len = Od_wcslen(pStr);
    _buf = new OdUInt16[len+1];
    for (size_t i = 0; i < len; i++)
    {
      _buf[i] = (OdUInt16)pStr[i];
    }
    _buf[len] = 0;
  }
  ~OdW2US() 
  {
    delete[]_buf;
  }
  operator const OdUInt16*() const { return _buf; }
};

/** \details
    <group Other_Classes>
*/
class OdUS2W
{
  wchar_t* _buf;
public:
  OdUS2W(const OdUInt16* pStr)
  {
    size_t len = 0;
    if (const OdUInt16* p = pStr)
    {
      while (*p++)
        len++;
    }
    _buf = new wchar_t[len+1];
    for (size_t i = 0; i < len; i++)
    {
      _buf[i] = (wchar_t)pStr[i];
    }
    _buf[len] = 0;
  }
  ~OdUS2W() 
  {
    delete[] _buf;
  }
  operator const wchar_t*() const { return _buf; }
};

#else

#define OdUS2W(a) (const wchar_t*)(a)
#define OdW2US(a) (const OdUInt16*)(a)

#endif

//////////////////////////////////////////////////////////////////////////

class OdUniqueString
{
public:
  FIRSTDLL_EXPORT static const OdUniqueString *Intern(const wchar_t *p);
};

//////////////////////////////////////////////////////////////////////////

/** \details
    <group Other_Classes>
*/
class FIRSTDLL_EXPORT OdConstString : public OdString
{
public:
  OdConstString(const OdChar* pSource = NULL);
  // Destructor of base class OdString is not virtual (critical for performance).
  // Therefore ~OdConstString is missing

  OdConstString& operator = (const OdConstString& pSource);
  OdString& operator = (const OdString& pSource);
  OdString& operator = (OdChar ch);
  OdString& operator = (const OdChar* pSource);
  OdString& operator = (const OdAnsiString& pSource);
  OdString& operator = (const char* pSource);
  operator const OdChar*() const;

protected:
  OdStringData m_data;  
};

#if defined(_AFX) || defined(__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)


inline OdString::OdString(const CStringW &csw) : OdString()
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  *this = pwsz;
}

inline OdString & OdString::operator = (const CStringW &csw)
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return this->assign(pwsz);
}

inline OdString & OdString::operator += (const CStringW &csw)
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return this->append(pwsz);
}

inline int OdString::compare(const CStringW & csw) const
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return this->compare(pwsz);
}

inline int OdString::compareNoCase(const CStringW & csw) const
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return this->compareNoCase(pwsz);
}

inline int OdString::match(const CStringW & csw) const
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return this->match(pwsz);
}

inline int OdString::matchNoCase(const CStringW & csw) const
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return this->matchNoCase(pwsz);
}

inline bool OdString::operator == (const CStringW & csw) const
{
  return this->compare(csw) == 0;
}

inline bool OdString::operator != (const CStringW & csw) const
{
  return this->compare(csw) != 0;
}

inline bool OdString::operator > (const CStringW & csw) const
{
  return this->compare(csw) > 0;
}

inline bool OdString::operator >= (const CStringW & csw) const
{
  return this->compare(csw) >= 0;
}

inline bool OdString::operator < (const CStringW & csw) const
{
  return this->compare(csw) < 0;
}

inline bool OdString::operator <= (const CStringW & csw) const
{
  return this->compare(csw) <= 0;
}

#ifdef _AFX
// Global CString-related operators
inline bool operator == (const CStringW & csw, const OdString & ods)
{
  return ods.compare(csw) == 0;
}

inline bool operator != (const CStringW & csw, const OdString & ods)
{
  return ods.compare(csw) != 0;
}

inline bool operator >  (const CStringW & csw, const OdString & ods)
{
  return ods.compare(csw) < 0;
}

inline bool operator >= (const CStringW & csw, const OdString & ods)
{
  return ods.compare(csw) <= 0;
}

inline bool operator <  (const CStringW & csw, const OdString & ods)
{
  return ods.compare(csw) > 0;
}

inline bool operator <= (const CStringW & csw, const OdString & ods)
{
  return ods.compare(csw) >= 0;
}

#ifndef DISABLE_CSTRING_PLUS_ACSTRING
inline OdString operator + (const CStringW & csw, const OdString & ods)
{
  const wchar_t *pwsz = (const wchar_t *)csw;
  return ods.precat(pwsz);
}
#endif

#endif

#endif // _AFX

//////////////////////////////////////////////////////////////////////////

#include "TD_PackPop.h"

#endif // __ODSTRING_H__


