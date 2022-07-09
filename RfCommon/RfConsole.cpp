#include"pch.h"
#include "RfConsole.h"
void RfConsole::Clear()
{
	printf("\x1B[2J\x1B[H");
}