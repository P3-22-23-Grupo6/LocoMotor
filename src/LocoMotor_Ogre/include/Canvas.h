#pragma once
#ifndef UI_CANVAS
#define UI_CANVAS

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

	class Canvas {

		static Ogre::OverlaySystem* _ovrSys;
		Ogre::Overlay* _canvas;
		Ogre::OverlayContainer* _container;

		static unsigned int _numOfCanvas;

	public:
		Canvas();
		~Canvas();

		bool Init(const char* name, Ogre::SceneManager* man);

		bool Render();

		static void SetSceneManager();

		void AddUIElement();

	};

}

#endif