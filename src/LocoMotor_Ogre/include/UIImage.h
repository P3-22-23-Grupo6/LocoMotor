#pragma once
#ifndef UI_IMAGE
#define UI_IMAGE

#include "UIElement.h"
#include <string>

namespace OgreWrapper {
	class UIImage :public UIElement {
	public:
		UIImage(std::string imgName);
		~UIImage() = default;
		//virtual bool Init();
	};
}


#endif


