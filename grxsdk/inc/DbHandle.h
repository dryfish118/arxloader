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




#ifndef ODDBHANDLE
#define ODDBHANDLE /*!DOM*/

#include "TD_PackPush.h"

#include "DbRootExport.h"
#include "OdArrayPreDef.h"
#include "OdaDefs.h"
#include "OdString.h"

/** \details
  Returns the decimal value of a hexadecimal digit.
  
  \param hexDigit [in]  Hex digit.
  
  Examples:  
  getHexValue('A') returns 10, etc.
*/
DBROOT_EXPORT int getHexValue(
  int hexDigit);

/** \details
  Returns the 64 bit integer value corresponding to the passed in string.
  \param pStr [in] String representation of an integer.
*/
//TOOLKIT_EXPORT OdInt64 atoi64(const OdChar* pStr);
//TOOLKIT_EXPORT void    i64toA(const OdInt64 &val, OdChar* pStr);

/** \details
    This class encapsulates the 64-bit integer handles associated with OdDbObject instances.
    
    Corresponding C++ library: TD_Db
    
    \remarks
    Handles are persistent and unique within a database. Handles are not, 
	however, unique between databases.
    
    <group OdDb_Classes>
*/
class DBROOT_EXPORT OdDbHandle
{
public:
  OdDbHandle() : m_val(0) {}

  OdDbHandle(int lo, int hi) { m_val = OD_MAKEQWORD(lo, hi); }

  OdDbHandle(OdUInt64 value) : m_val(value) {}
  
  OdDbHandle(const OdChar* value) { *this = value; }

  OdDbHandle& operator=(const OdChar* value);
  
  OdDbHandle& operator=(const OdDbHandle& value)
  {
    m_val = value.m_val;
    return *this;
  }

  OdDbHandle& operator=(OdUInt64 val)
  {
    m_val = val;
    return *this;
  }
  
  operator OdInt()   const { return (OdInt)m_val; }
  operator OdInt32() const { return (OdInt32)m_val; }
  operator OdUInt64() const { return m_val; }
  
  /** \details
    Returns the hexidecmal representation of this Handle object as a null terminated string.
    
    \param pBuf [in]  Pointer to the buffer to receive the string.
    
    \remarks
    The buffer must be at least 17 bytes long.
  */
    bool getIntoAsciiBuffer(
    OdChar* pBuf) const;
    
    bool getIntoAsciiBuffer(OdChar* pBuf, size_t nBufLen) const;

    enum { kStrSiz = 17 };
    template<size_t nBufLen> inline bool getIntoAsciiBuffer(wchar_t(&buf)[nBufLen]) const
    {
      return this->getIntoAsciiBuffer(buf, nBufLen);
    }

  /** \details
    Returns the hexidecmal representation of this Handle object as an OdString.
  */
  OdString ascii() const;
  /** \details
    Returns true and only if this Handle object is null.
  */

  OdDbHandle slowOperatorPlus(const OdDbHandle&) const;

  void copyToOldType(OdUInt8 hand[8]) const;

  void copyFromOldType(const OdUInt8 hand[8]);

  void getValueBytes(OdUInt8* v1, OdUInt8* v2) const;

  void setValueBytes(OdUInt8 v1, const OdUInt8* v2);

  void print() const;

  bool restZeros(int i) const;

  bool isNull() const { return m_val == 0; }
  
  void setNull()
  {
    m_val = 0;
  }

  bool isOne() const
  {
    return (m_val == 1);
  }

  enum
  {
    kMaxValueBytes = 8,
  };

  OdDbHandle& operator++()
  {
    m_val++;
    return *this;
  }
  OdDbHandle operator++(int)
  {
    OdDbHandle tempHandle = *this;
    ++(*this);
    return tempHandle;
  }

  OdDbHandle operator- (const OdUInt64& value) const
  {
    return OdDbHandle(m_val - value);
  }

  OdDbHandle& operator-= (const OdInt64& value)
  {
    m_val -= value;
    return *this;
  }

  bool operator == (
    OdUInt64 value) const { return m_val == value; }
  
  bool operator != (
    OdUInt64 value) const { return m_val != value; }
  
  bool operator > (
    OdUInt64 value) const { return m_val > value; }
  
  bool operator < (
    OdUInt64 value) const { return m_val < value; }
  
  bool operator <= (
    OdUInt64 value) const { return m_val < value || m_val == value; }
  
  bool operator >= (
    OdUInt64 value) const { return m_val > value || m_val == value; }
  
  OdDbHandle& operator+=(
    const OdInt64& value)
  {
    m_val += value;
    ODA_ASSERT_ONCE(!isNull()); // check handle stuff overflow
    return *this;
  }
  OdDbHandle operator+(
    const OdInt64& value)
  {
    OdDbHandle res;
    res.m_val = m_val + value;
    return res;
  }

  OdDbHandle operator + (OdULongPtr value) const
  {
    OdDbHandle res;
    res.m_val = m_val + value;
    return res;
  }

  OdDbHandle operator + (const OdDbHandle& value) const
  {
    OdDbHandle res;
    res.m_val = m_val + value.m_val;
    return res;
  }

  OdDbHandle& operator += (const OdDbHandle& value)
  {
    m_val += value.m_val;
    ODA_ASSERT_ONCE(!isNull()); // check handle stuff overflow
    return *this;
  }

  OdDbHandle operator - (const OdDbHandle& value) const
  {
    OdDbHandle res;
    res.m_val = m_val - value.m_val;
    return res;
  }

  OdDbHandle& operator -= (const OdDbHandle& value)
  {
    m_val -= value.m_val;
    return *this;
  }

  bool operator > (const OdDbHandle& value) const
  {
    return m_val > value.m_val;
  }

  bool operator >= (const OdDbHandle& value) const
  {
    return m_val >= value.m_val;
  }

  bool operator < (const OdDbHandle& value) const
  {
    return m_val < value.m_val;
  }

  bool operator <= (const OdDbHandle& value) const
  {
    return m_val <= value.m_val;
  }

  operator OdInt64 () const
  {
    return *((OdInt64*)(&m_val));
  }

  int compare(const OdDbHandle& value) const
  {
    if (m_val > value.m_val)
    {
      return -1;
    }
    else if (m_val == value.m_val)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }


  /** \details
    Returns the this Handle object as an array OdUInt8[8].
    
    \param bytes [in]  array of bytes to receive the handle.
    
    \remarks
    The low order byte is returned in bytes[0].
    
    \remarks
    The buffer must be at least 17 bytes long.
  */

  void increment()
  {
    m_val++;
  }

  void decrement()
  {
    m_val--;
  }

  int byte(OdUInt32 i) const
  {
    return *((unsigned char *)&m_val + i);
  }

  void bytes(
    OdUInt8 * bytes) const
  {
    OdUInt64 val = m_val;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes = (OdUInt8)(val & 0xFF);
  }

    OdUInt32 low() const
    {
      return OD_LODWORD(m_val);
    }

    OdUInt32 high() const
    {
      return OD_HIDWORD(m_val);
    }
  void setLow(OdUInt32 lo)
  {
    m_val = OD_MAKEQWORD(lo, high());
  }

  void setHigh(OdUInt32 hi)
  {
    m_val = OD_MAKEQWORD(low(), hi);
  }
private:
    OdUInt64  m_val;
};


/** \details
  This template class is a specialization of the OdArray class for OdDbHandle objects.
*/
typedef OdArray<OdDbHandle> OdHandleArray;

#include "TD_PackPop.h"

#endif

