cmake_minimum_required(VERSION 3.21)

project(AESkyrimPlugin VERSION 1.0.0 LANGUAGES CXX)

set(ENABLE_SKYRIM_AE ON )
set(ENABLE_SKYRIM_SE OFF)
set(ENABLE_SKYRIM_VR OFF)
set(BUILD_TESTS      OFF)

add_subdirectory(extern/CommonLibSSE-NG)

add_library(${PROJECT_NAME} SHARED src/main.cpp)

if (DEFINED ENV{SKYRIM_MODS_FOLDER} AND IS_DIRECTORY $ENV{SKYRIM_MODS_FOLDER})
	set(MOD_DEPLOY_DIR "$ENV{SKYRIM_MODS_FOLDER}/${PROJECT_NAME}/SKSE/Plugins")
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory "${MOD_DEPLOY_DIR}"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE:${PROJECT_NAME}>"
			"${MOD_DEPLOY_DIR}/"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_PDB_FILE:${PROJECT_NAME}>"
			"${MOD_DEPLOY_DIR}/"
		COMMENT "Deploying to ${MOD_DEPLOY_DIR}"
	)
endif()

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE
		"$<$<CONFIG:Release>:/Zi>"
	)
	target_link_options(${PROJECT_NAME} PRIVATE
		"$<$<CONFIG:Release>:/DEBUG;/OPT:REF;/OPT:ICF>"
	)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)