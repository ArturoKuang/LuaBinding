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
	LuaScript(const std::string& fileName);
	~LuaScript();

	//callback function when intializing lua script and calls Init in lua
	void Init();
	void Load();
	void OnClick();

	//Calls update on lua script
	void Update(float dt);
	void SetDevice(ID3D11Device* device);
	void SetEntity(Object3D* e);

private:
	sol::state lua;
	std::string fileName;
	sol::function updateTick;
	sol::function startFunction;
	sol::function onClick;
	sol::optional<sol::function> unsafe_update;
	
	ID3D11Device* device = nullptr;
	EntityManager* entityManager = nullptr;
	Object3D* entity = nullptr;

	void EntitySetPos(float x, float y, float z);
	void RemoveEntity();

	//Define lua states for scripts
	void DefinedLuaTypes();

	//Data Definitions 
	struct MeshCreationData
	{
		MeshCreationData(char* fileName, ID3D11Device* device, float r, float g, float b, float a)
		{
			XMFLOAT4 color = XMFLOAT4(r, g, b, a);
			mesh = new Mesh(fileName, device, color);
		}

		Mesh* GetMesh() { return mesh; };

		private:
			Mesh* mesh = nullptr;
			ID3D11Device* device = nullptr;
	};

	
	struct Object3DCreationData
	{
		Object3DCreationData(
			std::string name,
			ID3D11Device * device)
		{
			entityManager = EntityManager::GetInstance();
			entity = dynamic_cast<Object3D*>(entityManager->SpawnRandomInstanceOf((char*)name.c_str(), device));
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
			Object3D* entity = nullptr;
			ID3D11Device* device = nullptr;
			EntityManager* entityManager = nullptr;
	};
};

