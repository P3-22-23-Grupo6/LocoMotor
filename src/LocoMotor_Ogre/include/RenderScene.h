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
	class StaticGeometry;
	class OverlaySystem;
}

class LMVector3;
class LMQuaternion;

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
		/// @brief Creates a new Scene wrapping an Ogre::SceneManager object Do not call this, use OgreManager::createScene instead
		/// @param scene Ogre::SceneManager to wrap
		RenderScene(Ogre::SceneManager* scene);

		Ogre::SceneManager* GetMan() {
			return _manager;
		};


		/// @brief Destructor
		~RenderScene();

		void Deactivate();


		/// @brief Renders a frame from the active camera
		void Render();

		void SetSkybox();

		Node* CreateNode(std::string name);

		Node* CreateNode(std::string name, std::string parent);
		Node* GetNode(std::string name);

		void DestroyNode(std::string name);

		Canvas* GetCanvas();

		Light* CreateLight();
		Renderer3D* CreateRenderer(std::string mesh);
		OgreWrapper::Renderer3D* CreateStaticRenderer(std::string mesh, OgreWrapper::Node* meshNode);
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

		Ogre::OverlaySystem* _overlay;

		Ogre::StaticGeometry* _stGeom;
	};
}
#endif

