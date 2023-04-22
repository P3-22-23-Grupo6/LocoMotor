#pragma once
#pragma once
#ifndef LM_UIIMAGE
#define LM_UIIMAGE

#include "Component.h"

namespace OgreWrapper {
	class UIImage;
}

namespace LocoMotor {
	class UIImageLM : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "UIImage";
		};

		UIImageLM(std::string imgName);
		~UIImageLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void ChangeImage(std::string newimg);

	protected:
		OgreWrapper::UIImage* _uimg;
		std::string _imgName;

	};
}
#endif