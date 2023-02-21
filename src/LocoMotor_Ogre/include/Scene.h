#ifndef _SCENE_H_
#define _SCENE_H_

namespace Ogre {
	class SceneManager;
	class SceneNode;
}


namespace OgreWrapper
{
	class Light;
	class Camera;
	class Renderer3D;

	class RenderScene
	{
	public:
		/// <summary>
		/// Creates a new Scene wrapping an Ogre::SceneManager object
		/// Do not call this, use OgreManager::createScene instead
		/// </summary>
		/// <param name="scene">Ogre::SceneManager to wrap</param>
		RenderScene(Ogre::SceneManager* scene);

		/// <summary>
		/// Destructor
		/// </summary>
		~RenderScene();

		Ogre::Camera* Prueba() {

			Ogre::SceneNode* mLightNode = _manager->getRootSceneNode()->createChildSceneNode();
			Ogre::Light* mLight = _manager->createLight();
			mLightNode->attachObject(mLight);

			mLight->setType(Ogre::Light::LT_DIRECTIONAL);
			mLightNode->setDirection(0, -1, 0);

			Ogre::Camera* cam = _manager->createCamera("Cam");
			cam->setNearClipDistance(1);
			cam->setFarClipDistance(10000);
			cam->setAutoAspectRatio(true);
			//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

			Ogre::SceneNode* mCamNode = _manager->getRootSceneNode()->createChildSceneNode("nCam");
			mCamNode->attachObject(cam);

			mCamNode->setPosition(0, 0, 1000);
			mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
			//mCamNode->setDirection(Ogre::Vector3(0, 0, -1)); 
			return cam;
		}

		/// <summary>
		/// Renders a frame from the active camera
		/// </summary>
		void Render();

	private:
		Ogre::SceneManager* _manager;
	};
}
#endif

