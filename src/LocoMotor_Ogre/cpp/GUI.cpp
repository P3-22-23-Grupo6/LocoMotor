#include "GUI.h"

CEGUI::OgreRenderer* OgreWrapper::GUI::myRenderer = nullptr;

void OgreWrapper::GUI::init(const std::string& resourceDirectory) {
	//Check si el renderer y el sistema han sido inicializados
	if (myRenderer == nullptr) {
		myRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

		//Asignar los recursos de la UI a Assets/GUI
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*> (CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets");
		rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes");
		rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts");
		rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts");
		rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeels");
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
}
void OgreWrapper::GUI::draw() {
	
}

CEGUI::Window* OgreWrapper::GUI::createWidget(const std::string& type, const std::string& name) {
	return CEGUI::WindowManager::getSingleton().createWindow(type, name);
}

void OgreWrapper::GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile); 
}

void OgreWrapper::GUI::setFont(const std::string& fontFile) {
	m_context->setDefaultFont(fontFile);
}