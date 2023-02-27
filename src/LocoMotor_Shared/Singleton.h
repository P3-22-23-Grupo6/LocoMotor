#pragma once
#ifndef LM_SINGLETON
#define LM_SINGLETON

template<typename T>
class Singleton {
public:

	/// @brief When trying to copy the singleton, the former instance will be deleted
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton (const Singleton<T>& o) = delete;

	/// @brief Use this method to initialize the corresponding class, passing the necessary parameters to construct it
	/// @param The necessary parameters to initialize the class 
	/// @return A pointer to the instance of the singleton
	template<typename ...Targs>
	static T* Init (Targs &&...args);

	/// @brief Get a pointer to the instance of the singleton
	/// @return :/
	static T* GetInstance ();

	/// @brief Use this method to delete the instance of the class, you can also use delete as with any other pointer
	static void Clear ();

protected:
	Singleton () = default;
	virtual ~Singleton () = default;

private:
	static T* _instance;
};

#endif

