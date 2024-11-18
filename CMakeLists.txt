cmake_minimum_required(VERSION 3.12...3.27.4)

project(snake_oil_sdl)

set(FETCHCONTENT_QUIET FALSE)

find_package(SDL3 CONFIG QUIET)
find_package(SDL3_image CONFIG QUIET)

if(NOT SDL3_FOUND)
  message(STATUS "SDL3 not found. Building it from source.")
  include(FetchContent)
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
  include(FetchContent)
  # TODO: replace main tag with release tag
  #       once there is a sdl3 release https://github.com/libsdl-org/SDL_image/releases
  FetchContent_Declare(
    SDL_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG        "main"
    GIT_PROGRESS   TRUE

    # on my linux machine the submodule cloning takes forever
    # and eventually fails because git just chokes
    # sdl image has quite a few git submodules
    # https://github.com/libsdl-org/SDL_image/tree/main/external
    # also on my system i can clone sdl image without --recursive
    # and it just builds fine (as long as sdl3 is installed)
    # this is potentially not portable to windows/macOS
    # maybe git modules should only be unset on linux
    GIT_SUBMODULES ""
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
