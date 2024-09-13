/**
 * @file main.c
 * @author Prof. Dr. David Buzatto
 * @brief Conceitos Raylib (https://www.raylib.com/).
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "raylib.h"

int main( void ) {

    // suavização (antialiasing)
    SetConfigFlags( FLAG_MSAA_4X_HINT );
    InitWindow( 800, 450, "Conceitos" );
    SetTargetFPS( 60 );

    // loop do jogo (game loop)
    while ( !WindowShouldClose() ) {
        
        // lê entrada...
        // atualiza...
        // desenha...

        // exemplos de funções de desenho
        // "documentação": https://www.raylib.com/cheatsheet/cheatsheet.html

        BeginDrawing();
        ClearBackground( WHITE );

        DrawPixel( 100, 100, BLACK );

        DrawLine( 50, 50, 150, 80, BLUE );

        DrawRectangleLines( 200, 50, 100, 50, GREEN );
        DrawRectangle( 350, 50, 50, 100, ORANGE );

        DrawCircleLines( 100, 150, 30, RED );
        DrawCircle( 200, 150, 30, PURPLE );

        DrawEllipseLines( 100, 250, 50, 20, LIME ); 
        DrawEllipse( 200, 250, 20, 50, YELLOW ); 

        DrawPolyLines( (Vector2){ 100, 350 }, 5, 40, 0, PINK );
        DrawPoly( (Vector2){ 200, 350 }, 6, 40, 30, MAROON );

        DrawSplineSegmentBezierCubic( 
            (Vector2){ 250, 200 },
            (Vector2){ 400, 270 },
            (Vector2){ 250, 340 },
            (Vector2){ 400, 400 }, 
            2.0f, BLACK );

        EndDrawing();

    }

    CloseWindow();

    return 0;

}
