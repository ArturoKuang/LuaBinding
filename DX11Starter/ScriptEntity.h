#pragma once
#include "Entity.h"
#include "LuaScript.h"

class ScriptEntity : public Entity
{
public:
	ScriptEntity(char* n, ID3D11Device* device);
	~ScriptEntity();

	void OnStart() override;
	void OnFrame(float dt) override;
private:
	LuaScript* script = nullptr;
};

