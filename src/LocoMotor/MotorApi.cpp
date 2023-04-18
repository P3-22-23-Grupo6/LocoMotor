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
#include "Spline.h"
#include "ComponentsFactory.h"
#include <OgreSimpleSpline.h>//TEMPORAL

#include "MeshRenderer.h"
#include <RigidBodyComponent.h>
#include <ParticleSystem.h>
#include <Camera.h>
#include <EnemyAI.h>

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
	Component* cmp = raceManager_gObj->AddComponent("RaceManager");

#pragma region RaceTrack
	auto map = _mScene->AddGameobject("map");
	map->AddComponent("MeshRenderer");
	map->GetComponent<MeshRenderer>()->Start("map", "Plane.mesh", "FalconRedone/FalconMat");//track.mesh para el antiguo
	map->AddComponent("RigidBodyComponent");
	map->GetComponent<RigidBodyComponent>()->Start(0);


	auto map01 = _mScene->AddGameobject("map01");
	map01->AddComponent("MeshRenderer");
	map01->GetComponent<MeshRenderer>()->Start("map01", "Track.mesh", "");//Track.mesh para el antiguo
	map01->SetPosition(LMVector3(0, -8, 0));
	map01->AddComponent("RigidBodyComponent");
	map01->GetComponent<RigidBodyComponent>()->Start(0);
	//TurboPlane
	auto turboPlane = _mScene->AddGameobject("TurboPlane");
	turboPlane->AddComponent("MeshRenderer");
	turboPlane->GetComponent<MeshRenderer>()->Start("TurboPlane", "TurboPlane.mesh", "");//Track.mesh para el antiguo
	turboPlane->SetPosition(LMVector3(0, 0.1f, 0));
	turboPlane->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
#pragma region palmTrees
	auto palmTree = _mScene->AddGameobject("PalmTree00");
	palmTree->AddComponent("MeshRenderer");
	palmTree->GetComponent<MeshRenderer>()->Start("PalmTree00", "PalmTree.mesh", "");//Track.mesh para el antiguo
	palmTree->SetPosition(LMVector3(-50,0,-85));
	palmTree->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	palmTree->GetNode()->SetDirection(50,0,0);
	palmTree->AddComponent("RigidBodyComponent");
	palmTree->GetComponent<RigidBodyComponent>()->Start(0);
	auto palmTree01 = _mScene->AddGameobject("PalmTree01");
	palmTree01->AddComponent("MeshRenderer");
	palmTree01->GetComponent<MeshRenderer>()->Start("PalmTree01", "PalmTree.mesh", "");//Track.mesh para el antiguo
	palmTree01->SetPosition(LMVector3(40, 0, -50));
	palmTree01->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	palmTree01->AddComponent("RigidBodyComponent");
	palmTree01->GetComponent<RigidBodyComponent>()->Start(0);
	auto palmTree02 = _mScene->AddGameobject("PalmTree02");
	palmTree02->AddComponent("MeshRenderer");
	palmTree02->GetComponent<MeshRenderer>()->Start("PalmTree02", "PalmTree.mesh", "");//Track.mesh para el antiguo
	palmTree02->SetPosition(LMVector3(60, 0, -200));
	palmTree02->GetNode()->SetScale(15.0f, 15.0f, 15.0f);
	palmTree02->AddComponent("RigidBodyComponent");
	palmTree02->GetComponent<RigidBodyComponent>()->Start(0);
#pragma endregion

	auto track00 = _mScene->AddGameobject("Track00");
	track00->AddComponent("MeshRenderer");
	track00->GetComponent<MeshRenderer>()->Start("Track00", "Track00.mesh", "");//Track.mesh para el antiguo
	track00->SetPosition(LMVector3(20, 0, -200));
	track00->AddComponent("RigidBodyComponent");
	track00->GetComponent<RigidBodyComponent>()->Start(0);
#pragma endregion

	ship_gObj = _mScene->AddGameobject("ship");
	ship_gObj->AddComponent("MeshRenderer");
	ship_gObj->GetComponent<MeshRenderer>()->Start("ship", "BlueFalcon.mesh", "");// or BlueFalconAlt.mesh
	ship_gObj->AddComponent("ParticleSystem");

	ship_gObj->AddComponent("RigidBodyComponent");
	ship_gObj->GetComponent<RigidBodyComponent>()->Start(1);

	ship_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	//ship_gObj->GetNode()->SetPosition(0, 1000.0f, 0);
	ship_gObj->SetPosition(LMVector3(0, 4, 0));
	ship_gObj->setMovable(true);
	ship_gObj->AddComponent("PlayerController");

	//ENEMY MODEL
	enemy_gObj = _mScene->AddGameobject("Enemy");
	enemy_gObj->AddComponent("MeshRenderer");
	enemy_gObj->GetComponent<MeshRenderer>()->Start("Enemy", "EnemyCar.mesh", "FalconRedone/FalconMat");
	//enemy_gObj->AddComponent("RigidBodyComponent");
	//enemy_gObj->GetComponent<RigidBodyComponent>()->Start(1);
	enemy_gObj->AddComponent("AudioSource");
	enemy_gObj->GetComponent<AudioSource>()->Start();
	enemy_gObj->GetComponent<AudioSource>()->Play("Assets/engine.wav", -1);
	enemy_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	enemy_gObj->SetPosition(LMVector3(-20, .5f, 0));
	enemy_gObj->AddComponent("EnemyAI");



	// CHECKPOINTS
	//raceManager_gObj->GetComponent<RaceManager>()->Start();


	const int numberOfCheckpoints = 3;
	LMVector3 checkpointPositions[numberOfCheckpoints];

	checkpointPositions[0] = LMVector3(0, 4, -60);
	checkpointPositions[1] = LMVector3(0, 4, -120);
	checkpointPositions[2] = LMVector3(0, 4, -180);

	for (size_t i = 0; i < numberOfCheckpoints; i++) {

		std::string checkpointName = "checkP" + i;
		LocoMotor::GameObject* checkpoint_gObj = _mScene->AddGameobject(checkpointName);
		checkpoint_gObj->AddComponent("MeshRenderer");
		checkpoint_gObj->GetComponent<MeshRenderer>()->Start(checkpointName, "SphereDebug.mesh", "");
		checkpoint_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
		checkpoint_gObj->SetPosition(checkpointPositions[i]);
		Component* checkpointComp = checkpoint_gObj->AddComponent("Checkpoint");
	}

	//LocoMotor::GameObject* checkpoint_gObj = _mScene->AddGameobject("checkP");
	//checkpoint_gObj->AddComponent("MeshRenderer");
	//checkpoint_gObj->GetComponent<MeshRenderer>()->Start("checkP", "SphereDebug.mesh", "");
	//checkpoint_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	//checkpoint_gObj->SetPosition(LMVector3(0, 4, -50));
	//Component* checkpointComp = checkpoint_gObj->AddComponent("Checkpoint");


