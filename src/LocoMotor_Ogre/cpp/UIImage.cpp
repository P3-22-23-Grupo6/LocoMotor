#include "UIImage.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"


OgreWrapper::UIImage::UIImage(std::string imgName): UIElement() {

	_overlay = _overlayMngr->create((const char*) &_numOfUIElements);
	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "Main"));
}

OgreWrapper::UIImage::~UIImage() {
}

bool OgreWrapper::UIImage::Init() {
	UIElement::Init();

	return false;
}
