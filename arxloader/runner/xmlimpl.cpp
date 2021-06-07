#include "pch.h"
#include "xmlimpl.h"

CXmlUtilDocWriter* xmlutilCreateXMLDocWriter()
{
  return new CXMLDocWriterImpl;
}

 CXmlUtilDocReader* xmlutilCreateXMLDocReader()
{
  return new CXMLDocReaderImpl;
}

//////////////////////////////////////////////////////////////////////////
// CXMLDocWriterImpl
CXMLDocWriterImpl::CXMLDocWriterImpl(void)
{
  if (FAILED(xmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument30))))
  {
    throw L"";
  }
  xmldoc->appendChild(xmldoc->createProcessingInstruction(L"xml", L"version='1.0' encoding='UTF-8'"));
}

CXMLDocWriterImpl::~CXMLDocWriterImpl(void)
{
  std::vector<CXmlUtilNode*>::iterator it = m_arNode.begin();
  for (; it != m_arNode.end(); it++)
  {
    ClXMLNodeImpl* node = static_cast<ClXMLNodeImpl*>(*it);
    if (node)
    {
      delete node;
    }
  }
}

bool CXMLDocWriterImpl::Save(const wchar_t* file)
{
  ATLASSERT(xmldoc);

  MSXML2::IMXWriterPtr pMXWriter = NULL;
  MSXML2::ISAXXMLReaderPtr pSAXReader = NULL;
  if (FAILED(pMXWriter.CreateInstance(__uuidof(MSXML2::MXXMLWriter)))
    || FAILED(pSAXReader.CreateInstance( __uuidof(MSXML2::SAXXMLReader))))
  {
    return false;
  }

  MSXML2::ISAXContentHandlerPtr pISAXContentHandler = pMXWriter;
  MSXML2::ISAXErrorHandlerPtr pISAXErrorHandler = pMXWriter;
  MSXML2::ISAXDTDHandlerPtr pISAXDTDHandler = pMXWriter;

  pMXWriter->omitXMLDeclaration = VARIANT_FALSE;
  pMXWriter->standalone = VARIANT_FALSE;
  pMXWriter->indent = VARIANT_TRUE;
  pMXWriter->encoding = _bstr_t(L"UTF-8");

  pSAXReader->putContentHandler(pISAXContentHandler);
  pSAXReader->putDTDHandler(pISAXDTDHandler);
  pSAXReader->putErrorHandler(pISAXErrorHandler);
  pSAXReader->putProperty((unsigned short*)L"http://xml.org/sax/properties/lexical-handler",
    _variant_t(pMXWriter.GetInterfacePtr()));
  pSAXReader->putProperty((unsigned short*)L"http://xml.org/sax/properties/declaration-handler",
    _variant_t(pMXWriter.GetInterfacePtr()));

  IStream * pOutStream = NULL;
  ::CreateStreamOnHGlobal(NULL, TRUE, &pOutStream);
  pMXWriter->put_output(_variant_t(pOutStream));
  pSAXReader->parse(xmldoc.GetInterfacePtr());

  HGLOBAL hGlobal = NULL;
  ::GetHGlobalFromStream(pOutStream, &hGlobal);
  LARGE_INTEGER llStart = {0, 0};
  ULARGE_INTEGER ullSize = {0, 0};
  pOutStream->Seek(llStart, STREAM_SEEK_CUR, &ullSize);
  LPVOID pOutput = ::GlobalLock(hGlobal);
  
  HANDLE hFile = ::CreateFile(file , GENERIC_WRITE,
    FILE_SHARE_WRITE | FILE_SHARE_READ,
    NULL , CREATE_ALWAYS , 0 , NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
    GlobalUnlock(hGlobal);
    return false;
  }

  DWORD dwWritten = 0;
  ::WriteFile(hFile, pOutput, (UINT)ullSize.QuadPart, &dwWritten, NULL);
  ::FlushFileBuffers(hFile);
  ::CloseHandle(hFile);
  ::GlobalUnlock(hGlobal);
  
  return true;
}

CXmlUtilNode* CXMLDocWriterImpl::CreateRoot(const wchar_t* name)
{
  ATLASSERT(xmldoc);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  node->xmlnode = xmldoc->createElement(name);
  if (node->xmlnode)
  {
    node->doc = this;
    xmldoc->appendChild(node->xmlnode);
    m_arNode.push_back(node);
    return m_arNode.back();
  }
  delete node;
  return NULL;
}

CXmlUtilNode* CXMLDocWriterImpl::CreateNode(const wchar_t* name)
{
  ATLASSERT(xmldoc);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  node->xmlnode = xmldoc->createElement(name);
  if (node->xmlnode)
  {
    node->doc = this;
    m_arNode.push_back(node);
    return m_arNode.back();
  }
  delete node;
  return NULL;
}

void CXMLDocWriterImpl::Release()
{
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// CXMLDocReaderImpl
CXMLDocReaderImpl::CXMLDocReaderImpl()
:   m_root(NULL)
{
  if (FAILED(xmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument30))))
  {
    throw L"";
  }
}

