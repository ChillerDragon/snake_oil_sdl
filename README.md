# snake_oil_sdl

Playing around with SDL.

## Naming convention

- `resource_new()` if it returns a pointer to a newly allocated ressource. Ex: ``Player *player_new()``
- `resource_delete()` to free this pointer. Ex: ``void player_delete()``

- `component_init(Component*)` if it returns void and sets up a new component. Ex: ``void game_init(Game *game)``
- `component_shutdown(Component*)` has to be called to cleanup the components state. Ex: ``void game_shutdown(Game *game)``

