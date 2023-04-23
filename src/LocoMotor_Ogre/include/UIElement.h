#pragma once
#ifndef UI_ELEMENT
#define UI_ELEMENT

//#include <OgreTextAreaOverlayElement.h>

namespace Ogre {
	/*class Image;
	class SceneManager;
	class String;*/
	class OverlayManager;
	class Overlay;
	class OverlayContainer;
}

namespace OgreWrapper {

	/*struct AnchorPoint {
		float x = 0;
		float y = 0;
	};*/

	/*struct Position {
		short x = 0;
		short y = 0;
	};*/

	struct NativeWindowPair;

	class UIElement {

	public:
		UIElement();
		~UIElement();

		virtual bool Init();

		void SetPosition(double x, double y);
		void SetDimensions(double w, double h);
		void Show();
		void Hide();

		//bool Render();

		//static void SetSceneManager();

	protected:
		Ogre::Overlay* _overlay;
		Ogre::OverlayContainer* _container;
		Ogre::OverlayManager* _overlayMngr;

		/*AnchorPoint _anchor;
		Position _position;*/

		static unsigned int _numOfUIElements;

		const double defaultX = 0, defaultY = 0, defaultW = 0.5, defaultH = 0.5;
	};

}

#endif