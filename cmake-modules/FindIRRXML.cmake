# Find IrrXMl from irrlicht project
#
# Find LibIrrXML headers and library
#
#   IRRXML_FOUND          - IrrXML found
#   IRRXML_INCLUDE_DIR    - Headers location
#   IRRXML_LIBRARY        - IrrXML main library
if(WIN32)

    set(IRRXML_ROOT_DIR "${CMAKE_SOURCE_DIR}/lib/IrrXML")
    set(IRRXML_LIB_NAME "IrrXML.lib")

    # Find includes
    find_path(IRRXML_INCLUDE_DIR 
        NAMES
            irrXML.h
        HINTS
            ${IRRXML_ROOT_DIR}/include
    )

    # Find library

    # location
    find_path(IRRXML_LIBRARY_DIR
    NAMES
        "${IRRXML_LIB_NAME}"
    HINTS
        ${IRRXML_ROOT_DIR}/lib
    )

    find_library(IRRXML_LIBRARY 
        "${IRRXML_LIB_NAME}" 			
    PATHS 
        ${IRRXML_LIBRARY_DIR})

    set(IRRXML_LIBRARIES ${IRRXML_LIBRARY})

    message("${IRRXML_LIBRARY} -> ${TargetDirectory}/Release/${IRRXML_LIB_NAME}")

    FUNCTION(IRRXML_COPY_LIBS TargetDirectory)
    ADD_CUSTOM_TARGET(IrrXmlCopyLibs
        COMMAND ${CMAKE_COMMAND} -E copy ${IRRXML_LIBRARY} ${TargetDirectory}/Release/${IRRXML_LIB_NAME}
        COMMENT "Copying IrrXml libraries to '${TargetDirectory}'"
        VERBATIM)
    ENDFUNCTION(IRRXML_COPY_LIBS)

else(WIN32)

    find_path(
        IRRXML_INCLUDE_DIRS
        NAMES postprocess.h scene.h version.h config.h cimport.h
        HINTS /usr/local/include/assimp /usr/include/assimp
    )

    find_library(
        IRRXML_LIBRARIES
        NAMES assimp
        HINTS /usr/local/lib/ /usr/lib/ /usr/lib/x86_64-linux-gnu
    )
    
    if (IRRXML_INCLUDE_DIRS AND IRRXML_LIBRARIES)
        SET(IRRXML_FOUND TRUE)
    ENDIF (IRRXML_INCLUDE_DIRS AND IRRXML_LIBRARIES)

    if (IRRXML_FOUND)
        if (NOT IRRXML_FIND_QUIETLY)
            message(STATUS "Found asset importer library: ${IRRXML_LIBRARIES}")
        endif (NOT IRRXML_FIND_QUIETLY)
        else (IRRXML_FOUND)
        if (IRRXML_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find asset importer library")
        endif (IRRXML_FIND_REQUIRED)
    endif (IRRXML_FOUND)

endif(WIN32)