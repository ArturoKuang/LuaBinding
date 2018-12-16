#include "EntityManager.h"


EntityManager* EntityManager::Instance = nullptr;

EntityManager::EntityManager()
{
	entities = std::vector<Entity*>();
	size = 0;
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
	Object3D* obj = dynamic_cast<Object3D*>(e);
	if (obj)
	{
		obj->setPixelShader(pShader);
		obj->setVertexShader(vShader);
	}
	entities.emplace_back(e);
	size++;
}

Entity* EntityManager::SpawnRandomInstanceOf(char * filename, ID3D11Device * device)
{
	//float between 0.0 and 1.0
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	float x = ((static_cast <float> (rand()) / float(RAND_MAX)) * 6) - 3;
	float y = ((static_cast <float> (rand()) / float(RAND_MAX)) * 6) - 3;
	float z = ((static_cast <float> (rand()) / float(RAND_MAX)) * 6) - 3;

	float w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float h = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float d = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	XMFLOAT4 color(r, g, b, 1.0f);
	Mesh* mesh = new Mesh(filename, device, color);
	//char* name = strcat("Random ", filename);
	Object3D* obj = new Object3D(filename, mesh);
	obj->setPosition(XMFLOAT3(x, y, z));
	obj->setScale(XMFLOAT3(w, h, d));
	AddEntity(obj);
	return obj;
}

void EntityManager::Remove()
{
	Entity* e = entities.back();
	entities.pop_back();
	size--;
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
