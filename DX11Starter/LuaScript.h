#pragma once
#define SOL_CHECK_ARGUMENTS 1

#include <string>
#include <iostream>
#include <sol.hpp>
#include "assert.hpp"
#include "Mesh.h"
#include "EntityManager.h"
#include "Object3D.h"

class LuaScript
{
public:
	LuaScript(const std::string& fileName, ID3D11Device* device);
	~LuaScript();

	//Intializes lua script and calls Init in lua
	void Init();

	//Calls update on lua script
	void Update(float dt);
	void SetDevice(ID3D11Device* device);

private:
	sol::state lua;
	std::string fileName;
	sol::function updateTick;
	sol::function startFunction;
	sol::optional<sol::function> unsafe_update;
	//Directx
	ID3D11Device* device = nullptr;
	EntityManager* entityManager = nullptr;

	//Define lua states for scripts
	void DefinedLuaTypes();

	//Data Definitions
	
	struct Object3DCreationData
	{
		Object3DCreationData(
			std::string name)
		{
			entityManager = EntityManager::GetInstance();
			entity = new Object3D((char*)name.c_str(), mesh);
			entityManager->AddEntity(entity);
		}

		Object3DCreationData(
			std::string name,
			std::string fileName,
			ID3D11Device* device,
			float r, float g, float b, float a
		)
		{
			this->device = device;
			XMFLOAT4 color = XMFLOAT4(r, g, b, a);
			entityManager = EntityManager::GetInstance();
			MeshCreationData* mesh = new MeshCreationData((char*)fileName.c_str(), device, r, g, b, a);
			entity = new Object3D((char*)name.c_str(), mesh->GetMesh());
			entityManager->AddEntity(entity);
		}

		void SetPosition(const float x, const float y, const float z)
		{
			assert(entity != nullptr);

			entity->Move(x, y, z);
		}

		private:
			Object3D* entity;
			ID3D11Device* device;
			EntityManager* entityManager;
	};
};

