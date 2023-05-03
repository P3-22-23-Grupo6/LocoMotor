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
		Renderer3D(Ogre::StaticGeometry* rend);
		~Renderer3D();
		Ogre::MovableObject* GetMovObj() override;
		void SetMaterial(std::string mat);
		Ogre::Mesh* GetMesh();
		void SetVisible(bool visible);
	private:
		Ogre::Entity* _mesh;

	};
}
#endif //_RENDERER3D_H_

