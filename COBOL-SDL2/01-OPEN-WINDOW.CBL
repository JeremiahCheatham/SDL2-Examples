       IDENTIFICATION DIVISION.
       PROGRAM-ID. 01-OPEN-WINDOW.

       DATA DIVISION.
       FILE SECTION.
       WORKING-STORAGE SECTION.
           77 SDL_INIT_EVERYTHING USAGE BINARY-INT VALUE 62001.
           77 SDL_WINDOWPOS_CENTERED USAGE BINARY-INT VALUE 805240832.

           77 WINDOW_TITLE PIC X(20) VALUE Z"01 Open Window".
           77 WINDOW_WIDTH USAGE BINARY-INT VALUE 800.
           77 WINDOW_HEIGHT USAGE BINARY-INT VALUE 600.

           77 sdl-window USAGE POINTER VALUE NULL.
           77 sdl-renderer USAGE POINTER VALUE NULL.

           77 return-value USAGE BINARY-INT VALUE 0.
           77 error-message PIC X(50).

       PROCEDURE DIVISION.
       MAIN-PROCEDURE.
           PERFORM INITIALIZE-SDL.
           
           CALL "SDL_RenderClear" USING
               BY VALUE sdl-renderer
           END-CALL.
           
           CALL "SDL_RenderPresent"
               USING BY VALUE sdl-renderer
           END-CALL.
           
           CALL "SDL_Delay" USING
               BY VALUE 5000
           END-CALL.

           PERFORM CLEAN-AND-EXIT.

       INITIALIZE-SDL.
           CALL "SDL_Init" USING
               BY VALUE SDL_INIT_EVERYTHING
               RETURNING return-value
           END-CALL.

           IF return-value NOT = 0 THEN
               MOVE Z"Error initializing SDL2" TO error-message
               PERFORM PRINT-ERROR
           END-IF.

           CALL "SDL_CreateWindow" USING
               BY CONTENT WINDOW_TITLE
               BY VALUE SDL_WINDOWPOS_CENTERED
               BY VALUE SDL_WINDOWPOS_CENTERED
               BY VALUE WINDOW_WIDTH
               BY VALUE WINDOW_HEIGHT
               BY VALUE 0
               RETURNING sdl-window
           END-CALL.

           IF sdl-window EQUALS NULL THEN
               MOVE Z"Error creating window" TO error-message
               PERFORM PRINT-ERROR
           END-IF.

           CALL "SDL_CreateRenderer" USING
               BY VALUE sdl-window
               BY VALUE -1
               BY VALUE 0
               RETURNING sdl-renderer
           END-CALL.

           IF sdl-renderer EQUALS NULL THEN
               MOVE Z"Error creating renderer" TO error-message
               PERFORM PRINT-ERROR
           END-IF.

           EXIT.

       PRINT-ERROR.
           CALL "print_sdl_error" USING
               BY REFERENCE error-message
               RETURNING RETURN-CODE
           END-CALL.

           PERFORM CLEAN-AND-EXIT.

       CLEAN-AND-EXIT.
           CALL "SDL_DestroyRenderer" USING
               BY VALUE sdl-renderer
               RETURNING return-value
           END-CALL.
           SET sdl-renderer TO NULL.

           CALL "SDL_DestroyWindow" USING
               BY VALUE sdl-window
               RETURNING return-value
           END-CALL.
           SET sdl-window TO NULL.

           CALL "SDL_Quit" RETURNING return-value END-CALL.

           STOP RUN.
       
       END PROGRAM 01-OPEN-WINDOW.