#pragma once
#include "RfGLWindow.h"
#include"imgui/imgui.h"
class RfImguiWindow :
    public RfGLWindow
{
    float lastTime = 0.0f;
public:
    RfImguiWindow();
protected:
    virtual void OnPaint() override;
    virtual void OnImgui();
    virtual void OnGLDraw();
    virtual bool  OnWinProcHandle(void* msg,
        void* wparam, void* lparam) override;
protected:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float frameTime = 0.0f;
};

