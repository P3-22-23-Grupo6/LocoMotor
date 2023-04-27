#pragma once
#pragma once
#ifndef LM_UIIMAGE
#define LM_UIIMAGE

#include "Component.h"
#include <functional>

namespace OgreWrapper {
	class UIImage;
	class OgreManager;
}

namespace LocoMotor {

	class InputManager;

	class UIImageLM : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "UIImage";
		};

		UIImageLM();
		~UIImageLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void SetPosition(double x, double y);
		void SetSize(double x, double y);

		void SetInteractive(bool interactive);
		bool GetInteractive();
		void Update(float dt)override;
		void CallOnClick(const std::function<void()> &func);
		bool MouseOnImage();
		void ChangeImage(std::string newimg);

		void SetImage(std::string newimg);
		void SetOnMouseImage(std::string newimg);
		void SetPressedImage(std::string newimg);

	protected:
		OgreWrapper::UIImage* _uimg;
		OgreWrapper::OgreManager* _ogMng;
		std::string _imgName;
		std::string _onMouseImgName;
		std::string _pressedImgName;

		std::function<void()> _onClick;
		double posX, posY;


		double winHeight, winWidth;
		double sizeX, sizeY;

	};
}
#endif