#pragma once

#ifndef _RENDERENTITY_H_
#define _RENDERENTITY_H_


#include <OgreMovableObject.h>

namespace OgreWrapper {
	class RenderEntity {
	public:
		virtual ~RenderEntity() = default;
		virtual Ogre::MovableObject* GetMovObj() = 0;
	};
}

#endif //_RENDERENTITY_H_