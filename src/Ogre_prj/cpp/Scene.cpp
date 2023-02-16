#include "Scene.h"
#include <iostream>

OgreWrapper::Scene::Scene(Ogre::SceneManager* scene)
{
	mSM = scene;
}

OgreWrapper::Scene::~Scene()
{
	mSM->clearScene();
	
	
}

