#pragma once

class Engine;
class Level {
friend class Engine;
public:
	virtual void OnBegin() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnShutdown() = 0;
protected:
	Engine* engine = nullptr;
};
