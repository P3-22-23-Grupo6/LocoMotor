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
		~UIText() = default;

		bool Init() override;

		void ChangeText(std::string newtxt);
		void SetHeight(double height);
		void SetFont(std::string nfont);
		void AlignCenter();
		void AlignLeft();
		void AlignRight();
		
		void SetTopColor(double r, double g, double b);
		void SetBottomColor(double r, double g, double b);


	protected:
		Ogre::TextAreaOverlayElement* _txtElem;
		std::string _uFont;
		std::string _uTxtName;
		
	};


}


#endif