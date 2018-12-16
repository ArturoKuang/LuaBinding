#include "TextPanel.h"


void TextPanel::LoadScripts()
{
	AddCube = new LuaScript("../Scripts/AddCube.lua");
	AddCube->SetDevice(device);
	AddCube->Load();
	RemoveCube = new LuaScript("../Scripts/DeleteCube.lua");
	RemoveCube->SetDevice(device);
	RemoveCube->Load();
}

TextPanel::TextPanel(char * name, float x, float y, ID3D11Device* device) : Entity(name)
{
	this->device = device;
	text_msg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna ";
	pos = ImVec2(x, y);
	LoadScripts();
}

TextPanel::TextPanel(char * name, float x, float y, char * msg, ID3D11Device* device) : Entity(name)
{
	this->device = device;
	pos = ImVec2(x, y);
	text_msg = msg;
	LoadScripts();
}

TextPanel::~TextPanel()
{
	delete AddCube;
	delete RemoveCube;
}

void TextPanel::SetMsg(char * msg)
{
	text_msg = msg;
}


void TextPanel::OnFrame(float dt){}

void TextPanel::OnStart()  {}

void TextPanel::Draw(ID3D11DeviceContext * ctx, XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	ImGui::Begin(name);
	if (ImGui::Button("Spawn Cube"))
	{
		AddCube->OnClick();
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Cube"))
	{
		RemoveCube->OnClick();
	}
	ImGui::Separator();
	ImGui::LabelText("msg", text_msg);
	ImGui::End();
}

