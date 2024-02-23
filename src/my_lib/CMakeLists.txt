# Fichero `cmake` específico para mi librería
#

# Defino cuales son los fuentes y las cabeceras que quiero
# incluir en mi librería.
set(LIBRARY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/my_lib.cc"
    )
set(LIBRARY_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/my_lib.h"
    )
set(LIBRARY_INCLUDES
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    )

# Defino que quiero "linkar" con mi librería
add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})

if(NOT DEFINED IGNORELIBS) # Ignoro las librerias para subir la doc a  github pages
    target_link_libraries(
        ${LIBRARY_NAME}
        PRIVATE
                # Descomentar/comentar lo que te interese o añade más...
                # Nota: Necesitarás compilarlas desde el CMakeLists.txt principal.
                #       revisa la sección del gestor de paquetes.

                #nlohmann_json::nlohmann_json
                #fmt::fmt
                #cxxopts::cxxopts
                spdlog::spdlog)
endif()

# Si habilité el añadir más warnings, lo ejecuto aquí
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# Si habilité LTO lo ejecuto aquí
if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${LIBRARY_NAME}
        ENABLE
        ON)
endif()

# Si habilité CLANG Tidy lo ejecuto.
if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${LIBRARY_NAME})
endif()
