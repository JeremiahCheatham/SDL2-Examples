\ Include all basic SDL2 functionality
require SDL2/SDL.fs

\ Helpers for C
0 CONSTANT NULL
: c-str> ( c-str -- string u ) 0 BEGIN 2DUP + C@ WHILE 1+ REPEAT ;
: >c-str ( string u -- c-str )
    1+ DUP ALLOCATE
    DROP ROT OVER 3 PICK 1- MOVE
    DUP ROT 1- + 0 SWAP C!
;

\ Set constants for creating the SDL Window.
s" 02 Close Window" >c-str CONSTANT WINDOW_TITLE
800 CONSTANT SCREEN_WIDTH
600 CONSTANT SCREEN_HEIGHT

\ Pointers for SDL window, renderer and other variables. 
NULL VALUE window
NULL VALUE renderer
CREATE event SDL_Event ALLOT

\ Release allocated memory for pointers and shutdown SDL correctly.
: game-cleanup ( -- )
    renderer SDL_DestroyRenderer
    window SDL_DestroyWindow
    SDL_Quit
    BYE
;

: initialize-sdl ( -- )
    \ initialize SDL2. 0 is returned on success.
    SDL_INIT_EVERYTHING SDL_Init IF
        ." Error initializing SDL: " SDL_GetError c-str> TYPE CR
        game-cleanup
    THEN
;

\ Create the SDL2 Window and store the pointer in window. NULL/0 is returned if failed.
: create-window ( -- )
    WINDOW_TITLE SDL_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED SCREEN_WIDTH SCREEN_HEIGHT 0
    SDL_CreateWindow TO window
    window 0= IF 
        ." Error creating  window: " SDL_GetError c-str> TYPE CR
        game-cleanup
    THEN
;

\ Create the SDL Renderer and store the pointer in renderer. NULL/0 is returned if failed.
: create-renderer ( -- )
    window -1 0 SDL_CreateRenderer TO renderer
    renderer 0= IF
        ." Failed to create renderer: " SDL_GetError c-str> TYPE CR
        game-cleanup
    THEN
;

: game-loop ( -- )
    \ An infinate loop.
    BEGIN
        \ Loop through all the SDL events since last game loop.
        BEGIN event SDL_PollEvent WHILE
            \ Check event type, SDL_QUIT or SDL_KEYDOWN.
            event SDL_Event-type L@
            DUP SDL_QUIT_ENUM = IF
                DROP game-cleanup
            THEN
            \ Check which key has been pressed.
            SDL_KEYDOWN = IF event SDL_KeyboardEvent-keysym L@
                SDL_SCANCODE_ESCAPE = IF
                    game-cleanup
                THEN
            THEN
        REPEAT
        
        \ Clears the back screen buffer.
        renderer SDL_RenderClear DROP
        
        \ Do all your drawing here.

        \ Flips the front and back buffers, displays what has been drawn. 
        renderer SDL_RenderPresent

        \ 16ms delay in a loop is about 60 FPS.
        16 SDL_Delay

    FALSE UNTIL
;

: play-game ( -- )
    initialize-sdl
    create-window
    create-renderer
    game-loop
;

play-game
