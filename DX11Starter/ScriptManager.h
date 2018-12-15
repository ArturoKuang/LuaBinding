#pragma once
#include <vector>
#include <string>
#include "LuaScript.h"

class ScriptManager
{
public:
	ScriptManager();
	~ScriptManager();

	void LoadScript(const std::string& fileName);
	void Initialize();
	void Update(float dt);

private:
	std::vector<LuaScript*> scripts;
};

