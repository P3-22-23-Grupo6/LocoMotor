#ifndef _NODE_H_
#define _NODE_H_
namespace Ogre {
	class SceneNode;
	class MovableObject;
}

namespace OgreWrapper {
	class Node {
	public:
		Node (Ogre::SceneNode* node);
		~Node ();

		void Translate (float x, float y, float z);
		void Rotate (float x, float y, float z);
		void Scale (float x, float y, float z);

		void Attach (Ogre::MovableObject* obj);
	protected:
		Ogre::SceneNode* _node;
	};
}
#endif

