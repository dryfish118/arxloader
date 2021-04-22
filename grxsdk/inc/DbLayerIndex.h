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




#ifndef OD_DBLYINDX_H
#define OD_DBLYINDX_H

#include "TD_PackPush.h"
#include "DbIndex.h"
#include "DbBlockIterator.h"
#include "DbIdBuffer.h"

class OdDbLayerTable;

/** \details
    This class implements Layer Index objects in an OdDbDatabase instance.


    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbLayerIndex: public OdDbIndex
{
public:
  ODDB_DECLARE_MEMBERS(OdDbLayerIndex);

  OdDbLayerIndex();

  OdDbFilteredBlockIteratorPtr newIterator(
    ODSYSDEF,
    const OdDbFilter* pFilter) const;
  
  OdDbFilteredBlockIterator* newIterator(
    const OdDbFilter* pFilter) const;

  virtual OdResult rebuildFull(
    OdDbIndexUpdateData* pIdxData);
  
  OdResult compute(OdDbLayerTable* pLT,
    OdDbBlockTableRecord* pBTR);
  
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);
  
  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

protected:
  virtual OdResult rebuildModified(
    OdDbBlockChangeIterator* iterator);
};


/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbLayerIndex object pointers.
*/
typedef OdSmartPtr<OdDbLayerIndex> OdDbLayerIndexPtr;


class OdDbLayerIndexIterator : public OdRxObjectImpl<OdDbFilteredBlockIterator>
{
  OdDbLayerIndexIterator& operator = (const OdDbLayerIndexIterator&);
  OdDbBlockIteratorPtr m_pSource;
public:
  TOOLKIT_EXPORT OdDbLayerIndexIterator(const OdDbLayerIndex* pIndex, const OdDbLayerFilter* pFilter);

  static OdDbFilteredBlockIteratorPtr createObject(const OdDbLayerIndex* pIndex, const OdDbLayerFilter* pFilter);

  void setSourceIterator(const OdDbBlockIterator* pSourceIter);

  OdResult start();

  OdDbObjectId next();

  OdDbObjectId id() const;

  OdResult seek(OdDbObjectId id);

  double estimatedHitFraction() const;
  OdResult accepts(OdDbObjectId, OdBool& idPassesFilter) const;

private:
  OdDbLayerIndexPtr                           m_pLayerIndex;
  // mutable  needed below for AIX
  mutable OdArray<OdDbIdBufferIteratorPtr>            m_buffers;
  mutable OdArray<OdDbIdBufferIteratorPtr>::iterator  m_bufferIter;
};


#include "TD_PackPop.h"

#endif // OD_DBLYINDX_H

