#include "pch.h"

#include "sharefile.h"

typedef int(*GETLARGEPAGEMINIMUM)(void);

static DWORD buf_size()
{
  static DWORD size = 0;
  if (size == 0)
  {
    HINSTANCE hDll = LoadLibrary(L"kernel32.dll");
    GETLARGEPAGEMINIMUM pGetLargePageMinimum = (GETLARGEPAGEMINIMUM)GetProcAddress(hDll,
      "GetLargePageMinimum");
    size = (*pGetLargePageMinimum)();
    FreeLibrary(hDll);
  }

  return size;
}

class CShareFileImpl
{
  HANDLE m_hFileMap;
  wchar_t* m_lpFile;
  wchar_t* m_lpBuf;
public:
  CShareFileImpl(const wchar_t* szShareName, bool bOpen)
    : m_lpFile(nullptr)
  {
    if (bOpen)
    {
      m_hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, szShareName);
    }
    else
    {
      m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
        PAGE_READWRITE, 0, buf_size(), szShareName);
    }
    if (m_hFileMap == nullptr)
    {
      return;
    }

    m_lpBuf = m_lpFile = (wchar_t*)MapViewOfFile(m_hFileMap, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
    if (!bOpen && m_lpBuf)
    {
      m_lpBuf[0] = 0;
    }
  }

  ~CShareFileImpl()
  {
    if (m_lpFile)
    {
      UnmapViewOfFile(m_lpFile);
      m_lpFile = nullptr;
    }

    if (m_hFileMap)
    {
      CloseHandle(m_hFileMap);
      m_hFileMap = nullptr;
    }
  }

  void reset()
  {
    m_lpBuf = m_lpFile;
  }

  void write(const CString& str)
  {
    if (m_lpFile)
    {
      int len = str.GetLength() * sizeof(wchar_t);
      memcpy_s(m_lpBuf, len + 1, (LPCTSTR)str, len);
      m_lpBuf += str.GetLength();
      m_lpBuf[0] = 0;
    }
  }

  CString readLine()
  {
    CString str;
    if (m_lpFile)
    {
      wchar_t* pos = wcschr(m_lpBuf, L'\n');
      if (pos == nullptr)
      {
        str = m_lpBuf;
        m_lpBuf += wcslen(m_lpBuf);
      }
      else
      {
        size_t len = pos - m_lpBuf;
        wchar_t* buf = str.GetBuffer((int)len + 1);
        wcsncpy_s(buf, len + 1, m_lpBuf, len);
        str.ReleaseBuffer();
        m_lpBuf += len + 1;
      }
    }
    return str;
  }
};

CShareFile::CShareFile(const CString& name, bool bOpen)
  : m_impl(new CShareFileImpl(name, bOpen))
{
}

CShareFile::~CShareFile()
{
  delete m_impl;
}

void CShareFile::reset()
{
  m_impl->reset();
}

void CShareFile::writeLine(const CString& str)
{
  m_impl->write(str);
}

CString CShareFile::readLine()
{
  return m_impl->readLine();
}