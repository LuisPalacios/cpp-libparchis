// Ejemplo de programa sencillo en CPP

// Estándares
#include <iostream>

// Mis variables estáticas
#include "config.hpp"

// Librerías externas
#include <spdlog/spdlog.h>

/**
 * Punto de entrada principal
*/
int main(int argc, char **argv)
{
    // Mensaje de log de bienvenida
    const auto welcome_message = fmt::format("Bienvenido al programa {} v{}\n",
                                             project_name,
                                             project_version);
    spdlog::info(welcome_message);

    // Hello World
    std::cout << "Hello World !" << std::endl;

    return 0;
}
