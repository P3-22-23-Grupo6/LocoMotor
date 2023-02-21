#include "Scene.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

OgreWrapper::RenderScene::RenderScene (Ogre::SceneManager* scene) {
	_manager = scene;
}

OgreWrapper::RenderScene::~RenderScene () {
	_manager->clearScene ();
}

void OgreWrapper::RenderScene::Render () {

}

