#pragma once

#ifndef _RENDERER3D_H_
#define _RENDERER3D_H_

#include "RenderEntity.h"

namespace Ogre {
	class Entity;
}
namespace OgreWrapper {
	class Renderer3D : public RenderEntity {
	public:
		Renderer3D(Ogre::Entity* rend);
		~Renderer3D();
		Ogre::MovableObject* GetMovObj() override;
		/// @brief Sets the mesh material
		void SetMaterial(std::string mat);
		/// @brief Gets the mesh 
		Ogre::Mesh* GetMesh();
		/// @brief Sets the mesh vibility
		void SetVisible(bool visible);
	private:
		Ogre::Entity* _mesh;

	};
}
#endif //_RENDERER3D_H_

