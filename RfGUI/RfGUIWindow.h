#pragma once

#include<RfBaseWindow.h>
#include<RfD2HWNDRender.h>
#include"pch.h"
class RfView;
class RfLayout;
class RfGUIWindow:public RfBaseWindow
{
    virtual void  OnPaint(int l, int t, int r, int b) override;
public:
    struct RfPaintParams
    {
        RfRect dirtyRect;
        RfD2Render* render = nullptr;
    };
public:
    RfGUIWindow(InitParams p = {});
    RfD2HWNDRender* GetHWNDRender();
    void SetMainLayout(RfLayout* layout);
    void Repaint(RfRect dirty);
    void Measure();
     void Layout();
protected:
    void AddLayout(RfLayout* layout);
    void RemoveLayout(RfLayout* layout);
protected:
    virtual void OnMeasure();
    virtual  void OnLayout();
    //
    void OnSize(RfSizeEvent& e)override;
    virtual void OnPaint(RfPaintParams e) ;
    //mouse event 
    virtual void  OnMouseMove(RfMouseEvent& e) override ;
    virtual void  OnMouseEnter() override ;
    virtual void  OnMouseExit() override ;
    virtual void  OnMouseUp(RfMouseEvent& e) override ;
    virtual void  OnMouseDown(RfMouseEvent& e) override ;
    virtual void  OnMouseWheel(RfMouseEvent& e) override ;
    //key
    virtual void  OnKeyDown(RfKeyEvent& e) override ;
    virtual void  OnKeyUp(RfKeyEvent& e) override ;
protected:
    RfD2HWNDRender* hwndRender = nullptr;
    std::vector<RfLayout*> childs;
    RfView* mouseEnterView = nullptr,
        * mouseCaptureView = nullptr,
        * keyCaptureView = nullptr;
    friend class RfView;
    friend class RfLayout;
};

