#include "Log.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

#ifdef PLATFORM_X64
// Include only neccesarry stuff, ignore the rest.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <Windows.h>
#endif // PLATFORM_X64


Log* Log::_instance = nullptr;

Log* Log::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Log();
	}
	return _instance;
}

void Log::PrintMessage(const char* message, const char* system, va_list args)
{
	static char buffer[1024];
	vsnprintf(buffer, 1024, message, args);
	printf("[%s] %s\n", system, buffer);

	//Print to Debug console Visual Studio
#ifdef PLATFORM_X64
	OutputDebugStringA(buffer);
	OutputDebugStringA("\n");
#endif
}

void Log::LogError(const char* message, const char* system, ...)
{
	va_list args;
	va_start(args, system);
	Log* instance = GetInstance();
	if (instance->_verbosityLevel >= VerbosityLevel::Errors)
	{
		instance->SetConsoleColor(Colors::Red);
		instance->PrintMessage(message, system, args);
	}
	va_end(args);
}
void Log::LogWarning(const char* message, const char* system, ...)
{
	va_list args;
	va_start(args, system);
	Log* instance = GetInstance();
	if (instance->_verbosityLevel >= VerbosityLevel::Warnings)
	{
		instance->SetConsoleColor(Colors::Yellow);
		instance->PrintMessage(message, system, args);
	}
	va_end(args);
}
void Log::LogMessage(const char* message, const char* system, ...)
{
	va_list args;
	va_start(args, system);
	Log* instance = GetInstance();
	if (instance->_verbosityLevel >= VerbosityLevel::All)
	{
		instance->SetConsoleColor(Colors::Default);
		instance->PrintMessage(message, system, args);
	}
	va_end(args);
}

void Log::SetConsoleColor(Colors color)
{
#ifdef PLATFORM_X64
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (int)color);
#endif // PLATFORM_X64
}