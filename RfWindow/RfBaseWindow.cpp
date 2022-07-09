#include"pch.h"
#include"RfBaseWindow.h"

#define PRIV_INFO privateInfo_
#define  M_HWND privateInfo_->winHWND_
#define WIN_HWND win->privateInfo_->winHWND_
#define WIN_PRIV win->privateInfo_
char ConvertKeyChar(WPARAM wparam)
{
	char c = (char)wparam;
	switch (wparam)
	{
	case 0x08:
		c = RfKey::BACKSPACE;
		break;
	case 0x0A:
		// Process a linefeed. 
		break;
	case 0x1B:
		c = RfKey::ESC;
		break;
	case 0x09:
		c = RfKey::TAB;
		break;
	case 0x0D:
		c = RfKey::ENTER;
		break;
	}
	return c;
}
char ConvertKeyDown(WPARAM wparam)
{
	char c = 0;
	switch (wparam)
	{
	case VK_LEFT:
		c = RfKey::LEFT;
		break;
	case VK_RIGHT:
		c = RfKey::RIGHT;
		break;
	case VK_UP:
		c = RfKey::UP;
		break;
	case VK_DOWN:
		c = RfKey::DOWN;
		break;
	case VK_HOME:
		c = RfKey::HOME;
		break;
	case VK_END:
		c = RfKey::END;
		break;
	case VK_INSERT:
		c = RfKey::INSERT;
		break;
	case VK_DELETE:
		c = RfKey::DEL;
		break;
	case VK_F2:
		c = RfKey::F2;
		break;
	}
	return c;
}

auto ToCursor(RfCursor cur)
{
	switch (cur)
	{
	case RfCursor::ARROW:
		return IDC_ARROW;
	case RfCursor::CROSS:
		return IDC_CROSS;
	case RfCursor::HAND:
		return IDC_HAND;
	case RfCursor::HELP:
		return IDC_HELP;
	case RfCursor::WAIT:
		return IDC_WAIT;
	case RfCursor::SIZE_NS:
		return IDC_SIZENS;
	case RfCursor::SIZE_WE:
		return IDC_SIZEWE;
	case RfCursor::SIZE_NSWE:
		return IDC_SIZENESW;
	case RfCursor::NO:
		return IDC_NO;
	default:
		return IDC_ARROW;
	}
}

class MouseTracker
{
	bool m_bMouseTracking;

public:
	MouseTracker() : m_bMouseTracking(false)
	{
	}

	void OnMouseMove(HWND hwnd)
	{
		if (!m_bMouseTracking)
		{
			// Enable mouse tracking.
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&tme);
			m_bMouseTracking = true;
		}
	}
	void Reset(HWND hwnd)
	{
		m_bMouseTracking = false;
	}
};
struct RfBaseWindow::PrivateInfo
{
	HWND winHWND_ = NULL;
	MouseTracker tracker_;
	bool isMouseDown_ = false;
	bool isCreated_ = false;
	bool isMouseExit_ = false;
	HDC hdc_ = nullptr;
};

