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

		Ogre::Viewport* GetViewport();
		Ogre::MovableObject* GetMovObj() override;
		//Cambia el Aspect Ratio para ajustarlo a un nuevo Viewport(pensado para el resize en multijugador, si lo hay jaja saludos)
		void SetAspectRatio(Ogre::Real ratio);
		//Cambia el FieldOfView de Ogre Camera por defecto(en radianes, de 1-1.6~aprox.)
		void SetFOV(float newFOV);//Ogre::Radian radians);
		void SetViewportRatio(int viewportIndex, int modeIndex);//0 Normal Camera, 1=1º Cam PvP, 2= 2ª PvP
		void SetTracking(bool shouldTrack, Ogre::SceneNode* nodeToTrack, const Ogre::Vector3& offset);//Test, no se utiliza
		//Cambia el Clipping Plane, para optimizacion
		void SetClippingPlane(Ogre::Real nearDis, Ogre::Real farDis);
		void Render();

	private:
		static int _zOrder;
		int _mZOrder;
		Ogre::Camera* _mCamera;
		Ogre::Viewport* _vp;
	};
}
#endif

