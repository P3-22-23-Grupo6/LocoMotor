#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Node.h"
namespace Ogre {
	class Camera;
	class Viewport;
	struct Vector3;
}

namespace OgreWrapper {
	
	class Camera:public Node {
	public:

		Camera(Ogre::Camera* camera, Ogre::SceneNode* node);
		~Camera();

		void LookAt(const Ogre::Vector3& targetPoint);
		void Render ();
	
	private:
		Ogre::Camera* mCamera;
		Ogre::Viewport* vp;
	};
}
#endif

