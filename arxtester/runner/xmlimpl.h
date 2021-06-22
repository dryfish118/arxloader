#ifndef _XMLIMPL_H_
#define _XMLIMPL_H_

#include "xmlutil.h"
#import <msxml3.dll>

class CXMLDocWriterImpl :
    public CXmlUtilDocWriter
{
public:
    CXMLDocWriterImpl(void);
    virtual ~CXMLDocWriterImpl(void);

public:
    virtual bool Save(const wchar_t* file);
    virtual CXmlUtilNode* CreateRoot(const wchar_t* name);
    virtual CXmlUtilNode* CreateNode(const wchar_t* name);
    virtual void Release();

protected:
    MSXML2::IXMLDOMDocumentPtr  xmldoc;
    std::vector<CXmlUtilNode*>   m_arNode;
};

class CXMLDocReaderImpl :
    public CXmlUtilDocReader
{
public:
    CXMLDocReaderImpl();
    virtual ~CXMLDocReaderImpl();

public:
    virtual bool Load(const wchar_t* file);
    virtual CXmlUtilNode* Root();
    virtual void Release();

protected:
    MSXML2::IXMLDOMDocumentPtr  xmldoc;
    CXmlUtilNode*                m_root;
};

class ClXMLNodeImpl :
  public CXmlUtilNode
{
  friend class CXMLDocWriterImpl;
  friend class CXMLDocReaderImpl;
public:
  ClXMLNodeImpl();
  virtual ~ClXMLNodeImpl();

public:
  virtual bool Append(CXmlUtilNode* node);
  virtual int ChildCount();
  virtual CXmlUtilNode* Child(int i);
  virtual CXmlUtilNode* Child(const wchar_t* name);
  virtual CXmlUtilNode* CreateChild(const wchar_t* name);
  virtual size_t AttributeCount();
  virtual CXmlUtilNode* Attribute(int i);
  virtual CXmlUtilNode* Attribute(const wchar_t* name);
  virtual bool AddAttribute(const wchar_t* name, const wchar_t* value);
  virtual std::wstring Name();
  virtual std::wstring Value();
  virtual void SetValue(const wchar_t* value);

protected:
  MSXML2::IXMLDOMNodePtr xmlnode;
  std::vector<CXmlUtilNode*> m_arNode;
  CXmlUtilDocWriter* doc;
};

#endif //_XMLIMPL_H_
