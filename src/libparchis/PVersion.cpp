/**
 *  @class  PVersion PVersion.cpp "PVersion.cpp"
 *  @file   PVersion.cpp
 *  @brief  Parchis Class: Simply used to return the subversion number
 *
 *  ---------------------------------------------------------------------------
 */


//---------------------------------------------------------------------------

#include "PVersion.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma mark -
#pragma mark Public Methods

//---------------------------------------------------------------------------

/**
 * Constructor of PVersion
 *
 */
PVersion::PVersion()
{
    // Crear una expresión regular para validar el formato
    std::regex versionRegex("^v(\\d+)\\.(\\d+)\\.(\\d+)$");
    std::smatch matches;

    // Comprobar si el string coincide con el formato de la expresión regular
    if (std::regex_match(version_tag, matches, versionRegex))
    {
        // Convertir y almacenar los números
        version_major = std::stoi(matches[1].str());
        version_minor = std::stoi(matches[2].str());
        version_patch = std::stoi(matches[3].str());
    }
}

//---------------------------------------------------------------------------

/**
 * Destructor of PVersion
 *
 */
PVersion::~PVersion()
{
}

//---------------------------------------------------------------------------

/**
 * Getter: Return the Full git version of Parchis Engine
 *         Value of this command when library was compiled
 *         git describe --tags --long
 *
 * @return string with version of the library, tag plus commit
 */
std::string PVersion::getVersionFull()
{
    return version_full;
}

/**
 * Getter: Return the git TAG of the library
 *         Value of this command when library was compiled
 *         git describe --abbrev=0 --tags
 *
 * @return string with version of the library, the tag of the commit
 */
std::string PVersion::getVersionTag()
{
    return version_tag;
}

/**
 * Getter: Return the git COMMIT of the library
 *         Value of this command when library was compiled
 *         git rev-parse --short HEAD
 *
 * @return string with version of the library, the commit
 */
std::string PVersion::getVersionCommit()
{
    return version_commit;
}

/**
 * Getter: Return the git TAG major value
 *         Value X of this command when library was compiled
 *         git describe --abbrev=0 --tags -> vX.Y.Z
 *
 * @return int with the major version of the library.
 */
int PVersion::getVersionMajor()
{
    return version_major;
}

/**
 * Getter: Return the git TAG minor value
 *         Value Y of this command when library was compiled
 *         git describe --abbrev=0 --tags -> vX.Y.Z
 *
 * @return int with the minor version of the library.
 */
int PVersion::getVersionMinor()
{
    return version_minor;
}
/**
 * Getter: Return the git TAG patch value
 *         Value Z of this command when library was compiled
 *         git describe --abbrev=0 --tags -> vX.Y.Z
 *
 * @return int with the patch version of the library.
 */
int PVersion::getVersionPatch()
{
    return version_patch;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
