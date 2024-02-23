/**
 *  @class  PVersion PVersion.h "PVersion.h"
 *  @brief  Parchis Class: To stablish the semantic versioning and build
 *
 *  Belongs to the Library: "Parchis Engine C++ library"
 *
 *  @author  Luis Palacios
 *  @date    2024/02/23
 *
 *  @par Description
 *
 * This class is simply used to return the semantic version and build code of the library.
 *
 * ======================================================================================================
 * Semantic Versioning and Git Tags
 *
 * There are three parts to a semantic version number:
 * The major number     Breaking functionality changes
 * The minor number     Backwards compatibly functionality changes
 * The path number      Bug fixes and trivial updates
 *
 * A semantic version, once set, should be considered set in stone. Once released, that version of
 * the code cannot be changed. Once you’ve marked a version of your codebase with a semantic version, you
 * are not supposed to change which state of your code that version points to. If you’ve released
 * version 1.3.0, a minor release, and you realize you missed something, you can’t just arbitrarily
 * add it to your Git repository and then re-tag that commit. If you’ve released a version that needs
 * to be updated, you will have to create a new release, complete with a new semantic version number.
 *
 * In the worst-case scenario, if you release version 2.0.0 of your application and then realize you
 * forgot to add a bunch of files to your repo, you would have to create a new major release, going
 * immediately from version 2.0.0 to 3.0.0. That is not fun for anybody.
 *
 * Using semantic versioning in your project means being responsible for double-checking your version
 * number before you release your code. As soon as your code is released into a production environment,
 * you have to assume that somebody is using the code, and you should not change the version number.
 * This is especially true for publicly released code, such as npm packages.
 *
 * ======================================================================================================
 * Annotated Git Tags + Semantic Versioning
 *
 * Because semantic versions are set in stone, this makes them perfect for combining with Git tags.
 * A Git tag is a way to add a marker to a Git commit to signify that it’s a meaningful commit in some way
 *
 * There are two different types of Git tags.
 *
 * LIGHTWEIGHT TAGS (NO USAR)
 * First are lightweight tags. Lightweight tags are basically just named pointers to a commit.
 * It’s a human-readable name that you can assign to a Git commit hash. To generate a lightweight
 * tag in the Git CLI, you use the `git tag` command followed by the tag name, and then potentially
 * the hash of the commit you want that tag applied to. If you only want the tag to reference the
 * current commit, you can omit the commit hash.
 *
 *      git tag <tag-name> [commit]   <=== NO USAR !!!!
 *
 * ANNOTATED TAGS (USAR)
 * The other types of Git tags are known as annotated tags. These are the recommended types of tags
 * to use in your projects because, in addition to being human-readable names associated with a Git
 * commit hash, they become full objects in the Git database. Without getting too deep into Git
 * structure via database, a ‘full object’ means that the object can be checksummed.
 *
 * Annotated Git tags are also the recommended type of tags to use as they contain additional information
 * about the commit, like who created the tag, when they created it, as well as providing tag messages
 * in addition to the commit message. For public projects, they can be signed and verified using systems
 * like PGP or GPG.
 *
 * Using the `git tag -a` will denote it as an annotated tag. Adding the -m flag will provide some sort
 * of annotation message, and the hash for the commit you’re applying the tag to.
 *
 *      git tag -a <tag-name> -m "<anotación>" [commit]  <== USAR "-a"
 *
 * There is a lot of value in naming your annotated tags using the semantic version number.  This practice generates
 * semantic releases, sometimes referred to ​​semantic version build numbers, which allow you to have
 * marked commits in your Git repository with a specific version number. If you change the major, minor, or
 * patch version number, you’re indicating the level of changes since your last Git tag. This is a very
 * helpful way to demonstrate the level of changes in your codebase.
 *
 * Using semantic releases in a Git repository allows you to more easily review your history and track how and
 * when changes were made in your codebase. This is really helpful to you, but also to your team and potentially
 * your users, especially when viewing your release notes.
 *
 * ======================================================================================================
 * Semantic Versioning and Release Notes
 *
 * While semantic releases are extremely useful to the internal team working on a project, if you are going
 * to expose these release numbers externally in your release notes, there are still a few additional considerations.
 * There are multiple approaches to creating release notes—the accompanying documentation pushed out with most
 * software releases—but in every case, the goal is to provide information beyond just: “the code was updated.”
 * If you just do the bare minimum of exposing the ​​semantic version build number in these release notes, this can
 * provide a degree of changes, but it doesn’t provide any information about what changed. While you may be able
 * to get away with this for patch releases, it’s not enough for minor or major updates.
 *
 * Minor changes, or any change that introduces new functionality, needs, at a very minimum, to expose the
 * annotation messages and provide usage details. Ideally, these details could be included in the annotation message.
 *
 * Major releases, or any release that requires people to do some sort of upgrade, should give people an
 * understanding of any actions that they will need to take as a result.
 *
 * Recommended minimum for annotations
 *
 * Patch release - list of bug fixes
 * Minor release - list of changes, usage details
 * Major release - list of removals, additions, upgrade process
 *
 *
 * ======================================================================================================
 * libparchis convention:
 *
 *      vM.m.p (build)
 *       | | |   |
 *       | | |   +----- git rev-parse --short HEAD (i.e. 3ad9785)
 *       | | +--------- patch number
 *       | +----------- minor number
 *       +------------- major number
 *
 * Establecer el TAG con la Versión Major.Minor.Patch y una descripción
 *
 *      git tag -a v1.0.0 -m "Versión inicial"
 *
 * Visualizar TAG de la rama actual
 *
 *      git describe --tags --long
 *      v1.0.0-0-g3ad9785
 *
 *      git describe --abbrev=0 --tags
 *      v1.0.0
 *
 *      git rev-parse --short HEAD
 *      g3ad9785
 *
 *
 *
 *
 *
$ cat > _libcpp_git.sh


 git=/usr/bin/git
 version=`$git describe --tags --long`
 echo '#include "PVersion.h"'                  > ../PVersion.cpp
 echo ""                                      >> ../PVersion.cpp
 echo ""                                      >> ../PVersion.cpp
 echo "PVersion::PVersion () "                >> ../PVersion.cpp
 echo "{"                                     >> ../PVersion.cpp
 echo -n '    version = "'  >> ../PVersion.cpp
 echo -n ${version}                           >> ../PVersion.cpp
 echo '";'                                    >> ../PVersion.cpp
 echo "}"                                     >> ../PVersion.cpp
 echo ""                                      >> ../PVersion.cpp
 echo "PVersion::~PVersion () "               >> ../PVersion.cpp
 echo "{"                                     >> ../PVersion.cpp
 echo "}"                                     >> ../PVersion.cpp
 echo ""                                      >> ../PVersion.cpp
 echo "const char* PVersion::getVersion ()"   >> ../PVersion.cpp
 echo "{"                                     >> ../PVersion.cpp
 echo "    return version;"                   >> ../PVersion.cpp
 echo "}"                                     >> ../PVersion.cpp


 $ chmod 755 _libcpp_git.sh

 * 2) Invoque it as the first built step in QTCreator

   Projects, build steps, add a step and move it to the first position
   Enable   : Yes
   Name     : Create Version.cpp
   Command  : Complete_path_to_the_script/_libcpp_svnversion.sh  or
              Complete_path_to_the_script/_libcpp_git.sh  or
   Work Dir : %{sourceDir}

 * @endcode
 *
 *
 * @par Under XCode
 * Project->Target->Add Target->Aggregate->Run Script
 * @code

 git=/usr/bin/git
 version=`$git describe --tags --long`

 echo "/ **                                                                            " >  ../PVersion.cpp
 echo ' *  @class  PVersion PVersion.cpp \"PVersion.cpp\"                             ' >> ../PVersion.cpp
 echo " *  @file   PVersion.cpp                                                       " >> ../PVersion.cpp
 echo " *  @brief  Parchis Class: Simply used to return the subversion number         " >> ../PVersion.cpp
 echo " *                                                                             " >> ../PVersion.cpp
 echo " *  ---------------------------------------------------------------------------" >> ../PVersion.cpp
 echo " * /                                                                            " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo '#include "PVersion.h"                                                          ' >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "#pragma mark -                                                                 " >> ../PVersion.cpp
 echo "#pragma mark Public Methods                                                    " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "/ **                                                                            " >> ../PVersion.cpp
 echo " * Constructor of PVersion                                                     " >> ../PVersion.cpp
 echo " *                                                                             " >> ../PVersion.cpp
 echo " * /                                                                            " >> ../PVersion.cpp
 echo "PVersion::PVersion ()                                                          " >> ../PVersion.cpp
 echo "{                                                                              " >> ../PVersion.cpp

 echo -n '    version = "'                    >> ../PVersion.cpp
 echo -n ${version}                           >> ../PVersion.cpp
 echo '";'                                    >> ../PVersion.cpp

 echo "}                                                                              " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "/ **                                                                            " >> ../PVersion.cpp
 echo " * Destructor of PVersion                                                      " >> ../PVersion.cpp
 echo " *                                                                             " >> ../PVersion.cpp
 echo " * /                                                                            " >> ../PVersion.cpp
 echo "PVersion::~PVersion ()                                                         " >> ../PVersion.cpp
 echo "{                                                                              " >> ../PVersion.cpp
 echo "}                                                                              " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "/ **                                                                            " >> ../PVersion.cpp
 echo " * Getter: Return the version of Parchis Engine                                " >> ../PVersion.cpp
 echo " *                                                                             " >> ../PVersion.cpp
 echo " * @return the version of parchis engine                                       " >> ../PVersion.cpp
 echo " * /                                                                            " >> ../PVersion.cpp
 echo "const char* PVersion::getVersion ()                                            " >> ../PVersion.cpp
 echo "{                                                                              " >> ../PVersion.cpp
 echo "    return version;                                                            " >> ../PVersion.cpp
 echo "}                                                                              " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp
 echo "//---------------------------------------------------------------------------  " >> ../PVersion.cpp
 echo "                                                                               " >> ../PVersion.cpp


 *  @endcode
 */


