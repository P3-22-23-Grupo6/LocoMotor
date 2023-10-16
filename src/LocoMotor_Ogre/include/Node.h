#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <string>
#include <vector>
namespace Ogre {
	class Quaternion;
	class SceneNode;
	class MovableObject;
}

namespace OgreWrapper {
	class RenderEntity;
	class Node {
	public:
		Node(Ogre::SceneNode* node, std::string name);
		~Node();
		/// @brief
		/// Translates the node, taking into account the actual position.
		/// Uses the parent node's axis as reference
		/// @param x X translation
		/// @param y Y translation
		/// @param z Z translation
		void Translate(float x, float y, float z);
		/// @brief
		/// Rotates the node, taking into account the actual rotation.
		/// Uses the local axis as reference
		/// Parameters passed in Degrees
		/// @param x X rotation
		/// @param y Y rotation
		/// @param z Z rotation
		void Rotate(float x, float y, float z);
		/// @brief
		/// Rotates the node in LocalSpace
		/// Parameters passed in Degrees
		void RotateLocal(float x, float y, float z);
		/// @brief
		/// Scales the node, taking into account the actual scale.
		/// @param x X scale factor
		/// @param y Y scale factor
		/// @param z Z scale factor
		void Scale(float x, float y, float z);
		/// @brief
		/// Sets the position.
		/// @param x X position
		/// @param y Y position
		/// @param z Z positiontion
		void SetPosition(float x, float y, float z);
		/// @brief
		/// Sets the position x
		float GetPosition_X();
		/// @brief
		/// Sets the position y
		float GetPosition_Y();
		/// @brief
		/// Sets the position z
		float GetPosition_Z();
		/// @brief
		/// Sets the rotation w
		float GetRotation_W();
		/// @brief
		/// Sets the rotation x
		float GetRotation_X();
		/// @brief
		/// Sets the rotation y
		float GetRotation_Y();
		/// @brief
		/// Sets the rotation z
		float GetRotation_Z();
		/// @brief
		/// Sets the scale x
		float GetScale_X();
		/// @brief
		/// Sets the scale y
		float GetScale_Y();
		/// @brief
		/// Sets the scale z
		float GetScale_Z();
		/// @brief
		/// Sets the scale of the node.
		/// @param x X scale factor
		/// @param y Y scale factor
		/// @param z Z scale factor
		void SetScale(float x, float y, float z);
		/// @brief
		/// Sets the point to wich the node looks.
		/// @param x
		/// @param y
		/// @param z
		void LookAt(float x, float y, float z);
		/// @brief
		/// Sets the point to wich the node looks.
		/// @param x
		/// @param y
		/// @param z
		void SetDirection(float x, float y, float z);
		/// @brief
		/// Attaches an object to the node.
		/// @param ent
		void Attach(RenderEntity* ent);
		/// @brief
		/// Resets the node Orientation
		void ResetOrientation();
		/// @brief Sets the node orientation
		void SetOrientation(Ogre::Quaternion& q);
		/// @brief Creates a child in the node
		void AddChild(OgreWrapper::Node* nodeToAdd);
		/// @brief Creates a child in the node
		Node* CreateChild(const std::string& name);
		/// @brief Destroy the node child
		void DestroyChild(OgreWrapper::Node* nod);
		/// @brief Gets the node name 
		std::string GetName();
	protected:
		Ogre::SceneNode* _node;
		std::vector<RenderEntity*> _ent;
		std::string _name;
	};
}
#endif

