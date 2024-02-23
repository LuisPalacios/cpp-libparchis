# Plantilla para proyectos C++

![C++](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20%2F23-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Linux Build](https://github.com/LuisPalacios/CppPlantilla/actions/workflows/ubuntu.yml/badge.svg)
![MacOS Build](https://github.com/LuisPalacios/CppPlantilla/actions/workflows/macos.yml/badge.svg)
[![codecov](https://codecov.io/gh/LuisPalacios/CppPlantilla/graph/badge.svg?token=VXUOCDCWQ5)](https://codecov.io/gh/LuisPalacios/CppPlantilla)

&nbsp;

## Cómo utilizar la plantilla

- Desde GitHub, clona esta plantilla y úsala al crear un nuevo Repositorio:
  - **Repository name**: Nombre de tu nuevo repositorio
  - **Repository template**: CppPlantilla
  - **Include All Branches**: `[x]` (Para que incluya `gh-pages`)
  - **Description**: Añadir una descripción opcional.
- Realiza los siguientes cambios para que se publique en tu GitHub Pages
  - Repositorio -> Settings -> Pages
    - **Source: Deploy from a branch**
    - **Branch: gh-pages  Directorio: /(root))  Clic en SAVE**
  - Repositorio -> Settings -> Actions -> General
    - **Workflow Permissions: Read and write**
  - Modifica el fichero `./docs/Doxyfile` y cambia la siguiente línea.
    - **PROJECT_NAME = "C++ Plantilla LuisPa"**
- Entra en tu cuenta de [codecov.io](https://codecov.io) y configura el nuevo repo.
  - **CODECOV_TOKEN**: Añade nuevo `repository secret` en Repo > settings > secrets ... > actions
  - `.github/workflows/ubuntu.yml`: Cambia (`slug: TuCuentaGitHub/CppPlantilla`) con tu usuario/repo.
- Verifica y adapta el fichero `.vscode/settings.json` a tus gustos.
- Modifica este fichero `./README.md`
  - Cambia la primera línea por el título de tu proyecto
  - Cambia los enlaces a los cuatro Badges: C++, Licencia, Build, Codecov.
  - Cambia el contenido desde `## Cómo utilizar la plantilla` por el tuyo.
- Empieza a codificar, cambia los fuentes incluidos como ejemplo:
  - `./tests/main.cc`
  - `./src/my_lib/my_lib.cc`
  - `./src/my_lib/my_lib.h`
  - `./app/main.cc`
- Revisa los `CMakeLists.txt` para indicar tus fuentes, librerías, gestores, etc.
  - `./CMakeLists.txt`
  - `./src/my_lib/CMakeLists.txt`
  - `./app/CMakeLists.txt`

&nbsp;

## Qué es esta plantilla?

Puedes utilizarla a la hora de crear un repositorio nuevo para un proyecto C++ en tu cuenta de GitHub. Incluye todo lo siguiente:

- Buenas prácticas separando los fuentes y las cabeceras en carpetas distintas
- Uso de CMake para construir y compilar
- Soporte de bibliotecas externas, usando uno de los tres siguientes gestores:
  - Gestor de paquetes [CPM](https://github.com/cpm-cmake/CPM.cmake)
  - Gestor de paquetes [Conan](https://conan.io/)
  - Gestor de paquetes [VCPKG](https://github.com/microsoft/vcpkg)
  - Incluye varias bibliotecas de propósito general a modo de ejemplo: [JSON](https://github.com/nlohmann/json), [spdlog](https://github.com/gabime/spdlog), [cxxopts](https://github.com/jarro2783/cxxopts) y [fmt](https://github.com/fmtlib/fmt)
- Incluye Unit Tests con [Catch2](https://github.com/catchorg/Catch2) v2
- Pruebas de integración continua con Github Actions y [pre-commit](https://pre-commit.com/)
- Informes de cobertura del código, incluida la carga automática a [Codecov](https://codecov.io)
- Documentación del código con [Doxygen](https://doxygen.nl/) y [Github Pages](https://franneck94.github.io/CppProjectTemplate/)
- Herramientas: Clang-Format, Cmake-Format, Clang-tidy, Sanitizers

&nbsp;

## Estructura

``` text
├── CMakeLists.txt
├── app
│   ├── CMakesLists.txt
│   └── main.cc
├── cmake
│   └── cmake modules
├── docs
│   ├── Doxyfile
│   └── html/
├── external
│   ├── CMakesLists.txt
│   ├── ...
├── src
│   ├── CMakesLists.txt
│   ├── my_lib.h
│   └── my_lib.cc
└── tests
    ├── CMakeLists.txt
    └── main.cc
```

El código de la librería está en [src/](src/), el programa en [app/](app) y los tests en [tests/](tests/).

&nbsp;

## Requisitos de software

- CMake 3.21+
- GNU Makefile
- Doxygen
- Conan or VCPKG
- MSVC >= 2017, G++ >= 9, Clang++ >= 9
- Opcional: Code Coverage (Solo sobre GNU|Clang): lcov, gcovr
- Optional: Makefile, Doxygen, Conan, VCPKG

&nbsp;

## Instalación y construcción

Primero hacer un clone y seguir los pasos que describo al principio (*Cómo utilizar la plantilla*).

```shell
git clone --recursive https://github.com/LuisPalacios/CppPlantilla.git
make prepare
```

- Crear el ejecutable

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
cd app
./main
```

- Unit testing

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target unit_tests
cd tests
./unit_tests
```

- Documentación

La documentación que genera doxygen en el directorio `html` puede subirse a GitHub Pages. Consultar la siguiente sección.

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target docs
```

- Code Coverage

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON ..
cmake --build . --config Debug --target coverage
```

Si quieres saber más sobre CMake consulta [este artículo](./README_cmake.md).

&nbsp;

## Preparar GitHub Pages

Si has creado un repositorio nuevo partiendo de esta plantilla no necesitas crear la rama `gh-pages+ de nuevo, dejo aquí documentado todo el proceso solo como referencia.

GitHub permite, a través de su servicio *GitHub Pages* hospedar tus propias páginas web en cada uno de tus repositorios. Podemos usarlo para subir la documentación de nuestro repositorio.

El proceso está documentado en [pages.github.com](https://pages.github.com) y en su [documentación oficial](https://docs.github.com/en/pages/setting-up-a-github-pages-site-with-jekyll/creating-a-github-pages-site-with-jekyll).

Para este respositorio sigue esta chuleta:

- Crea la rama `gh-pages`

Crea una nueva branch, sin histórico ni contenido, llamada `gh-pages`

```shell
git checkout --orphan gh-pages
git rm -rf .

mkdir docs
cd docs
touch .keep.txt
git add .
git commit -m 'Creación inicial de la rama gh-pages'
git push --set-upstream origin gh-pages
```

- Entra en GitHub desde el navegador y activa GitHub Pages.

  - Haz clic en la pestaña Configuración / Settings.
  - Haz clic en `Pages` en la parte izquierda.
  - Source: Deploy from a branch
  - Branch: gh-pages  Directorio: /(root))  Clic en SAVE

- Verifica que tienes el fichero [~/.github/workflows/documentation.yaml](./.github/workflows/documentation.yml) preparado con las acciones a realizar.

- Verifica que tienes permisos.

  - Haz clic en la pestaña Configuración / Settings.
  - Haz clic en `Actions->General` en la parte izquierda.
  - Workflow Permissions: Read and write

- Haz un push al repositorio.

```shell
touch algo.txt
git push
```

- Ve a tu repositorio -> Actions (debería estar construyendo la documentación)

</br>
