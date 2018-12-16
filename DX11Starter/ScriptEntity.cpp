#include "ScriptEntity.h"

ScriptEntity::ScriptEntity(char * n, ID3D11Device* device) : Entity(n)
{
	script = new LuaScript(n);
}

void ScriptEntity::OnStart()
{
	script->Init();
}

void ScriptEntity::OnFrame(float dt)
{
	script->Update(dt);
}

ScriptEntity::~ScriptEntity()
{
	delete script;
}
