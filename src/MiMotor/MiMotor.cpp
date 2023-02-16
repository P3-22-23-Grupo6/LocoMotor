// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"

void prueba(const char* filename);
int main()
{
    OgreWrapper::OgreManager::init("Prueba");
    OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::getInstance();
    man->createScene("Escena");
    man->createScene("Escena2");

    OgreWrapper::Scene* x = man->getScene("Escenah");
    std::cout << (x == nullptr ? "null\n" : "jiji\n");
    man->render();
    
    std::cout << "Hello World!\n";
    char basura;
    std::cin >> basura;
    return 0;
}
