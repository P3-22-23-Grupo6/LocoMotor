#include "UIText.h"

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
//#include "OgreFont.h"


OgreWrapper::UIText::UIText(std::string txtName,std::string font) : UIElement() {
//OgreWrapper::UIText::UIText(std::string txtName, Ogre::FontPtr font) : UIElement() {

    _txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
           _overlayMngr->createOverlayElement("TextArea", "UITextElem" + std::to_string(_numOfUIElements)));

    _txtElem->setMetricsMode(Ogre::GMM_RELATIVE);
   
    _txtElem->setCaption(txtName);
    _txtElem->setCharHeight(0.5);
    _txtElem->setPosition(defaultX, defaultY);
    _txtElem->setDimensions(defaultW, defaultH);
    _txtElem->setFontName(font);
    //_txtElem->setFontName(font.get()->getName());
    _txtElem->setColourBottom(Ogre::ColourValue::Black);
    _txtElem->setColourTop(Ogre::ColourValue::Black);
    _txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);
   
    _overlay = _overlayMngr->create("UITextContainer" + std::to_string(_numOfUIElements));
    //_overlay->add2D((Ogre::OverlayContainer*) _txtElem);

    _container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImageTextContainer" + std::to_string(_numOfUIElements)));
    _container->setMetricsMode(Ogre::GMM_RELATIVE);
    
    _container->setPosition(0.5, defaultY);
    _container->setDimensions(defaultW, defaultH);
    _container->addChild(_txtElem);
    _overlay->add2D(_container);
    /**/
    
    _overlay->show();
}
