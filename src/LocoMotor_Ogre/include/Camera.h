#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "RenderEntity.h"
#include <OgreVector3.h>
namespace Ogre {
	class Camera;
	class Viewport;
	//typedef Vector3;
}

namespace OgreWrapper {

	class Camera : public RenderEntity {
	public:

		Camera(Ogre::Camera* camera, int cameraMode = 0);//0 Normal Camera, 1=1� Cam PvP, 2= 2� PvP
		~Camera();

		Ogre::Viewport* GetViewport();
		Ogre::MovableObject* GetMovObj() override;
		void SetAspectRatio(Ogre::Real ratio);
		void Render();

	private:
		static int _zOrder;
		int _mZOrder;
		Ogre::Camera* _mCamera;
		Ogre::Viewport* vp;
	};
}
#endif

