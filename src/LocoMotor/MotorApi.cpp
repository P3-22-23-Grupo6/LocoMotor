#include "MotorApi.h"
#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "InputManager.h"
#include "CheckML.h"
#include "PhysicsManager.h"
#include "lmVector.h"
#include "RenderScene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Node.h"
#include "LMSpline.h"
#include "Transform.h"
#include "ComponentsFactory.h"
#include <OgreSimpleSpline.h>//TEMPORAL

#include "MeshRenderer.h"
#include <RigidBodyComponent.h>
#include <ParticleSystem.h>
#include <Camera.h>
#include <EnemyAI.h>
#include "CallBackBullet.h"
#include "LmVectorConverter.h"
#include "UIImageLM.h"
#include "UITextLM.h"

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

	auto _renderScn = _mScene->GetRender();

#pragma region Manager responsable del gameplay
	LocoMotor::GameObject* raceManager_gObj = _mScene->AddGameobject("raceManager");
	raceManager_gObj->AddComponent("Transform");
	Component* cmp = raceManager_gObj->AddComponent("RaceManager");

#pragma region RaceTrack
	auto map = _mScene->AddGameobject("map");
	map->AddComponent("Transform");
	map->AddComponent("MeshRenderer");
	map->GetComponent<MeshRenderer>()->Start("map", "SandPlane.mesh", "FalconRedone/FalconMat");//track.mesh para el antiguo
	map->AddComponent("RigidBodyComponent");
	map->GetComponent<RigidBodyComponent>()->Start(0);
	//WaterPlane
	auto waterPlane = _mScene->AddGameobject("waterPlane");
	waterPlane->AddComponent("Transform");
	waterPlane->SetPosition(LMVector3(0,30,0));
	waterPlane->AddComponent("MeshRenderer");
	waterPlane->GetComponent<MeshRenderer>()->Start("waterPlane", "WaterPlane.mesh", "FalconRedone/FalconMat");//track.mesh para el antiguo
	//waterPlane->AddComponent("RigidBodyComponent");
	//waterPlane->GetComponent<RigidBodyComponent>()->Start(0);
	

	//Track Main Road
	auto trackMain = _mScene->AddGameobject("trackMain");
	trackMain->AddComponent("Transform");
	trackMain->AddComponent("MeshRenderer");
	trackMain->GetComponent<MeshRenderer>()->Start("trackMain", "TrackMain.mesh", "");
	trackMain->AddComponent("RigidBodyComponent");
	trackMain->GetComponent<RigidBodyComponent>()->Start(0);
	//Track Border No Coll
	auto trackBorder = _mScene->AddGameobject("trackBorder");
	trackBorder->AddComponent("Transform");
	trackBorder->AddComponent("MeshRenderer");
	trackBorder->GetComponent<MeshRenderer>()->Start("trackBorder", "TrackBorder.mesh", "");
	trackBorder->AddComponent("RigidBodyComponent");
	trackBorder->GetComponent<RigidBodyComponent>()->Start(0);
	//Collision
	auto Debug01 = _mScene->AddGameobject("Debug01");
	Debug01->AddComponent("Transform");
	Debug01->AddComponent("MeshRenderer");
	Debug01->GetComponent<MeshRenderer>()->Start("Debug01", "Debug_c.mesh", "");
	Debug01->AddComponent("RigidBodyComponent");
	Debug01->GetComponent<RigidBodyComponent>()->Start(0);
#pragma region palmTrees
	auto palmTree = _mScene->AddGameobject("PalmTree00");
	palmTree->AddComponent("Transform");
	palmTree->AddComponent("MeshRenderer");
	palmTree->GetComponent<MeshRenderer>()->Start("PalmTree00", "PalmTree.mesh", "");
	palmTree->AddComponent("RigidBodyComponent");
	palmTree->GetComponent<RigidBodyComponent>()->Start(0);
	
	auto palmTree02 = _mScene->AddGameobject("PalmTree02");
	palmTree02->AddComponent("Transform");
	palmTree02->AddComponent("MeshRenderer");
	palmTree02->GetComponent<MeshRenderer>()->Start("PalmTree02", "PalmTree.mesh", "");
	palmTree02->AddComponent("RigidBodyComponent");
	palmTree02->GetComponent<RigidBodyComponent>()->Start(0);
