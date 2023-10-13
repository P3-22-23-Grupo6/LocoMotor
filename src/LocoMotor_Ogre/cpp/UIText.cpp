#include "UIText.h"
#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlay.h"
#include "OgreResourceManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include <iostream>


OgreWrapper::UIText::UIText() : UIElement() {
	_uFont = "BerlinSans32";
	_uTxtName = "New Text";
	_uType = "t";
}

OgreWrapper::UIText::~UIText() {
	_container->removeChild(_txtElem->getName());
	_overlayMngr->destroyOverlayElement(_txtElem);
}

bool OgreWrapper::UIText::Init(const std::string& sceneName) {

	UIElement::Init(sceneName);

	_txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
		  _overlayMngr->createOverlayElement("TextArea", "UITextElem" + std::to_string(_numOfUIElements)));

	_txtElem->setMetricsMode(Ogre::GMM_RELATIVE);
	_txtElem->setCaption(_uTxtName);
	_txtElem->setCharHeight(0.25);
	_txtElem->setPosition(0.5, 0);
	_txtElem->setDimensions((float)_defaultW, (float)_defaultH);
	_txtElem->setColourBottom(Ogre::ColourValue::Black);
	_txtElem->setColourTop(Ogre::ColourValue::Black);
	_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
	
	_container->addChild(_txtElem);

	/*Ogre::FontPtr tempFont = _txtElem->getFont();
	if (tempFont != nullptr) {
		_txtElem->getFont()->setType(Ogre::FT_IMAGE);
	}*/
	return false;
}

void OgreWrapper::UIText::ChangeText(std::string newtxt) {
	_txtElem->setCaption(newtxt);
}

bool OgreWrapper::UIText::SetFont(std::string nfont) {
	
	auto a = Ogre::FontManager::getSingletonPtr();
	if (a->getByName(nfont)) {
		_txtElem->setFontName(nfont);
		if(_uType[0] == 'i') _txtElem->getFont()->setType(Ogre::FT_IMAGE);
		else _txtElem->getFont()->setType(Ogre::FT_TRUETYPE);
		return true;
	}
	return false;
}

void OgreWrapper::UIText::SetType(std::string nfont) {
	_uType = nfont;
	//_txtElem->getFont()->setType(Ogre::FT_IMAGE);
}

void OgreWrapper::UIText::AlignCenter() {
	_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
}

void OgreWrapper::UIText::AlignLeft() {
	_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);
}

void OgreWrapper::UIText::AlignRight() {
	_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
}

void OgreWrapper::UIText::SetTopColor(double r, double g, double b) {
	_txtElem->setColourTop(Ogre::ColourValue((float) r, (float) g, (float) b));
}

void OgreWrapper::UIText::SetBottomColor(double r, double g, double b) {
	_txtElem->setColourBottom(Ogre::ColourValue((float) r, (float) g, (float) b));
}

void OgreWrapper::UIText::SetHeight(double height) {
	_txtElem->setCharHeight((float) height);
}
