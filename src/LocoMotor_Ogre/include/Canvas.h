#pragma once
#ifndef UI_CANVAS
#define UI_CANVAS

#include <vector>
#include <string>

namespace Ogre {
	class SceneManager;
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
}

namespace OgreWrapper {

	struct AnchorPoint {
		float x = 0;
		float y = 0;
	};

	struct Position {
		short x = 0;
		short y = 0;
	};

	class RenderScene;
	class UIElement;

	class Canvas {
	public:
		Canvas();
		~Canvas();

		/// @brief Inits the canvas to the sceneManager
		bool Init(Ogre::SceneManager* man);
		/// @brief Deletes all uiElement and destroy the canvas
		bool ShutDown();
		/// @brief Adds an uielemet to the canvas
		void AddUIElement(UIElement* uiEl);
	private:
		Ogre::Overlay* _canvas;
		Ogre::OverlayContainer* _container;

		std::vector<UIElement*> _uiElems;

		static unsigned int _numOfCanvas;

	};

}

#endif