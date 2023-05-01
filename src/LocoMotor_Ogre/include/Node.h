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
		/// @param x X scale factor</param>
		/// @param y Y scale factor</param>
		/// @param z Z scale factor</param>
		void Scale(float x, float y, float z);

		/// @brief
		/// Sets the position.
		/// @param x X position
		/// @param y Y position
		/// @param z Z positiontion
		void SetPosition(float x, float y, float z);

		/// @brief
		/// Sets the position.
		/// @param x X position
		/// @param y Y position
		/// @param z Z position
		float GetPosition_X();
		float GetPosition_Y();
		float GetPosition_Z();

		/// @brief
		/// Gets the rotation.
		/// <param name="x">X position
		/// <param name="y">Y position
		/// <param name="z">Z position
		float GetRotation_W();
		float GetRotation_X();
		float GetRotation_Y();
		float GetRotation_Z();

		/// @brief
		/// Gets the position.
		/// @param x X position
		/// @param y Y position
		/// @param z Z position
		float GetScale_X();
		float GetScale_Y();
		float GetScale_Z();

		/// @brief
		/// Sets the scale of the node.
		/// @param x X scale factor</param>
		/// @param y Y scale factor</param>
		/// @param z Z scale factor</param>
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

		void SetOrientation(Ogre::Quaternion& q);

		Node* CreateChild(const std::string& name);

		std::string GetName();
	protected:
		Ogre::SceneNode* _node;
		std::vector<RenderEntity*> _ent;
		std::string _name;
	};
}
#endif

