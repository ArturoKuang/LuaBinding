#include "EntityManager.h"


EntityManager* EntityManager::Instance = nullptr;

EntityManager::EntityManager()
{
	entities = std::vector<Entity*>();
}

EntityManager::~EntityManager()
{
	for (auto e : entities) 
	{
		delete e;
	}
	entities.clear();
}

EntityManager * EntityManager::GetInstance()
{
	if (Instance == nullptr)
		Instance = new EntityManager();

	return Instance;
}

void EntityManager::ReleaseInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void EntityManager::AddEntity(Entity * e)
{
	entities.emplace_back(e);
}

void EntityManager::Remove()
{
	Entity* e = entities.back();
	entities.pop_back();
	delete e;
}

void EntityManager::Init()
{
	for (auto e : entities)
		e->OnStart();
}

void EntityManager::Update(float dt)
{
	for (auto e : entities)
		e->OnFrame(dt);
}

void EntityManager::Draw(ID3D11DeviceContext * context, 
	XMFLOAT4X4 viewMatrix, 
	XMFLOAT4X4 projectionMatrix)
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto e : entities)
		e->Draw(context, viewMatrix, projectionMatrix);

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}
