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
#include <EnemyAI.h>
#include "CallBackBullet.h"
#include "LmVectorConverter.h"
#include "UIImageLM.h"
#include "UITextLM.h"
#include "ScriptManager.h"
#include "LMVector.h"
//#include <tweeners/builder.hpp>
//#include <tweeners/easing.hpp>
//#include <tweeners/system.hpp>

using namespace LocoMotor;
using namespace PhysicsWrapper;
MotorApi::MotorApi() {
	_gameName = "";
}

void MotorApi::RegisterGame(const char* gameName) {
	_gameName = gameName;
	OgreWrapper::OgreManager::Init(gameName);

	Scene* _mScene = _scnManager->CreateScene("Escena");

#pragma region Escena que teniamos antes

	OgreWrapper::RenderScene* _renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene("Escena");

#pragma region Manager responsable del gameplay
	LocoMotor::GameObject* raceManager_gObj = _mScene->AddGameobject("raceManager");
	raceManager_gObj->AddComponent("Transform");
	Component* cmp = raceManager_gObj->AddComponent("RaceManager");
	//	raceManager_gObj->AddComponent("UITextLM");
	//// TODO: cargar fuentes sin necesidad de .fontdef aka que esto funcione:
	//// ship_gObj->GetComponent<UITextLM>()->SetFont("BrunoAceSC-Regular.ttf");
	//	raceManager_gObj->GetComponent<UITextLM>()->SetPosition(-0.45, .9);
	//	raceManager_gObj->GetComponent<UITextLM>()->AlignLeft();
	//	
	//	raceManager_gObj->GetComponent<UITextLM>()->ChangeText("X / 3");
	//	raceManager_gObj->GetComponent<UITextLM>()->SetSize(0.1, 0.1);
#pragma endregion


#pragma region UI
	raceManager_gObj->AddComponent("UITextLM");
	raceManager_gObj->GetComponent<UITextLM>()->SetFont("BrunoAce");
	raceManager_gObj->GetComponent<UITextLM>()->SetPosition(0.45, .05);
	raceManager_gObj->GetComponent<UITextLM>()->AlignRight();
	raceManager_gObj->GetComponent<UITextLM>()->ChangeText("0 fps");
	raceManager_gObj->GetComponent<UITextLM>()->SetSize(0.05, 0.05);
	raceManager_gObj->GetComponent<UITextLM>()->SetBottomColor(0, 0, 0);
	raceManager_gObj->GetComponent<UITextLM>()->SetTopColor(0, 0, 0);

	raceManager_gObj->AddComponent("AudioSource");
	raceManager_gObj->GetComponent<AudioSource>()->Set2D();

	LocoMotor::GameObject* lapsText_gObj = _mScene->AddGameobject("lapsText");
	lapsText_gObj->AddComponent("Transform");

	lapsText_gObj->AddComponent("UITextLM");
	lapsText_gObj->GetComponent<UITextLM>()->SetFont("BrunoAce");
	lapsText_gObj->GetComponent<UITextLM>()->SetPosition(-0.45, .9);
	lapsText_gObj->GetComponent<UITextLM>()->AlignLeft();
	lapsText_gObj->GetComponent<UITextLM>()->ChangeText("0 / 3");
	lapsText_gObj->GetComponent<UITextLM>()->SetSize(0.1, 0.1);
	lapsText_gObj->GetComponent<UITextLM>()->SetBottomColor(1, 1, 1);
	lapsText_gObj->GetComponent<UITextLM>()->SetTopColor(1, 1, 1);

	LocoMotor::GameObject* positionText_gObj = _mScene->AddGameobject("positionText");
	positionText_gObj->AddComponent("Transform");
	positionText_gObj->AddComponent("UITextLM");
	positionText_gObj->GetComponent<UITextLM>()->SetFont("BrunoAce");
	positionText_gObj->GetComponent<UITextLM>()->SetPosition(0.45, .9);
	positionText_gObj->GetComponent<UITextLM>()->AlignRight();
	positionText_gObj->GetComponent<UITextLM>()->ChangeText("1�st");
	positionText_gObj->GetComponent<UITextLM>()->SetSize(0.1, 0.1);
	positionText_gObj->GetComponent<UITextLM>()->SetBottomColor(1, 1, 1);
	positionText_gObj->GetComponent<UITextLM>()->SetTopColor(1, 1, 1);

	LocoMotor::GameObject* countdownText_gObj = _mScene->AddGameobject("countdownText");
	countdownText_gObj->AddComponent("Transform");
	countdownText_gObj->AddComponent("UITextLM");
	countdownText_gObj->GetComponent<UITextLM>()->SetFont("Heavitas");
	countdownText_gObj->GetComponent<UITextLM>()->SetPosition(0, .3);
	countdownText_gObj->GetComponent<UITextLM>()->AlignCenter();
	countdownText_gObj->GetComponent<UITextLM>()->SetSize(0.15, 0.15);
	countdownText_gObj->GetComponent<UITextLM>()->SetBottomColor(1, 1, 1);
	countdownText_gObj->GetComponent<UITextLM>()->SetTopColor(1, 1, 1);
#pragma endregion 

#pragma region RaceTrack
	//Boost
	auto boost = _mScene->AddGameobject("boost");
	boost->AddComponent("Transform");
	boost->AddComponent("MeshRenderer");
	boost->GetComponent<MeshRenderer>()->Start("boost", "TurboTestMesh.mesh", "", true);
	boost->AddComponent("RigidBodyComponent");
	boost->GetComponent<RigidBody>()->Start(0);
	//boost->AddComponent("Boost");
	Component* cmpBoost = boost->AddComponent("Boost");
	//Track Main Road
	auto trackMain = _mScene->AddGameobject("trackMain");
	trackMain->AddComponent("Transform");
	trackMain->AddComponent("MeshRenderer");
	trackMain->GetComponent<MeshRenderer>()->Start("trackMain", "AllTrack.mesh", "", true);
	trackMain->AddComponent("RigidBodyComponent");
	trackMain->GetComponent<RigidBody>()->Start(0);
	//Temporary SkyBox
	auto skyboxMesh = _mScene->AddGameobject("skyboxMesh");
	skyboxMesh->AddComponent("Transform");
	skyboxMesh->AddComponent("MeshRenderer");
	skyboxMesh->GetComponent<MeshRenderer>()->Start("skyboxMesh", "SkyboxMesh.mesh", "", true);
	//Enviroment
	//auto firstArea = _mScene->AddGameobject("firstArea");
	//firstArea->AddComponent("Transform");
	//firstArea->AddComponent("MeshRenderer");
	//firstArea->GetComponent<MeshRenderer>()->Start("firstArea", "FirstArea.mesh", "", true);

	//Sea and Sky
	//auto terrain = _mScene->AddGameobject("terrain");
	//terrain->AddComponent("Transform");
	//terrain->AddComponent("MeshRenderer");
	//terrain->GetComponent<MeshRenderer>()->Start("terrain", "Terrain.mesh", "", true);
#pragma endregion

	ship_gObj = _mScene->AddGameobject("ship");
	ship_gObj->AddComponent("Transform");
	ship_gObj->AddComponent("ParticleSystem");

	ship_gObj->AddComponent("RigidBodyComponent");
	ship_gObj->GetComponent<RigidBody>()->Start(1);

	//ship_gObj->GetNode()->SetPosition(0, 1000.0f, 0);
	ship_gObj->AddComponent("PlayerController");

	ship_gObj->AddComponent("MeshRenderer");
	ship_gObj->GetComponent<MeshRenderer>()->Start("ship", "BlueFalcon.mesh", "");// or BlueFalconAlt.mesh
	ship_gObj->AddComponent("AudioSource");
	ship_gObj->GetComponent<AudioSource>()->Start();


	LocoMotor::GameObject* velocityText_gObj = _mScene->AddGameobject("velocityText");
	velocityText_gObj->AddComponent("Transform");

	velocityText_gObj->AddComponent("UITextLM");
	velocityText_gObj->GetComponent<UITextLM>()->SetFont("BrunoAce");
	velocityText_gObj->GetComponent<UITextLM>()->SetPosition(-0.45, .1);
	velocityText_gObj->GetComponent<UITextLM>()->AlignLeft();
	velocityText_gObj->GetComponent<UITextLM>()->ChangeText("300 km/h");
	velocityText_gObj->GetComponent<UITextLM>()->SetSize(0.1, 0.1);
	velocityText_gObj->GetComponent<UITextLM>()->SetBottomColor(1, 1, 1);
	velocityText_gObj->GetComponent<UITextLM>()->SetTopColor(1, 1, 1);


	// CHECKPOINTS
	//raceManager_gObj->GetComponent<RaceManager>()->Start();


	const int numberOfCheckpoints = 4;
	LMVector3 checkpointPositions[numberOfCheckpoints];

	checkpointPositions[0] = LMVector3(-613.7f, 77.f, -513.4f);
	checkpointPositions[1] = LMVector3(-827.8f, -35.3f, 204.9f);
	checkpointPositions[2] = LMVector3(-63.7f, 71.5f, 688.5f);
	checkpointPositions[3] = LMVector3(-1.6f, 7.6f, 56.2f);


	std::vector<GameObject*> lsBalls = std::vector<GameObject*>();

	for (size_t i = 0; i < numberOfCheckpoints; i++) {

		std::string checkpointName = "checkP" + i;
		LocoMotor::GameObject* checkpoint_gObj = _mScene->AddGameobject(checkpointName);
		checkpoint_gObj->AddComponent("Transform");
		checkpoint_gObj->AddComponent("MeshRenderer");
		checkpoint_gObj->GetComponent<MeshRenderer>()->Start(checkpointName, "SphereDebug.mesh", "", true);
		checkpoint_gObj->GetTransform()->SetSize(LMVector3(40, 40, 40));
		checkpoint_gObj->GetTransform()->SetPosition(checkpointPositions[i]);
		Component* checkpointComp = checkpoint_gObj->AddComponent("Checkpoint");
		lsBalls.push_back(checkpoint_gObj);
	}

#pragma region SPLINE
	//Difference when converting units from Blender to OgreMesh space
	float blenderScale = 20.0f;
	std::vector<LMVector3> positionsList //Estoy tomando medidas con el archivo de Blender, aun no puedo exportar posiciones
	{
		LMVector3(2, 1, -8) * blenderScale,
		LMVector3(2, 1, -27) * blenderScale,
		LMVector3(2, 1,-44) * blenderScale,
		LMVector3(2, 4,-57) * blenderScale,
		LMVector3(-0.7f, 10,-68) * blenderScale,
		LMVector3(-8.7f, 16,-78) * blenderScale,
		LMVector3(-21.75f, 16,-75) * blenderScale,
		LMVector3(-34.75f, 13,-71) * blenderScale,
		LMVector3(-40, 10,-63) * blenderScale,
		LMVector3(-41.75f, 4,-53) * blenderScale,
		LMVector3(-42, 1,-43) * blenderScale,
		LMVector3(-42.5f, -0.3f,-34) * blenderScale,
		LMVector3(2, 1, -8) * blenderScale
	};

	LocoMotor::Spline* nuevaSpl = new LocoMotor::Spline();
	nuevaSpl->SetAutoCalc(true);
	for (int i = 0; i < positionsList.size(); i++) {
		nuevaSpl->AddPoint(LMVector3(positionsList[i]));
		auto wayPoint = _mScene->AddGameobject("WayPoint" + i);
		wayPoint->AddComponent("Transform");
		wayPoint->AddComponent("MeshRenderer");
		wayPoint->GetComponent<MeshRenderer>()->Start("WayPoint" + i, "SphereDebug.mesh", "", true);
		wayPoint->SetPosition(LMVector3(positionsList[i]));
		wayPoint->SetScale(LMVector3(5, 5, 5));
	}

	for (int i = 0; i < 1; i++) {
		std::string enemyName = "Enemy" + std::to_string(i);
		//std::string enemyName = "Enemy0";
		GameObject* enemy_gObj = _mScene->AddGameobject(enemyName);
		enemy_gObj->AddComponent("Transform");
		enemy_gObj->AddComponent("MeshRenderer");
		enemy_gObj->GetComponent<MeshRenderer>()->Start(enemyName, "EnemyCar.mesh", "FalconRedone/FalconMat");
		enemy_gObj->AddComponent("AudioSource");
		enemy_gObj->GetComponent<AudioSource>()->Start();
		enemy_gObj->GetComponent<AudioSource>()->Play("Assets/Sounds/engine2.wav", -1);
		enemy_gObj->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
		enemy_gObj->SetPosition(LMVector3(-70 + i * 35, 3.0f, -80));

		enemy_gObj->AddComponent("EnemyAI");
		enemy_gObj->GetComponent<EnemyAI>()->Start(nuevaSpl, -70.f + i * 35.f);
	}

	std::vector<GameObject*> waypointBalls = std::vector<GameObject*>();

	//NO QUITAR AUN HASTA QUE ESTE LA SPLINE
	//int maxBalls = 300;
	//for (float i = 1; i < maxBalls; i++) {
	//	auto wayPointNew = _mScene->AddGameobject("WayPointProc" + std::to_string(i));
	//	wayPointNew->AddComponent("Transform");
	//	wayPointNew->AddComponent("MeshRenderer");
	//	wayPointNew->GetComponent<MeshRenderer>()->Start("WayPointProc" + std::to_string(i), "DebugSphere2.mesh", "");
	//	//nuevaSpl->RecalcTangents();
	//	waypointBalls.push_back(wayPointNew);
	//}

#pragma endregion

	_scnManager->StartScene(_mScene);

	ship_gObj->SetPosition(LMVector3(0, 30, 0));
	ship_gObj->GetComponent<RigidBody>()->SetFriction(0.f);
	trackMain->SetPosition(LMVector3(0, 0, 0));
	//firstArea->SetPosition(LMVector3(0, -10, 0));
	boost->SetPosition(LMVector3(80, 0, -120));
	ship_gObj->SetScale(LMVector3(10.0f, 10.0f, 10.0f));

	//for (int i = 1; i < numberOfCheckpoints; i++) {
	//	lsBalls[i]->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
	//	lsBalls[i]->SetPosition(checkpointPositions[i]);
	//}
	//for (int i = 1; i < waypointBalls.size(); i++) {
	//	waypointBalls[i]->SetScale(LMVector3(3.0f, 3.0f, 3.0f));
	//	waypointBalls[i]->SetPosition(nuevaSpl->Interpolate((float) i / maxBalls));
	//}

#pragma region All Components Started

	_mScene->GetCamera()->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 15, 45));
	//_mScene->GetCamera()->GetComponent<Camera>()->SetFOV(60);
	_mScene->GetCamera()->GetComponent<Camera>()->SetClippingPlane(1, 8000);

	raceManager_gObj->GetComponent<AudioSource>()->SetVolume(0.1f);
	raceManager_gObj->GetComponent<AudioSource>()->Play("Assets/Sounds/mainTheme.mp3", -1, 17105, 214244);
	raceManager_gObj->GetComponent<AudioSource>()->SetFreq("Assets/Sounds/mainTheme.mp3", 0.98f);
	ship_gObj->GetComponent<AudioSource>()->Play("Assets/Sounds/engine.wav", -1);
	trackMain->GetComponent<RigidBody>()->UseItAsRaycast();
	//trackBorder->GetComponent<RigidBodyComponent>()->SetCollisionGroup(6);
	//Debug01->GetComponent<RigidBodyComponent>()->SetCollisionGroup(6);
	boost->GetComponent<RigidBody>()->beATrigger();
	//waterPlane->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));


