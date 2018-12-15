#pragma once
class Entity
{
protected:
	Entity* parent = nullptr;
	char* name = nullptr;
public:
	Entity(char* n) { name = n; }
	virtual void OnStart() = 0;
	virtual void OnFrame(float dt) = 0;
	char* GetName() { return name; }
	void SetName(char* n) { name = n; }
	Entity* GetParent() { return parent; }
	void SetParent(Entity* p) { parent = p; }
};