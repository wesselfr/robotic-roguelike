#pragma once
#include "API.h"

class Command
{
public:
	virtual ENGINE_API ~Command() {}
	virtual void ENGINE_API Execute(Actor& actor) {}
};


