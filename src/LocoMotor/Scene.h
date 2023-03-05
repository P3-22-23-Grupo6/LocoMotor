#pragma once

#include <string>
#include <vector>

class Scene {
public:
	
	Scene(std::string nombre);
	~Scene();
	void Start();

	void Update();
	void Render();

	//?
	void Deactivate();

	//Activate



	bool GetActiveStatus();

	std::string GetSceneName();


	//void addGameObject();

private:
	//camera
	//Camera* _cam 

	//nombre de la escena
	std::string _name;

	bool _isActiveScene=false;

	//std::vector<Gameobject> _gameObjList

};