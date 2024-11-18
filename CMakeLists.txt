cmake_minimum_required(VERSION 3.12...3.27.4)

project(snake_oil_sdl)

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

  # I did not manage to get the cleaner FetchContent_Declare()
  # work for SDL_image because its sub dependencies are a bit messy
  # compared to the regular SDL
  ExternalProject_Add(SDL_image
    # pin this to a tag once sdl_image released for sdl3
    GIT_TAG                "main"
    GIT_REPOSITORY         https://github.com/libsdl-org/SDL_image
    GIT_PROGRESS           TRUE
    GIT_SUBMODULES_RECURSE FALSE
    SOURCE_DIR             "${CMAKE_BINARY_DIR}/sdl_image-src"
    BINARY_DIR             "${CMAKE_BINARY_DIR}/sdl_image-build"
    CONFIGURE_COMMAND      ""
    BUILD_COMMAND          ""
    INSTALL_COMMAND        ""
    TEST_COMMAND           ""
    TLS_VERIFY             ON
  )
  # include_directories(
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