#pragma endregion

	ship_gObj = _mScene->AddGameobject("ship");
	ship_gObj->AddComponent("Transform");
	ship_gObj->AddComponent("MeshRenderer");
	ship_gObj->GetComponent<MeshRenderer>()->Start("ship", "BlueFalcon.mesh", "");// or BlueFalconAlt.mesh
	ship_gObj->AddComponent("ParticleSystem");
	ship_gObj->AddComponent("AudioListener");

	ship_gObj->AddComponent("RigidBodyComponent");
	ship_gObj->GetComponent<RigidBodyComponent>()->Start(1);

	//ship_gObj->GetNode()->SetPosition(0, 1000.0f, 0);
	ship_gObj->setMovable(true);
	ship_gObj->AddComponent("PlayerController");

	

	// CHECKPOINTS
	//raceManager_gObj->GetComponent<RaceManager>()->Start();


	const int numberOfCheckpoints = 3;
	LMVector3 checkpointPositions[numberOfCheckpoints];

	checkpointPositions[0] = LMVector3(0, 4, -60);
	checkpointPositions[1] = LMVector3(0, 4, -120);
	checkpointPositions[2] = LMVector3(0, 4, -180);

	
	std::vector<GameObject*> lsBalls = std::vector<GameObject*>();

	for (size_t i = 0; i < numberOfCheckpoints; i++) {

		std::string checkpointName = "checkP" + i;
		LocoMotor::GameObject* checkpoint_gObj = _mScene->AddGameobject(checkpointName);
		checkpoint_gObj->AddComponent("Transform");
		checkpoint_gObj->AddComponent("MeshRenderer");
		checkpoint_gObj->GetComponent<MeshRenderer>()->Start(checkpointName, "SphereDebug.mesh", "");
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
		wayPoint->GetComponent<MeshRenderer>()->Start("WayPoint" + i, "SphereDebug.mesh", "");
		wayPoint->SetPosition(LMVector3(positionsList[i]));
		wayPoint->SetScale(LMVector3(5, 5, 5));
	}

	for (int i = 0; i < 1; i++){
		auto enemy_gObj = _mScene->AddGameobject("Enemy" + i);
		enemy_gObj->AddComponent("Transform");
		enemy_gObj->AddComponent("MeshRenderer");
		enemy_gObj->GetComponent<MeshRenderer>()->Start("Enemy" + i, "EnemyCar.mesh", "FalconRedone/FalconMat");
		enemy_gObj->AddComponent("AudioSource");
		enemy_gObj->GetComponent<AudioSource>()->Start();
		enemy_gObj->GetComponent<AudioSource>()->Play("Assets/engine.wav", -1);
		enemy_gObj->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
		enemy_gObj->SetPosition(LMVector3(-70 + i * 35, 3.0f, -80));

		enemy_gObj->AddComponent("EnemyAI");
		enemy_gObj->GetComponent<EnemyAI>()->Start(nuevaSpl, -70.f + i * 35.f);
	}

	std::vector<GameObject*> waypointBalls = std::vector<GameObject*>();
	int maxBalls = 400;
	for (float i = 1; i < maxBalls; i++) {
		auto wayPointNew = _mScene->AddGameobject("WayPointProc" + std::to_string(i));
		wayPointNew->AddComponent("Transform");
		wayPointNew->AddComponent("MeshRenderer");
		wayPointNew->GetComponent<MeshRenderer>()->Start("WayPointProc" + std::to_string(i), "DebugSphere2.mesh", "");
		nuevaSpl->RecalcTangents();
		waypointBalls.push_back(wayPointNew);
	}
#pragma endregion

	//Skybox
	_renderScn->SetSkybox();

	//UIExamples
	

#pragma endregion

	_scnManager->ChangeScene("Escena");

	ship_gObj->SetPosition(LMVector3(50, 6, 0));
	ship_gObj->GetComponent<RigidBodyComponent>()->SetFriction(0.f);
	trackMain->SetPosition(LMVector3(0, -3, -100));
	trackBorder->SetPosition(LMVector3(0, -3, -100));
	Debug01->SetPosition(LMVector3(0, -3, -100));
	palmTree->SetPosition(LMVector3(-50, 0, -85));
	//palmTree01->SetPosition(LMVector3(40, 0, -50));
	palmTree02->SetPosition(LMVector3(60, 0, -200));
	//track00->SetPosition(LMVector3(20, 0, -200));
	//enemy_gObj->SetPosition(LMVector3(-20, .5f, 0));
	palmTree->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
	//palmTree01->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
	palmTree02->SetScale(LMVector3(15.0f, 15.0f, 15.0f));
	ship_gObj->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
	

	//for (int i = 1; i < numberOfCheckpoints; i++) {
	//	lsBalls[i]->SetScale(LMVector3(10.0f, 10.0f, 10.0f));
	//	lsBalls[i]->SetPosition(checkpointPositions[i]);
	//}
	for (int i = 1; i < waypointBalls.size(); i++) {
		waypointBalls[i]->SetScale(LMVector3(3.0f, 3.0f, 3.0f));
		waypointBalls[i]->SetPosition(nuevaSpl->Interpolate((float) i / maxBalls));
	}

#pragma region All Components Started

	_mScene->GetCamera()->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 15, 65));

	map->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
	trackMain->GetComponent<RigidBodyComponent>()->SetCollisionGroup(2);
	//waterPlane->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
#pragma endregion

}

void MotorApi::Init() {
	FmodWrapper::AudioManager::Init(8);
	PhysicsManager::Init();
	InputManager::Get();
	_scnManager = LocoMotor::SceneManager::Init();
	PhysicsManager::GetInstance()->setContactStartCallback(contactStartBullet);
	PhysicsManager::GetInstance()->setContactProcessCallback(contactProcessedBullet);
	PhysicsManager::GetInstance()->setContactEndedCallback(contactExitBullet);
	auto cmpFac = ComponentsFactory::Init();
	cmpFac->RegisterComponent<AudioSource>("AudioSource");
	cmpFac->RegisterComponent<AudioListener>("AudioListener");
	cmpFac->RegisterComponent<Camera>("Camera");
	cmpFac->RegisterComponent<MeshRenderer>("MeshRenderer");
	cmpFac->RegisterComponent<ParticleSystem>("ParticleSystem");
	cmpFac->RegisterComponent<RigidBodyComponent>("RigidBodyComponent");
	cmpFac->RegisterComponent<EnemyAI>("EnemyAI");
	cmpFac->RegisterComponent<Transform>("Transform");
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
		if (InputManager::Get()->RegisterEvents())
			break;

		_scnManager->Update();
		//std::cout << _scnManager->GetDelta();
	}
	PhysicsManager::Clear();
	SceneManager::Clear();
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();

	InputManager::Destroy();
	ComponentsFactory::Clear();
	return;
}
