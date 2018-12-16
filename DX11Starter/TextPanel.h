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

	LuaScript* AddCube = nullptr;
	LuaScript* RemoveCube = nullptr;
	ID3D11Device* device = nullptr;

	void LoadScripts();

public:
	TextPanel(char* name, float x, float y, ID3D11Device* device);
	TextPanel(char* name, float x, float y, char* msg, ID3D11Device* device);
	~TextPanel();

	void SetMsg(char* msg);
	void OnFrame(float dt) override;
	void OnStart() override;
	void Draw(ID3D11DeviceContext* ctx, XMFLOAT4X4 view, XMFLOAT4X4 projection) override;
};

