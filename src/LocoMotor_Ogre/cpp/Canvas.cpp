#include "Canvas.h"
#include "OgreManager.h"
#include "OgreComponents.h"
#include "OgreOverlayPrerequisites.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"
#include "OgreImage.h"
#include "OgreRenderWindow.h"
#include <OgreRoot.h>
#include "UIElement.h"


unsigned int OgreWrapper::Canvas::_numOfCanvas = 0;

OgreWrapper::Canvas::Canvas() {
	_canvas = nullptr;
	_container = nullptr;
	_numOfCanvas++;
}

OgreWrapper::Canvas::~Canvas() {
	ShutDown();
}

bool OgreWrapper::Canvas::Init(Ogre::SceneManager* man) {

	Ogre::OverlayManager* _aux = Ogre::OverlayManager::getSingletonPtr();

	_canvas = _aux->create("MainOverlay" + _numOfCanvas);
	_container = static_cast<Ogre::OverlayContainer*>(_aux->createOverlayElement("Panel", "Main" + _numOfCanvas));
	_container->setPosition(0.0f, 0.0f);
	_container->setDimensions(1.0f, 1.0f);
	_canvas->add2D(_container);
	_canvas->show();
	return false;
}


void OgreWrapper::Canvas::AddUIElement(UIElement* uiEl) {
	_container->addChild(uiEl->GetElement());
	_uiElems.push_back(uiEl);
}

bool OgreWrapper::Canvas::ShutDown() {
	_uiElems.clear();
	Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(_container);
	Ogre::OverlayManager::getSingletonPtr()->destroy(_canvas->getName());
	return false;
}

