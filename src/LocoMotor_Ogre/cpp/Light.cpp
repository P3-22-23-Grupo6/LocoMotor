#include "Light.h"

OgreWrapper::Light::Light (Ogre::Light* l, Ogre::Light::LightTypes type) {
	_light = l;
	_light->setType (type);
}

OgreWrapper::Light::~Light () {
}

Ogre::MovableObject* OgreWrapper::Light::GetMovObj () {
	return _light;
}

void OgreWrapper::Light::SetDiffuse (float r, float g, float b) {
	_light->setDiffuseColour (r, g, b);
}

void OgreWrapper::Light::SetSpecular (float r, float g, float b) {
	_light->setSpecularColour (r, g, b);
}
