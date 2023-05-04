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

		/// @brief Inits the uielement in the scene 
		virtual bool Init(const std::string& sceneName);
		/// @brief Sets the position of the entity on the UI
		void SetPosition(double x, double y);
		/// @brief Sets the size of the entity on the UI
		void SetDimensions(double w, double h);
		/// @brief Shows/turns visible the entity on the UI
		void Show();
		/// @brief Hides/turns invisible the entity on the UI
		void Hide();
		/// @brief sets the entity as an interactive entity
		/// @param nteractive enables or disables the interaction of the entity
		void SetInteractive(bool interactive);
		/// @brief Checks if the image is intractive or not
		bool GetInteractive();
		/// @brief Returns the entity
		Ogre::OverlayContainer* GetElement();

	protected:
		Ogre::OverlayContainer* _container;
		Ogre::OverlayManager* _overlayMngr;

		static unsigned int _numOfUIElements;

		const double _defaultX = 0, _defaultY = 0, _defaultW = 0.5, _defaultH = 0.5;

		bool _isInteractive = false;
	};

}

#endif