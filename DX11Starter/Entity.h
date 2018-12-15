#pragma once
class Entity
{
protected:
	char* name;
public:
	Entity(char* n) { name = n; }
	virtual void OnStart() = 0;
	virtual void OnFrame() = 0;
	char* GetName() { return name; }
};