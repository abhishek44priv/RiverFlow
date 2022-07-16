#pragma once
#include<functional>
class RfTimer
{
	public:
		struct TimerEvent
		{
			unsigned int millsecond;
		};
		RfTimer(int millSeconds, std::function<void(TimerEvent e)> callback);
		void StopForIteration(int iteration);
		bool IsStop();
		void Stop();
		void Resume();
		~RfTimer();
		void Destroy();
	private:
		void MinusStopIteration();
	private:
		class _TimerHelper;
		struct Opaque;
		Opaque* opaque = nullptr;
		friend class _TimerHelper;
};

