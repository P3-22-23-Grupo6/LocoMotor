#ifndef _SCENE_H_
#define _SCENE_H_

#include <map>
#include <string>

namespace Ogre {
	class SceneManager;
	class SceneNode;
	class Camera;
	class Viewport;
	class SimpleSpline;
}


namespace OgreWrapper {

	class Light;
	class Camera;
	class Renderer3D;
	class Node;
	class ParticleHelper;
	class Spline;
	class Canvas;

	class RenderScene {
	public:
		/// <summary>
		/// Creates a new Scene wrapping an Ogre::SceneManager object
		/// Do not call this, use OgreManager::createScene instead
		/// </summary>
		/// <param name="scene">Ogre::SceneManager to wrap</param>
		RenderScene(Ogre::SceneManager* scene);

		Ogre::SceneManager* GetMan() {
			return _manager;
		};

		/*RenderScene(RenderScene&& r) {
		};*/

		/// <summary>
		/// Destructor
		/// </summary>
		~RenderScene();

		/// <summary>
		/// Genera una escena de prueba
		/// </summary>
		void Prueba();

		/// <summary>
		/// Renders a frame from the active camera
		/// </summary>
		void Render();

		void SetSkybox();

		Node* CreateNode(std::string name);

		Node* CreateNode(std::string name, std::string parent);
		Node* GetNode(std::string name);

		Light* CreateLight();
		Renderer3D* CreateRenderer(std::string mesh);
		Camera* CreateCamera(std::string mesh);

		void SetActiveCamera(Camera* cam);
		Camera* GetMainCamera();

		ParticleHelper* CreateParticleHelper(std::string name, std::string filename);

	private:
		Ogre::SceneManager* _manager;
		Camera* _mainCam;
		Node* _root;
		std::map<std::string, Node*> _sceneStructure;

		Canvas* _canvas;
	};
}
#endif

