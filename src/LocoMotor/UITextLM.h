#pragma once
#ifndef LM_UITEXT
#define LM_UITEXT

#include "Component.h"

namespace OgreWrapper {
	class UIText;
}

namespace LocoMotor {
	class UITextLM : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "UIText";
		};

		UITextLM(std::string txtName, std::string font);
		~UITextLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void ChangeText(std::string newtxt);
		void SetTextHeight(double height);
		void SetFont(std::string nfont);
		void AlignCenter();
		void AlignLeft();
		void AlignRight();

		void SetTopColor(int r, int g, int b);
		void SetBottomColor(int r, int g, int b);

	protected:
		OgreWrapper::UIText* _uTxt;
		std::string _uFont;
		std::string _uTxtName;
	};
}
#endif