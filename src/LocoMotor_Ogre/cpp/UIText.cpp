#include "UIText.h"

#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlay.h"
#include "OgreResourceManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include <iostream>
//#include "OgreFont.h"


OgreWrapper::UIText::UIText() : UIElement() {
    _uFont = "";
    _uTxtName = "New Text";
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
    _txtElem->setDimensions(defaultW, defaultH);
    //_txtElem->setFontName(_uFont);

    //_txtElem->setFontName(font.get()->getName());
    _txtElem->setColourBottom(Ogre::ColourValue::Black);
    _txtElem->setColourTop(Ogre::ColourValue::Black);
    _txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
    _container->addChild(_txtElem);

    return false;
}

void OgreWrapper::UIText::ChangeText(std::string newtxt) {
    _txtElem->setCaption(newtxt);
}

bool OgreWrapper::UIText::SetFont(std::string nfont) {
    if (Ogre::FontManager::getSingletonPtr()->getByName(nfont)) {
        _txtElem->setFontName(nfont);
        return true;
    }
    return false;
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
    _txtElem->setColourTop(Ogre::ColourValue(r,g,b));
}

void OgreWrapper::UIText::SetBottomColor(double r, double g, double b) {
    _txtElem->setColourBottom(Ogre::ColourValue(r,g,b));
}

void OgreWrapper::UIText::SetHeight(double height) {
    _txtElem->setCharHeight(height);
}
