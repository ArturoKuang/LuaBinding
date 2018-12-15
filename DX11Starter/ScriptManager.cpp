#include "ScriptManager.h"



ScriptManager::ScriptManager(){}

ScriptManager::~ScriptManager()
{
	for (auto it : scripts)
	{
		delete it;
	}
}

void ScriptManager::LoadScript(const std::string & fileName)
{
	LuaScript* script = new LuaScript(fileName);
	scripts.emplace_back(script);
}

void ScriptManager::Initialize()
{
	for (auto it : scripts)
	{
		it->Init();
	}
}

void ScriptManager::Update(float dt)
{
	for (auto it : scripts)
	{
		it->Update(dt);
	}
}
