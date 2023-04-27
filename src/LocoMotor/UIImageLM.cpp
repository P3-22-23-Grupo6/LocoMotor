#include "UIImageLM.h"
#include "UIImage.h"
#include "InputManager.h"
#include "OgreManager.h"


using namespace LocoMotor;

const std::string UIImageLM::name = "UIImage";

LocoMotor::UIImageLM::UIImageLM() {
	_uimg = nullptr;
	posX = 0.;
	posY = 0.;
	sizeX = 0.;
	sizeY = 0.;
	_ogMng = OgreWrapper::OgreManager::GetInstance();
}

LocoMotor::UIImageLM::~UIImageLM() {
	delete _uimg;
}

void LocoMotor::UIImageLM::InitComponent() {
	_uimg = new OgreWrapper::UIImage();
	_uimg->Init();
}

void LocoMotor::UIImageLM::Init(std::vector<std::pair<std::string, std::string>>& params) {
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
		else if (params[i].first == "size") {
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
			SetSize(resultX, resultY);
		}
		else if (params[i].first == "img" || params[i].first == "image") {
			ChangeImage(params[i].second);
		}
	}
}

void LocoMotor::UIImageLM::SetPosition(double x, double y) {
	posX = x;
	posY = y;
	_uimg->SetPosition(x, y);
}

void LocoMotor::UIImageLM::SetSize(double x, double y) {
	sizeX = x;
	sizeY = y;
	_uimg->SetDimensions(x, y);
}

void LocoMotor::UIImageLM::SetInteractive(bool interactive) {
	_uimg->SetInteractive(interactive);
}

bool LocoMotor::UIImageLM::GetInteractive() {
	return _uimg->GetInteractive();
}

void LocoMotor::UIImageLM::Update(float dt) {

	if (GetInteractive()) {
		winHeight = _ogMng->GetWindowHeight();
		winWidth = _ogMng->GetWindowWidth();
		if (MouseOnImage()) {

			if (LocoMotor::InputManager::GetInstance()->GetMouseButtonDown(1)) {
				ChangeImage(_pressedImgName);
				_onClick();
				
			}
			else {
				ChangeImage(_onMouseImgName);
			}
		}
		else ChangeImage(_imgName);
	}

}

void LocoMotor::UIImageLM::CallOnClick(const std::function<void()>& func) {

	_onClick = func;
}

void LocoMotor::UIImageLM::ChangeImage(std::string newimg) {
	if(newimg!="")
	_uimg->ChangeImage(newimg);

}

void LocoMotor::UIImageLM::SetImage(std::string newimg) {
	_imgName = newimg;
}

void LocoMotor::UIImageLM::SetOnMouseImage(std::string newimg) {
	_onMouseImgName = newimg;
}

void LocoMotor::UIImageLM::SetPressedImage(std::string newimg) {
	_pressedImgName = newimg;
}


bool LocoMotor::UIImageLM::MouseOnImage() {
	auto pos = LocoMotor::InputManager::GetInstance()->GetMousePos();

	return (pos.first/winWidth > posX && pos.first/winWidth < posX + sizeX) &&
		(pos.second/winHeight > posY && pos.second/winHeight < posY + sizeY);
}
