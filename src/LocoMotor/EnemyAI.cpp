#include "EnemyAI.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"
#include "Spline.h"
#include <OgreSimpleSpline.h>
#include <LMVector.h>

//float testTime = 0.0f;
LocoMotor::EnemyAI::EnemyAI() {
}

LocoMotor::EnemyAI::~EnemyAI(){
	delete mySpline;
}

void LocoMotor::EnemyAI::Start(OgreWrapper::Spline* splineToFollow)
 {
	timeStep = 0.0f;
	lastTimeStep = 0.0f;
	myGbj = gameObject;
	_node = gameObject->GetNode();
	mySpline = splineToFollow;

	//currentNode = LMVector3::OgreToLm(mySpline->GetPoint(0));
	Ogre::Vector3 ogrePos = mySpline->GetPoint(2); //mySpline.GetPoint(0);
	myGbj->SetPosition(LMVector3::OgreToLm(ogrePos));
}

void LocoMotor::EnemyAI::Update(float dt) 
{
	//std::cout << dt;
	timeStep += 0.01f;
	if (timeStep > 1) {
		timeStep = 0.0f;
		//lastTimeStep = 0.0f;
	}
	
	//if (timeStep - lastTimeStep > 0.2f) {
	//	lastTimeStep = timeStep;
	//}
	myGbj->SetPosition(LMVector3::OgreToLm(mySpline->Interpolate(timeStep)));
}