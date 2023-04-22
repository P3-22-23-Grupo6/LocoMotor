#include "UIImageLM.h"

#include "UIImage.h"


using namespace LocoMotor;

const std::string UIImageLM::name = "UIImage";

LocoMotor::UIImageLM::UIImageLM(std::string imgName) {
	_uimg = nullptr;
	_imgName = imgName;
}

LocoMotor::UIImageLM::~UIImageLM() {
	delete _uimg;
}

void LocoMotor::UIImageLM::InitComponent() {
	_uimg = new OgreWrapper::UIImage(_imgName);
}

void LocoMotor::UIImageLM::Init(std::vector<std::pair<std::string, std::string>>& params) {
	_uimg->Init();
}

void LocoMotor::UIImageLM::ChangeImage(std::string newimg) {
	_uimg->ChangeImage(newimg);

}



