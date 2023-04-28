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

		Camera(Ogre::Camera* camera, int cameraMode = 0);//0 Normal Camera, 1=1º Cam PvP, 2= 2ª PvP
		~Camera();

		Ogre::Viewport* GetViewport();
		Ogre::MovableObject* GetMovObj() override;
		//Cambia el Aspect Ratio para ajustarlo a un nuevo Viewport(pensado para el resize en multijugador, si lo hay jaja saludos)
		void SetAspectRatio(Ogre::Real ratio);
		//Cambia el FieldOfView de Ogre Camera por defecto(en radianes, de 1-1.6~aprox.)
		void SetFOV(float newFOV);//Ogre::Radian radians);
		void Render();

	private:
		static int _zOrder;
		int _mZOrder;
		Ogre::Camera* _mCamera;
		Ogre::Viewport* vp;
	};
}
#endif

