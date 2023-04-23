#include "UIElement.h"
#include "OgreManager.h"
#include "OgreComponents.h"
#include "OgreOverlayPrerequisites.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"
#include "OgreImage.h"
#include "OgreRenderWindow.h"
#include <OgreRoot.h>

using namespace OgreWrapper;

//Ogre::SceneManager* UIElement::_ogreScnManager = nullptr;

unsigned int OgreWrapper::UIElement::_numOfUIElements = 0;

OgreWrapper::UIElement::UIElement() {
	_overlay = nullptr;
	_container = nullptr;
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();
	_numOfUIElements++;
}

OgreWrapper::UIElement::~UIElement() {

}

bool OgreWrapper::UIElement::Init() {

	return false;
}

void OgreWrapper::UIElement::SetPosition(double x, double y) {
	_container->setPosition(x, y);
}

void OgreWrapper::UIElement::SetDimensions(double w, double h) {
	_container->setDimensions(w, h);
}

void OgreWrapper::UIElement::Show() {
	_container->show();
}

void OgreWrapper::UIElement::Hide() {
	_container->hide();
}

