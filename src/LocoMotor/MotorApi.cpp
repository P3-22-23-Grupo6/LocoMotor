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
#include "Boost.h"
#include "ComponentsFactory.h"

#include "MeshRenderer.h"
#include <RigidBodyComponent.h>
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

	auto _renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene("Escena");

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
	raceManager_gObj->AddComponent("UIImageLM");
	raceManager_gObj->GetComponent<UIImageLM>()->ChangeImage("TemporalUIMat");
	raceManager_gObj->GetComponent<UIImageLM>()->SetPosition(0.3, 0.);
	raceManager_gObj->GetComponent<UIImageLM>()->SetSize(0.3, 0.3);

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
#pragma endregion 

#pragma region RaceTrack
	//WaterPlane
	//auto waterPlane = _mScene->AddGameobject("waterPlane");
	//waterPlane->AddComponent("Transform");
	//waterPlane->SetPosition(LMVector3(0,30,0));
	//waterPlane->AddComponent("MeshRenderer");
	//waterPlane->GetComponent<MeshRenderer>()->Start("waterPlane", "WaterPlane.mesh", "FalconRedone/FalconMat", true);//track.mesh para el antiguo
	
	//Boost
	auto boost = _mScene->AddGameobject("boost");
	boost->AddComponent("Transform");
	boost->AddComponent("MeshRenderer");
	boost->GetComponent<MeshRenderer>()->Start("boost", "TurboTestMesh.mesh", "", true);
	boost->AddComponent("RigidBodyComponent");
	boost->GetComponent<RigidBodyComponent>()->Start(0);
	boost->AddComponent("Boost");

	//Track Main Road
	auto trackMain = _mScene->AddGameobject("trackMain");
	trackMain->AddComponent("Transform");
	trackMain->AddComponent("MeshRenderer");
	trackMain->GetComponent<MeshRenderer>()->Start("trackMain", "AllTrack.mesh", "", true);
	trackMain->AddComponent("RigidBodyComponent");
	trackMain->GetComponent<RigidBodyComponent>()->Start(0);

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
	ship_gObj->setMovable(true);
	ship_gObj->AddComponent("Transform");
	ship_gObj->AddComponent("ParticleSystem");

	ship_gObj->AddComponent("RigidBodyComponent");
	ship_gObj->GetComponent<RigidBodyComponent>()->Start(1);

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
	std::vector<LMVector3> positionsList //Estoy tomando medidas con el archivo de Blender, aun no puedo exportar posiciones
	{
		LMVector3(0, 5, 0),
		LMVector3(0, 5, -210),
		LMVector3(-17,27,-325),
		LMVector3(-50,65,-420),
		LMVector3(-165,101,-535),
		LMVector3(-342,107,-570),
		LMVector3(-545,90,-556),
		LMVector3(-800,3,-392),
		LMVector3(-838,-37,-218),
		LMVector3(-830,-37,	75),
		LMVector3(-805,-37, 345),
		LMVector3(-679,-37, 630),
		LMVector3(-415,0, 742),
		LMVector3(-151,60, 736),
		LMVector3(90,67, 567),
		LMVector3(98,28, 347),
		LMVector3(31,8, 185),
		LMVector3(0, 5, 0)//reset
	};

	LocoMotor::Spline* nuevaSpl = new LocoMotor::Spline();
	for (int i = 0; i < 18; i++) {
		nuevaSpl->AddPoint(LMVector3(positionsList[i]));
		auto wayPoint = _mScene->AddGameobject("WayPoint" + i);
		wayPoint->AddComponent("Transform");
		wayPoint->AddComponent("MeshRenderer");
		wayPoint->GetComponent<MeshRenderer>()->Start("WayPoint" + i, "SphereDebug.mesh", "", true);
		wayPoint->SetPosition(LMVector3(positionsList[i]));
		wayPoint->SetScale(LMVector3(5, 5, 5));
	}

	for (int i = 0; i < 1; i++){
		std::string enemyName = "Enemy" + std::to_string(i);
		//std::string enemyName = "Enemy0";
		auto enemy_gObj = _mScene->AddGameobject(enemyName);
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
	//int maxBalls = 400;
	//for (float i = 1; i < maxBalls; i++) {
	//	auto wayPointNew = _mScene->AddGameobject("WayPointProc" + std::to_string(i));
	//	wayPointNew->AddComponent("Transform");
	//	wayPointNew->AddComponent("MeshRenderer");
	//	wayPointNew->GetComponent<MeshRenderer>()->Start("WayPointProc" + std::to_string(i), "DebugSphere2.mesh", "");
	//	nuevaSpl->RecalcTangents();
	//	waypointBalls.push_back(wayPointNew);
	//}
#pragma endregion

	

#pragma endregion

	_scnManager->StartScene(_mScene);

	ship_gObj->SetPosition(LMVector3(0, 6, 0));
	ship_gObj->GetComponent<RigidBodyComponent>()->SetFriction(0.f);
	trackMain->SetPosition(LMVector3(0, -10, 0));
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
	trackMain->GetComponent<RigidBodyComponent>()->SetCollisionGroup(2);
	trackMain->GetComponent<RigidBodyComponent>()->SetCollisionGroup(2);
	//trackBorder->GetComponent<RigidBodyComponent>()->SetCollisionGroup(6);
	//Debug01->GetComponent<RigidBodyComponent>()->SetCollisionGroup(6);
	boost->GetComponent<RigidBodyComponent>()->beATrigger();
	//waterPlane->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
#pragma endregion
}

void MotorApi::Init() {
	OgreWrapper::OgreManager::Init("AHHHH");
	FmodWrapper::AudioManager::Init(8);
	PhysicsManager::Init();
	InputManager::Init();
	SceneManager::Init();
	_scnManager = LocoMotor::SceneManager::Init();
	ScriptManager::Init();
	PhysicsManager::GetInstance()->setContactStartCallback(LMcontactStart);
	PhysicsManager::GetInstance()->setContactProcessCallback(LMcontactProcessed);
	PhysicsManager::GetInstance()->setContactEndedCallback(LMcontactExit);
	auto cmpFac = ComponentsFactory::Init();
	cmpFac->RegisterComponent<AudioSource>("AudioSource");
	cmpFac->RegisterComponent<AudioListener>("AudioListener");
	cmpFac->RegisterComponent<Camera>("Camera");
	cmpFac->RegisterComponent<MeshRenderer>("MeshRenderer");
	cmpFac->RegisterComponent<ParticleSystem>("ParticleSystem");
	cmpFac->RegisterComponent<RigidBodyComponent>("RigidBodyComponent");
	cmpFac->RegisterComponent<EnemyAI>("EnemyAI");
	cmpFac->RegisterComponent<Transform>("Transform");
	cmpFac->RegisterComponent<UITextLM>("UITextLM");
	cmpFac->RegisterComponent<UIImageLM>("UIImageLM");
	cmpFac->RegisterComponent<Boost>("Boost");
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
	return;
}
