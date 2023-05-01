#pragma once
#ifndef UI_TEXT
#define UI_TEXT

#include "UIElement.h"
#include <string>


namespace Ogre {
	class TextAreaOverlayElement;
	//class FontPtr;
}

namespace OgreWrapper {

	

	class UIText : public UIElement {
	public:
		UIText();
		//UIText(std::string txtName, Ogre::FontPtr font);
		~UIText();

		bool Init(const std::string& sceneName) override;
		/// @brief changes the text
		/// @param newtext is the text is going to replace the previous one
		void ChangeText(std::string newtxt);
		/// @brief changes the size of the text 
		/// @param height is the size the text will have
		void SetHeight(double height);
		/// @brief Sets the font the text will be using
		/// @param nfont is the name of the file
		void SetFont(std::string nfont);
		/// @brief Places the text using the position as an anchor on the center
		/*
		                                       |        <-----position/anchor
		                                  Sample text
		
		*/
		void AlignCenter();
		
		/// @brief Places the text using the position as an anchor on the left
		/*
									     |        <-----position/anchor
										  Sample text

		*/
		void AlignLeft();
		/// @brief Places the text using the position as an anchor on the right
		/*
											         |        <-----position/anchor
										  Sample text

		*/
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
		std::string _uTxtName;
		
	};


}


#endif