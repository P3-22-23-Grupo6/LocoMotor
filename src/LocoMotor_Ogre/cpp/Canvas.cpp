#include "Canvas.h"
#include "OgreManager.h"
#include "OgreComponents.h"
#include "OgreOverlayPrerequisites.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "OgreImage.h"
#include "OgreRenderWindow.h"
#include <OgreRoot.h>

//TEMP
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>
#include <iostream>

unsigned int OgreWrapper::Canvas::_numOfCanvas = 0;
Ogre::OverlaySystem* OgreWrapper::Canvas::_ovrSys = nullptr;

OgreWrapper::Canvas::Canvas() {
	_canvas = nullptr;
	_container = nullptr;
	_numOfCanvas++;
}

OgreWrapper::Canvas::~Canvas() {
	if (_ovrSys) {
		delete _ovrSys;
		_ovrSys = nullptr;
	}
}

bool OgreWrapper::Canvas::Init(const char* name, Ogre::SceneManager* man) {

	std::cout << "\n\nCANVAS=====================================================================\n";

	if (!_ovrSys)
		_ovrSys = OGRE_NEW Ogre::OverlaySystem();
	man->addRenderQueueListener(_ovrSys);
	auto _aux = Ogre::OverlayManager::getSingletonPtr();
	_canvas = _aux->create((const char*) &_numOfCanvas);
	// _aux->addOverlay(_canvas);
	_container = static_cast<Ogre::OverlayContainer*>(_aux->createOverlayElement("Panel", "Main"));
	_container->setPosition(0.0f, 0.0f);
	_container->setDimensions(0.2, 0.2);
	_container->setMaterialName(/*Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName()*/"TestMat");
	// Add the panel to the overlay

	_canvas->add2D(_container);

#pragma region TEMP, Mostrar texto
	/*
	Ogre::FontPtr pFont = Ogre::FontManager::getSingletonPtr()->create("MyFont", Ogre::OverlayElement::DEFAULT_RESOURCE_GROUP);
	pFont->setType(Ogre::FT_TRUETYPE);
	pFont->setSource("Roboto-Thin.ttf");
	pFont->setTrueTypeSize(16);
	pFont->_setMaterial(Ogre::MaterialManager::getSingleton().getDefaultMaterial());
	pFont->setTrueTypeResolution(1024);

	Ogre::GlyphInfo a = Ogre::GlyphInfo();
	a.uvRect = Ogre::Font::UVRect(1, 1, 1, 1);
	a.codePoint = 200;
	a.aspectRatio = 1.f;
	a.advance = 1.f;
	a.bearing = 1.f;
	pFont->setGlyphInfo(a);

	//pFont->load();

	std::cout << "AAAAAAA";

	auto tex = static_cast<Ogre::TextAreaOverlayElement*>(_aux->createOverlayElement("TextArea", "texto"));
	tex->setCaption("HAA");
	tex->setMetricsMode(Ogre::GMM_RELATIVE);
	tex->setPosition(0.f, 0.f);
	tex->setDimensions(50, 50.5);
	tex->setCharHeight(1);
	tex->setFontName(pFont.get()->getName());
	tex->setColourBottom(Ogre::ColourValue::Black);
	tex->setColourTop(Ogre::ColourValue::Black);
	tex->setHorizontalAlignment(Ogre::GHA_LEFT);
	tex->setVerticalAlignment(Ogre::GVA_TOP);
	tex->setAlignment(Ogre::TextAreaOverlayElement::Left);
	//std::cout << tex->getFontName();
	_container->addChild(tex);
	*/
#pragma endregion

	_canvas->show();

	std::cout << "===========================================================================\n\n";

	return false;
}

bool OgreWrapper::Canvas::Render() {
	return false;
}

void OgreWrapper::Canvas::SetSceneManager() {
}
