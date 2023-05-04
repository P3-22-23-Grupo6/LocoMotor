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

		/// @brief Changes the image is going to appear
		void ChangeImage(std::string nImage);
		bool Init(const std::string& sceneName) override;
		/// @brief 
		void SetTop(int topIndex);
	};
}
#endif


