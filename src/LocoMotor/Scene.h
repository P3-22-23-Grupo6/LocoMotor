#pragma once

#include <string>
#include <unordered_map>

namespace OgreWrapper {
	class Camera;
	class RenderScene;
	class Node;
}

namespace LM_Component {
	class Camera;
}

namespace LocoMotor {
	class GameObject;
	class Scene {
	public:

		Scene(std::string nombre);
		~Scene();
		void Start();

		void Update(float dt);
		void Render();

		//?
		void Deactivate();

		//Activate



		bool GetActiveStatus();

		std::string GetSceneName();

		void SetSceneCam(OgreWrapper::Camera* cam);


		GameObject* AddGameobject(std::string name);
		//void AddObject(GameObject* obj);

		GameObject* GetObjectByName(std::string name);

		OgreWrapper::RenderScene* GetRender();

		GameObject* GetCamera();

	private:
		//camera


		LM_Component::Camera* _currentCam;

		OgreWrapper::Camera* _cam;

		//nombre de la escena
		std::string _name;

		bool _isActiveScene = false;

		OgreWrapper::RenderScene* _renderScn;

		std::unordered_map<std::string, GameObject*> _gameObjList;

		OgreWrapper::Node* _nod;

		OgreWrapper::Node* _node;

		GameObject* camera_gObj;
		GameObject* ship_gObj;
	};
}