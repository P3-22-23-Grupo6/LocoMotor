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
#include "Spline.h"
#include "ComponentsFactory.h"

#include "MeshRederer.h"
#include <RigidBodyComponent.h>
#include <ParticleSystem.h>
#include <Checkpoint.h>
#include <Camera.h>
#include <EnemyAI.h>

#include <tweeners/builder.hpp>
#include <tweeners/easing.hpp>
#include <tweeners/system.hpp>

using namespace LocoMotor;
using namespace PhysicsWrapper;
MotorApi::MotorApi() {
	_gameName = "";
}


void MotorApi::RegisterGame(const char* gameName) {
	_gameName = gameName;
	OgreWrapper::OgreManager::Init(gameName); 

	auto _mSceneM = _scnManager->CreateScene("Menu");
	auto _mScene = _scnManager->CreateScene("Escena");
	
#pragma region Escena que teniamos antes

	auto _renderScn = _mScene->GetRender();

	#pragma region RaceTrack
		auto map = _mScene->AddGameobject("map");
		map->AddComponent("MeshRenderer");
		map->GetComponent<MeshRenderer>()->Start("map", "Plane.mesh", "FalconRedone/FalconMat");//track.mesh para el antiguo
		map->AddComponent("RigidBodyComponent");
		map->GetComponent<RigidBodyComponent>()->Start(0);
		map->AddComponent("PlayerController");


		auto map01 = _mScene->AddGameobject("map01");
		map01->AddComponent("MeshRenderer");
		map01->GetComponent<MeshRenderer>()->Start("map01", "Track.mesh", "");//Track.mesh para el antiguo
		map01->SetPosition(LMVector3(0, -8, 0));
		map01->AddComponent("RigidBodyComponent");
		map01->GetComponent<RigidBodyComponent>()->Start(0);
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

	//ENEMY MODEL
	enemy_gObj = _mScene->AddGameobject("Enemy");
	enemy_gObj->AddComponent("MeshRenderer");
	enemy_gObj->GetComponent<MeshRenderer>()->Start("Enemy", "EnemyCar.mesh", "FalconRedone/FalconMat");
	enemy_gObj->AddComponent("RigidBodyComponent");
	enemy_gObj->GetComponent<RigidBodyComponent>()->Start(1);
	enemy_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	enemy_gObj->SetPosition(LMVector3(-20, .5f, 0));
	enemy_gObj->AddComponent("EnemyAI");

	//OgreWrapper::Spline* nuevaSpline = _mScene->;

#pragma region PathWaypoints
	LMVector3 pos01 = LMVector3(50, 10, -100);
	LMVector3 pos02 = LMVector3(-50, 60, -100);
	LMVector3 pos03 = LMVector3(-20, 10, -50);

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

	mySpline = new Ogre::SimpleSpline;
	mySpline->addPoint(Ogre::Vector3(LMVector3(pos01)));
	mySpline->addPoint(Ogre::Vector3(LMVector3(pos02)));
	mySpline->addPoint(Ogre::Vector3(LMVector3(pos03)));
	mySpline->addPoint(Ogre::Vector3(LMVector3(pos01)));

	OgreWrapper::Spline* nuevaSpl = new OgreWrapper::Spline();

	int maxBalls = 100;
	for (float i = 1; i < maxBalls; i++){
		auto wayPointNew = _mScene->AddGameobject("WayPointProc" + std::to_string(i));
		wayPointNew->AddComponent("MeshRenderer");
		wayPointNew->GetComponent<MeshRenderer>()->Start("WayPointProc" + std::to_string(i), "DebugSphere2.mesh", "");
		wayPointNew->GetNode()->SetScale(3, 3, 3);
		//wayPointNew->SetPosition(LMVector3(i *5, 10, -100));
		wayPointNew->SetPosition(LMVector3::OgreToLm(mySpline->interpolate(i / maxBalls)));
		mySpline->recalcTangents();
	}

	//enemy_gObj->AddComponent("EnemyAI");
	//enemy_gObj->GetComponent<EnemyAI>()->Start(enemy_gObj, enemy_gObj->GetNode(), mySpline);
	//enemy_gObj->SetPosition(LMVector3::OgreToLm(mySpline->interpolate(interpol)));
	
	//while (tween.progress() < 1.0f) {
	//	tween.step(0.01f);
	//}
#pragma endregion

	//// CHECKPOINT
	//Skybox
	_renderScn->SetSkybox();
	//GameObject* checkpoint = _mScene->AddGameobject("checkpoint");
	//checkpoint->AddComponent<MeshRenderer>("checkpoint", "BlueFalcon.mesh", "FalconRedone/FalconMat", _renderScn);
	//checkpoint->AddComponent<RigidBodyComponent>(0);
	//checkpoint->GetNode()->SetScale(60.0f, 10.0f, 10.0f);
	//checkpoint->SetPosition(LMVector3(0, 5, -50));
	//checkpoint->AddComponent<Checkpoint>(ship_gObj, 0);

#pragma endregion

	_scnManager->ChangeScene("Menu");

#pragma region All Components Started

	_mScene->GetCamera()->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 15, 65));

	


	/*map->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
	map->GetComponent<RigidBodyComponent>()->setStatic();*/
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
	cmpFac->RegisterComponent<EnemyAI>("EnemyAI");
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
		enemy_gObj->GetNode()->LookAt(ship_gObj->GetNode()->GetPosition_X(),
									  ship_gObj->GetNode()->GetPosition_Y(),
									  ship_gObj->GetNode()->GetPosition_Z());
		//float interpol = _scnManager->GetDelta();
		//if (interpol > 1) interpol = 0;
		//enemy_gObj->SetPosition(LMVector3::OgreToLm(mySpline->interpolate(0.69f)));
		//Ogre::Vector3 a = mySpline->interpolate(0.69f);
		//enemy_gObj->GetNode()->Translate(a.x, a.y, a.z);


		if (InputManager::Get()->GetKeyDown(SDL_SCANCODE_T)) {

			if (_scnManager->GetActiveSceneName() == "Escena") {

				OgreWrapper::OgreManager::GetInstance()->SetActiveScene(_scnManager->GetSceneByName("Menu")->GetRender());
				_scnManager->ChangeScene("Menu");
				
				//_scnManager->DeleteScene("Escena");
				
			}
			else {
			
				OgreWrapper::OgreManager::GetInstance()->SetActiveScene(_scnManager->GetSceneByName("Escena")->GetRender());
				_scnManager->ChangeScene("Escena");
				
				//_scnManager->DeleteScene("Menu");

			}
		}
		
	}
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	PhysicsManager::Clear();
	InputManager::Destroy();
	ComponentsFactory::Clear();
	delete _scnManager;
	return;
}