class _NativeWindowHelper
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		RfBaseWindow* win = NULL;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			win = (RfBaseWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)win);
			WIN_HWND = hwnd;
		}
		win = (RfBaseWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (win)
		{
			if (win->OnWinProcHandle((void*)uMsg, (void*)wParam, (void*)lParam))return true;
			switch (uMsg)
			{
			case WM_CLOSE:
			{
				win->OnClose();
				break;
			}
			case WM_DESTROY:
			{
				win->OnDestroy();
				break;
			}
				//key focus
			case WM_SETFOCUS:
			{
				win->OnKeyCapture();
				return 0;
			}
			case WM_KILLFOCUS:
			{
				win->OnKeyReleaseCapture();
				return 0;
			}
			/*--------------------RfKey---------------*/
			case WM_CHAR:
			{
				RfKeyEvent e{};
				e.key = ConvertKeyChar(wParam);
				win->OnKeyDown(e);
				break;
			}
			case WM_KEYDOWN:
			{
				RfKeyEvent e{};
				e.key = ConvertKeyDown(wParam);
				if (!e.key)break;
				win->OnKeyDown(e);
				break;
			}
			case WM_KEYUP:
			{
				RfKeyEvent e{};
				e.key = (char)wParam;
				win->OnKeyUp(e);
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				WIN_PRIV->isMouseDown_ = true;
				RfMouseEvent e;
				e.extraButton = (int)wParam;
				if (uMsg == WM_LBUTTONDOWN)
					e.button = e.B_LEFT;
				else if (uMsg == WM_RBUTTONDOWN)
					e.button = e.B_RIGHT;
				e.x = GET_X_LPARAM(lParam);
				e.y = GET_Y_LPARAM(lParam);
				win->OnMouseDown(e);
				break;
			}
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			{
				WIN_PRIV->isMouseDown_ = false;
				RfMouseEvent e;
				e.extraButton = (int)wParam;
				if (uMsg == WM_LBUTTONUP)
					e.button = e.
					B_LEFT;
				else if (uMsg == WM_RBUTTONUP)
					e.button = e.B_RIGHT;
				e.x = GET_X_LPARAM(lParam);
				e.y = GET_Y_LPARAM(lParam);
				win->OnMouseUp(e);
				break;
			}
			case WM_MOUSELEAVE:
			{
				WIN_PRIV->isMouseExit_ = true;
				win->OnMouseExit();
				WIN_PRIV->tracker_.Reset(hwnd);
				break;
			}
			//case WM_MOUSEHOVER:
			//    win->OnMouseEnter();
			//   // m_mouseTrack.Reset(M_HWND);
			//    return 0;
			case WM_MOUSEMOVE:
			{
				if (WIN_PRIV->isMouseExit_)
				{
					win->OnMouseEnter();
					WIN_PRIV->isMouseExit_ = false;
					WIN_PRIV->tracker_.Reset(hwnd);
					return 0;
				}
				WIN_PRIV->tracker_.OnMouseMove(hwnd);
				RfMouseEvent e;
				e.extraButton = (int)wParam;
				e.button = e.UNKNOWN;
				e.x = GET_X_LPARAM(lParam);
				e.y = GET_Y_LPARAM(lParam);
				win->OnMouseMove(e);
				break;
			}
			case WM_CREATE:
			{
				/*std::cout << "***********\n";
				WIN_PRIV->isCreated_ = true;
				WIN_PRIV->hdc_ = ::GetDC(WIN_HWND);
				win->OnCreate();*/
				return 0;
			}
			case WM_MOUSEWHEEL:
			{
				RfMouseEvent e;
				if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
					e.delta = RfMouseEvent::SCROLL_UP;
				if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
					e.delta = RfMouseEvent::SCROLL_DOWN;
				e.x = GET_X_LPARAM(lParam);
				e.y = GET_Y_LPARAM(lParam);
				win->OnMouseWheel(e);
				return 0;
			}
			case WM_SIZE:
			{
				RfSizeEvent event;
				event.flag = (int)wParam;
				event.width = LOWORD(lParam);
				event.height = HIWORD(lParam);
				win->OnSize(event);
				return 0;
			}
			case WM_PAINT:
			{
				
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				//FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));
				auto r = ps.rcPaint;
				
				EndPaint(hwnd, &ps);
				win->OnPaint(r.left, r.top, r.right, r.bottom);
				win->OnPaint();

				//::ValidateRect(hwnd, NULL);
				//e.dirtyRect.Print();
				return 0;
			}
			case WM_ERASEBKGND:
				return TRUE;
			case WM_ACTIVATE:
			{
				if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
				{
					win->OnActivate();
				}
				else if (wParam == WA_INACTIVE)
				{
					win->OnDeactivate();
				}
				return 0;
			}
			case WM_SHOWWINDOW:
			{
				if (wParam)
					win->OnVisible();
				else
					win->OnHide();
				return 0;
			}
			case WM_ENABLE:
			{
				if (wParam)
					win->OnEnable();
				else
					win->OnDisable();
				return 0;
			}
			
			}
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
};
RfBaseWindow::RfBaseWindow(InitParams params)
{
	privateInfo_ = new PrivateInfo;
	const wchar_t classname[] = L"Win32Window";
	{

		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = _NativeWindowHelper::WindowProc;
		wc.hInstance = ::GetModuleHandle(0);

		wc.lpszClassName = classname;
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS | (params.isDC? CS_OWNDC:0);
		::RegisterClass(&wc);

		HWND parentHWND = NULL;
		int _style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		const wchar_t* name_ =params.name;
		HWND hwnd=0;
		if (params.parent)
		{
			parentHWND = (HWND)params.parent->GetHandle();
			_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			name_ = L"Win32 child";
			//create
			 hwnd = ::CreateWindowEx(0, classname, name_,
				_style, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
				parentHWND,
				NULL, ::GetModuleHandle(0), this);
			
		}
		else
		{
			//create
			 hwnd = ::CreateWindowEx(NULL, classname, name_,
				_style | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				parentHWND,
				NULL, ::GetModuleHandle(0), this);
		}

	
		if (params.isDC)
		{
			privateInfo_->isCreated_ = true;
			privateInfo_->hdc_ = ::GetDC(hwnd);
		}
		//error
		if (hwnd == NULL)
		{
			std::cout << "windows doesn't created\n";
			exit(5555);
		}
	}
}




RfBaseWindow::~RfBaseWindow()
{
	this->Destroy();
}
void RfBaseWindow::SetName(const wchar_t* name)
{
	::SetWindowText(M_HWND, name);
}

void RfBaseWindow::Hide()
{
	ShowWindow(M_HWND, SW_HIDE);
}

void RfBaseWindow::Show()
{
	ShowWindow(M_HWND, SW_SHOW);
}

int RfBaseWindow::GetWidth()
{
	RECT rect;
	GetClientRect(M_HWND, &rect);
	return rect.right;
}

int RfBaseWindow::GetHeight()
{
	RECT rect;
	GetClientRect(M_HWND, &rect);
	return rect.bottom;
}

bool RfBaseWindow::IsMouseDown()
{
	return privateInfo_->isMouseDown_;
}
void RfBaseWindow::CaptureMouse()
{
	if (M_HWND)
		::SetCapture(M_HWND);
}

void RfBaseWindow::ReleaseMouseCapture()
{
	::ReleaseCapture();
}
void RfBaseWindow::SetCursor(RfCursor cursor)
{
	//::SetCursor(LoadCursor(0, ToCursor(cursor)));
	SetClassLongPtr((HWND)GetHandle(),    // window handle 
		GCLP_HCURSOR,        // change cursor 
		(LONG_PTR)LoadCursor(0, ToCursor(cursor)));  // new cursor 
}
void RfBaseWindow::ResetCursor()
{
	SetCursor(RfCursor::ARROW);
}
void RfBaseWindow::Repaint()
{
	::InvalidateRect(M_HWND, NULL, 0);
}

void RfBaseWindow::Repaint(int l, int t, int r, int b)
{
	RECT cr;
	cr.left = l<0?0:l;
	cr.top = t < 0 ? 0 : t;
	cr.right = r < 0 ? 0 : r;
	cr.bottom = b < 0 ? 0 : b;
	if((r-l)>0 && (b-t)>0)
	::InvalidateRect(M_HWND, &cr, 0);
}

void RfBaseWindow::Destroy()
{
	if (M_HWND)
	{
		::DestroyWindow(M_HWND);
		ReleaseDC(M_HWND, privateInfo_->hdc_);
		delete privateInfo_;
	}
}

void* RfBaseWindow::GetDC()
{
	return privateInfo_->hdc_;
}

void RfBaseWindow::CaptureKey()
{
	::SetFocus(M_HWND);
}

void RfBaseWindow::ReleaseKeyCapture()
{
}

void RfBaseWindow::Enable()
{
	EnableWindow(M_HWND, TRUE);
}

void RfBaseWindow::Disable()
{
	EnableWindow(M_HWND, FALSE);
}

void RfBaseWindow::Maximized()
{
	ShowWindow(M_HWND, SW_MAXIMIZE);
}

void RfBaseWindow::Minimized()
{
	ShowWindow(M_HWND, SW_MINIMIZE);
}

bool RfBaseWindow::IsEnable()
{
	return IsWindowEnabled(M_HWND);
}

bool RfBaseWindow::IsVisible()
{
	return IsWindowVisible(M_HWND);
}

bool RfBaseWindow::IsCreated()
{
	return privateInfo_->isCreated_;
}


void RfBaseWindow::EventLoop()
{
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
	

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
void* RfBaseWindow::GetHandle()
{
	return privateInfo_->winHWND_;
}

void RfBaseWindow::Animate(bool val)
{
}

void RfBaseWindow::OnSize(RfSizeEvent& e)
{

}

void RfBaseWindow::OnPaint(int l, int t, int r, int b)
{
}

void RfBaseWindow::OnPaint()
{
}


void RfBaseWindow::OnClose()
{
	if (MessageBox((HWND)GetHandle(), L"Really quit?", L"Confirm", MB_OKCANCEL) == IDOK)
	{
		DestroyWindow((HWND)GetHandle());
	}
}

void RfBaseWindow::OnDestroy()
{
	PostQuitMessage(0);
}

void RfBaseWindow::OnEnable()
{
}

void RfBaseWindow::OnDisable()
{
}

void RfBaseWindow::OnVisible()
{
}

void RfBaseWindow::OnHide()
{
}

void RfBaseWindow::OnActivate()
{
}

void RfBaseWindow::OnDeactivate()
{
}

void RfBaseWindow::OnMouseMove(RfMouseEvent& e)
{
}

void RfBaseWindow::OnMouseEnter()
{
}

void RfBaseWindow::OnMouseExit()
{
}

void RfBaseWindow::OnMouseUp(RfMouseEvent& e)
{
}

void RfBaseWindow::OnMouseDown(RfMouseEvent& e)
{
}

void RfBaseWindow::OnMouseWheel(RfMouseEvent& e)
{
}

void RfBaseWindow::OnMouseCapture()
{
}

void RfBaseWindow::OnMouseReleaseCapture()
{
}

void RfBaseWindow::OnKeyDown(RfKeyEvent& e)
{
}

void RfBaseWindow::OnKeyUp(RfKeyEvent& e)
{
}

void RfBaseWindow::OnKeyCapture()
{
}

void RfBaseWindow::OnKeyReleaseCapture()
{
}

bool RfBaseWindow::OnWinProcHandle(void* msg, void* wparam, void* lparam)
{
	return false;
}

