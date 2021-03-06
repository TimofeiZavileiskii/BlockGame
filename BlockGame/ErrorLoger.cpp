#include "pch.h"
#include "ErrorLoger.h"

ErrorLoger* ErrorLoger::errorLoger = nullptr;

ErrorLoger* ErrorLoger::instance()
{
	if (errorLoger == nullptr)
	{
		errorLoger = new ErrorLoger();
	}

	return errorLoger;
}

void ErrorLoger::PushError(const std::string& title, const std::string& message)
{
	std::cout << "---" << title << " reports:\n";
	std::cout << message << "\n";
}

void ErrorLoger::PushError(const std::string& title, int message)
{
	std::cout << "---" << title << " reports:\n";
	std::cout << message << "\n";
}