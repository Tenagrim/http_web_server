#pragma once
#include <ITimeMachine.hpp>
namespace ft
{

	class FakeTimeMachine : public ITimeMachine
	{
	private:
	public:
		FakeTimeMachine();
		virtual ~FakeTimeMachine();
		FakeTimeMachine(const FakeTimeMachine &ref);
		
		std::string getTimestamp(void);
		std::string getTimestamp(struct timeval &time);
		std::string getTimestamp(time_t time);
		
		FakeTimeMachine &operator=(const FakeTimeMachine &ref);
	};
} // namespace ft