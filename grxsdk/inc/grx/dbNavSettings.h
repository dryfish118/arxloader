

#pragma once
#pragma pack(push, 8)

class GcDbImpHomeView;

///////////////////////////////////////////////////////////////////////////////
//
// class GcDbHomeView - navigation home view settings class
//
//#define GCDB_PORT
class GcDbHomeView
{
public:
  GCDB_DLL_DECL GcDbHomeView();
  GCDB_DLL_DECL GcDbHomeView(const GcDbHomeView& rhvw);
  GCDB_DLL_DECL virtual ~GcDbHomeView();

    // Member variable routines
  GCDB_DLL_DECL const GcGePoint3d&     eye()           const;
  GCDB_DLL_DECL const GcGePoint3d&     center()        const;
  GCDB_DLL_DECL const GcGeVector3d&    up()            const;
  GCDB_DLL_DECL const double           width()         const;
  GCDB_DLL_DECL const double           height()        const;
  GCDB_DLL_DECL const bool             isPerspective() const;

  GCDB_DLL_DECL void setEye         (const GcGePoint3d& ptEye);
  GCDB_DLL_DECL void setCenter      (const GcGePoint3d& ptCenter);
  GCDB_DLL_DECL void setUp          (const GcGeVector3d& vUp);
  GCDB_DLL_DECL void setWidth       (double dWidth);
  GCDB_DLL_DECL void setHeight      (double dHeight);
  GCDB_DLL_DECL void setPerspective (bool bPerspective);

  GCDB_DLL_DECL bool isDefaultHomeView() const;
    // DB access utility
  GCDB_DLL_DECL OdResult  setHomeView(GcDbDatabase * pDb) const;
  GCDB_DLL_DECL OdResult  getHomeView(GcDbDatabase * pDb,
                                            bool           bCreateDefault = false);

    // Fill members with default values
  GCDB_DLL_DECL void toggleDefaultSettings();

  GCDB_DLL_DECL bool            operator == (const GcDbHomeView& rhvw) const;
  GCDB_DLL_DECL bool            operator != (const GcDbHomeView& rhvw) const;
  GCDB_DLL_DECL GcDbHomeView&   operator  = (const GcDbHomeView& rhvw);

private:
    GcDbImpHomeView * mpImpObj;
};

// Navigation home view routine
GCDB_DLL_DECL
OdResult  gcdbSetHomeView(GcDbDatabase *        pDb, 
                                  const GcDbHomeView&   hmView);

GCDB_DLL_DECL
OdResult  gcdbGetHomeView(GcDbDatabase *        pDb, 
                                  GcDbHomeView&         hmView);

// ViewCube compass show/hide
GCDB_DLL_DECL OdResult
gcdbSetShowCompass(GcDbDatabase *         pDb, 
                   bool                   bShow);

GCDB_DLL_DECL OdResult
gcdbGetShowCompass(GcDbDatabase *         pDb, 
                   bool &                 bShow);

#pragma pack(pop)