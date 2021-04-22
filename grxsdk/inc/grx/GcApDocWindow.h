#pragma once

#include "gsoft.h"
#include "gcdocman.h"

#include "GcApWindow.h"

class GcApDocWindowImp;

class GcApDocWindowReactor
{
public:
    GCAD_PORT virtual void documentWindowLoaded();
};

class GcApDocWindow : public GcApWindow
{
public:
    GCAD_PORT GcRxObject* document();

    GCAD_PORT const GCHAR* title() const;

    GCAD_PORT void setTitle(const GCHAR* title);

    GCAD_PORT bool canClose() const;

    GCAD_PORT void setCanClose(bool bCanClose);

public:
    GCAD_PORT void close();

    GCAD_PORT void activate();

    GCAD_PORT void enable(bool bEnable);

    GCAD_PORT void addReactor(GcApDocWindowReactor* reactor);

    GCAD_PORT void removeReactor(GcApDocWindowReactor* reactor);

protected:
    GCAD_PORT virtual void setDocument(GcRxObject* document);

protected:
    GCAD_PORT virtual void onCreate(HWND hWnd);

    GCAD_PORT virtual void onLoad();

    GCAD_PORT virtual void onActivate();

    GCAD_PORT virtual void onDestroy();

public:
    GCAD_PORT GcApDocWindow();

    GCAD_PORT virtual ~GcApDocWindow();

public:
    GCAD_PORT virtual HWND windowHandle() GSOFT_OVERRIDE;

private:
    GcApDocWindow(const GcApDocWindow&);
    GcApDocWindow& operator=(const GcApDocWindow&);

    friend class GcApDocWindowImp;
};

class GcApDwgDocWindow : public GcApDocWindow
{
public:
    GCAD_PORT GcApDocument* document();

private:
    GcApDwgDocWindow();

    friend class GcApDocWindowImp;
};

class GcApDocWindowManagerImp;
class GcApDocWindowIteratorImp;

class GcApDocWindowIterator
{
public:
    GCAD_PORT bool done() const;

    GCAD_PORT void step();

    GCAD_PORT GcApDocWindow* current();

private:
    GcApDocWindowIterator();

public:
    GCAD_PORT ~GcApDocWindowIterator();

private:
    GcApDocWindowIteratorImp* m_pImp;

    friend class GcApDocWindowManagerImp;
};

class GcApDocWindowManagerReactor
{
public:
    GCAD_PORT virtual void documentWindowCreated(GcApDocWindow* docWindow);

    GCAD_PORT virtual void documentWindowActivated(GcApDocWindow* docWindow);

    GCAD_PORT virtual void documentWindowDestroyed(GcApDocWindow* docWindow);

    GCAD_PORT virtual void documentWindowMoved(GcApDocWindow* docWindow, int newIndex, int oldIndex);

    GCAD_PORT virtual void documentWindowReplaced(GcApDocWindow* newDocWindow, GcApDocWindow* oldDocWindow);
};

class GcApDocWindowManagerImp;

class GcApDocWindowManager
{
public:
    GCAD_PORT GcApDocWindow* activeDocumentWindow();

    GCAD_PORT int documentWindowCount() const;

    GCAD_PORT bool addDocumentWindow(GcApDocWindow* docWindow);

    GCAD_PORT bool moveDocumentWindow(GcApDocWindow* docWindow, int newIndex);

    GCAD_PORT GcApDocWindowIterator* newIterator() const;

    GCAD_PORT void addReactor(GcApDocWindowManagerReactor* pReactor);

    GCAD_PORT void removeReactor(GcApDocWindowManagerReactor* pReactor);

private:
    GcApDocWindowManager();
    ~GcApDocWindowManager();

    GcApDocWindowManagerImp* m_pImp;

    friend class GcApDocWindowManagerImp;
};

GCAD_PORT GcApDocWindowManager* gcDocWindowManagerPtr();
#define gcDocWindowManager gcDocWindowManagerPtr()