#include "CallBackBullet.h"
#include "GameObject.h"
#include "btBulletDynamicsCommon.h"

void LocoMotor::LMcontactStart(btPersistentManifold* const& manifold) {
	//Tomamos los dos rb guardados previamente en UserPointer
	LocoMotor::GameObject* rb1 = static_cast<LocoMotor::GameObject*>(manifold->getBody0()->getUserPointer());
	LocoMotor::GameObject* rb2 = static_cast<LocoMotor::GameObject*>(manifold->getBody1()->getUserPointer());

	//Si existen
	if (rb1 && rb2) {
		rb1->OnCollisionEnter(rb2);
		rb2->OnCollisionEnter(rb1);
	}
}
bool LocoMotor::LMcontactProcessed(btManifoldPoint& cp, void* body0, void* body1) {
	btCollisionObject* colObj0 = static_cast<btCollisionObject*>(body0);
	btCollisionObject* colObj1 = static_cast<btCollisionObject*>(body1);

	LocoMotor::GameObject* rb1 = static_cast<LocoMotor::GameObject*>(colObj0->getUserPointer());
	LocoMotor::GameObject* rb2 = static_cast<LocoMotor::GameObject*>(colObj1->getUserPointer());

	if (rb1 && rb2) {
		rb1->OnCollisionStay(rb2);
		rb2->OnCollisionStay(rb1);
	}

	return true; //no importa su valor
}
//Indica como debe actuar la fisica al salir una colision trigger
void LocoMotor::LMcontactExit(btPersistentManifold* const& manifold) {
	LocoMotor::GameObject* rb1 = static_cast<LocoMotor::GameObject*>(manifold->getBody0()->getUserPointer());
	LocoMotor::GameObject* rb2 = static_cast<LocoMotor::GameObject*>(manifold->getBody1()->getUserPointer());

	if (rb1 && rb2) {
		rb1->OnCollisionExit(rb2);
		rb2->OnCollisionExit(rb1);
	}
}
