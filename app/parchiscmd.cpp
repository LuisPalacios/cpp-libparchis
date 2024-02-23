/**
 *
 * parchiscmd.cpp
 * The Parchis cmdcpp
 *
 * Command Line Tool program for the Parchis game.
 *
 * This program uses the C++ engine library from parchis, as is, without any modification
 * as per Dec, 2010.
 *
 * Ported on January 2011
 * Copyright (c) 2009-2011 Luis Palacios
 * All rights reserved.
 *
 * Parchís is a Spanish board game of the Cross and Circle family.
 * It is an adaptation of the Indian game Pachisi. There are other
 * adaptations like Parcheesi, Ludo or Parqués.
 *
 */

#include "PDebug.h"
#include "PVersion.h"
//#include "ParchisCmd.h"
#include <cstdlib>
#include <getopt.h>
#include <iostream> // Stream declarations
#include <sstream>  // Stream declarations

// Mis variables estáticas
#include "config.hpp"

// Librerías externas
#include <spdlog/spdlog.h>

/**
 * Punto de entrada principal
*/
int main(int argc, char **argv)
{
    // Show the engine and Qt Versions
    PVersion *pVersion;
    pVersion = new PVersion();

    // Imprimir los valores
    std::cout << "Full   : " << pVersion->getVersionFull() << std::endl;
    std::cout << "TAG    : " << pVersion->getVersionTag() << std::endl;
    std::cout << "Commit : " << pVersion->getVersionCommit() << std::endl;
    std::cout << "Major  : " << pVersion->getVersionMajor() << std::endl;
    std::cout << "Minor  : " << pVersion->getVersionMinor() << std::endl;
    std::cout << "Patch  : " << pVersion->getVersionPatch() << std::endl;

    // Debug setup
    PDebug dbg;
    std::ostringstream oss;

    // Variables para hacer el parsing de argumentos
    bool showHelp = false;
    bool showVersion = false;

    // Long options
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"verbose", required_argument, NULL, 'v'},
        {"numgames", required_argument, NULL, 'n'},
        {"version", no_argument, NULL, 'V'},
        {"psn", required_argument, NULL, 'c'},
        {0, 0, 0, 0}};

    // Options check and analisys
    int c;
    int iDbgLevel = 0;
    int iNumGames = 1;

    while ((c = getopt_long(argc, argv, "hv:n:Vp:", long_options, NULL)) != -1)
    {
        switch (c)
        {
        case 'h':
            showHelp = true; // Show help and exit
            break;
        case 'v':
            iDbgLevel = atoi(optarg); // Activate the log level
            if (iDbgLevel < 0)
            {
                std::cout << "verbose level must equal or greater than 0"
                          << std::endl;
                return 2;
            }
            break;
        case 'n':
            iNumGames = atoi(
                optarg); // Will play iNumGames consecutive in "Console mode", implies -c
            if (iNumGames < 0)
            {
                std::cout << "Number of games must be > 0" << std::endl;
                return 2;
            }
            break;
        case 'V':
            showVersion = true; // Show version and exit
            break;
        case 'p':
            // ignore -psn* for macosx
            break;
        default:
            return 2;
        }
    }

    // Mensaje de log de bienvenida
    const auto welcome_message =
        fmt::format("Bienvenido a {} v{}\n", project_name, project_version);
    spdlog::info(welcome_message);

    // Hello World
    std::cout << "Hello World !" << std::endl;

    // Show help and/or version information:
    if (showHelp || showVersion)
    {
        if (showHelp)
        {

            std::cout
                << "Parchis, engine v" << pVersion->getVersion() << std::endl
                << std::endl
                << "Uso: " << project_name << std::endl
                << "  -h,        --help           print this help and exit"
                << std::endl
                << "  -v level,  --verbose=level  set verbosity level "
                   "(default: 0)"
                << std::endl
                << "  -n num,    --numgames=num   play num games (only cmd "
                   "mode)"
                << std::endl
                << "  -V         --version        show version number and exit"
                << std::endl;
        }

        if (showVersion)
        {
            // std::cout << std::endl << "Parchis v" << version << std::endl;
            std::cout << "Parchis, engine v" << pVersion->getVersion()
                      << std::endl
                      << std::endl;
        }

        return 0;
    }

    return 0;
}
