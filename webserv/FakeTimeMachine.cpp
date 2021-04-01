#include <FakeTimeMachine.hpp>

namespace ft
{
	


	FakeTimeMachine::FakeTimeMachine()
	{}

	FakeTimeMachine::~FakeTimeMachine()
	{}

	FakeTimeMachine::FakeTimeMachine(const FakeTimeMachine &ref)
	{
		(void)ref;
	}

	FakeTimeMachine &FakeTimeMachine::operator=(const FakeTimeMachine &ref)
	{
		(void)ref;
		return (*this);
	}
	std::string		FakeTimeMachine::getTimestamp(void)
	{
		return ("Thu, 01 Apr 2021 09:17:42 GMT");
	}
	std::string		FakeTimeMachine::getTimestamp(struct timeval &time)
	{
		(void)time;
		return ("Thu, 01 Apr 2021 09:17:42 GMT");
	}
	std::string		FakeTimeMachine::getTimestamp(time_t time)
	{
		(void)time;
		return ("Thu, 01 Apr 2021 09:17:42 GMT");
	}

} // namespace ft
