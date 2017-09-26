if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ASSIMP_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(ASSIMP_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)
	set(ASSIMP_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/lib/assimp")

	# Find path of each library
	find_path(ASSIMP_INCLUDE_DIRS
		NAMES
			assimp/anim.h
		HINTS
			${ASSIMP_ROOT_DIR}/include
	)

	if(MSVC12)
		set(ASSIMP_MSVC_VERSION "vc120")
	elseif(MSVC14)	
		set(ASSIMP_MSVC_VERSION "vc140")
	elseif(MSVC15)	
		set(ASSIMP_MSVC_VERSION "vc150")
	endif(MSVC12)
	
	if(MSVC12 OR MSVC14 OR MSVC15)
	
		find_path(ASSIMP_LIBRARY_DIR
			NAMES
				assimp-${ASSIMP_MSVC_VERSION}-mt.lib
			HINTS
				${ASSIMP_ROOT_DIR}/lib${ASSIMP_ARCHITECTURE}
		)

		find_library(ASSIMP_LIBRARY_RELEASE				assimp-${ASSIMP_MSVC_VERSION}-mt.lib 			PATHS ${ASSIMP_LIBRARY_DIR})
				
		set(ASSIMP_LIBRARY optimized 	${ASSIMP_LIBRARY_RELEASE})
		
		set(ASSIMP_LIBRARIES "${ASSIMP_LIBRARY_RELEASE}")
	
	FUNCTION(ASSIMP_COPY_LIBS TargetDirectory)
	ADD_CUSTOM_TARGET(AssimpCopyLibs
		COMMAND ${CMAKE_COMMAND} -E copy ${ASSIMP_ROOT_DIR}/bin${ASSIMP_ARCHITECTURE}/assimp-${ASSIMP_MSVC_VERSION}-mt.lib 		${TargetDirectory}/Release/assimp-${ASSIMP_MSVC_VERSION}-mt.lib
		COMMENT "Copying Assimp libraries to '${TargetDirectory}'"
		VERBATIM)
	ENDFUNCTION(ASSIMP_COPY_LIBS)

	endif()
	
else(WIN32)

	find_path(
	  ASSIMP_INCLUDE_DIRS
	  NAMES postprocess.h scene.h version.h config.h cimport.h
	  HINTS /usr/local/include/assimp /usr/include/assimp
	)

	find_library(
	  ASSIMP_LIBRARIES
	  NAMES assimp
	  HINTS /usr/local/lib/ /usr/lib/ /usr/lib/x86_64-linux-gnu
	)
	
	if (ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES)
	  SET(ASSIMP_FOUND TRUE)
	ENDIF (ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES)

	if (ASSIMP_FOUND)
	  if (NOT ASSIMP_FIND_QUIETLY)
		message(STATUS "Found asset importer library: ${ASSIMP_LIBRARIES}")
	  endif (NOT ASSIMP_FIND_QUIETLY)
	else (ASSIMP_FOUND)
	  if (ASSIMP_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find asset importer library")
	  endif (ASSIMP_FIND_REQUIRED)
	endif (ASSIMP_FOUND)
	
endif(WIN32)