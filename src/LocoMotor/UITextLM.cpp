#include "UITextLM.h"

#include "UIText.h"


using namespace LocoMotor;

const std::string UITextLM::name = "UIText";

LocoMotor::UITextLM::UITextLM(std::string txtName, std::string font) {
	_uTxt = nullptr;
	_uFont = font;
	_uTxtName = txtName;

}

LocoMotor::UITextLM::~UITextLM() {
	delete _uTxt;
}

void LocoMotor::UITextLM::InitComponent() {
	_uTxt = new OgreWrapper::UIText(_uTxtName, _uFont);
}

void LocoMotor::UITextLM::Init(std::vector<std::pair<std::string, std::string>>& params) {
	_uTxt->Init();
}

void LocoMotor::UITextLM::ChangeText(std::string newtxt) {
	_uTxt->ChangeText(newtxt);
}

void LocoMotor::UITextLM::SetTextHeight(double height) {
	_uTxt->SetHeight(height);
}

void LocoMotor::UITextLM::SetFont(std::string nfont) {
	_uTxt->SetFont(nfont);
}

void LocoMotor::UITextLM::AlignCenter() {
	_uTxt->AlignCenter();
}

void LocoMotor::UITextLM::AlignLeft() {
	_uTxt->AlignLeft();
}

void LocoMotor::UITextLM::AlignRight() {
	_uTxt->AlignRight();
}

void LocoMotor::UITextLM::SetTopColor(int r, int g, int b) {
	_uTxt->SetTopColor(r, g, b);
}

void LocoMotor::UITextLM::SetBottomColor(int r, int g, int b) {
	_uTxt->SetBottomColor(r,g,b);
}
