#include "UITextLM.h"
#include "UIText.h"
#include "GameObject.h"
#include "Scene.h"
#include "LogSystem.h"


using namespace LocoMotor;

const std::string UITextLM::name = "UIText";

LocoMotor::UITextLM::UITextLM() {
	_uTxt = nullptr;
	_uFont = "";
	_uTxtName = "";
	posX = 0.;
	posY = 0.;
	sizeX = 0.;
	sizeY = 0.;
}

LocoMotor::UITextLM::~UITextLM() {
	delete _uTxt;
}

void LocoMotor::UITextLM::InitComponent() {
	//_uTxt = new OgreWrapper::UIText();
	//_uTxt->Init(gameObject->GetScene()->GetSceneName());
}

void LocoMotor::UITextLM::Init(std::vector<std::pair<std::string, std::string>>& params) {

	_uTxt = new OgreWrapper::UIText();
	_uTxt->Init(gameObject->GetScene()->GetSceneName());


	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "posx" || params[i].first == "positionx") {
			SetPosition(std::stod(params[i].second), posY);
		}
		else if (params[i].first == "posy" || params[i].first == "positiony") {
			SetPosition(posX, std::stod(params[i].second));
		}
		else if (params[i].first == "pos" || params[i].first == "position") {
			unsigned char currAxis = 0;
			std::string num = "";
			double resultX = 0.;
			double resultY = 0.;
			for (const auto& c : params[i].second) {
				if (c != ' ') {
					num += c;
				}
				else {
					float value = 0.f;
					try {
						value = std::stod(num);
					}
					catch (const char*) {
						value = 0.f;
					}
					if (currAxis == 0) {
						resultX = value;
					}
					else if (currAxis == 1) {
						resultY = value;
					}
					currAxis++;
					if (currAxis == 2) break;
					num = "";
				}
			}
			SetPosition(resultX, resultY);
		}
		else if (params[i].first == "sizex") {
			SetSize(std::stod(params[i].second), sizeY);
		}
		else if (params[i].first == "sizey") {
			SetSize(sizeX, std::stod(params[i].second));
		}
		else if (params[i].first == "topcolor") {
			LMVector3 color = LMVector3::StringToVector(params[i].second);
			SetTopColor(color.GetX(), color.GetY(), color.GetZ());
		}
		else if (params[i].first == "bottomcolor") {
			LMVector3 color = LMVector3::StringToVector(params[i].second);
			SetBottomColor(color.GetX(), color.GetY(), color.GetZ());
		}
		else if (params[i].first == "txt" || params[i].first == "text") {
			ChangeText(params[i].second);
		}
		else if (params[i].first == "fnt" || params[i].first == "font") {
			SetFont(params[i].second);
		}
		else if (params[i].first == "align") {

			if (params[i].second == "center")
				AlignCenter();
			else if (params[i].second == "left")
				AlignLeft();
			else if (params[i].second == "right")
				AlignRight();
		}
	}
}

void LocoMotor::UITextLM::SetPosition(double x, double y) {
	posX = x;
	posY = y;
	_uTxt->SetPosition(x, y);
}

void LocoMotor::UITextLM::SetSize(double x, double y) {
	sizeX = x;
	sizeY = y;
	SetTextHeight(y);
	_uTxt->SetDimensions(x, y);
}

void LocoMotor::UITextLM::ChangeText(std::string newtxt) {
	_uTxt->ChangeText(newtxt);
}

void LocoMotor::UITextLM::SetTextHeight(double height) {
	_uTxt->SetHeight(height);
}

void LocoMotor::UITextLM::SetFont(std::string nfont) {
	if (!_uTxt->SetFont(nfont)) {
		LocoMotor::LogSystem::GetInstance()->Save(0, "Couldn't set to font '" + nfont + "'");
	}
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

void LocoMotor::UITextLM::SetTopColor(double r, double g, double b) {
	_uTxt->SetTopColor(r, g, b);
}

void LocoMotor::UITextLM::SetBottomColor(double r, double g, double b) {
	_uTxt->SetBottomColor(r,g,b);
}

double LocoMotor::UITextLM::GetSizeX() {
	return sizeX;
}

double LocoMotor::UITextLM::GetSizeY() {
	return sizeY;
}
