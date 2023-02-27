#include "Singleton.h"
#include <memory>


template<typename T>
T* Singleton<T>::_instance = nullptr;

template<typename T>
template<typename ...Targs>
T* Singleton<T>::Init (Targs && ...args) {
	if (_instance != nullptr)
		return _instance;
	_instance = new T (std::forward<Targs> (args)...);
	return _instance;
}

template<typename T>
T* Singleton<T>::GetInstance () {
	if (_instance == nullptr) {
		return nullptr;
	}
	return _instance;
}

template<typename T>
void Singleton<T>::Clear () {
	delete _instance;
	_instance = nullptr;
}

/*
template<typename T>
T* Singleton<T>::_instance = nullptr;

template<typename T>
struct StaticHolder {
	static T* param;
};
template<typename T>
T* StaticHolder<T>::param = Singleton<T>::_instance;

template<typename T>
template<typename ...Targs>
T* Singleton<T>::Init (Targs && ...args) {
	if (StaticHolder<T>::param != nullptr)
		return StaticHolder<T>::param;
	StaticHolder<T>::param = new T (std::forward<Targs> (args)...);
	return StaticHolder<T>::param;
}

template<typename T>
T* Singleton<T>::GetInstance () {
	StaticHolder<T>::param;
	if (StaticHolder<T>::param == nullptr) {
		return nullptr;
	}
	return StaticHolder<T>::param;
}

template<typename T>
void Singleton<T>::Clear () {
	delete StaticHolder<T>::param;
	StaticHolder<T>::param = nullptr;
}
*/