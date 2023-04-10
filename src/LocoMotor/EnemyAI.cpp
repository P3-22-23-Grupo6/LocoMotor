#include "EnemyAI.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"
#include <OgreSimpleSpline.h>

//float testTime = 0.0f;
LocoMotor::EnemyAI::EnemyAI() {
}

LocoMotor::EnemyAI::~EnemyAI()
{
	delete _node;
	delete _renderScn;
}

void LocoMotor::EnemyAI::Start(LocoMotor::GameObject* enemyGbj, OgreWrapper::Node* node, Ogre::SimpleSpline* ogreSpline) {
	myGbj = enemyGbj;
	_node = node;
	mySpline = ogreSpline;
	//mySpline->addPoint(ogreSpline.getPoint(0));
	//mySpline->addPoint(ogreSpline.getPoint(1));
	//mySpline->addPoint(ogreSpline.getPoint(2));
}

void LocoMotor::EnemyAI::Update(float dt) 
{
	//if (testTime > 1) testTime = 0.0f;
	//testTime += dt;
	////Look At Waypoint
	//float a = mySpline->getPoint(1).x;
	//float b = mySpline->getPoint(1).z;
	//float c = mySpline->getPoint(1).y;
	//_node->LookAt(a,b,c);
	//std::cout << a;
	//std::cout << b;
	//std::cout << c;
	//myGbj->SetPosition(LMVector3(a,b,c));
}