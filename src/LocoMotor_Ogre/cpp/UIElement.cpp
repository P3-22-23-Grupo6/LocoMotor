#include "UIElement.h"
#include "OgreManager.h"
#include "OgreComponents.h"
#include "OgreOverlayPrerequisites.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "OgreImage.h"
#include "OgreRenderWindow.h"
#include "Canvas.h"
#include "RenderScene.h"
#include <OgreRoot.h>

using namespace OgreWrapper;

unsigned int OgreWrapper::UIElement::_numOfUIElements = 0;

OgreWrapper::UIElement::UIElement() {
	_container = nullptr;
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();
	_numOfUIElements++;
}

OgreWrapper::UIElement::~UIElement() {
	_overlayMngr->destroyOverlayElement(_container);
}

bool OgreWrapper::UIElement::Init(const std::string& sceneName) {
	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIContainer" + std::to_string(_numOfUIElements)));
	_container->initialise();
	_container->setMetricsMode(Ogre::GMM_RELATIVE);
	_container->setPosition(_defaultX, _defaultY);
	_container->setDimensions(_defaultW, _defaultH);
	OgreManager::GetInstance()->GetScene(sceneName)->GetCanvas()->AddUIElement(this);
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

bool OgreWrapper::UIElement::GetInteractive() {
	return _isInteractive;
}

Ogre::OverlayContainer* OgreWrapper::UIElement::GetElement() {
	return _container;
}

void OgreWrapper::UIElement::SetInteractive(bool interactive) {
	_isInteractive = interactive;
}

