#include "RenderScene.h"
#include "OgreManager.h"
#include "Node.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <iostream>

OgreWrapper::RenderScene::RenderScene (Ogre::SceneManager* scene) {
	_manager = scene;
	OgreManager::GetInstance ()->mShaderGenerator->addSceneManager (_manager);
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
	mLight->setDiffuseColour (1, 1, 1);
	mLightNode->setDirection (-1, -1, -1);

	Ogre::Camera* cam = _manager->createCamera ("Cam");
	cam->setNearClipDistance (1);
	cam->setFarClipDistance (10000);
	cam->setAutoAspectRatio (true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	Ogre::SceneNode* mCamNode = _manager->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject (cam);

	vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));

	mCamNode->translate (0, 0, 1000);
	mCamNode->lookAt (Ogre::Vector3 (0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1)); 

	OgreWrapper::Node* mCubeNode = new OgreWrapper::Node (_manager->getRootSceneNode ()->createChildSceneNode ());
	Ogre::Entity* cube = _manager->createEntity ("cube.mesh");
	//cube->setMaterialName ("LocoMotor/blanco");
	mCubeNode->Attach (cube);
}

