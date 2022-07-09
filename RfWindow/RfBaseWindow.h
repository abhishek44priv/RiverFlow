#pragma once
#include"RfCursor.h"
#include"RfEvent.h"
#include"RfKey.h"
class RfBaseWindow
{
	struct PrivateInfo;
public:
	struct InitParams
	{
		const wchar_t* name = L"RfBaseWindow";
		RfBaseWindow* parent = nullptr;
		bool isDC = false;
	};
	RfBaseWindow(InitParams params = {});
	~RfBaseWindow();
	void SetName(const wchar_t* name);
	void Hide();
	void Show();
	void Enable();
	void Disable();
	void Maximized();
	void Minimized();
	bool IsEnable();
	bool IsVisible();
	bool IsCreated();
	int GetWidth();
	int GetHeight();
	void Destroy();
	void Repaint();
	void Repaint(int l, int t, int r, int b);
	void* GetHandle();
	void Animate(bool val);
	//dc
	void* GetDC();
	//key
	void CaptureKey();
	void ReleaseKeyCapture();
	//mouse
	bool IsMouseDown();
	void CaptureMouse();
	void ReleaseMouseCapture();
	//cursor
	void SetCursor(RfCursor cursor);
	void ResetCursor();
	//others
	static void EventLoop();

protected:
	virtual void  OnClose();

	virtual void OnSize(RfSizeEvent& e);
	virtual void  OnPaint(int l, int t, int r, int b);
	virtual void  OnPaint();
	virtual void  OnDestroy();
	virtual void  OnEnable();
	virtual void  OnDisable();
	virtual void  OnVisible();
	virtual void  OnHide();
	virtual void  OnActivate();
	virtual void  OnDeactivate();
	//mouse event 
	virtual void  OnMouseMove(RfMouseEvent& e);
	virtual void  OnMouseEnter();
	virtual void  OnMouseExit();
	virtual void  OnMouseUp(RfMouseEvent& e);
	virtual void  OnMouseDown(RfMouseEvent& e);
	virtual void  OnMouseWheel(RfMouseEvent& e);
	virtual void  OnMouseCapture();
	virtual void  OnMouseReleaseCapture();
	//key
	virtual void  OnKeyDown(RfKeyEvent& e);
	virtual void  OnKeyUp(RfKeyEvent& e);
	virtual void  OnKeyCapture();
	virtual void  OnKeyReleaseCapture();
	//
	virtual bool  OnWinProcHandle(void* msg,
		 void* wparam, void* lparam);

protected:
	
	PrivateInfo* privateInfo_ = nullptr;
	friend class _NativeWindowHelper;
};

