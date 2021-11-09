#include <iostream>
#include "Engine.h"
#include "Log.h"
#include <thread>
#include "Levels/GameLevel.h"

int main()
{
    Engine engine;
    EngineConfiguration config;
    config.title = "Plane Shooter!";
    config.width = 600;
    config.height = 800;

	#ifdef _DEBUG
    config.debugEnabled = true;
	#endif


    if (engine.Init(config) >= 0) { 
        engine.SetActiveLevel(new GameLevel());
        engine.Run();
        engine.Shutdown();
    }

    return 0;
}