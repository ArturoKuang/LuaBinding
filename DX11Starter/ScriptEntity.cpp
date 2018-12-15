#include "ScriptEntity.h"

ScriptEntity::ScriptEntity(char * n) : Entity(n)
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
