#pragma once
#include<RfGUIWindow.h>
#include<RfTimer.h>
#include<RfLayout.h>
#include<RfWidget.h>
#include<RfBorderLayout.h>
#include<format>
#include<iostream>
#include<RfLinearLayout.h>
#include<RfTextView.h>
#include<RfScrollView.h>
#include<RfConsole.h>
#define repeat_for(t) for(int i=0;i<t;i++)
#define _W(n) std::to_wstring(n)
#define print std::cout<<std::format