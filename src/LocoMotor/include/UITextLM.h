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
		UITextLM();
		~UITextLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		/// @brief Sets the position of the text on the screen
		/// @param x -> horizontal axis position
		/// @param y -> vertical axis position
		void SetPosition(double x, double y);
		/// @brief Sets the size of the text on the screen 
		/// @param x -> horizontal scale
		/// @param y -> vertical scale
		void SetSize(double x, double y);
		/// @brief changes the text
		/// @param newtext is the text is going to replace the previous one
		void ChangeText(std::string newtxt);
		/// @brief changes the size of the text 
		/// @param height is the size the text will have
		void SetTextHeight(double height);
		/// @brief Sets the font the text will be using
		/// @param nfont is the name of the file
		void SetFont(std::string nfont);	
		/*
											   |        <-----position/anchor
										  Sample text

		*/
		/// @brief Places the text using the position as an anchor on the center
		void AlignCenter();

		
		/*
										 |        <-----position/anchor
										  Sample text

		*/
		/// @brief Places the text using the position as an anchor on the left
		void AlignLeft();
		
		/*
													 |        <-----position/anchor
										  Sample text

		*/
		/// @brief Places the text using the position as an anchor on the right
		void AlignRight();

		/// @brief Sets the color of the top of the text
		/// @param r red color
		/// @param g green color
		/// @param b blue color
		void SetTopColor(double r, double g, double b);
		/// @brief Sets the color of the bottom of the text
		/// @param r red color
		/// @param g green color
		/// @param b blue color
		void SetBottomColor(double r, double g, double b);

		double GetSizeX();
		double GetSizeY();

	protected:
		OgreWrapper::UIText* _uTxt;
		std::string _uFont;
		std::string _uTxtName;

		double _posX, _posY;
		double _sizeX, _sizeY;
	};
}
#endif