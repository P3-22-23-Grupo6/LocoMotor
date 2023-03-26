// Clase dedicada a la inicializacion de CEGUI para el renderizado de UI,
//carga de recursos de UI, etc.
#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

namespace OgreWrapper {

	class GUI {
	public:
		void init(const std::string& resourceDirectory);
		void destroy();
		
		void draw();

		void loadScheme(const std::string& schemeFile);
		void setFont(const std::string& fontFile);
		CEGUI::Window* createWidget(const std::string& type, const std::string& name = "");
		//static void setWidgetDestRec(CEGUI::Window*);

		//Getters
		static CEGUI::OgreRenderer* getRenderer(){return myRenderer;}
		const CEGUI::GUIContext* getContext() {return m_context;}

	private:
		static CEGUI::OgreRenderer* myRenderer;
		CEGUI::GUIContext* m_context = nullptr;
		CEGUI::Window* m_root = nullptr;
	};

}