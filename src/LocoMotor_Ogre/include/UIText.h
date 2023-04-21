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

	

	class UIText :public UIElement {
	public:
		UIText(std::string txtName,std::string font);
		//UIText(std::string txtName, Ogre::FontPtr font);
		~UIText();

	protected:
		Ogre::TextAreaOverlayElement* _txtElem;
		
	};


}


#endif