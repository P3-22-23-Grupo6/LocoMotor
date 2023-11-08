#ifndef LM_PARTICLESYS
#define LM_PARTICLESYS
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"

namespace OgreWrapper {
	class ParticleHelper;
	class Node;
	class RenderScene;
}

namespace LocoMotor {
	class Scene;
	class GameObject;
	class MOTOR_API ParticleSystem : public Component {
	public:
		ParticleSystem();
		OgreWrapper::Node* _node;

		/// @brief Initializes the particle system by setting its name and filename based on the input
		/// @param params A vector of pairs, where each pair contains a string key and a string value. These
		/// pairs represent the parameters passed to the Init() function.
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitRuntime(std::string fileName, std::string fileMat) ;


		/// @brief Initializes a particle system component by creating a node, creating particles,
		///	attaching them to the node of the game object, and setting the node to the game object.
		void Start() override;

		/// @brief updates the position of a particle system node based on the position of its associated
		/// game object. 
		/// @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
		/// used to ensure that the particle system updates at a consistent rate regardless of the frame rate.
		void Update(float dt) override;

		bool allowMultiple = true;

	private:
		OgreWrapper::RenderScene* _renderScn;
		OgreWrapper::ParticleHelper* _particleHelper;

		std::string _filename;
		std::string _name;
	};
}

#endif