//
// Created by Gerry Shona on 4/6/21.
//

#include <iostream>
#include <Environment.hpp>

int main(int ac, char **av, char **env)
{

	ft::Environment environment;

	environment.setVar("user", "GSHONA");
	environment.setVar("user2", "PCATRINA");
	environment.setVar("user3", "SADOLPH");

	char **c = environment.getEnv();

	while (*c)
	{
		std::cout << *c<< "\n";
		c++;
	}
}
