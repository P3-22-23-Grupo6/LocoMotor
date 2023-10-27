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
#include "OgreStaticGeometry.h"
#include <OgreShaderGenerator.h>
#include <iostream>
#include <Ogre.h>
#include <OgreOverlaySystem.h>

OgreWrapper::RenderScene::RenderScene(Ogre::SceneManager* scene) {
	_manager = scene;
	_mainCam = nullptr;
	_root = new OgreWrapper::Node(scene->getRootSceneNode(), "root");
	_canvas = new OgreWrapper::Canvas();
	_canvas->Init(_manager);
	_stGeom = _manager->createStaticGeometry("st");
	lastCamZOrder = 0;
	SetSkybox();
}

Ogre::SceneManager* OgreWrapper::RenderScene::GetMan() {
	return _manager;
}


OgreWrapper::RenderScene::~RenderScene() {
	delete _root;
	delete _canvas;
	using iterador = std::map<std::string, Node*>::iterator;
	for (iterador it = _sceneStructure.begin(); it != _sceneStructure.end(); it = _sceneStructure.erase(it)) {
		delete it->second;
	}
}

void OgreWrapper::RenderScene::Deactivate() {
	_manager->destroyAllCameras();
	_manager->destroyAllParticleSystems();
}

void OgreWrapper::RenderScene::Render() {
	if(_mainCam!=nullptr)
	_mainCam->GetViewport()->update();
}

void OgreWrapper::RenderScene::SetSkybox() {
	//_manager->setSkyBox(true, "SkyBoxBlue");
	//6_manager->setFog(Ogre::FOG_EXP, Ogre::ColourValue(0.174509f, 0.182f, 0.2215f, 1), 0.002f, 300, 500);
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode(std::string name) {
	if (_sceneStructure.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	Node* node = _root->CreateChild(name);
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
	Node* node = GetNode(name)->CreateChild(name);
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

void OgreWrapper::RenderScene::DestroyNode(std::string name) {
	if (_sceneStructure.count(name) == 0 || name == "Root") {
		std::cerr << "No node with the name " << name << " found\n";
	}
	else {
		_root->DestroyChild(_sceneStructure[name]);
		_sceneStructure.erase(name);
	}
}

OgreWrapper::Canvas* OgreWrapper::RenderScene::GetCanvas() {
	return _canvas;
}

OgreWrapper::Light* OgreWrapper::RenderScene::CreateLight() {
	return new Light(_manager->createLight(), Ogre::Light::LT_DIRECTIONAL);
}

OgreWrapper::Renderer3D* OgreWrapper::RenderScene::CreateRenderer(std::string mesh) {
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh))
		return new Renderer3D(_manager->createEntity(mesh));
	else
		return nullptr;
}

OgreWrapper::Renderer3D* OgreWrapper::RenderScene::CreateStaticRenderer(std::string mesh, OgreWrapper::Node* meshNode) {
	Ogre::Entity* ent;
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh))
		ent = _manager->createEntity(mesh);
	else 
		return nullptr;
	_stGeom->addEntity(ent, Ogre::Vector3(meshNode->GetPosition_X(), 
					   meshNode->GetPosition_Y(), 
					   meshNode->GetPosition_Z()), 
					   Ogre::Quaternion(meshNode->GetRotation_W(),
					   meshNode->GetRotation_X(),
					   meshNode->GetRotation_Y(),
					   meshNode->GetRotation_Z()),
					   Ogre::Vector3(meshNode->GetScale_X(),
					   meshNode->GetScale_Y(),
					   meshNode->GetScale_Z()));
	return new Renderer3D(ent);
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
	if (_manager->hasParticleSystem(name))
		return nullptr;
	auto part = Ogre::ParticleSystemManager::getSingletonPtr()->getTemplate(filename);
	if (part != nullptr)
		return new ParticleHelper(_manager->createParticleSystem(name, filename));
	return nullptr;
}