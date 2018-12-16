#pragma once
#include <vector>
#include"Entity.h"
class EntityManager
{
public:
	static EntityManager* GetInstance();
	void ReleaseInstance();

	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

	void AddEntity(Entity* e);
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

	static EntityManager* Instance;
	std::vector<Entity*> entities;
};

