#include "MotorApi.h"
#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "InputManager.h"
#include "CheckML.h"
#include "PhysicsManager.h"
//Coroutine¿
#include <concepts>
#include <coroutine>
#include <exception>
#include <iostream>

#include "RenderScene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Node.h"
#include "LMSpline.h"
#include "Transform.h"
#include "Light.h"
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
#include "../../../projects/LocoMotor/Light.h"


using namespace LocoMotor;
using namespace PhysicsWrapper;
MotorApi::MotorApi() {
	_gameName = "";
}

void MotorApi::RegisterGame(const char* gameName) {
	_gameName = gameName;
	OgreWrapper::OgreManager::Init();
	std::string err = OgreWrapper::OgreManager::GetInstance()->Initialize(gameName);
	if (err != "") {
		LogSystem::GetInstance()->Save(0, err);
		_exit = true;
	}
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
	cmpFac->RegisterComponent<Light>("Light");
}

void MotorApi::MainLoop() {
	//If Ogre Manager was not initialize by a Registergame() call, it will be initialized with the name GAME DLL FAIL
	if (OgreWrapper::OgreManager::GetInstance() == nullptr) {
		OgreWrapper::OgreManager::Init();
		std::string err = OgreWrapper::OgreManager::GetInstance()->Initialize("GAME DLL FAIL");
		if (err != "") {
			LogSystem::GetInstance()->Save(0, err);
			_exit = true;
		}
	}
	float counter = 0.0f;
	//Gizmo Parent for child Testing
	GameObject* gizmoParent = _scnManager->AddObjectRuntime("gizmoParent");
	gizmoParent->AddComponent("MeshRenderer");
	gizmoParent->GetComponent<Transform>()->InitRuntime();
	gizmoParent->GetComponent<MeshRenderer>()->InitRuntime("SphereDebug.mesh");
	gizmoParent->GetTransform()->Start();
	GameObject* gizmoBillboard = _scnManager->AddObjectRuntime("gizmoBillboard");
	gizmoBillboard->AddComponent("Transform");
	gizmoBillboard->AddComponent("MeshRenderer");
	gizmoBillboard->GetComponent<Transform>()->InitRuntime(LMVector3(0, 2, 0));
	gizmoBillboard->GetComponent<MeshRenderer>()->InitRuntime("BillboardRacers.mesh", "m_TransImg");
	gizmoBillboard->GetTransform()->Start();
	gizmoParent->GetTransform()->AddChild(gizmoBillboard->GetTransform());
	//OgreWrapper::OgreManager::GetInstance()->FadeMaterial("m_Test00");
	while (!_exit) {
		counter++;
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

		if (counter < 2) {
			std::string gizmoName = "Gizmo" + std::to_string((int)counter);
			GameObject* gizmoObj = _scnManager->AddObjectRuntime(gizmoName);
			gizmoObj->AddComponent("Transform");
			gizmoObj->AddComponent("MeshRenderer");
			gizmoObj->GetComponent<Transform>()->InitRuntime(LMVector3(0, 0, 0), LMVector3(0, 180, 0));
			gizmoObj->GetComponent<MeshRenderer>()->InitRuntime("Gizmo_Axis.mesh");
			gizmoObj->GetTransform()->Start();
			gizmoParent->GetTransform()->AddChild(gizmoObj->GetTransform());
			//OgreWrapper::OgreManager::GetInstance()->RenderToImage();
		}
		gizmoParent->GetTransform()->SetPosition(LMVector3(4,2,-4));
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
