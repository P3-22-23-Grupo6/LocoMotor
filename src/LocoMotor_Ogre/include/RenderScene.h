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
		/// @brief Gets the current sceneManager
		Ogre::SceneManager* GetMan();
		/// @brief Destructor
		~RenderScene();
		/// @brief Destroy all camera and particle system
		void Deactivate();
		/// @brief Renders a frame from the active camera
		void Render();
		/// @brief Sets the default skybox
		void SetSkybox();
		/// @brief Creates a node with a name
		Node* CreateNode(std::string name);
		/// @brief Creates a node with a name using the parent
		Node* CreateNode(std::string name, std::string parent);
		/// @brief Gets the node with a name
		Node* GetNode(std::string name);
		/// @brief Destroy the node with a name
		void DestroyNode(std::string name);
		/// @brief Gets the scene canvas
		Canvas* GetCanvas();
		/// @brief Creates a light in the scene
		Light* CreateLight();
		/// @brief Creates a Renderer3D with a mesh
		Renderer3D* CreateRenderer(std::string mesh);
		/// @brief Creates a static Renderer3D with a mesh
		Renderer3D* CreateStaticRenderer(std::string mesh, OgreWrapper::Node* meshNode);
		/// @brief Creates a camera
		Camera* CreateCamera(std::string mesh);
		/// @brief Sets the active camera
		void SetActiveCamera(Camera* cam);
		/// @brief Gets the scene main camera
		Camera* GetMainCamera();
		/// @brief Creates a particle helper with a name using a file
		ParticleHelper* CreateParticleHelper(std::string name, std::string filename);

	private:
		Ogre::SceneManager* _manager;
		Camera* _mainCam;
		Node* _root;
		std::map<std::string, Node*> _sceneStructure;
		Canvas* _canvas;
		Ogre::OverlaySystem* _overlay;
		Ogre::StaticGeometry* _stGeom;
		int lastCamZOrder;
	};
}
#endif

