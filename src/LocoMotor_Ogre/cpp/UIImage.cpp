#include "UIImage.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"


OgreWrapper::UIImage::UIImage(): UIElement() {
}

void OgreWrapper::UIImage::ChangeImage(std::string nImage) {
	if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(nImage))
		_container->setMaterialName(nImage);
}

bool OgreWrapper::UIImage::Init(const std::string& sceneName) {
	UIElement::Init(sceneName);
	_container->setMaterialName(Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName());

	return false;
}
