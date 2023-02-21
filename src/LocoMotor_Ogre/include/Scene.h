#ifndef _SCENE_H_
#define _SCENE_H_
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class Light;
class Viewport;
class Camera;
class Renderer3D;

namespace OgreWrapper
{
	class Scene
	{
	private:
		Ogre::SceneManager* mSM;

	public:
		/// <summary>
		/// Creates a new Scene wrapping an Ogre::SceneManagerObject
		/// Do not call this, use OgreManager::createScene instead
		/// </summary>
		/// <param name="scene">Ogre::SceneManager to wrap</param>
		Scene(Ogre::SceneManager* scene);

		/// <summary>
		/// Destructor
		/// </summary>
		~Scene();

		Ogre::Camera*  Prueba() {
			
            Ogre::SceneNode* mLightNode = mSM->getRootSceneNode()->createChildSceneNode();
            Ogre::Light* mLight = mSM->createLight();
            mLightNode->attachObject(mLight);

            mLight->setType(Ogre::Light::LT_DIRECTIONAL);
            mLightNode->setDirection(0, -1, 0);

            Ogre::Camera* cam = mSM->createCamera("Cam");
            cam->setNearClipDistance(1);
            cam->setFarClipDistance(10000);
            cam->setAutoAspectRatio(true);
            //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

            Ogre::SceneNode* mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
            mCamNode->attachObject(cam);

            mCamNode->setPosition(0, 0, 1000);
            mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
            //mCamNode->setDirection(Ogre::Vector3(0, 0, -1)); 
			return cam;
		}

	};
}

#endif

