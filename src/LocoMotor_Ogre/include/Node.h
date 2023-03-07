#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <string>

namespace Ogre {
	class SceneNode;
	class MovableObject;
}

namespace OgreWrapper {
	class RenderEntity;

	class Node {
	public:
		Node(Ogre::SceneNode* node);
		~Node();

		/// <summary>
		/// Translates the node, taking into account the actual position.
		/// Uses the parent node's axis as reference
		/// </summary>
		/// <param name="x">X translation</param>
		/// <param name="y">Y translation</param>
		/// <param name="z">Z translation</param>
		void Translate(float x, float y, float z);

		/// <summary>
		/// Rotates the node, taking into account the actual rotation.
		/// Uses the local axis as reference
		/// Parameters passed in Degrees
		/// </summary>
		/// <param name="x">X rotation</param>
		/// <param name="y">Y rotation</param>
		/// <param name="z">Z rotation</param>
		void Rotate(float x, float y, float z);

		/// <summary>
		/// Scales the node, taking into account the actual scale.
		/// </summary>
		/// <param name="x">X scale factor</param>
		/// <param name="y">Y scale factor</param>
		/// <param name="z">Z scale factor</param>
		void Scale(float x, float y, float z);

		/// <summary>
		/// Sets the position.
		/// </summary>
		/// <param name="x">X position</param>
		/// <param name="y">Y position</param>
		/// <param name="z">Z positiontion</param>
		void SetPosition(float x, float y, float z);

		/// <summary>
		/// Sets the position.
		/// </summary>
		/// <param name="x">X position</param>
		/// <param name="y">Y position</param>
		/// <param name="z">Z positiontion</param>
		float GetPosition_X();
		float GetPosition_Y();
		float GetPosition_Z();

		/// <summary>
		/// Sets the scale of the node.
		/// </summary>
		/// <param name="x">X scale factor</param>
		/// <param name="y">Y scale factor</param>
		/// <param name="z">Z scale factor</param>
		void SetScale(float x, float y, float z);

		/// <summary>
		/// Sets the point to wich the node looks.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void LookAt(float x, float y, float z);


		/// <summary>
		/// Sets the point to wich the node looks.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		void SetDirection(float x, float y, float z);

		/// <summary>
		/// Attaches an object to the node.
		/// </summary>
		/// <param name="obj"></param>
		void Attach(RenderEntity* ent);

		Node* CreateChild();
	protected:
		Ogre::SceneNode* _node;
		RenderEntity* _ent;
	};
}
#endif

