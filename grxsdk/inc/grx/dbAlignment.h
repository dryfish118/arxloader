#ifndef _DBALIGNMENT_H
#define _DBALIGNMENT_H

#include "gcdb.h"
#include "dbmain.h"

#pragma pack (push, 8)



class GSOFT_NO_VTABLE GcDbAlignment : public GcRxObject {
public:
    GCRX_DECLARE_MEMBERS(GcDbAlignment);

    virtual Gcad::ErrorStatus getAlignment(
        GcDbEntity*           pEnt,
        const GcArray< GcDbObjectIdArray,
            GcArrayObjectCopyReallocator< GcDbObjectIdArray > >& 
                nestedPickedEntities,
        const GcGePoint3d&    pickPoint,
        const GcGeVector3d&   normal,
        GcGePoint3d&          closestPoint,
        GcGeVector3d&         direction) = 0;
};

ODRX_DEFINE_MEMBERS3(GcDbAlignment);

#pragma pack (pop)

#endif  
