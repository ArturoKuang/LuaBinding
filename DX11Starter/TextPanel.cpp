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
	ImGui::SetCursorPos(pos);
	ImGui::LabelText("msg", text_msg);
	ImGui::Button("Spawn Cubes", ImVec2(2.0f, 1.0f));
	ImGui::Button("Delete Cubes", ImVec2(2.0f, 1.0f));
	ImGui::End();
}

void TextPanel::OnStart()  {}

