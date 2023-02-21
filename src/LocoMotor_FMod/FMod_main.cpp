// FMod_prj.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fmod.hpp>

void prueba(const char* filename) {
    FMOD::System* a;
    FMOD::System_Create(&a);
    a->init(8, FMOD_INIT_NORMAL, 0);

    FMOD::Sound* test;
    std::cout << a->createSound(filename, FMOD_DEFAULT, nullptr, &test) << std::endl;    //18 == FMOD_ERR_FILE_NOTFOUND

    FMOD::Channel* ch;

    std::cout << a->playSound(test, nullptr, false, &ch) << std::endl;    //31 == FMOD_ERR_INVALID_PARAM

    bool isPlaying;
    ch->isPlaying(&isPlaying);
    std::cout << isPlaying<< std::endl;

}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
