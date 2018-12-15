#pragma once
#include "Entity.h"
#include "LuaScript.h"

class ScriptEntity : Entity
{
public:
	ScriptEntity(char* n);
	~ScriptEntity();

	void OnStart();
	void OnFrame(float dt);
private:
	LuaScript* script = nullptr;
};

