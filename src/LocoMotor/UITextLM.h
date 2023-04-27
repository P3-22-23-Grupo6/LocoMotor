#pragma once
#ifndef LM_UITEXT
#define LM_UITEXT
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"

namespace OgreWrapper {
	class UIText;
}

namespace LocoMotor {
	class MOTOR_API UITextLM : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "UIText";
		};

		UITextLM();
		~UITextLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void SetPosition(double x, double y);
		void SetSize(double x, double y);

		void ChangeText(std::string newtxt);
		void SetTextHeight(double height);
		void SetFont(std::string nfont);
		void AlignCenter();
		void AlignLeft();
		void AlignRight();

		void SetTopColor(double r, double g, double b);
		void SetBottomColor(double r, double g, double b);

	protected:
		OgreWrapper::UIText* _uTxt;
		std::string _uFont;
		std::string _uTxtName;

		double posX, posY;
		double sizeX, sizeY;
	};
}
#endif