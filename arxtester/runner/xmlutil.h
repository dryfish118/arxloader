#ifndef _XMLUTIL_H_
#define _XMLUTIL_H_

class CXmlUtilNode;

class CXmlUtilDocWriter
{
public:
    virtual bool Save(const wchar_t* file)=0;
    virtual CXmlUtilNode* CreateRoot(const wchar_t* name)=0;
    virtual CXmlUtilNode* CreateNode(const wchar_t* name)=0;
    virtual void Release()=0;
};

class CXmlUtilDocReader
{
public:
    virtual bool Load(const wchar_t* file)=0;
    virtual CXmlUtilNode* Root()=0;
    virtual void Release()=0;
};

class CXmlUtilNode
{
public:
    virtual bool Append(CXmlUtilNode* node)=0;
    virtual int ChildCount()=0;
    virtual CXmlUtilNode* Child(int i)=0;
    virtual CXmlUtilNode* Child(const wchar_t* name)=0;
    virtual CXmlUtilNode* CreateChild(const wchar_t* name)=0;
    virtual size_t AttributeCount()=0;
    virtual CXmlUtilNode* Attribute(int i)=0;
    virtual CXmlUtilNode* Attribute(const wchar_t* name)=0;
    virtual bool AddAttribute(const wchar_t* name, const wchar_t* value)=0;
    virtual std::wstring Name()=0;
    virtual std::wstring Value()=0;
    virtual void SetValue(const wchar_t* value)=0;
};

CXmlUtilDocWriter* xmlutilCreateXMLDocWriter();
CXmlUtilDocReader* xmlutilCreateXMLDocReader();

#endif //_XMLUTIL_H_