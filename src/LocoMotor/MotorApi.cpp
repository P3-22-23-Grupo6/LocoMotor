#include "MotorApi.h"
#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "InputManager.h"
#include "CheckML.h"
#include "PhysicsManager.h"
#include "BulletRigidBody.h"
#include "lmVector.h"
#include "RenderScene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Node.h"
#include "ComponentsFactory.h"

#include "MeshRederer.h"
#include <RigidBodyComponent.h>
#include <ParticleSystem.h>
#include <Checkpoint.h>
#include <Camera.h>

using namespace LocoMotor;
using namespace PhysicsWrapper;
MotorApi::MotorApi() {
	_gameName = "";
}

void MotorApi::init() {
	auto audio = FmodWrapper::AudioManager::Init(8);
	audio->AddSound("Assets/si.wav");
	////new int();
	OgreWrapper::OgreManager::Init(_gameName);
	//OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::GetInstance();
	//OgreWrapper::RenderScene* x = man->CreateScene("Escena");
	//x->Prueba();
	//man->SetActiveScene(x);
	//std::cout << (x == nullptr ? "null\n" : "jiji\n");
	PhysicsManager::Init();
	auto btmngr = PhysicsManager::GetInstance();
	//RigidBodyInfo info1;
	//info1.boxSize = btVector3(50, 50, 50);
	//info1.mass = 0.0f;
	//info1.origin = btVector3(0, -50, 0);
	//btmngr->CreateRigidBody(info1);
	//RigidBodyInfo info2;
	//info2.size = 1.0;
	//info2.mass = 1.0f;
	//info2.origin = btVector3(2, 10, 0);
	//BulletRigidBody* bola = btmngr->CreateRigidBody(info2);

	LocoMotor::SceneManager* mSM = new LocoMotor::SceneManager();
	mSM->CreateScene("Escena");
	mSM->ChangeScene("Escena");


	//audioSrc.PlaySound(0, -1);

	InputManager* input = InputManager::Get();


	//LocoMotor::GameObject* gObj = new LocoMotor::GameObject();

	//gObj->AddComponent<LocoMotor::AudioListener>();
	//gObj->AddComponent<LocoMotor::AudioSource>();

	float frc = 1;
	// Activa la variable de uso del giroscopio, en el momento en el que detecte el mando, 
	// intentara activar el giroscopio automaticamente si el mando conectado tiene giroscopio
	input->ActivateGyroscopeWhenConnected();
	while (true) {

		// INPUT
		if (input->RegisterEvents())
			break;
		bool buttonPressed = input->GetKeyDown(SDL_SCANCODE_A);

		if (input->GetKey(SDL_SCANCODE_A) || input->GetButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
			frc += 0.005f;
		}
		else if (input->GetKey(SDL_SCANCODE_S) || input->GetButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
			frc -= 0.005f;
		}
		float variation = frc + ((float(std::rand() % 11) - 5) / 300.f);
		//audioSrc.SetSoundFreq(0, frc);
		// std::cout << frc << std::endl;

		// AUDIO
		// list.Prueba(.05f);
		audio->Update(0.0f);
		//bola->setRotation(bola->getRotation() + LMQuaternion(0, 0.1, 0, 0));

		// RENDER
		//man->Render();
		btmngr->Update();
		mSM->Update();
		// DEMO TECNICA

		// Giroscopio
		float currentGyroscope = input->GetGyroscopeAngle(InputManager::Horizontal);
		//std::cout << "GIROSCOPIOSSS = " << currentGyroscope << "\n";

		// Clampear valor
		float intensity = abs(currentGyroscope);
		if (intensity > 1) intensity = 1;

		// Vibrar mando
		//if (currentGyroscope > .3 || currentGyroscope < -.3)
		//	InputManager::Get()->RumbleController(intensity, .01);

		// Color LED
		input->SetControllerLedColor(intensity * 255, 0, (1 - intensity) * 255);

		if (input->controllerConnected() && input->GetButtonDown(SDL_CONTROLLER_BUTTON_X)) {
			//gObj->GetComponent<LocoMotor::AudioSource>()->Play(0);
		}
	}
	delete mSM;
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	PhysicsManager::Clear();
	InputManager::Destroy();
}

