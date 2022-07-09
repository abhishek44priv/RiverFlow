#pragma once
#include<RfBaseWindow.h>
#include"RfD2HWNDRender.h"
class RfD2Window:public RfBaseWindow
{
public:
    RfD2Window(InitParams p = {});
protected:
    void OnSize(RfSizeEvent& e)override;
    void OnPaint()override;
    RfD2HWNDRender* GetHWNDRender();
protected:
    RfD2HWNDRender* d2HWNDRender = nullptr;
};

