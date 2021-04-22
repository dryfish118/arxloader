#pragma once
#include "gcadstd.h"
#include "gds.h"
#include "../DbDatabase.h"
#include "../DbMText.h"
#include "../DbDimension.h"
#include "../DbArcDimension.h"
#include "../DbDimStyleTableRecord.h"
#include "../DbOrdinateDimension.h"
#include "../DbAlignedDimension.h"
#include "../DbRotatedDimension.h"
#include "../Db3PointAngularDimension.h"
#include "../Db2LineAngularDimension.h"
#include "../DbRadialDimension.h"
#include "../DbDiametricDimension.h"
#include "../DbRadialDimensionLarge.h"

#define DYNAMIC_CONSTRAINT_LAYER_OLD		_T("LayerNameForDynamicConstraint")
#define DYNAMIC_CONSTRAINT_LAYER_HIDDEN_OLD	_T("*LayerNameForDynamicConstraint")

#define DYNAMIC_CONSTRAINT_LAYER			_T("ADSK_CONSTRAINTS")
#define DYNAMIC_CONSTRAINT_LAYER_HIDDEN		_T("*ADSK_CONSTRAINTS")

#define GcDbDimensionStyleOverrule OdDbDimensionStyleOverrule


class OdDbDimensionStyleOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdDbDimensionStyleOverrule);

  TOOLKIT_EXPORT OdDbDimensionStyleOverrule();

  TOOLKIT_EXPORT virtual OdDbObjectId   dimensionStyle(const OdDbDimension* pSubject);

  TOOLKIT_EXPORT virtual OdResult   setDimensionStyle(OdDbDimension* pSubject, OdDbObjectId dimStyleId);

  TOOLKIT_EXPORT virtual OdResult   getDimstyleData(const OdDbDimension* pSubject, OdDbDimStyleTableRecord*& pRecord);

  TOOLKIT_EXPORT virtual OdResult   setDimstyleData(OdDbDimension* pSubject, OdDbDimStyleTableRecord* pRecord);

  TOOLKIT_EXPORT virtual OdResult   setDimstyleData(OdDbDimension* pSubject, OdDbObjectId dimstyleId);
};