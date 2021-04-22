#pragma once

#include "Gs.h"

class OdGsNode;

namespace Otil
{
  class Image;
};

// ****************************************************************************
// OdGsConfig
// ****************************************************************************


class OdGsConfigReactor
{
public:
  OdGsConfigReactor(void) { }
  virtual     ~OdGsConfigReactor(void) { }

  virtual void hardwareAccelerationWasModified(bool /*newValue*/) { }
  virtual void configWasModified(void) { }
  virtual void deviceSwitchToBegin(void) { }
  virtual void deviceSwitchHasEnded(void) { }
};

class OdGsConfig
{
protected:
  OdGsConfig(void) = default;

public:

  enum Handedness
  {
    kLeft,
    kRight
  };

  enum Quality
  {
    kLowQuality,
    kMediumQuality,
    kHighQuality
  };

  enum DegradationChannel
  {
    kViewportDraw,   
    kLineAntialias,  
    kLighting,        
    kTransparencyQuality,
    kShadowsFull,        
    kTransparency,       
    kDiscardBackfaces,   
    kShadowsGround,      
    kEdgeStyles,         
    kFacetEdges,         
    kFastSilhouette,     
    kTextures,           
    kMaterials,          
    kLightingQuality,    
    kBackgrounds,        
    kIntersectEdges,     
    kFaceted,            
    kWireframe,          
    kDegradationChannels
  };

  virtual                    ~OdGsConfig(void) = default;

  virtual bool                configure(void) = 0;
  virtual bool                showConfigDialog(const wchar_t *strInput = nullptr) const = 0;

  virtual void                driverName(OdChar *pszPath, int nStrLen) const = 0;
  virtual int                 driverVersion(void) const = 0;
  virtual int                 driverRevision(void) const = 0;
  virtual void                driverPath(OdChar *pszPath,
    int    nStrLen) const = 0;
  virtual void                setDriverPath(const OdChar *pszPath) = 0;

  virtual void                currentDisplayDriver(OdChar *pszPath,
    int    nPathStrLen,
    OdChar *pszDriver,
    int    nDriverStrLen,
    bool  &bAccelerated) const = 0;

  virtual void                hardwareAcceleratedDriver(OdChar *pszPath,
    int    nPathStrLen,
    OdChar *pszDriver,
    int    nDriverStrLen) const = 0;
  virtual void                setHardwareAcceleratedDriver(const OdChar *pszPath,
    const OdChar *pszDriver) = 0;

  virtual void                defaultHardwareAcceleratedDriver(OdChar *pszPath,
    int    nPathStrLen,
    OdChar *pszDriver,
    int    nDriverStrLen) const = 0;
  virtual void                hardwareAcceleratedDrivers(OdChar  *pszPath,
    int     nPathStrLen,
    OdChar **pszDrivers,
    int     nDrivers,
    int     nDriverStrLen) = 0;
  virtual int                 numHardwareAcceleratedDrivers(void) = 0;

  virtual void                setDynamicTessellation(bool bDynamicTessellation) = 0;
  virtual bool                dynamicTessellation(void) const = 0;

  virtual GS::ErrorStatus     setMaxLODs(int nLevels) = 0;
  virtual int                 maxLODs(void) const = 0;

  virtual GS::ErrorStatus     setSurfaceTessellationTol(int surfaceTessellationTol) = 0;
  virtual int                 surfaceTessellationTol(void) const = 0;

  virtual GS::ErrorStatus     setCurveTessellationTol(int curveTessellationTol) = 0;
  virtual int                 curveTessellationTol(void) const = 0;

  // adaptive degradation
  virtual GS::ErrorStatus     setFrameRate(int nFramesPerSecond) = 0;
  virtual int                 frameRate(void) const = 0;

  virtual void                setAdaptiveDegradation(bool bAdaptiveDegradation) = 0;
  virtual bool                adaptiveDegradation(void) const = 0;

  virtual int                 degradationChainPosition(DegradationChannel) const = 0;
  virtual DegradationChannel  degradationChannelAt(int position) const = 0;
  virtual void                shiftDegradationChainPosition(DegradationChannel,
    bool bShiftDown) = 0;
  virtual void                setCanDegradeChannel(DegradationChannel,
    bool bDegrade) = 0;
  virtual bool                canDegradeChannel(DegradationChannel) const = 0;

  virtual void                setRedrawOnWindowExpose(bool bRedrawWindowExpose) = 0;  // internal use
  virtual bool                redrawOnWindowExpose(void) const = 0;

  virtual void                setHandedness(Handedness) = 0;
  virtual Handedness          handedness(void) const = 0;

  virtual void                setDiscardBackFaces(bool bDiscardBackFaces) = 0;
  virtual bool                discardBackFaces(void) const = 0;

  virtual void                setTransparency(Quality quality) = 0;
  virtual Quality             transparency(void) const = 0;

  virtual void                addReactor(OdGsConfigReactor *) = 0;
  virtual void                removeReactor(OdGsConfigReactor *) = 0;

  struct EffectStatus
  {
    const OdUniqueString* pUniqueString;         
    OdString              effectName;            
    bool                  bEnabled;
    bool                  bRecommended;
    bool                  bAvailable;
    int                   nFeatureLevel;         
  };

  struct CertificationData
  {
    OdString              sCardName;        
    OdString              sDriverVersion;   
    OdString              sProductDriverURL;
    OdString              sTuningDate;      
    OdString              sDeviceFailed;    
    int                   nHardwareFeatureLevel;
    int                   nSoftwareFeatureLevel;
    int                   nCertificationStatus; 
    int                   nHardwareID;          
  };

  enum EffectListType {
    kEL_Current,
    kEL_RegistryHardware,
    kEL_RegistrySoftware,
    kEL_File
  };

  virtual OdArray<EffectStatus> * getEffectList(EffectListType type) = 0;

  virtual bool                isFeatureEnabled(const OdUniqueString*) const = 0;
  virtual void                setFeatureEnabled(const OdUniqueString*, bool bEnable = true) = 0;
  virtual bool                isFeatureAvailable(const OdUniqueString*) const = 0;
  virtual bool                isFeatureRecommended(const OdUniqueString*) const = 0;

  virtual void                setHardwareAcceleration(bool bEnable) = 0;
  virtual bool                isHardwareAccelerationEnabled(void) = 0;
  virtual bool                isHardwareAccelerationAvailable(void) = 0;
  virtual bool                isHardwareAccelerationRecommended(void) = 0;
  virtual bool                isNoHardwareOverrideEnabled(void) = 0;

  virtual CertificationData   getCertificationData(void) = 0;
  virtual OdString            getVirtualDeviceName(void) = 0;

  virtual void                setGenerateVertexNormals(bool bEnable) = 0;
  virtual bool                generateVertexNormals(void) const = 0;
};

class OdGsConfig2 : public OdGsConfig
{
public:
  virtual bool generateVertexNormals(void) const = 0;
  virtual void setGenerateVertexNormals(bool bEnable) = 0;
};

struct OdGsDrawableLink
{
  LONG_PTR id;
  OdGiDrawable *pDrawable;
  OdGsNode *pNode;
};

typedef OdArray<OdGsDrawableLink> OdGsDrawablePath;




