#include "UIImageLM.h"
#include "UIImage.h"
#include "InputManager.h"
#include "OgreManager.h"
#include "GameObject.h"
#include "Scene.h"

using namespace LocoMotor;

const std::string UIImageLM::name = "UIImage";

LocoMotor::UIImageLM::UIImageLM() {
	_uimg = nullptr;
	_posX = 0.;
	_posY = 0.;
	_sizeX = 0.5;
	_sizeY = 0.5;
	_ogMng = OgreWrapper::OgreManager::GetInstance();
}

LocoMotor::UIImageLM::~UIImageLM() {
	delete _uimg;
}

void LocoMotor::UIImageLM::InitComponent() {
	_uimg = new OgreWrapper::UIImage();
	_uimg->Init(gameObject->GetScene()->GetSceneName());
}

void LocoMotor::UIImageLM::Init(std::vector<std::pair<std::string, std::string>>& params) {
	_uimg = new OgreWrapper::UIImage();
	_uimg->Init(gameObject->GetScene()->GetSceneName());
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "posx" || params[i].first == "positionx") {
			SetPosition(std::stod(params[i].second), _posY);
		}
		else if (params[i].first == "posy" || params[i].first == "positiony") {
			SetPosition(_posX, std::stod(params[i].second));
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
			SetSize(std::stod(params[i].second), _sizeY);
		}
		else if (params[i].first == "sizey") {
			SetSize(_sizeX, std::stod(params[i].second));
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
		else if (params[i].first == "interactive") {
			SetInteractive(true);
		}
		else if (params[i].first == "top") {
			SetTop(std::stod(params[i].second));
		}
	}
}

void LocoMotor::UIImageLM::SetPosition(double x, double y) {
	_posX = x;
	_posY = y;
	_uimg->SetPosition(x, y);
}

void LocoMotor::UIImageLM::SetSize(double x, double y) {
	_sizeX = x;
	_sizeY = y;
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
		_winHeight = _ogMng->GetWindowHeight();
		_winWidth = _ogMng->GetWindowWidth();
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

void LocoMotor::UIImageLM::SetTop(int topIndex) {
	_uimg->SetTop(topIndex);
}


bool LocoMotor::UIImageLM::MouseOnImage() {
	std::pair<int, int> pos = LocoMotor::InputManager::GetInstance()->GetMousePos();

	return (pos.first/_winWidth > _posX && pos.first/_winWidth < _posX + _sizeX) &&
		(pos.second/_winHeight > _posY && pos.second/_winHeight < _posY + _sizeY);
}
