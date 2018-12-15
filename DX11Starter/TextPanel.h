#pragma once
#include "Entity.h"
class TextPanel : Entity
{
private:

public:
	TextPanel(char* n);
	~TextPanel();

	void OnFrame(float dt);
	void OnStart();
};

