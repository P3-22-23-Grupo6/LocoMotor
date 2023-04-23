#include "UIText.h"

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
//#include "OgreFont.h"


OgreWrapper::UIText::UIText() : UIElement() {

    _uFont = "MyFont.fontdef";
    _uTxtName = "New Text";
    //_txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
    //       _overlayMngr->createOverlayElement("TextArea", "UITextElem" + std::to_string(_numOfUIElements)));

    //_txtElem->setMetricsMode(Ogre::GMM_RELATIVE);
   
    //_txtElem->setCaption(txtName);
    //_txtElem->setCharHeight(0.25);
    //_txtElem->setPosition(0.5, 0);
    //_txtElem->setDimensions(defaultW, defaultH);
    //_txtElem->setFontName(font);
    //
    ////_txtElem->setFontName(font.get()->getName());
    //_txtElem->setColourBottom(Ogre::ColourValue::Black);
    //_txtElem->setColourTop(Ogre::ColourValue::Black);
    //_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
   
    //_overlay = _overlayMngr->create("UITextContainer" + std::to_string(_numOfUIElements));
    ////_overlay->add2D((Ogre::OverlayContainer*) _txtElem);

    ////Metemos el texto en un container
    //_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImageTextContainer" + std::to_string(_numOfUIElements)));
    //_container->setMetricsMode(Ogre::GMM_RELATIVE);
    //
    //_container->setPosition(defaultX, defaultY);
    //_container->setDimensions(defaultW, defaultH);
    //_container->addChild(_txtElem);
    //_overlay->add2D(_container);
    /**/
    
   /* _overlay->show();*/
}

bool OgreWrapper::UIText::Init() {

    _txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
          _overlayMngr->createOverlayElement("TextArea", "UITextElem" + std::to_string(_numOfUIElements)));

    _txtElem->setMetricsMode(Ogre::GMM_RELATIVE);

    _txtElem->setCaption(_uTxtName);
    _txtElem->setCharHeight(0.25);
    _txtElem->setPosition(0.5, 0);
    _txtElem->setDimensions(defaultW, defaultH);
    _txtElem->setFontName(_uFont);

    //_txtElem->setFontName(font.get()->getName());
    _txtElem->setColourBottom(Ogre::ColourValue::Black);
    _txtElem->setColourTop(Ogre::ColourValue::Black);
    _txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);

    _overlay = _overlayMngr->create("UITextContainer" + std::to_string(_numOfUIElements));
    //_overlay->add2D((Ogre::OverlayContainer*) _txtElem);

    //Metemos el texto en un container
    _container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImageTextContainer" + std::to_string(_numOfUIElements)));
    _container->setMetricsMode(Ogre::GMM_RELATIVE);

    _container->setPosition(defaultX, defaultY);
    _container->setDimensions(defaultW, defaultH);
    _container->addChild(_txtElem);
    _overlay->add2D(_container);

    _overlay->show();

    return false;
}

void OgreWrapper::UIText::ChangeText(std::string newtxt) {
    _txtElem->setCaption(newtxt);

}

void OgreWrapper::UIText::SetFont(std::string nfont) {
    _txtElem->getFont()->setSource(nfont);
    _txtElem->getFont()->load();
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

void OgreWrapper::UIText::SetTopColor(int r, int g, int b) {
    _txtElem->setColourTop(Ogre::ColourValue(r,g,b));
}

void OgreWrapper::UIText::SetBottomColor(int r, int g, int b) {
    _txtElem->setColourBottom(Ogre::ColourValue(r,g,b));
}

void OgreWrapper::UIText::SetHeight(double height) {
    _txtElem->setCharHeight(height);
}
