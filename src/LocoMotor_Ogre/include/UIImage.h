#pragma once
#ifndef UI_IMAGE
#define UI_IMAGE

#include "UIElement.h"
#include <string>

namespace OgreWrapper {
	class UIImage :public UIElement {
	public:
		UIImage();
		~UIImage() = default;

		// Cambia la imagen a renderizar
		void ChangeImage(std::string nImage);
		bool Init() override;


	};

}


#endif


