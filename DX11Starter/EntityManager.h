#pragma once
#include <vector>
#include "Entity.h"
#include "Mesh.h"
#include "Object3D.h"

class EntityManager
{
public:
	static EntityManager* GetInstance();
	void ReleaseInstance();

	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

	void AddEntity(Entity* e);
	size_t GetSize() { return size; }
	std::vector<Entity*> GetEntities(){ return entities; }
	Entity* SpawnRandomInstanceOf(char* filename, ID3D11Device* device);
	void Remove();
	void Init();
	void Update(float dt);
	void Draw(
		ID3D11DeviceContext* context, 
		XMFLOAT4X4 viewMatrix, 
		XMFLOAT4X4 projectionMatrix);
	void setPixelShader(SimplePixelShader* p) { pShader = p; }
	void setVertexShader(SimpleVertexShader* v) { vShader = v; }

private:
	EntityManager();
	~EntityManager();
	size_t size;
	SimplePixelShader* pShader;
	SimpleVertexShader* vShader;
	static EntityManager* Instance;
	std::vector<Entity*> entities;
};

