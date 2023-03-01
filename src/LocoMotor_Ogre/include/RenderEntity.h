#pragma once

#ifndef _RENDERENTITY_H_
#define _RENDERENTITY_H_

#include "Node.h"

namespace OgreWrapper {
	class RenderEntity {
	public:
		virtual ~RenderEntity () = default;
		virtual Ogre::MovableObject* GetMovObj () = 0;
		void SetNode (Node* n) {
			_node = n;
		}
	protected:
		Node* _node;
	};
}

#endif // !_RENDERENTITY_H_