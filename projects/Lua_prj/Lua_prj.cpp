// Lua_prj.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <LuaBridge\LuaBridge.h>

class Vector3 {
protected:
    float x;
    float y;
    float z;
public:
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }
    void SetZ(float newZ) { z = newZ; }

    float GetX() { return x; }
    float GetY() { return y; }
    float GetZ() { return z; }
};

int main()
{
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
