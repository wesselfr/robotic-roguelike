#include <iostream>
#include "Engine.h"
#include "Log.h"
#include <thread>
#include "Levels\TestLevel.h"

int main()
{
    Engine engine;
    EngineConfiguration config;
    config.title = "Robotic Roguelike";

    if (engine.Init(config) >= 0) { 
        engine.SetInputMode(InputMode::Sticky);
        engine.SetActiveLevel(new TestLevel());
        engine.Run();
        engine.Shutdown();
    }

    return 0;
}