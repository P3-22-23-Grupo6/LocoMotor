#include "GUI.h"
#include "OgreManager.h"

CEGUI::OgreRenderer* OgreWrapper::GUI::myRenderer = nullptr;

void OgreWrapper::GUI::init(const std::string& resourceDirectory) {
	//Check si el renderer y el sistema han sido inicializados
	if (myRenderer == nullptr) {
		//myRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
		myRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*OgreWrapper::OgreManager::GetInstance()->GetRenderTarget());

		//Asignar los recursos de la UI a Assets/GUI
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*> (CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets");
		rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes");
		rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts");
		rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts");
		rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeel");
		rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts");

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager	::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(myRenderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
}

void OgreWrapper::GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}
void OgreWrapper::GUI::draw() {
	myRenderer->beginRendering();
	m_context->draw();
	myRenderer->endRendering();
	//Disable Scissors test (?), solo en GL se supone?
}

CEGUI::Window* OgreWrapper::GUI::createWidget(const std::string& type, const std::string& name) {
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	m_root->addChild(newWindow);

	newWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0.5f), CEGUI::UDim(0.5f, 0.5f)));
	newWindow->setSize(CEGUI::USize(CEGUI::UDim(1,1), CEGUI::UDim(1, 1)));
	return newWindow;
}

void OgreWrapper::GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile); 
}

void OgreWrapper::GUI::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);
}