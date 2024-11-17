#!/bin/bash

error=0

if grep -rn 'SDL_GetTicks(' src/
then
	echo "Error: do not use SDL_GetTicks only SDL_GetTicksNS to avoid confusion"
	error=1
fi

exit "$error"

