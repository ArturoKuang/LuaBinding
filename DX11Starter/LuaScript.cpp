#include "LuaScript.h"


LuaScript::LuaScript(const std::string & fileName, ID3D11Device* device)
{
	entityManager = EntityManager::GetInstance();
	this->device = device;
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
	if(updateTick)
		updateTick(dt);
}

void LuaScript::SetDevice(ID3D11Device * device)
{
	this->device = device;
}

void LuaScript::DefinedLuaTypes()
{
	lua["print"] = [](std::string s) {std::cout << s << std::endl; };
	lua["device"] = device;
	lua.set_function("RemoveEntity", &EntityManager::Remove);

	lua.new_usertype<Object3DCreationData>("Entity",
		sol::constructors<
		Object3DCreationData(
			std::string name
		),
		Object3DCreationData(
			std::string name,
			std::string fileName,
			ID3D11Device* device,
			float r, float g, float b, float a
		)>(),

		"SetPos", &Object3DCreationData::SetPosition
		);

	lua.new_usertype<DirectX::XMFLOAT3>("vec3",
		"x", &DirectX::XMFLOAT3::x,
		"y", &DirectX::XMFLOAT3::y,
		"z", &DirectX::XMFLOAT3::z
		);
}