void MotorApi::RegisterGame(const char* gameName) {
	_gameName = gameName;
	OgreWrapper::OgreManager::Init(gameName); 

	auto _mScene = _scnManager->CreateScene("Escena");

#pragma region Escena que teniamos antes

	auto _renderScn = _mScene->GetRender();

	auto map = _mScene->AddGameobject("map");
	map->AddComponent("MeshRenderer");
	map->GetComponent<MeshRenderer>()->Start("map", "Track.mesh", "FalconRedone/FalconMat");
	map->AddComponent("RigidBodyComponent");
	map->GetComponent<RigidBodyComponent>()->Start(0);
	map->AddComponent("PlayerController");

	auto ship_gObj = _mScene->AddGameobject("ship");
	ship_gObj->AddComponent("MeshRenderer");
	ship_gObj->GetComponent<MeshRenderer>()->Start("ship", "BlueFalcon.mesh", "FalconRedone/FalconMat");
	ship_gObj->AddComponent("ParticleSystem");
	//ship_gObj->AddComponent<ParticleSystem>("fire", _mScene->GetRender(), "Racers/Fire");

	ship_gObj->AddComponent("RigidBodyComponent");
	ship_gObj->GetComponent<RigidBodyComponent>()->Start(1);
	//_gameObjList.push_back(ship_gObj);

	//ship_gObj->SetRigidBody(PhysicsWrapper::PhysicsManager::GetInstance()->CreateRigidBody(rb));
	//rend->SetMaterial("Racers/Falcon");
	ship_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	//ship_gObj->GetNode()->SetPosition(0, 1000.0f, 0);
	ship_gObj->SetPosition(LMVector3(0, 10, 0));
	ship_gObj->setMovable(true);


	//// CHECKPOINT

	//GameObject* checkpoint = _mScene->AddGameobject("checkpoint");
	//checkpoint->AddComponent<MeshRenderer>("checkpoint", "BlueFalcon.mesh", "FalconRedone/FalconMat", _renderScn);
	//checkpoint->AddComponent<RigidBodyComponent>(0);
	//checkpoint->GetNode()->SetScale(60.0f, 10.0f, 10.0f);
	//checkpoint->SetPosition(LMVector3(0, 5, -50));
	//checkpoint->AddComponent<Checkpoint>(ship_gObj, 0);



	_renderScn->Prueba();
	//Skybox
	_renderScn->SetSkybox();


#pragma endregion

	_scnManager->ChangeScene("Escena");

#pragma region All Components Started

	_mScene->GetCamera()->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 15, 65));

	map->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
	map->GetComponent<RigidBodyComponent>()->setStatic();
#pragma endregion

}

void MotorApi::Init() {
	FmodWrapper::AudioManager::Init(8);
	PhysicsManager::Init();
	InputManager::Get();
	_scnManager = new LocoMotor::SceneManager();

	auto cmpFac = ComponentsFactory::Init();
	cmpFac->RegisterComponent<AudioSource>("AudioSource");
	cmpFac->RegisterComponent<AudioListener>("AudioListener");
	cmpFac->RegisterComponent<Camera>("Camera");
	cmpFac->RegisterComponent<Checkpoint>("Checkpoint");
	cmpFac->RegisterComponent<MeshRenderer>("MeshRenderer");
	cmpFac->RegisterComponent<ParticleSystem>("ParticleSystem");
	cmpFac->RegisterComponent<RigidBodyComponent>("RigidBodyComponent");
}

void MotorApi::MainLoop() {
	OgreWrapper::OgreManager::Init("GAME DLL FAIL");
	while (!_exit) {

		FmodWrapper::AudioManager::GetInstance()->Update(0.0f);
		OgreWrapper::OgreManager::GetInstance()->Render();
		PhysicsManager::GetInstance()->Update();
		if (InputManager::Get()->RegisterEvents())
			break;

		_scnManager->Update();
	}
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	PhysicsManager::Clear();
	InputManager::Destroy();
	ComponentsFactory::Clear();
	delete _scnManager;
	return;
}
