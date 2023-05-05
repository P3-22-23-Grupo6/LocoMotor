#include "MotorApi.h"
#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "InputManager.h"
#include "CheckML.h"
#include "PhysicsManager.h"

#include "RenderScene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Node.h"
#include "LMSpline.h"
#include "Transform.h"
#include "ComponentsFactory.h"
#include "LogSystem.h"

#include "MeshRenderer.h"
#include <RigidBody.h>
#include <ParticleSystem.h>
#include <Camera.h>
#include "CallBackBullet.h"
#include "LmVectorConverter.h"
#include "UIImageLM.h"
#include "UITextLM.h"
#include "ScriptManager.h"
#include "LMVector.h"


using namespace LocoMotor;
using namespace PhysicsWrapper;
MotorApi::MotorApi() {
	_gameName = "";
}

void MotorApi::RegisterGame(const char* gameName) {
	_gameName = gameName;
	OgreWrapper::OgreManager::Init(gameName);
}

void MotorApi::Init() {
	LogSystem::Init();
	FmodWrapper::AudioManager::Init(8);
	PhysicsManager::Init();
	InputManager::Init();
	SceneManager::Init();
	_scnManager = LocoMotor::SceneManager::Init();
	ScriptManager::Init();
	PhysicsManager::GetInstance()->SetContactStartCallback(LMcontactStart);
	PhysicsManager::GetInstance()->SetContactProcessCallback(LMcontactProcessed);
	PhysicsManager::GetInstance()->SetContactEndedCallback(LMcontactExit);
	ComponentsFactory* cmpFac = ComponentsFactory::Init();
	cmpFac->RegisterComponent<AudioSource>("AudioSource");
	cmpFac->RegisterComponent<AudioListener>("AudioListener");
	cmpFac->RegisterComponent<Camera>("Camera");
	cmpFac->RegisterComponent<MeshRenderer>("MeshRenderer");
	cmpFac->RegisterComponent<ParticleSystem>("ParticleSystem");
	cmpFac->RegisterComponent<RigidBody>("RigidBodyComponent");
	cmpFac->RegisterComponent<Transform>("Transform");
	cmpFac->RegisterComponent<UITextLM>("UITextLM");
	cmpFac->RegisterComponent<UIImageLM>("UIImageLM");
}

void MotorApi::MainLoop() {
	//If Ogre Manager was not initialize by a Registergame() call, it will be initialized with the name GAME DLL FAIL
	OgreWrapper::OgreManager::Init("GAME DLL FAIL");

	while (!_exit) {

		if (_scnManager->GetCurrentScene() == nullptr) {
			LogSystem::GetInstance()->Save(0, "No scene has been loaded. Exiting now");
			break;
		}

		FmodWrapper::AudioManager::GetInstance()->Update(_scnManager->GetDelta());
		OgreWrapper::OgreManager::GetInstance()->Render();
		PhysicsManager::GetInstance()->Update(_scnManager->GetDelta());

		if (LocoMotor::InputManager::GetInstance()->RegisterEvents())
			break;

		_scnManager->Update();
	}

	SceneManager::Clear();
	PhysicsManager::Clear();
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	ScriptManager::Clear();
	InputManager::Clear();
	ComponentsFactory::Clear();
	LogSystem::Clear();
	return;
}
