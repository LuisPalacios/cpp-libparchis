# Fichero principal `cmake` para el proyecto.
#
cmake_minimum_required(VERSION 3.21)

# Cambiar nombre y versión
project(
    "C++ Plantilla"
    VERSION 1.0.0
    LANGUAGES C CXX)

# Variables globales de CMake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opciones Gestor de Paquetes
option(USE_CPM "Si queremos usar CPM." ON)
option(USE_CONAN "Si queremos usar Conan." OFF)
option(USE_VCPKG "Si queremos usar VCPKG." OFF)

# Opciones alrededor de Unit Testings
option(ENABLE_TESTING "Habilitar el build de Unit Testing." ON)

# Opciones para habilitar el mostrar más Warnings
option(ENABLE_WARNINGS "Añadir warnings al target." OFF)
option(ENABLE_WARNINGS_AS_ERRORS "Tratar los warnings como errores." OFF)

# Opciones para formateo de CLAN y CMAKE
option(ENABLE_CLANG_FORMAT "Añadir clang-format." OFF)
option(ENABLE_CMAKE_FORMAT "Añadir cmake-format." OFF)

# Opciones alrededor de CLANG Tidy
option(ENABLE_CLANG_TIDY "Añadir clang tidy." OFF)

# Opciones alrededor de Sanitización del código.
option(ENABLE_SANITIZE_ADDR "Habilitar address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Habilitar undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Habilitar leak sanitize (solo Gcc/Clang)." OFF)
option(ENABLE_SANITIZE_THREAD "Habilitar thread sanitize (solo Gcc/Clang)." OFF)

# Opciones alrededor de Coverage (de tests)
option(ENABLE_COVERAGE "Habilitar el build de Code Coverage." OFF)

# Oopciones para LTO
option(ENABLE_LTO "Añadir Link Time Optimization." OFF)

# Nombres del proyecto y la librería
set(LIBRARY_NAME "lib")
set(UNIT_TEST_NAME "unit_tests")
set(EXECUTABLE_NAME "main")

# Incluyo módulos adicionales CMake obligatorios
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(AddGitSubmodule)
include(Docs)               # Incluyo el cmake Docs.cmake

# Incluyo el módulo CMake de Warnings si lo habilité
if(ENABLE_WARNINGS)
    include(Warnings)
endif()

# Incluyo el módulo CMake de CLang format si lo habilité
if(ENABLE_CLANG_FORMAT)
    include(FormatCLang)
    add_clang_format_target()
endif()

# Incluyo el módulo CMake de CMake format si lo habilité
if(ENABLE_CMAKE_FORMAT)
    include(FormatCMake)
    add_cmake_format_target()
endif()

if(ENABLE_CLANG_TIDY)
    include(ClangTidy)
endif()

# Incluyo los módulos de Sanitizer si lo habilité
if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

# Incluyo los módulos de Coverage si lo habilité
if(ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

# Incluyo el módulo de Link Time Optimization si lo habilité
if(ENABLE_LTO)
    include(LTO)
endif()

# Añado las librerías externas. Dependiendo de ué método de
# gestión de paquetes quiero usar: Conan, VCPKG o CPM
if(NOT DEFINED IGNORELIBS) # Ignoro las librerias para subir la doc a  github pages
    if(USE_CONAN)
        message(STATUS "Usando Conan")
        include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
        find_package(nlohmann_json REQUIRED)
        find_package(fmt REQUIRED)
        find_package(spdlog REQUIRED)
        find_package(Catch2 REQUIRED)
        find_package(cxxopts REQUIRED)
    elseif(USE_VCPKG)
        message(STATUS "Usando VCPKG")
        include(${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake)
        find_package(nlohmann_json REQUIRED)
        find_package(fmt REQUIRED)
        find_package(spdlog REQUIRED)
        find_package(Catch2 REQUIRED)
        find_package(cxxopts REQUIRED)
    else(USE_CPM)
        message(STATUS "Usando CPM")
        include(CPM)
        # Dejo un par como ejemplo. Comentar o descomentar o añadir...
        cpmaddpackage("gh:gabime/spdlog@1.11.0")
        cpmaddpackage("gh:catchorg/Catch2@2.13.9")
        #cpmaddpackage("gh:fmtlib/fmt#9.1.0")
        #cpmaddpackage("gh:nlohmann/json@3.11.2")
        #cpmaddpackage("gh:jarro2783/cxxopts@3.1.1")
    endif()
endif()

# Librerías externas binarias.

# Boost libraries
# Ejemplo donde añado system, filesystem y regex
if(NOT DEFINED IGNORELIBS) # Ignoro las librerias para subir la doc a  github pages
    find_package(Boost 1.74.0
        REQUIRED
            system
            filesystem
            regex)
endif()

# Añado sub directorios
add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)

# Defgino los targets de instalación del ejecutable y la librería
install(
    TARGETS ${EXECUTABLE_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)
