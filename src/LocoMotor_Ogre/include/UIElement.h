#pragma once
#ifndef UI_ELEMENT
#define UI_ELEMENT

#include <string>

namespace Ogre {
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
}

namespace OgreWrapper {

	struct NativeWindowPair;

	class UIElement {

	public:
		UIElement();
		virtual ~UIElement();

		virtual bool Init(const std::string& sceneName);

		/// @brief Establece la posicion del elemento de UI
		void SetPosition(double x, double y);
		/// @brief Establece las dimensiones del elemento de UI
		void SetDimensions(double w, double h);
		/// @brief Muestra el elemento de UI
		void Show();
		/// @brief Oculta el elemento de UI
		void Hide();
		/// @brief Establece si el elemento de UI es interactivo para utilizarse como un boton
		void SetInteractive(bool interactive);
		/// @brief Devuelve si el elemento de UI es interactivo y se puede utilizar como un boton
		bool GetInteractive();

		Ogre::OverlayContainer* GetElement();

	protected:
		Ogre::OverlayContainer* _container;
		Ogre::OverlayManager* _overlayMngr;

		static unsigned int _numOfUIElements;

		const double defaultX = 0, defaultY = 0, defaultW = 0.5, defaultH = 0.5;

		bool _isInteractive=false;
	};

}

#endif