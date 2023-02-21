#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <OgreCamera.h>
#include <OgreSceneNode.h>

namespace OgreWrapper {

	class Camera {
	public:

		Camera(Ogre::Camera* camera, Ogre::SceneNode* node);
		~Camera();
	
	private:
		Ogre::SceneNode* mNode;
		Ogre::Camera* mCamera;

	};
}
#endif

