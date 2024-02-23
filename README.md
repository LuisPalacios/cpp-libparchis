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

# libparchis c++

&nbsp;

<div align="center">

![Parchis](art/logo-libparchis@2x.png?raw=true "logo-libparchis")

<div align="left">

&nbsp;

Este proyecto consiste en la librería del juego del Parchis desarrollada C++ que hago disponible como open source en febrero de 2024. ¿Qué es el Parchis?... pues un juego de tables, que también se conoce como Pachisi, Parchisi, Parchesi, Veinticinco o Parchís. Se trata de una adaptación del juego indio de la cruz y el círculo *Pachisi*. Creado en la India alrededor del año 500 a.C., el juego suele subtitularse Juego Real de la India porque supuestamente la realeza jugaba utilizando bailarines disfrazados como piezas en grandes tableros al aire libre (se conserva un tablero de este tipo en Fatehpur Sikri).

Empecé a desarrollar El Parchis en 1995 para aprender Visual Basic, luego lo rehice en Java, después lo volví a hacer en C++ (aquí es donde creé la primera versión de esta librería), más adelante he creado versiones del fronted (gui) en Qt, Objective-C y la última en Swift y un intento en OpenGL.

Para mi ha constituido un proyecto de aprendizaje de programación. Siempre es más fácil aprender un lenguaje nuevo cuando tienes un objetivo en mente.

La parte frontend no la he subido a GitHub, de momento...

&nbsp;

<div align="center">

![Parchis](./art/div-parchis.png?raw=true "ParchisDiv")

<div align="left">


---

<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/LuisPalacios/cpp-libparchis">Librería juego del Parchis en C++</a> © 2024 por <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://www.luispa.com/about/">Luis Palacios Derqui</a> licenciada bajo <a href="http://creativecommons.org/licenses/by-nc-nd/4.0/deed.es/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-NC-ND 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nd.svg?ref=chooser-v1"></a></p>