CXMLDocReaderImpl::~CXMLDocReaderImpl()
{
  if (m_root)
  {
    ClXMLNodeImpl* node = static_cast<ClXMLNodeImpl*>(m_root);
    if (node)
    {
      delete node;
    }
  }
}

bool CXMLDocReaderImpl::Load(const wchar_t* file)
{
  ATLASSERT(xmldoc);
  return xmldoc->load(file) == VARIANT_TRUE ? true : false;
}

CXmlUtilNode* CXMLDocReaderImpl::Root()
{
  ATLASSERT(xmldoc && !m_root);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  node->xmlnode = xmldoc->GetdocumentElement();
  if (node->xmlnode)
  {
    m_root = node;
    return m_root;
  }
  delete node;
  return NULL;
}

void CXMLDocReaderImpl::Release()
{
  delete this;
}

//////////////////////////////////////////////////////////////////////////
// ClXMLNodeImpl
ClXMLNodeImpl::ClXMLNodeImpl()
  : doc(NULL)
{
}

ClXMLNodeImpl::~ClXMLNodeImpl()
{
  std::vector<CXmlUtilNode*>::iterator it = m_arNode.begin();
  for (; it != m_arNode.end(); it++)
  {
    ClXMLNodeImpl* node = static_cast<ClXMLNodeImpl*>(*it);
    if (node)
    {
      delete node;
    }
  }
}

bool ClXMLNodeImpl::Append(CXmlUtilNode* node)
{
  ATLASSERT(xmlnode);
  if (node)
  {
    ClXMLNodeImpl* pnode = static_cast<ClXMLNodeImpl*>(node);
    ATLASSERT(pnode);
    return xmlnode->appendChild(pnode->xmlnode);
  }
  return false;
}

int ClXMLNodeImpl::ChildCount()
{
  ATLASSERT(xmlnode);
  return (int)xmlnode->GetchildNodes()->Getlength();
}

CXmlUtilNode* ClXMLNodeImpl::Child(int i)
{
  ATLASSERT(xmlnode);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  node->xmlnode = xmlnode->GetchildNodes()->Getitem(i);
  if (node->xmlnode)
  {
    m_arNode.push_back(node);
    return m_arNode.back();
  }
  delete node;
  return NULL;
}

CXmlUtilNode* ClXMLNodeImpl::Child(const wchar_t* name)
{
  ATLASSERT(xmlnode);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  for (long i = 0; i < xmlnode->GetchildNodes()->Getlength(); i++)
  {
    if (xmlnode->GetchildNodes()->Getitem(i)->GetbaseName() == _bstr_t(name))
    {
      node->xmlnode = xmlnode->GetchildNodes()->Getitem(i);
      break;
    }
  }
  if (node->xmlnode)
  {
    m_arNode.push_back(node);
    return m_arNode.back();
  }
  delete node;
  return NULL;
}

CXmlUtilNode* ClXMLNodeImpl::CreateChild(const wchar_t* name)
{
  ATLASSERT(doc && name);
  CXmlUtilNode* node = doc->CreateNode(name);
  Append(node);
  return node;
}

size_t ClXMLNodeImpl::AttributeCount()
{
  ATLASSERT(xmlnode);
  return xmlnode->Getattributes()->Getlength();
}

CXmlUtilNode* ClXMLNodeImpl::Attribute(int i)
{
  ATLASSERT(xmlnode);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  node->xmlnode = xmlnode->Getattributes()->Getitem(i);
  if (node->xmlnode)
  {
    m_arNode.push_back(node);
    return m_arNode.back();
  }
  delete node;
  return NULL;
}

CXmlUtilNode* ClXMLNodeImpl::Attribute(const wchar_t* name)
{
  ATLASSERT(xmlnode);
  ClXMLNodeImpl* node = new ClXMLNodeImpl;
  node->xmlnode = xmlnode->Getattributes()->getNamedItem(_bstr_t(name));
  if (node->xmlnode)
  {
    m_arNode.push_back(node);
    return m_arNode.back();
  }
  delete node;
  return NULL;
}

bool ClXMLNodeImpl::AddAttribute(const wchar_t* name, const wchar_t* value)
{
  ATLASSERT(xmlnode);
  MSXML2::IXMLDOMElementPtr xmlelem(xmlnode);
  if (xmlelem)
  {
    return SUCCEEDED(xmlelem->setAttribute(name, _bstr_t(value)));
  }
  return false;
}

std::wstring ClXMLNodeImpl::Name()
{
  ATLASSERT(xmlnode);
  return (wchar_t*)xmlnode->GetbaseName();
}

std::wstring ClXMLNodeImpl::Value()
{
  ATLASSERT(xmlnode);
  return (wchar_t*)xmlnode->Gettext();
}

void ClXMLNodeImpl::SetValue(const wchar_t* value)
{
  ATLASSERT(xmlnode);
  xmlnode->Puttext(value);
}
