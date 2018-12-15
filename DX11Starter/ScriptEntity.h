#pragma once
#include "Entity.h"
#include "LuaScript.h"

class ScriptEntity : public Entity
{
public:
	ScriptEntity(char* n);
	~ScriptEntity();

	void OnStart() override;
	void OnFrame(float dt) override;
private:
	LuaScript* script = nullptr;
};

