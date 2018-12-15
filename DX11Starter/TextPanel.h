#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "ScriptEntity.h"
#include <vector>

class TextPanel : public Entity
{
private:
	ImVec2 pos = ImVec2();
	char* text_msg = nullptr;
	std::vector<ScriptEntity> scripts;
public:
	TextPanel(char* name, float x, float y);
	TextPanel(char* name, float x, float y, char* msg);
	~TextPanel();

	void SetMsg(char* msg);
	void OnFrame(float dt) override;
	void OnStart() override;
};

