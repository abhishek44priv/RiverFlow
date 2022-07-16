#include"pch.h"
#include "RfTimer.h"

struct RfTimer::Opaque
{
	int m_stopIteration = 100000000;
	bool m_isStop = false;
	int _millSeconds = 0;
	std::function<void(TimerEvent e)> _callback;
	unsigned int m_id = 0;
};
struct _TimerInfo
{
	RfTimer* win32Timer = nullptr;
};
static std::vector<_TimerInfo> m_timerInfos;
class RfTimer::_TimerHelper
{
public:
	static void TimerProc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)     // current system time 
	{
		for (size_t i = 0; i < m_timerInfos.size(); i++)
		{
			_TimerInfo info = m_timerInfos[i];
			if (info.win32Timer->opaque->m_id == idTimer && !info.win32Timer->opaque->m_isStop)
			{
				if (info.win32Timer->opaque->m_stopIteration > 0)
				{
					RfTimer::TimerEvent e;
					e.millsecond = info.win32Timer->opaque->_millSeconds;
					m_timerInfos[i].win32Timer->opaque->_callback(e);
				}
				info.win32Timer->MinusStopIteration();
				break;
			}
		}
	}
};


RfTimer::RfTimer(int millSeconds, std::function<void(TimerEvent e)> callback)
{
	opaque = new Opaque();
	opaque->_millSeconds = millSeconds;
	opaque->_callback = callback;
	opaque->m_id = (unsigned int)SetTimer(
		NULL,
		NULL,
		millSeconds,
		(TIMERPROC)_TimerHelper::TimerProc); // timer callback 

	_TimerInfo info{ this };
	m_timerInfos.push_back(info);
}

void RfTimer::StopForIteration(int iteration)
{
	opaque->m_stopIteration = iteration;
}

void RfTimer::Stop()
{
	opaque->m_isStop = true;
}
bool RfTimer::IsStop()
{
	return opaque->m_isStop;
}

void RfTimer::Resume()
{
	opaque->m_isStop = false;
}

RfTimer::~RfTimer()
{
	Destroy();
	delete opaque;
}

void RfTimer::Destroy()
{
	::KillTimer(NULL, opaque->m_id);
	for (size_t i = 0; i < m_timerInfos.size(); i++)
	{
		_TimerInfo info = m_timerInfos[i];
		if (info.win32Timer->opaque->m_id == opaque->m_id)
		{
			m_timerInfos.erase(m_timerInfos.begin() + i);
			break;
		}
	}
}

void RfTimer::MinusStopIteration()
{
	opaque->m_stopIteration--;
	if (opaque->m_stopIteration < 0)
		opaque->m_stopIteration = 0;
}