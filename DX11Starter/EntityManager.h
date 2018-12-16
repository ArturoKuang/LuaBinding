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
	void SpawnRandomInstanceOf(char* filename, ID3D11Device* device, SimplePixelShader* pShader, SimpleVertexShader* vShader);
	void Remove();
	void Init();
	void Update(float dt);
	void Draw(
		ID3D11DeviceContext* context, 
		XMFLOAT4X4 viewMatrix, 
		XMFLOAT4X4 projectionMatrix);

private:
	EntityManager();
	~EntityManager();
	size_t size;
	static EntityManager* Instance;
	std::vector<Entity*> entities;
};

