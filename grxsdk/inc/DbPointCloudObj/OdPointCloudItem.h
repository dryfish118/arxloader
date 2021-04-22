#pragma once

#include "DbPointCloudObjExports.h"
#include "OdArray.h"
#include "OdString.h"
#include "gdsdef.h"

class OdPointCloudItem;
typedef OdPointCloudItem* PPointCloudItem;
typedef OdArray<OdPointCloudItem*> OdPointCloudItemArray; 

class DBPOINTCLOUDOBJ_EXPORT OdPointCloudItem
{
public:

  enum OdPointCloudItemType
  {
    kLegacyPointCloud = 0,

    kPointCloudProject,

    kIndividualScan,

    kScan,

    kRegion,

    kScanRootGroup,

    kRegionRootGroup,

    kUnassignedPoint
  };

  OdPointCloudItem();

  ~OdPointCloudItem() {}

  OdPointCloudItem(const OdString& name, const OdString& projectname, int objectid, OdPointCloudItemType categoryid, bool visibility = true, bool highlight = false, OdString guid = L"");

  OdPointCloudItem(const OdPointCloudItem& item);

  OdPointCloudItem& operator =  (const OdPointCloudItem& other);

  static OdPointCloudItem* CreateFromCmdString(const OdChar* cmd);

public:
  void        setName(const OdString& val);

  OdString    name() const;

  void        setProjectName(const OdString& val);

  OdString    projectName() const;

  void        setGuid(const OdString& val);

  const OdString&    guid() const;

  void        setId(int val);

  int         id() const;

  void        setVisibility(bool val);

  bool        visibility() const;

  void        setHighlight(bool val);

  bool        highlight() const;

  void        setColor(float red, float green, float blue);

  float       red() const;

  float       green() const;

  float       blue() const;

  void                    setAdsName(const gds_name& val);

  const gds_name&         adsName() const;

  void                    setItemType(OdPointCloudItemType val);

  OdPointCloudItemType    itemType() const;

private:
  void        copyItem(const OdPointCloudItem& other);
private:
  OdString    m_name;
  OdString    m_projectName;
  OdString    m_guid;
  int         m_id;
  bool        m_visibility;
  bool        m_highlight;
  gds_name    m_gdsName;
  float       m_red;
  float       m_green;
  float       m_blue;
  OdPointCloudItemType    m_itemType;
};
