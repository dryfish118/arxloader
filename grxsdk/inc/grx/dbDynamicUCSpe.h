#pragma once
#include "gcdb.h"
#include "dbmain.h"
#include "../DbDynUCSPE.h"

#define GcDbDynamicUCSPE    OdDbDynamicUCSPE

#pragma once
#pragma pack (push, 8)

class CPoint;
class GcDbNonSubEntDynamicUCSPE : public GcRxObject
{
public:
    GCRX_DECLARE_MEMBERS_EXPIMP(GcDbNonSubEntDynamicUCSPE, GCDBCORE2D_PORT);

    virtual Gcad::ErrorStatus
        getCandidatePlane(
            GcDbEntity* Ent,   
            const CPoint& pt,        
            GcGePlane &result,       
            double &distToEdge,      
            double &objWidth,        
            double &objHeight,       
            void*& context           
            ) = 0;

    virtual Gcad::ErrorStatus
            highlightPlane(
            GcDbEntity* Ent,   
            void* context            
            ) = 0;

    virtual Gcad::ErrorStatus
        dehighlightPlane(
            GcDbEntity* Ent,   
            void* context            
            ) = 0;
};

GCRX_DEFINE_MEMBERS3(GcDbNonSubEntDynamicUCSPE)
#pragma pack (pop)

