cmake_minimum_required(VERSION 3.12...3.27.4)

project(snake_oil_sdl LANGUAGES C VERSION "0.0.1")

include(FetchContent)
include(ExternalProject)

set(FETCHCONTENT_QUIET FALSE)

find_package(SDL3 CONFIG QUIET)
find_package(SDL3_image CONFIG QUIET)

if(NOT SDL3_FOUND)
  message(STATUS "SDL3 not found. Building it from source.")
  FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG        "preview-3.1.6"
    GIT_PROGRESS   TRUE
  )
  FetchContent_MakeAvailable(SDL)
else()
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# TODO: uncomment i just had no internet xd
# if(NOT SDL3_image_FOUND)
#   message(STATUS "SDL3_image not found. Building it from source.")
# 
#   # https://github.com/libsdl-org/SDL/issues/6454#issuecomment-1295645598
#   # dude idk cmake said: Missing variable is: CMAKE_OBJC_COMPILE_OBJECT
#   if(APPLE)
#       enable_language(OBJC)
#   endif()
# 
#   set(NEED_SDL_IMAGE_SUB_MODULES FALSE)
#   if(MSVC)
#     set(NEED_SDL_IMAGE_SUB_MODULES TRUE)
#   endif()
# 
#   FetchContent_Declare(
#     SDL_image
#     GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
#     GIT_TAG        "main"
#     GIT_PROGRESS   TRUE
#     GIT_SUBMODULES_RECURSE ${NEED_SDL_IMAGE_SUB_MODULES}
#   )
#   FetchContent_MakeAvailable(SDL_image)
# else()
#   find_package(SDL3_image REQUIRED CONFIG)
# endif()


FILE(GLOB SHARED_SOURCES
	src/shared/*.h
	src/shared/*.c
	src/protcol/*.h
	src/protocol/*.c
	src/game/*.h
	src/game/*.c
)
include_directories(src)

FILE(GLOB SERVER_SOURCES src/server/*.h src/server/*.c)
add_executable(${PROJECT_NAME}_srv WIN32 ${SHARED_SOURCES} ${SERVER_SOURCES})

FILE(GLOB CLIENT_SOURCES src/client/*.h src/client/*.c)
add_executable(${PROJECT_NAME} WIN32 ${SHARED_SOURCES} ${CLIENT_SOURCES})
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)


add_executable(fps WIN32 src/playground/fps.c)
target_link_libraries(fps PRIVATE SDL3::SDL3)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
include(CPack)
