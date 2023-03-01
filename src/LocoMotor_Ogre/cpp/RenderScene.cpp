#include "RenderScene.h"
#include "OgreManager.h"
#include "Node.h"
#include "Camera.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <iostream>

OgreWrapper::RenderScene::RenderScene (Ogre::SceneManager* scene) {
	_manager = scene;
	vp = nullptr;
	_root = new OgreWrapper::Node (scene->getRootSceneNode ());
}

OgreWrapper::RenderScene::~RenderScene () {
	delete _root;
	using iterador = std::map<std::string, Node*>::iterator ;
	for (iterador it = _sceneStructure.begin (); it != _sceneStructure.end (); it = _sceneStructure.erase (it)) {
		delete it->second;
	}
}

void OgreWrapper::RenderScene::Render () {
	vp->update();
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode (std::string name) {
	if (_sceneStructure.count (name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	Node* node = _root->CreateChild();
	_sceneStructure.insert ({ name,node });
	return node;
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode (std::string name, std::string parent) {
	if (_sceneStructure.count (name) > 0  || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	else if (_sceneStructure.count (parent) == 0) {
		std::cerr << "No node with name " << name << " found. Could not create child\n";
		return nullptr;
	}
	else if(parent == "Root"){
		return CreateNode (name);
	}
	Node* node = GetNode (name)->CreateChild ();
	return node;
}

OgreWrapper::Node* OgreWrapper::RenderScene::GetNode (std::string name) {
	if (_sceneStructure.count (name) > 0) {
		std::cerr << "No node with the name " << name << " found\n";
		return nullptr;
	}
	if(name == "Root") {
		return _root;
	}

	return _sceneStructure.at(name);
}

void OgreWrapper::RenderScene::Prueba () {
	Ogre::SceneNode* mLightNode = _manager->getRootSceneNode ()->createChildSceneNode ();
	Ogre::Light* mLight = _manager->createLight ();
	mLightNode->attachObject (mLight);

	mLight->setType (Ogre::Light::LT_DIRECTIONAL);
	mLight->setDiffuseColour (1, 1, 1);
	mLightNode->setDirection (-1, -1, -1);

	/*Ogre::Camera* cam = _manager->createCamera ("Cam");
	cam->setNearClipDistance (1);
	cam->setFarClipDistance (10000);
	cam->setAutoAspectRatio (true);*/
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	/*Ogre::SceneNode* mCamNode = _manager->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject (cam);

	vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));

	mCamNode->translate (0, 0, 1000);
	mCamNode->lookAt (Ogre::Vector3 (0, 0, 0), Ogre::Node::TS_WORLD);*/
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1)); 

	Node* mCamNode = CreateNode ("CamNode");
	Camera* cam = new Camera (_manager->createCamera ("cam"));

	mCamNode->Attach (cam);

	mCamNode->Translate (0, 0, 1000);
	mCamNode->LookAt (0, 0, 0);
	vp = cam->GetViewport();

	Ogre::SceneNode* mCubeNode = _manager->getRootSceneNode ()->createChildSceneNode ();
	Ogre::Entity* cube = _manager->createEntity ("cube.mesh");
	//cube->setMaterialName ("LocoMotor/blanco");
	mCubeNode->attachObject (cube);

	//CreateNode ("HolaMundo");
}

