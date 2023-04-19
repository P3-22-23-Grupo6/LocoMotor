#include "EnemyAI.h"
#include "GameObject.h"
#include "Transform.h"
#include "Spline.h"
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
	mySpline = splineToFollow;
	
	timeStep = 0.0f;
	lastTimeStep = 0.0f;
	myGbj = gameObject;
}

void LocoMotor::EnemyAI::Update(float dt) 
{
	timeStep += 0.0026f;
	if (timeStep > 1) {
		timeStep = 0.0f;
	}
	LMVector3 from = myGbj->GetTransform()->GetPosition();
	LMVector3 to = from + LMVector3(0,-20,0);

	LMVector3 upVector = myGbj->GetTransform()->GetRotation().Up();
	upVector.Normalize();
	RigidBodyComponent* rbComp = myGbj->GetComponent<RigidBodyComponent>();
	double raycastDistance = 7;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		LMVector3 newUp = n * 40;
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