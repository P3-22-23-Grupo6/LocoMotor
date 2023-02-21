#ifndef _SCENE_H_
#define _SCENE_H_

namespace Ogre {
	class SceneManager;
	class SceneNode;
	class Camera;
	class Viewport;
}


namespace OgreWrapper {
	class Light;
	class Camera;
	class Renderer3D;

	class RenderScene {
	public:
		/// <summary>
		/// Creates a new Scene wrapping an Ogre::SceneManager object
		/// Do not call this, use OgreManager::createScene instead
		/// </summary>
		/// <param name="scene">Ogre::SceneManager to wrap</param>
		RenderScene (Ogre::SceneManager* scene);

		/// <summary>
		/// Destructor
		/// </summary>
		~RenderScene ();

		/// <summary>
		/// Genera una escena de prueba
		/// </summary>
		void Prueba ();

		/// <summary>
		/// Renders a frame from the active camera
		/// </summary>
		void Render ();

	private:
		Ogre::SceneManager* _manager;
		Ogre::Viewport* vp;
	};
}
#endif

