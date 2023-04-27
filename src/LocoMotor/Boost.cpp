#include "Boost.h"
#include "GameObject.h"
#include "Transform.h"
#include <LMVector.h>
#include "RigidBodyComponent.h"
#include "LmVectorConverter.h"

LocoMotor::Boost::Boost() {
}

LocoMotor::Boost::~Boost(){
}

void LocoMotor::Boost::Start(float thrust)
 {
	boostThrust = thrust;
	
	myGbj = gameObject;
}

void LocoMotor::Boost::Update(float dt)
{
}

void LocoMotor::Boost::OnCollisionEnter(GameObject* other) {
	//other->GetComponent<RigidBodyComponent>()
	other->GetComponent<RigidBodyComponent>()->addForce(LMVector3(other->GetTransform()->GetRotation().Forward() * 20000));
}
