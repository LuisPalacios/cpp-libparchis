# Fichero `cmake` para el main !!
#

# Especifico cuales son los fuentes a incluir
set(APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")

# Especifico la ubicación del ejecutable
add_executable(
    ${EXECUTABLE_NAME}
    ${APP_SOURCES})

if(NOT DEFINED IGNORELIBS) # Ignoro las librerias para subir la doc a  github pages
    # Hago el link del ejecutable con las librerías
    target_link_libraries( ${EXECUTABLE_NAME}
        PRIVATE
        ${LIBRARY_NAME}     # Mi librería propia

        # Librerías binarias o externas adicionales, (Ver /CMakeLists.txt)
        Boost::regex
        #fmt::fmt
        spdlog::spdlog
        )
endif()

# Si habilité el añadir más warnings, lo ejecuto aquí
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${EXECUTABLE_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# Si habilité LTO lo ejecuto aquí
if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${EXECUTABLE_NAME}
        ENABLE
        ON)
endif()

# Si habilité CLANG Tidy lo ejecuto.
if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${EXECUTABLE_NAME})
endif()
