
// arxrunner.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "arxrunner.h"
#include "arxlistDlg.h"
#include "arxrunnerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArxRunnerApp

BEGIN_MESSAGE_MAP(CArxRunnerApp, CWinApp)
END_MESSAGE_MAP()


// CArxRunnerApp 构造

CArxRunnerApp::CArxRunnerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

CString getAutoCadInstallDir()
{
  CRegKey rk;
  if (ERROR_SUCCESS == rk.Open(HKEY_LOCAL_MACHINE,
    L"SOFTWARE\\Autodesk\\AutoCAD\\R23.1\\ACAD-3001:804", KEY_READ))
  {
    wchar_t	szDir[2048] = { 0 };
    ULONG len = 2048;
    if (ERROR_SUCCESS == rk.QueryStringValue(L"AcadLocation", szDir, &len))
    {
      return szDir;
    }
  }
  return L"";
}

typedef std::unordered_map<HMODULE, IArxModule*> ModuleArray;

static void listModule(const wchar_t* path, ModuleArray& modules)
{
  HMODULE hArx = LoadLibrary(path);
  if (hArx)
  {
    typedef IArxModule* (WINAPI *ARXMODULE)();
    ARXMODULE fun = (ARXMODULE)GetProcAddress(hArx, "arx_module");
    if (fun)
    {
      IArxModule* am = fun();
      if (am)
      {
        modules.insert(std::make_pair(hArx, am));
        hArx = nullptr;
      }
    }
    FreeLibrary(hArx);
  }
}

static void listModules(ModuleArray& modules)
{
  SetCurrentDirectory(getAutoCadInstallDir());

  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName(nullptr, szFilePath, MAX_PATH);
  if (wcslen(szFilePath) == 0)
  {
    return;
  }

#if _MSVC_LANG >= 201703L
  std::filesystem::path currentFilePath(szFilePath);
  std::filesystem::path currentPath = currentFilePath.parent_path();
  std::filesystem::directory_iterator its(currentPath);
  for (auto& it : its)
  {
    if (it.path().extension() == L".dll")
    {
      listModule(it.path().c_str(), modules);
    }
  }
#else
  wchar_t* szTail = wcsrchr(szFilePath, L'\\');
  wchar_t szDir[MAX_PATH] = { 0 };
  wcsncpy_s(szDir, MAX_PATH, szFilePath, szTail - szFilePath + 1);

  WIN32_FIND_DATA fd = { 0 };
  HANDLE hFind = FindFirstFile(AcString(szDir) + L"*.dll", &fd);
  if (hFind == INVALID_HANDLE_VALUE)
  {
    return;
  }

  do
  {
    listModule(AcString(szDir) + fd.cFileName, modules);
  } while (FindNextFile(hFind, &fd) != 0);

  FindClose(hFind);
#endif // ARX
}

// 唯一的 CArxRunnerApp 对象

CArxRunnerApp theApp;


// CArxRunnerApp 初始化

BOOL CArxRunnerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("ArxRunner"));

  ModuleArray modules;
  listModules(modules);

	CArxListDlg dlg;
  for (auto& it : modules)
  {
    dlg.m_modules.emplace_back(it.second);
  }
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

