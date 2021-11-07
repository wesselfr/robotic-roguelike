#include <iostream>
#include "Engine.h"
#include "Log.h"
#include <thread>
#include "Levels\TestLevel.h"

int main()
{
    Engine engine;
    EngineConfiguration config;
    config.title = "PlaneShooter";

    if (engine.Init(config) >= 0) { 
        engine.SetActiveLevel(new TestLevel());
        engine.Run();
        engine.Shutdown();
    }

    return 0;
}