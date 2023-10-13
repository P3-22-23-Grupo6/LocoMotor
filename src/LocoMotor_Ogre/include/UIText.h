#pragma once
#ifndef UI_TEXT
#define UI_TEXT

#include "UIElement.h"
#include <string>

namespace Ogre {
	class TextAreaOverlayElement;
}

namespace OgreWrapper {

	class UIText : public UIElement {
	public:
		UIText();
		~UIText();

		bool Init(const std::string& sceneName) override;

		/// @brief changes the text
		/// @param newtext is the text is going to replace the previous one
		void ChangeText(std::string newtxt);

		/// @brief changes the size of the text 
		/// @param height is the size the text will have
		void SetHeight(double height);

		/// @brief Sets the ç the text will be using
		/// @param nfont is the name of the file
		bool SetFont(std::string nfont);
		void SetType(std::string nType);

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

	protected:
		Ogre::TextAreaOverlayElement* _txtElem;
		std::string _uFont;
		std::string _uType;
		std::string _uTxtName;

	};


}


#endif