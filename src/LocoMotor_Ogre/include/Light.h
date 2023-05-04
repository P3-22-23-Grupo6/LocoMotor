#pragma once
#include "RenderEntity.h"

#include <OgreLight.h>
namespace OgreWrapper {
	class Light : public RenderEntity {
	public:
		Light(Ogre::Light* l, Ogre::Light::LightTypes type);
		~Light();
		Ogre::MovableObject* GetMovObj();
		/// @brief Sets the diffuse value of the light
		void SetDiffuse(float x, float y, float z);
		/// @brief Sets the specular value of the light
		void SetSpecular(float x, float y, float z);
	protected:
		Ogre::Light* _light;
	};
}

