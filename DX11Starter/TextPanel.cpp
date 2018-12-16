#include "TextPanel.h"


TextPanel::TextPanel(char * name, float x, float y) : Entity(name)
{
	text_msg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna ";
	pos = ImVec2(x, y);
}

TextPanel::TextPanel(char * name, float x, float y, char * msg) : Entity(name)
{
	pos = ImVec2(x, y);
	text_msg = msg;
}

TextPanel::~TextPanel(){}

void TextPanel::SetMsg(char * msg)
{
	text_msg = msg;
}


void TextPanel::OnFrame(float dt)
{
	ImGui::Begin(name);
	if (ImGui::Button("Spawn Cube"))
	{
		//callback
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Cube"))
	{
		//callback
	}
	ImGui::Separator();
	ImGui::LabelText("msg", text_msg);
	ImGui::End();
}

void TextPanel::OnStart()  {}

void TextPanel::Draw(ID3D11DeviceContext * ctx, XMFLOAT4X4 view, XMFLOAT4X4 projection){}