#ifndef PVERSION_H
#define PVERSION_H

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma mark ====== INCLUDES

//---------------------------------------------------------------------------

// Standard includes
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

// My includes
#include "PDebug.h"
#include "gitversion.hpp"

//---------------------------------------------------------------------------

#pragma mark ====== CLASS PSnapshot

//---------------------------------------------------------------------------

class PVersion
{

#pragma mark ====== PRIVATE INSTANCE MEMBERS
private:
    // DEBUGGING purposes

    PDebug dbg;             //!< To be able to send Log messages
    std::ostringstream oss; //!< Construct complex strings


    // STATIC PRIVATE ATTRIBUTES (For ivar's use comments for doxygen: //!<)
    const char *version; //!< Version number
    std::string version_full =
        GITVERSION_FULL; //!< Version number (git describe --tags --long)        v1.2.33-0-g3ad9785
    std::string version_tag =
        GITVERSION_TAG; //!< Version number (git describe --abbrev=0 --tags)    v1.2.33
    std::string version_commit =
        GITVERSION_COMMIT; //!< Version number (git rev-parse --short HEAD)        g3ad9785
    int version_major =
        0; //!< Major                                              1
    int version_minor =
        0; //!< Minor                                              2
    int version_patch =
        0; //!< Path                                               33

#pragma mark ====== PUBLIC INSTANCE METHODS
public:
    // CONSTRUCTORS/DESTRUCTOR

    PVersion();          // Constructor
    virtual ~PVersion(); // Destructor

    // Getter
    const char *getVersion();
    std::string getVersionFull();
    std::string getVersionTag();
    std::string getVersionCommit();
    int getVersionMajor();
    int getVersionMinor();
    int getVersionPatch();
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#endif // PVERSION_H
