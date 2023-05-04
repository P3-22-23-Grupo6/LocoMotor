#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "RenderEntity.h"
#include <OgreVector3.h>
namespace Ogre {
	class Camera;
	class Viewport;
}

namespace OgreWrapper {

	class Camera : public RenderEntity {
	public:

		Camera(Ogre::Camera* camera);
		~Camera();
		/// @brief Gets the viewport of the camera
		/// @return viewport
		Ogre::Viewport* GetViewport();
		/// @brief Gets the camera
		/// @return camera
		Ogre::MovableObject* GetMovObj() override;
		
		/// @brief Sets the Aspect Ratio to a new Viewport
		/// @param ratio The new aspect ratio
		void SetAspectRatio(Ogre::Real ratio);
		/// @brief Sets the FieldOfView of default Ogre Camera (in radian 1~1.6 aprox)
		/// @param newFOV value of the FOV
		void SetFOV(float newFOV);//Ogre::Radian radians);
		/// @brief Sets the viewport ratio to a specific one
		/// @param viewportIndex nº of viewport
		/// @param modeIndex -> 0 Normal Camera, 1=1º Cam PvP, 2= 2ª PvP
		void SetViewportRatio(int viewportIndex, int modeIndex);
		/// @brief Changes the ClippingPlane, for optimization
		/// @param nearDis nearest distance
		/// @param farDis furthest distance
		void SetClippingPlane(Ogre::Real nearDis, Ogre::Real farDis);
		/// @brief Updates the camera
		void Render();

	private:
		static int _zOrder;
		int _mZOrder;
		Ogre::Camera* _mCamera;
		Ogre::Viewport* _vp;
	};
}
#endif

