#pragma once
#include <iostream>

//Singleton class which allows to push errors and print them to console

class ErrorLoger
{
private:
	static ErrorLoger* errorLoger;

	ErrorLoger() {}

public:
	static ErrorLoger* instance();

	void PushError(const std::string& title, const std::string& message);
};