#pragma endregion
}

void MotorApi::Init() {
	LogSystem::Init();
	OgreWrapper::OgreManager::Init("AHHHH");
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
	cmpFac->RegisterComponent<EnemyAI>("EnemyAI");
	cmpFac->RegisterComponent<Transform>("Transform");
	cmpFac->RegisterComponent<UITextLM>("UITextLM");
	cmpFac->RegisterComponent<UIImageLM>("UIImageLM");
	//cmpFac->RegisterComponent<Boost>("Boost");
	//cmpFac->RegisterComponent<Checkpoint>("Checkpoint");

	/*cmpFac->RegisterComponent<UIImageLM>("UIImage");
	cmpFac->RegisterComponent<UITextLM>("UIText");*/


}

void MotorApi::MainLoop() {
	OgreWrapper::OgreManager::Init("GAME DLL FAIL");
	while (!_exit) {

		FmodWrapper::AudioManager::GetInstance()->Update(_scnManager->GetDelta());
		OgreWrapper::OgreManager::GetInstance()->Render();
		PhysicsManager::GetInstance()->Update(_scnManager->GetDelta());

		if (LocoMotor::InputManager::GetInstance()->RegisterEvents())
			break;

		_scnManager->Update();
		//std::cout << _scnManager->GetDelta();
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
