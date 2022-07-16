#pragma once
#include<RfBaseWindow.h>
#include<RfTimer.h>
class RfGLWindow :
    public RfBaseWindow
{
    void InitGLEW();
    void DummyWindow();
    bool SetPixelFormat();
    void CreateGLContext();
    void InitGL();
private:
public:
    RfGLWindow(InitParams p = {});
    ~RfGLWindow();
    //opengl
    void SwapBuffer();
    void MakeCurrent();
    void VSync(bool value);
    void Animate(float fps);
    //opengl specific

protected:
    void OnPaint()override;
    void OnMouseMove(RfMouseEvent& e);
    void OnSize(RfSizeEvent& e)override;
   
protected:
    void* m_glCtx = nullptr;
    RfTimer* timer = nullptr;

};