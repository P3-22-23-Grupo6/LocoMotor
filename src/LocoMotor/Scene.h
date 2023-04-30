#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
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
	class MOTOR_API Scene {
	public:

		Scene(std::string nombre);
		~Scene();
		void Start();

		void Update(float dt);
		void Render();

		//?
		void DeActivate();

		//Activate



		bool GetActiveStatus();

		std::string GetSceneName();

		void SetSceneCam(OgreWrapper::Camera* cam);


		GameObject* AddGameobject(std::string name);
		//void AddObject(GameObject* obj);

		GameObject* GetObjectByName(std::string name);

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