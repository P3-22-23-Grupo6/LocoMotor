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

	class UIImageLM : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "UIImage";
		};

		UIImageLM();
		~UIImageLM();
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		/// @brief Establece la posicion de la imagen en la pantalla
		void SetPosition(double x, double y);
		/// @brief Establece las dimensiones de la imagen en la pantalla
		void SetSize(double x, double y);

		/// @brief Establece si la imagen es interactiva para usarse como un boton
		void SetInteractive(bool interactive);
		/// @brief Devuelve true si la imagen es interactiva y puede usarse como un boton
		bool GetInteractive();
		/// @brief Si la imagen es interactiva, comprueba si el raton ha clickado sobre ella
		void Update(float dt)override;
		/// @brief Establece la funcion que debe ser llamada cuando se hace click sobre la imagen,
		/// en caso de ser interactiva
		void CallOnClick(const std::function<void()> &func);
		/// @brief Devuelve true si el raton esta posicionado sobre la imagen
		bool MouseOnImage();
		/// @brief Cambia la imagen a renderizar
		void ChangeImage(std::string newimg);
		/// @brief Establece la imagen que se va a utilizar
		void SetImage(std::string newimg);
		/// @brief Establece la imagen que se va a utilizar cuando el raton esta situado 
		/// sobre la imagen (para botones)
		void SetOnMouseImage(std::string newimg);
		/// @brief Establece la imagen que se va a utilizar cuando se ha hecho click 
		/// sobre la imagen (para botones)
		void SetPressedImage(std::string newimg);

	protected:
		OgreWrapper::UIImage* _uimg;
		OgreWrapper::OgreManager* _ogMng;
		std::string _imgName;
		std::string _onMouseImgName;
		std::string _pressedImgName;

		std::function<void()> _onClick;
		double posX, posY;


		double winHeight, winWidth;
		double sizeX, sizeY;

	};
}
#endif