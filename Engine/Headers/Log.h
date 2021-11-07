#pragma once
#include <stdarg.h>
#include "API.h"

enum class VerbosityLevel
{
	Off,
	Errors,
	Warnings,
	All
};

class Log
{
private:
	VerbosityLevel _verbosityLevel = VerbosityLevel::All;
	static Log* _instance;

	enum class Colors
	{
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Yellow = 6,
		White = 7,
		Default = 15
	};
public:
	static Log* GetInstance();
	/// <summary>
	/// Set the verbosity level of the Log system.
	//	0 = No logging
	//	1 = Error's only
	//	2 = Warnings + Errors
	//  3 = All
	/// </summary>
	/// <param name="level"></param>
	ENGINE_API void SetVerbosityLevel(VerbosityLevel level) { _verbosityLevel = level; }
	ENGINE_API static void LogError(const char* message, const char* system = "Error", ...);
	ENGINE_API static void LogWarning(const char* message, const char* system = "Warning", ...);
	ENGINE_API static void LogMessage(const char* message, const char* system = "Message", ...);
private:
	void PrintMessage(const char* message, const char* system, va_list args);
	void SetConsoleColor(Colors col);
};
