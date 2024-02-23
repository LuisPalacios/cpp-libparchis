# Fichero `cmake` específico para DOXYGEN
#

# Primero le pido a CMake que busque el paquete Doxygen en mi
# sistema, que compruebe si está instalado
find_package(Doxygen)

# Si ve que `doxygen` está instalado
if(DOXYGEN_FOUND)
    # Añado un TARGET para poder ejecutar doxygen. Para hacerlo uso
    # la función add_custom_target() que es una especie de utility
    # target, que en vez de compilar lo que permite es ejecutar un
    # comando desde consola. Básicmente defino qué comando quiero
    # ejecutar, le doy un nombre "docs", le digo qué comando debe
    # ejecutar ${DOXYGEN_EXECUTABLE} que viene de la búsqueda previa
    # y le digo "dónde" ejecutarlo, en mi subdirectorio docs
    add_custom_target(
        docs
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs)
endif()

##
## Nota: La documentación que genera doxygen en el directorio `html`
## puede subirse a GitHub Pages.
##
