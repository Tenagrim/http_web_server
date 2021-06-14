#pragma once
#include <ITimeMachine.hpp>
namespace ft
{

	class TimeMachine : public ITimeMachine
	{
	private:
	public:
		TimeMachine();
		virtual ~TimeMachine();
		TimeMachine(const TimeMachine &ref);

		std::string getTimestamp(void);
		std::string getTimestamp(struct timeval &time);
		std::string getTimestamp(time_t time);

		TimeMachine &operator=(const TimeMachine &ref);
	};
} // namespace ft