//#include "UIElement.h"
//#include "OgreManager.h"
//#include "OgreComponents.h"
//#include "OgreOverlayPrerequisites.h"
//#include "OgreOverlay.h"
//#include "OgreOverlayContainer.h"
//#include "OgreOverlayManager.h"
//#include "OgreImage.h"
//#include "OgreRenderWindow.h"
//#include <OgreRoot.h>
//
//using namespace OgreWrapper;
//
//Ogre::SceneManager* UIElement::_ogreScnManager = nullptr;
//
//OgreWrapper::UIElement::UIElement(const char* name) : Ogre::OverlayElement(name) {
//	_img = new Ogre::Image(Ogre::PF_BYTE_RGBA, 20, 20);
//}
//
//OgreWrapper::UIElement::~UIElement() {
//	_img->freeMemory();
//	delete _img;
//}
//
//bool OgreWrapper::UIElement::Init() {
//	_img->load("Assets/Material/17.png", "NoSe");
//	return false;
//}
//
//bool OgreWrapper::UIElement::Render() {
//	return false;
//}
//
//void OgreWrapper::UIElement::SetSceneManager() {
//}
