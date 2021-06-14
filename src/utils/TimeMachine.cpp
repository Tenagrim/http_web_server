#include <TimeMachine.hpp>

namespace ft
{



	TimeMachine::TimeMachine()
	{}

	TimeMachine::~TimeMachine()
	{}

	TimeMachine::TimeMachine(const TimeMachine &ref)
	{
		(void)ref;
	}

	TimeMachine &TimeMachine::operator=(const TimeMachine &ref)
	{
		(void)ref;
		return (*this);
	}
	std::string		TimeMachine::getTimestamp(void)
	{
		return ("Thu, 01 Apr 2021 09:17:42 GMT");
	}
	std::string		TimeMachine::getTimestamp(struct timeval &time)
	{
		(void)time;
		return ("Thu, 01 Apr 2021 09:17:42 GMT");
	}
	std::string		TimeMachine::getTimestamp(time_t time)
	{
		(void)time;
		return ("Thu, 01 Apr 2021 09:17:42 GMT");
	}

} // namespace ft
