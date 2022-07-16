#include "pch.h"
#include "RfImguiWindow.h"
#include"imgui/imgui_impl_win32.h"
#include"imgui/imgui_impl_opengl3.h"
#include"RfOpenGL.h"
#include<RfPreciseTime.h>
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
RfImguiWindow::RfImguiWindow()
{
   
    //imgui
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    
    //Init Win32
    ImGui_ImplWin32_Init(GetHandle());
    ImGui_ImplOpenGL3_Init("#version 130");
    lastTime= RfPreciseTime::Second();

    


}

void RfImguiWindow::OnPaint()
{
    auto currTime = RfPreciseTime::Second();
    frameTime = currTime - lastTime;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    OnImgui();
    // Rendering
    ImGui::Render();
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    OnGLDraw();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SwapBuffer();
    lastTime = currTime;
}

void RfImguiWindow::OnImgui()
{
    ImGui::Begin("hello");
    ImGui::End();
}

void RfImguiWindow::OnGLDraw()
{
}

bool RfImguiWindow::OnWinProcHandle(void* msg, void* wparam, void* lparam)
{
    return ImGui_ImplWin32_WndProcHandler((HWND)GetHandle(), (UINT)msg, (WPARAM)wparam, (LPARAM)lparam);
}
