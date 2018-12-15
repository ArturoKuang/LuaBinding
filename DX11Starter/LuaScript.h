#pragma once
#define SOL_CHECK_ARGUMENTS 1

#include <string>
#include <iostream>
#include <sol.hpp>
#include "assert.hpp"

class LuaScript
{
public:
	LuaScript(const std::string& fileName);
	~LuaScript();

	//Intializes lua script and calls Init in lua
	void Init();

	//Calls update on lua script
	void Update(float dt);

private:
	std::string fileName;
	sol::state lua;
	sol::function updateTick;
	sol::function startFunction;

	//Define lua states for scripts
	void DefinedLuaTypes();
};

