#include "pch.h"
#include "RfSwitch.h"

RfSwitch::RfSwitch(Context ctx)
	:RfWidget(ctx)
{
	measuredWidth = 50.0f;
	measuredHeight = MW() * 40.0f / 100.0f;
	bgColor = RfColor::AliceBlue;
}

void RfSwitch::OnMeasure(MeasureEvent e)
{

}

void RfSwitch::OnDraw(DrawEvent e)
{
	
	auto bgColor = RfColor::BlueViolet;
	auto radBig = MW() * 20.0f/100.0f;
	auto hh = MH() * 0.5f;
	e.render->FillRRect({ 0,hh- radBig,MW(),radBig*2.0f }, radBig, radBig, bgColor);
	//circle
	auto crad = radBig * 70.0f / 100.0f;
	e.render->FillEllipse({ isOn?MW()-radBig: radBig,hh}, crad, crad, RfColor::Black);

	//e.render->DrawRect({ 0,0,MW(),MH() }, RfColor::Black);
}

void RfSwitch::OnMouseEnter()
{
}

void RfSwitch::OnMouseExit()
{
}

void RfSwitch::OnMouseUp(MouseEvent e)
{
}

void RfSwitch::OnMouseDown(MouseEvent e)
{
	print("down\n");
	isOn = !isOn;
	Repaint();
}

void RfSwitch::OnMouseMove(MouseEvent e)
{
}

void RfSwitch::OnMouseScroll(MouseEvent e)
{
}
