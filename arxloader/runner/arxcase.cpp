#include "pch.h"

void executeCase(const CString& arg)
{
  int pos = arg.Find(L':');
  if (pos == -1)
  {
    return;
  }
  CString strEvent = arg.Left(pos++);

  int pos1 = arg.Find(L':', pos);
  if (pos1 == -1)
  {
    return;
  }
  int bGcad = _wtoi(arg.Mid(pos, pos1 - pos));
  
  int pos2 = arg.Find(L':', ++pos1);
  if (pos2 == -1)
  {
    return;
  }
  CString strModule = arg.Mid(pos1, pos2 - pos1);
  CString strCase = arg.Mid(pos2 + 1);

  HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, strEvent);
  if (hEvent == nullptr)
  {
    return;
  }

  wchar_t strCmdLine[MAX_PATH * 2] = { 0 };
  if (bGcad)
  {
  }
  else
  {
    swprintf_s(strCmdLine, MAX_PATH * 2,
      L"\"%sacad.exe\" /ld \"%sarxloader.arx\"",
      (LPCTSTR)getAutoCadInstallDir(),
      (LPCTSTR)appDir());
  }
  HANDLE hInst = startProc(strCmdLine);
  if (hInst)
  {
    

    HANDLE handles[] = { hEvent, hInst };
    DWORD objId = WaitForMultipleObjects(2, handles, FALSE, INFINITE);
    CloseHandle(hEvent);
    if (WAIT_OBJECT_0 + 0 == objId)
    {
      DWORD ret = 0;
      GetExitCodeProcess(hInst, &ret);
      ExitProcess(ret);
    }
  }
  else
  {
    CloseHandle(hEvent);
  }
}
