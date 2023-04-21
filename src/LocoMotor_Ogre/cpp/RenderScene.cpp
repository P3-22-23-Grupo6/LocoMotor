#include "RenderScene.h"
#include "OgreManager.h"
#include "Node.h"
#include "Renderer3D.h"
#include "Light.h"
#include "Camera.h"
#include "ParticleHelper.h"
#include "Canvas.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <iostream>
#include <Ogre.h>
//#include <OgreOverlayPrerequisites.h>

OgreWrapper::RenderScene::RenderScene(Ogre::SceneManager* scene) {
	_manager = scene;
	_mainCam = nullptr;
	_root = new OgreWrapper::Node(scene->getRootSceneNode());
	_canvas = new OgreWrapper::Canvas();
	_canvas->Init(_manager);
	//OverlayManager::getSingleton().createOverlayElement("Panel", "myNewPanel");
}

OgreWrapper::RenderScene::~RenderScene() {
	delete _root;
	delete _canvas;
	using iterador = std::map<std::string, Node*>::iterator;
	for (iterador it = _sceneStructure.begin(); it != _sceneStructure.end(); it = _sceneStructure.erase(it)) {
		delete it->second;
	}
}

void OgreWrapper::RenderScene::Render() {
	_mainCam->GetViewport()->update();
	// _canvas->Render();
}

void OgreWrapper::RenderScene::SetSkybox() {
	_manager->setSkyBox(true, "Racers/SkyBoxBlue", 300, true);
	//_manager->setSkyDome(true, "Racers/SkyBoxBlue", 5, 2);
	//_manager->setSkyPlane(true, Ogre::Plane(Ogre::Vector3::UNIT_Z, -20), "Racers/SkyBoxBlue", 1, 1, true, 1.0, 100, 100);
	
	//Para NIEBLA
	//Ogre::ColourValue fadeColour(0.8, 0.8, 1.0);
	//_mainCam->GetViewport()->setBackgroundColour(fadeColour);
	//_manager->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 5000, 7000);
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode(std::string name) {
	if (_sceneStructure.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	Node* node = _root->CreateChild();
	_sceneStructure.insert({ name,node });
	return node;
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode(std::string name, std::string parent) {
	if (_sceneStructure.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	else if (_sceneStructure.count(parent) == 0) {
		std::cerr << "No node with name " << name << " found. Could not create child\n";
		return nullptr;
	}
	else if (parent == "Root") {
		return CreateNode(name);
	}
	Node* node = GetNode(name)->CreateChild();
	return node;
}

OgreWrapper::Node* OgreWrapper::RenderScene::GetNode(std::string name) {
	if (_sceneStructure.count(name) == 0) {
		std::cerr << "No node with the name " << name << " found\n";
		return nullptr;
	}
	if (name == "Root") {
		return _root;
	}

	return _sceneStructure.at(name);
}

OgreWrapper::Light* OgreWrapper::RenderScene::CreateLight() {
	return new Light(_manager->createLight(), Ogre::Light::LT_DIRECTIONAL);
}

OgreWrapper::Renderer3D* OgreWrapper::RenderScene::CreateRenderer(std::string mesh) {
	return new Renderer3D(_manager->createEntity(mesh));
}

OgreWrapper::Camera* OgreWrapper::RenderScene::CreateCamera(std::string name) {
	return new Camera(_manager->createCamera(name));
}

void OgreWrapper::RenderScene::SetActiveCamera(OgreWrapper::Camera* cam) {
	_mainCam = cam;
}

OgreWrapper::Camera* OgreWrapper::RenderScene::GetMainCamera() {
	return _mainCam;
}

OgreWrapper::ParticleHelper* OgreWrapper::RenderScene::CreateParticleHelper(std::string name, std::string filename) {
	return new ParticleHelper(_manager->createParticleSystem(name, filename));
}

void OgreWrapper::RenderScene::Prueba() {
	//SET TEXTURE FILTERING A NONE
	Ogre::MaterialManager& matMan = Ogre::MaterialManager::getSingleton();
	matMan.setDefaultTextureFiltering(Ogre::TextureFilterOptions::TFO_BILINEAR);

	OgreWrapper::Node* mLightNode = CreateNode("Luz");
	OgreWrapper::Light* mLight = new Light(_manager->createLight(), Ogre::Light::LT_DIRECTIONAL);
	mLightNode->Attach(mLight);
	mLight->SetDiffuse(1, 1, 1);
	mLightNode->SetDirection(-1, -1, -1);
	//Road
	//OgreWrapper::Node* mTrackNode = CreateNode("Track");
	//OgreWrapper::Renderer3D* track = new Renderer3D(_manager->createEntity("map.mesh"));
	//mTrackNode->Attach(track);
	//mTrackNode->SetScale(0.7f, 0.7f, 0.7f);
	//mTrackNode->Rotate(-90, 0, 25);
}