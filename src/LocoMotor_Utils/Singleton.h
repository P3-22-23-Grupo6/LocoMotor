#pragma once
#ifndef LM_SINGLETON
#define LM_SINGLETON
//#include "CheckML.h"

#include <utility>
template<typename T>
class Singleton {
public:

	/// @brief When trying to copy the singleton, the former instance will be deleted
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;

	/// @brief Use this method to initialize the corresponding class, passing the necessary parameters to construct it
	/// @param The necessary parameters to initialize the class 
	/// @return A pointer to the instance of the singleton
	template<typename ...Targs>
	static T* Init(Targs &&...args) {
		if (_instance != nullptr)
			return _instance;
		_instance = new T(std::forward<Targs>(args)...);
		return _instance;
	};

	/// @brief Get a pointer to the instance of the singleton
	/// @return :/
	static  T* GetInstance() {
		if (_instance == nullptr) {
			return nullptr;
		}
		return _instance;
	};

	/// @brief Use this method to delete the instance of the class, you can also use delete as with any other pointer
	static void Clear() {
		delete _instance;
		_instance = nullptr;
	};


protected:
	Singleton() = default;
	virtual ~Singleton() = default;

private:
	 static  T* _instance;
};

#endif

