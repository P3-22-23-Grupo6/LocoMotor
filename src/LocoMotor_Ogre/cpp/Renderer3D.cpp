#include "Renderer3D.h"
#include <OgreEntity.h>

OgreWrapper::Renderer3D::Renderer3D(Ogre::Entity* rend) {
	_mesh = rend;
	_mesh->getMesh();
}

OgreWrapper::Renderer3D::Renderer3D(Ogre::StaticGeometry* rend) {
	//_mesh = rend;
	//_mesh->getMesh();
}

OgreWrapper::Renderer3D::~Renderer3D() {
}

Ogre::MovableObject* OgreWrapper::Renderer3D::GetMovObj() {
	return _mesh;
}

void OgreWrapper::Renderer3D::SetMaterial(std::string mat) {
	_mesh->setMaterialName(mat);
}

Ogre::Mesh* OgreWrapper::Renderer3D::GetMesh() {
	return _mesh->getMesh().get();
}