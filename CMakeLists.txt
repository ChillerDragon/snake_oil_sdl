cmake_minimum_required(VERSION 3.12...3.27.4)

project(snake_oil_sdl LANGUAGES C VERSION "0.0.1")

# windows doesnt respect empty git submodules
cmake_policy(SET CMP0097 NEW)

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

if(NOT SDL3_image_FOUND)
  message(STATUS "SDL3_image not found. Building it from source.")

  # https://github.com/libsdl-org/SDL/issues/6454#issuecomment-1295645598
  # dude idk cmake said: Missing variable is: CMAKE_OBJC_COMPILE_OBJECT
  if(APPLE)
      enable_language(OBJC)
  endif()

  FetchContent_Declare(
    SDL_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG        "main"
    GIT_PROGRESS   TRUE
    GIT_SUBMODULES ""
    GIT_SUBMODULES_RECURSE FALSE
  )
  FetchContent_MakeAvailable(SDL_image)
else()
  find_package(SDL3_image REQUIRED CONFIG)
endif()

FILE(GLOB GAME_SOURCES src/*.cpp src/*.h src/*.c)
add_executable(${PROJECT_NAME} WIN32 ${GAME_SOURCES})
# target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)


add_executable(fps WIN32 src/playground/fps.c)
target_link_libraries(fps PRIVATE SDL3::SDL3)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
include(CPack)