#pragma region PathWaypoints
	LMVector3 pos01 = LMVector3(50, 10, -180);
	LMVector3 pos02 = LMVector3(-50, 60, -180);
	LMVector3 pos03 = LMVector3(-20, 10, -100);

	auto wayPoint01 = _mScene->AddGameobject("WayPoint01");
	wayPoint01->AddComponent("MeshRenderer");
	wayPoint01->GetComponent<MeshRenderer>()->Start("WayPoint01", "SphereDebug.mesh", "");
	wayPoint01->GetNode()->SetScale(5, 5, 5);
	wayPoint01->SetPosition(pos01);

	auto wayPoint02 = _mScene->AddGameobject("WayPoint02");
	wayPoint02->AddComponent("MeshRenderer");
	wayPoint02->GetComponent<MeshRenderer>()->Start("WayPoint02", "SphereDebug.mesh", "");
	wayPoint02->GetNode()->SetScale(5, 5, 5);
	wayPoint02->SetPosition(pos02);

	auto wayPoint03 = _mScene->AddGameobject("WayPoint03");
	wayPoint03->AddComponent("MeshRenderer");
	wayPoint03->GetComponent<MeshRenderer>()->Start("WayPoint03", "SphereDebug.mesh", "");
	wayPoint03->GetNode()->SetScale(5, 5, 5);
	wayPoint03->SetPosition(pos03);

	OgreWrapper::Spline* nuevaSpl = new OgreWrapper::Spline();
	nuevaSpl->AddPoint(Ogre::Vector3(LMVector3(pos01)));
	nuevaSpl->AddPoint(Ogre::Vector3(LMVector3(pos02)));
	nuevaSpl->AddPoint(Ogre::Vector3(LMVector3(pos03)));
	nuevaSpl->AddPoint(Ogre::Vector3(LMVector3(pos01)));

	//enemy_gObj->setMovable(true);
	enemy_gObj->GetComponent<EnemyAI>()->Start(nuevaSpl);

	int maxBalls = 100;
	for (float i = 1; i < maxBalls; i++) {
		auto wayPointNew = _mScene->AddGameobject("WayPointProc" + std::to_string(i));
		wayPointNew->AddComponent("MeshRenderer");
		wayPointNew->GetComponent<MeshRenderer>()->Start("WayPointProc" + std::to_string(i), "DebugSphere2.mesh", "");
		wayPointNew->GetNode()->SetScale(3, 3, 3);
		//wayPointNew->SetPosition(LMVector3(i *5, 10, -100));
		wayPointNew->SetPosition(LMVector3::OgreToLm(nuevaSpl->Interpolate(i / maxBalls)));
		nuevaSpl->RecalcTangents();
	}
#pragma endregion

	//Skybox
	_renderScn->SetSkybox();

#pragma endregion

	_scnManager->ChangeScene("Escena");

#pragma region All Components Started

	_mScene->GetCamera()->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 15, 65));

	map->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
#pragma endregion

}

void MotorApi::Init() {
	FmodWrapper::AudioManager::Init(8);
	PhysicsManager::Init();
	InputManager::Get();
	_scnManager = LocoMotor::SceneManager::Init();

	auto cmpFac = ComponentsFactory::Init();
	cmpFac->RegisterComponent<AudioSource>("AudioSource");
	cmpFac->RegisterComponent<AudioListener>("AudioListener");
	cmpFac->RegisterComponent<Camera>("Camera");
	cmpFac->RegisterComponent<MeshRenderer>("MeshRenderer");
	cmpFac->RegisterComponent<ParticleSystem>("ParticleSystem");
	cmpFac->RegisterComponent<RigidBodyComponent>("RigidBodyComponent");
	cmpFac->RegisterComponent<EnemyAI>("EnemyAI");
	//cmpFac->RegisterComponent<Checkpoint>("Checkpoint");

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
	SceneManager::Clear();
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	PhysicsManager::Clear();
	InputManager::Destroy();
	ComponentsFactory::Clear();
	return;
}
