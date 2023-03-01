#pragma once
#include "RenderEntity.h"

#include <OgreLight.h>
namespace OgreWrapper {
	class Light : public RenderEntity {
	public: 
		Light (Ogre::Light* l, Ogre::Light::LightTypes type);
		~Light();
		Ogre::MovableObject* GetMovObj ();
		void SetDiffuse (float x, float y, float z);
		void SetSpecular (float x, float y, float z);
	protected:
		Ogre::Light* _light;
	};
}

