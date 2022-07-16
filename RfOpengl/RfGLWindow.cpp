#include"pch.h"
#include "RfGLWindow.h"
#include"RfOpenGL.h"


#define HDC_HANDLE (HDC)GetDC()

static bool isglInit = false;
using namespace std;
void RfGLWindow::InitGLEW()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "glew init error\n";
    else
    {
        isglInit = true;
        std::cout << "glew init pass\n";
    }
}

void RfGLWindow::DummyWindow()
{
    if (isglInit)return;
    WNDCLASS window_class{ 0 };
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = DefWindowProc;
    window_class.hInstance = GetModuleHandle(0);
    window_class.lpszClassName = L"Dummy window";

    if (!RegisterClass(&window_class)) {
        std::cout << ("Failed to register dummy OpenGL window.");
    }

    HWND dummy_window = CreateWindowEx(
        0,
        window_class.lpszClassName,
        L"Dummy OpenGL Window",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        window_class.hInstance,
        0);

    if (!dummy_window) {
        std::cout << ("Failed to create dummy OpenGL window.");
    }

    HDC dummy_dc = ::GetDC(dummy_window);

    PIXELFORMATDESCRIPTOR pfd{ 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
    if (!pixel_format) {
        std::cout << ("Failed to find a suitable pixel format.");
    }

    if (!::SetPixelFormat(dummy_dc, pixel_format, &pfd)) {
        std::cout << ("Failed to set the pixel format.");
    }

    HGLRC dummy_context = wglCreateContext(dummy_dc);
    if (!dummy_context) {
        std::cout << ("Failed to create a dummy OpenGL rendering context.");
    }

    if (!wglMakeCurrent(dummy_dc, dummy_context)) {
        std::cout << ("Failed to activate dummy OpenGL rendering context.");
    }

    InitGLEW();

    wglMakeCurrent(dummy_dc, 0);
    wglDeleteContext(dummy_context);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
}

bool RfGLWindow::SetPixelFormat()
{
    // Now we can choose a pixel format the modern way, using wglChoosePixelFormatARB.
    int pixel_format_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };

    int pixel_format = 0;
    UINT num_formats = 0;

    wglChoosePixelFormatARB(HDC_HANDLE, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
    if (!num_formats) {
        std::cout << ("Failed to set the OpenGL 3.3 pixel format.");
        return false;
    }

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(HDC_HANDLE, pixel_format, sizeof(pfd), &pfd);
    if (!::SetPixelFormat(HDC_HANDLE, pixel_format, &pfd)) {
        std::cout << ("Failed to set the OpenGL 3.3 pixel format.");
        return false;
    }

    return true;
}

void RfGLWindow::CreateGLContext()
{
    // Specify that we want to create an OpenGL 3.3 core profile context
    int gl33_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    m_glCtx = wglCreateContextAttribsARB(HDC_HANDLE, 0, gl33_attribs);
    if (!m_glCtx) {
        std::cout << ("Failed to create OpenGL 3.3 context.");
    }

    if (!wglMakeCurrent(HDC_HANDLE, (HGLRC)m_glCtx)) {
        std::cout << ("Failed to activate OpenGL  rendering context.");
    }
}

void RfGLWindow::InitGL()
{
    if (SetPixelFormat())
    {
        CreateGLContext();
        MakeCurrent();
    }
    else
    {
        std::cout << "setup fail\n";
    }
}

RfGLWindow::RfGLWindow(InitParams p)
    :RfBaseWindow({ p.name,p.parent,true })
{
    srand((UINT)time(0));
    DummyWindow();
    InitGL();
    
   
}

RfGLWindow::~RfGLWindow()
{
    if (timer)delete timer;
}

void RfGLWindow::SwapBuffer()
{
    SwapBuffers(HDC_HANDLE);
}

void RfGLWindow::MakeCurrent()
{
    if (!wglMakeCurrent(HDC_HANDLE, (HGLRC)m_glCtx)) {
        std::cout << ("Failed to activate OpenGL rendering context.");
    }
}

void RfGLWindow::VSync(bool value)
{
    if (value)
        wglSwapIntervalEXT(1);
    else
        wglSwapIntervalEXT(0);
}

void RfGLWindow::Animate(float fps)
{
    if (timer)
    {
        delete timer;
    }
    timer = new RfTimer((int)(1000.0f / fps), [&](auto e) {Repaint(); });
}



void RfGLWindow::OnPaint()
{
   
}

void RfGLWindow::OnMouseMove(RfMouseEvent& e)
{

}

void RfGLWindow::OnSize(RfSizeEvent& e)
{
    glViewport(0, 0, e.width, e.height);
}


