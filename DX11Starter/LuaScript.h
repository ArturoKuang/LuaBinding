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
	sol::state lua;
	std::string fileName;
	sol::function updateTick;
	sol::function startFunction;
	sol::optional<sol::function> unsafe_update;

	//Define lua states for scripts
	void DefinedLuaTypes();
};

