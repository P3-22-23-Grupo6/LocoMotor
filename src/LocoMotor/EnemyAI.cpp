#include "EnemyAI.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Node.h"
#include "Spline.h"
#include <OgreSimpleSpline.h>
#include <LMVector.h>
#include "RigidBodyComponent.h"

//float testTime = 0.0f;
LocoMotor::EnemyAI::EnemyAI() {
}

LocoMotor::EnemyAI::~EnemyAI(){
	delete mySpline;
}

void LocoMotor::EnemyAI::Start(OgreWrapper::Spline* splineToFollow, float sep)
 {
	startSeparation = sep;
	timeStep = 0.0f;
	lastTimeStep = 0.0f;
	enemySpeed = 26;
	myGbj = gameObject;
	_node = gameObject->GetNode();
	mySpline = splineToFollow;

	//currentNode = LMVector3::OgreToLm(mySpline->GetPoint(0));
	Ogre::Vector3 ogrePos = mySpline->GetPoint(2); //mySpline.GetPoint(0);
	myGbj->SetPosition(LMVector3::OgreToLm(ogrePos));
}

void LocoMotor::EnemyAI::Update(float dt) 
{
	timeStep += 0.0026f;// *100.0f;
	if (timeStep > 1) {
		timeStep = 0.0f;
	}
	//RAYCAST TEMPORAL
	LMVector3 from = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y(), _node->GetPosition_Z());
	LMVector3 to = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y() - 20, _node->GetPosition_Z());

	LMVector3 upVector = myGbj->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	RigidBodyComponent* rbComp = myGbj->GetComponent<RigidBodyComponent>();
	double raycastDistance = 7;
	upVector = LMVector3(upVector.GetX() * raycastDistance, upVector.GetY() * raycastDistance, upVector.GetZ() * raycastDistance);
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		float pitchIntensity = 1;
		LMVector3 newUp = LMVector3(n.GetX() * pitchIntensity, n.GetY() * pitchIntensity, n.GetZ() * pitchIntensity);
		myGbj->GetTransform()->SetUpwards(newUp);
	}

	//Interpolate Position
	Ogre::Vector3 newPos = mySpline->Interpolate(timeStep);
	newPos += myGbj->GetTransform()->GetRotation().Right() * startSeparation;
	//LookAt
	myGbj->GetTransform()->LookAt(LMVector3::OgreToLm(newPos));
	//Set Position
	myGbj->SetPosition(LMVector3::OgreToLm(newPos));
}