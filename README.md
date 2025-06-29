# snake_oil_sdl

Playing around with SDL.

## Recommended development setup

Build and install SDL 3 bleeding edge from source.

```
git clone https://github.com/libsdl-org/SDL
cd SDL
cmake -B build
cmake --build build
cmake --install build

git clone https://github.com/libsdl-org/SDL_image
cd SDL_image
cmake -B build
cmake --build build
cmake --install build
```

## Code style

- no global variables
- use ``int`` as much as possible. NO FLOATS! If something is describing a size or length use ``size_t``
  do not use SDL types because the protocol and server should not depend on sdl

## Naming convention

### constructors

- `resource_new()` if it returns a pointer to a newly allocated ressource. Ex: ``Player *player_new()``
- `resource_delete()` to free this pointer. Ex: ``void player_delete()``. It can crash when passed a null ptr! It is not like ``free()``. ONLY CALL WITH VALID POINTERS!

- `component_init(Component*)` if it returns void and sets up a new component. Ex: ``void game_init(Game *game)``
- `component_shutdown(Component*)` has to be called to cleanup the components state. Ex: ``void game_shutdown(Game *game)``

### misc

- filenames are ``lower_snake_case.c``
- variables are ``lower_snake_case``
- structs are ``UpperCamelCase``
- only private static functions can start with ``draw_`` the public api has to be ``ressource_name_draw(``
- function names need the filename as prefix unless they are private statics
- all render methods have to contain the word ``draw`` unless its the global wrappers for game and app they are called ``render``

### naming functions and variables

Functions names should never conflict with variable names!
The function name should clearly be an action and contain the words ``do_`` ``on_`` ``_handler`` ``calc_``
If it does not much and is just returning a fixed value even the ``get_`` prefix is fine.

```c
// THIS IS BAD!
int h = health();

// this is good!
int health = get_health();
```

