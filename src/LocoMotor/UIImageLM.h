#pragma once
#pragma once
#ifndef LM_UIIMAGE
#define LM_UIIMAGE

#include "Component.h"
#include <functional>

namespace OgreWrapper {
	class UIImage;
	class OgreManager;
}

namespace LocoMotor {

	class InputManager;

	class MOTOR_API UIImageLM : public Component {

	public:
		UIImageLM();
		~UIImageLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		/// @brief Sets the position of the image on the screen
		/// @param x -> horizontal axis position
		/// @param y -> vertical axis position
		void SetPosition(double x, double y);
		/// @brief Sets the position of the image on the screen
		/// @param x -> horizontal scale
		/// @param y -> vertical scale
		void SetSize(double x, double y);
		/// @brief sets an image as an interactive entity
		/// @param nteractive enables or disables the interaction of the image
		void SetInteractive(bool interactive);
		/// @brief Checks if the image is intractive or not
		bool GetInteractive();
		/// @brief If the image is interactive, check if the mouse is on, or pressing it
		/// @param dt  stands for delta time, which is the time elapsed since the last frame update.
		void Update(float dt)override;
		/// @brief Sets the function is going to be called when the image is pressed if it's interactive
		/// @param func is the function is going to be called
		void CallOnClick(const std::function<void()>& func);
		/// @brief Returns true if the mouse is on the bound of the image
		bool MouseOnImage();
		/// @brief Changes the image to render
		/// @param newimg is the image that will replace the previous 
		void ChangeImage(std::string newimg);
		/// @brief Sets the image is going to appear on a normal state (in case it's interactive)
		/// @param newimg is the image that will render in a normal state
		void SetImage(std::string newimg);
		/// @brief Sets the image is going to appear if the mouse is on the bound (in case it's interactive)
		/// @param newimg is the image that will render when the mouse in on bounds
		void SetOnMouseImage(std::string newimg);
		/// @brief Sets the image is going to appear if the mouse is pressing it (in case it's interactive)
		/// @param newimg is the image that will render when the mouse is pressing it
		void SetPressedImage(std::string newimg);
		/// @brief Sets the Top of the Image
		/// @param topIndex layer Index
		void SetTop(int topIndex);

	protected:
		OgreWrapper::UIImage* _uimg;
		OgreWrapper::OgreManager* _ogMng;
		std::string _imgName;
		std::string _onMouseImgName;
		std::string _pressedImgName;

		std::function<void()> _onClick;
		double _posX, _posY;


		double _winHeight, _winWidth;
		double _sizeX, _sizeY;

	};
}
#endif