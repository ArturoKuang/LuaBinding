#include "LuaScript.h"


LuaScript::LuaScript(const std::string & fileName)
{
	this->fileName = fileName;
	entityManager = EntityManager::GetInstance();
}

LuaScript::~LuaScript(){}

void LuaScript::Init()
{
	if (startFunction)
		startFunction();
}

void LuaScript::Load()
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

	//Call intialize function from lua
	sol::optional<sol::function> unsafe_start = lua["Intialize"];
	if (unsafe_start != sol::nullopt)
	{
		startFunction = unsafe_start.value();
	}

	//Set update function from lua
	sol::optional<sol::function> unsafe_update = lua["Update"];
	if (unsafe_update != sol::nullopt)
	{
		updateTick = unsafe_update.value();
	}

	sol::optional<sol::function> unsafe_onClick = lua["OnClick"];
	if (unsafe_onClick != sol::nullopt)
	{
		onClick = unsafe_onClick.value();
	}
}

void LuaScript::OnClick()
{
	if (onClick)
		onClick();
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

void LuaScript::SetEntity(Object3D * e)
{
	entity = e;
}

void LuaScript::EntitySetPos(float x, float y, float z)
{
	entity->Move(x, y, z);
}

void LuaScript::RemoveEntity()
{
	entityManager->Remove();
}

void LuaScript::DefinedLuaTypes()
{
	lua["print"] = [](std::string s) {std::cout << s << std::endl; };
	lua["device"] = device;
	lua["Move"] = [&](float x, float y, float z) { EntitySetPos(x, y, z);  };

	lua["RemoveEntity"] = [this]() { RemoveEntity(); };

	lua.new_usertype<Object3DCreationData>("Entity",
		sol::constructors<
		Object3DCreationData(
			std::string name,
			ID3D11Device* device
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
