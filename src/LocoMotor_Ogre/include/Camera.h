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

		Camera(Ogre::Camera* camera);
		~Camera();

		Ogre::Viewport* GetViewport();
		Ogre::MovableObject* GetMovObj() override;

		void Render();

	private:
		static int _zOrder;
		int _mZOrder;
		Ogre::Camera* mCamera;
		Ogre::Viewport* vp;
	};
}
#endif

