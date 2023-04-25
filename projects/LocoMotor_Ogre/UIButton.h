#pragma once
#ifndef UI_IMAGE
#define UI_IMAGE

#include "UIElement.h"
#include <string>
#include <functional>

namespace OgreWrapper {
	class UIButton :public UIElement {
	public:
		UIButton();
		~UIButton() = default;

		void ChangeImage(std::string nImage);
		bool Init() override;
		//callFunctionWhenPressed
		//void Update() //hay que ver desde donde lo metemos; posiblemente esta funcion esté en component del juego
		//

	//protected:
	//	std::function<std::string> _func;
	//	

	};

}


#endif