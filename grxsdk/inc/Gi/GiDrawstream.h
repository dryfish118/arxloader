//
// This API extends AcGi to support stream draw functionality
//

#pragma once

#include "GiDrawable.h"

#pragma pack(push, 8)

class IGcWriteStream;
class IGcReadStream;
class OdGiDrawStreamImp;

typedef bool (*GraphicsUpdateProc)(const OdArray<OdGiDrawable*>& drawableArray);

///////////////////////////////////////////////////////////////////////////////
// class OdGiDrawStream
//
class FIRSTDLL_EXPORT OdGiDrawStream : public OdGiDrawable
{
    friend class OdGiDrawStreamImp;
public:
    ODRX_DECLARE_MEMBERS(OdGiDrawStream);

    static bool build(const OdArray<OdGiDrawStream*>& streamArray, GraphicsUpdateProc lpFunc);

    OdGiDrawStream();
    OdGiDrawStream(const OdGiDrawable* pOwner);
   ~OdGiDrawStream();

    OdGiDrawable* getOwner() const;
    void setOwner(const OdGiDrawable* pOwner);
    bool isValid() const;

    bool serializeOut(IGcWriteStream* pOutput) const;
    bool serializeIn(IGcReadStream* pInput, OdDbDatabase* pDb = NULL);

    // Overridden methods from OdGiDrawable
    virtual OdBool isPersistent() const override;
    virtual OdDbObjectId id() const override;
    virtual OdGiDrawable::DrawableType drawableType() const override;
    virtual bool bounds(OdDbExtents& bounds) const override;
    virtual void setDrawStream(OdGiDrawStream* pStream) override;
    virtual OdGiDrawStream* drawStream() const override;

protected:
    // Overridden methods from OdGiDrawable
    virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) override;
    virtual OdBool subWorldDraw(OdGiWorldDraw* pWd) override;
    virtual void subViewportDraw(OdGiViewportDraw* pVd) override;
    virtual OdUInt32 subViewportDrawLogicalFlags(OdGiViewportDraw* pVd) override;

protected:
    OdGiDrawStreamImp* m_pImp;
};

#pragma pack(pop)
