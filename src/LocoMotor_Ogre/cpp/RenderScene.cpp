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
//#include <OgreOverlayPrerequisites.h>

OgreWrapper::RenderScene::RenderScene(Ogre::SceneManager* scene) {
	_manager = scene;
	_mainCam = nullptr;
	_root = new OgreWrapper::Node(scene->getRootSceneNode(), "root");
	_canvas = new OgreWrapper::Canvas();
	_canvas->Init(_manager);
	_stGeom = _manager->createStaticGeometry("st");
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

void OgreWrapper::RenderScene::Deactivate() {
	_manager->destroyAllCameras();
	//_manager->destroyAllStaticGeometry();
}

void OgreWrapper::RenderScene::Render() {
	_mainCam->GetViewport()->update();
	// _canvas->Render();
}

void OgreWrapper::RenderScene::SetSkybox() {
	//_manager->setSkyBox(true, "Racers/SkyBoxBlue", 300, true);
	_manager->setSkyDome(true, "Racers/SkyBoxBlue", 5, 2);
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
	_root->DestroyChild(_sceneStructure[name]);
	_sceneStructure.erase(name);
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
	/*if (!_stGeom) {
	}*/
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