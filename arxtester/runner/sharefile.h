#ifndef SHAREFILE_H
#define SHAREFILE_H

class CShareFileImpl;

const wchar_t strCaseName[] = L"Global-casesTobeTested";

class CShareFile
{
public:
  CShareFile(const CString& name, bool bOpen = false);
  ~CShareFile();

  void reset();
  void writeLine(const CString& str);
  CString readLine();

private:
  CShareFileImpl* m_impl;
};


#endif//SHAREFILE_H