#include "LuaScript.h"


LuaScript::LuaScript(const std::string & fileName)
{
	std::cout << "\n=== running lua code ===" << std::endl;
	lua.open_libraries(sol::lib::base);
	
	DefinedLuaTypes();

	auto code_result = lua.script_file(fileName.c_str(), 
		[](lua_State*, 
		sol::protected_function_result pfr) 
	{
		return pfr;
	});

	//script did not compile
	c_assert(code_result.valid());
}

LuaScript::~LuaScript(){}

void LuaScript::Init()
{
	//Call intialize function from lua
	sol::optional<sol::function> unsafe_start = lua["Intialize"];
	if (unsafe_start != sol::nullopt)
	{
		startFunction = unsafe_start.value();
		startFunction();
	}

	//Set update function from lua
	sol::optional<sol::function> unsafe_update = lua["Update"];
	if (unsafe_update != sol::nullopt)
	{
		updateTick = unsafe_update.value();
	}
}

void LuaScript::Update(float dt)
{
	updateTick(dt);
}

void LuaScript::DefinedLuaTypes()
{
	lua["print"] = [](std::string s) {std::cout << s << std::endl; };

}
