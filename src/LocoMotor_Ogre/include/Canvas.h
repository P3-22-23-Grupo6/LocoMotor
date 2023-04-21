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
	class OverlaySystem;
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

		static Ogre::OverlaySystem* _ovrSys;
		Ogre::Overlay* _canvas;
		Ogre::OverlayContainer* _container;

		Ogre::OverlayManager* _overlay;

		std::vector<UIElement*> _uiElems;

		static unsigned int _numOfCanvas;

	public:
		Canvas();
		~Canvas();

		bool Init(Ogre::SceneManager* man);
		bool ShutDown();

		bool Render();

		static void SetSceneManager();

		void addUIElement(UIElement* uiEl);

		/*template<typename T, typename ...Ts>
		T* addUIElement(std::string type, std::string name, Ts &&... args) {

			T* uEl = new T(type,name, args...);

			_uiElems.push_back(uEl);

			return uEl;
		}*/

	

	};

}

#endif