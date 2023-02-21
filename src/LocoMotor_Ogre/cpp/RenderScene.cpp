#include "RenderScene.h"
#include "OgreManager.h"
#include "Node.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <iostream>

OgreWrapper::RenderScene::RenderScene (Ogre::SceneManager* scene) {
	_manager = scene;
}

OgreWrapper::RenderScene::~RenderScene () {
	_manager->clearScene ();
}

void OgreWrapper::RenderScene::Render () {
	std::cout << "Render\n";
	vp->update();
}

void OgreWrapper::RenderScene::Prueba () {
	Ogre::SceneNode* mLightNode = _manager->getRootSceneNode ()->createChildSceneNode ();
	Ogre::Light* mLight = _manager->createLight ();
	mLightNode->attachObject (mLight);

	mLight->setType (Ogre::Light::LT_DIRECTIONAL);
	mLightNode->setDirection (0, -1, 0);

	Ogre::Camera* cam = _manager->createCamera ("Cam");
	cam->setNearClipDistance (1);
	cam->setFarClipDistance (10000);
	cam->setAutoAspectRatio (true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	OgreWrapper::Node* mCamNode = new OgreWrapper::Node(_manager->getRootSceneNode()->createChildSceneNode("nCam"));
	mCamNode->Attach (cam);

	vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));

	mCamNode->Translate (0, 0, 1000);
	//mCamNode->lookAt (Ogre::Vector3 (0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1)); 
	
	
}

