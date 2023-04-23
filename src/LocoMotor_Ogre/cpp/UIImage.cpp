#include "UIImage.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"


OgreWrapper::UIImage::UIImage(): UIElement() {
	/*_overlay = _overlayMngr->create((const char*) &_numOfUIElements);
	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImageContainer" + std::to_string(_numOfUIElements)));
	_container->setMetricsMode(Ogre::GMM_RELATIVE);
	_container->setMaterialName(imgName);
	_container->setPosition(defaultX, defaultY);
	_container->setDimensions(defaultW, defaultH);
	_overlay = _overlayMngr->create("UIImage" + std::to_string(_numOfUIElements));
	_overlay->add2D(_container);
	_overlay->show();*/
}

void OgreWrapper::UIImage::ChangeImage(std::string nImage) {
	_container->setMaterialName(nImage);
}

bool OgreWrapper::UIImage::Init() {
	_overlay = _overlayMngr->create((const char*) &_numOfUIElements);
	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImageContainer" + std::to_string(_numOfUIElements)));
	_container->setMetricsMode(Ogre::GMM_RELATIVE);
	_container->setMaterialName(Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName());
	_container->setPosition(defaultX, defaultY);
	_container->setDimensions(defaultW, defaultH);
	_overlay = _overlayMngr->create("UIImage" + std::to_string(_numOfUIElements));
	_overlay->add2D(_container);
	_overlay->show();

	return false;
}
