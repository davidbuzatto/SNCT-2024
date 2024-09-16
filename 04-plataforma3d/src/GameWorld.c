/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "Jogador.h"
#include "Bloco.h"
#include "ResourceManager.h"

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

const float GRAVIDADE = 1.0f;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->jogador = criarJogador(
        (Vector3){ 30.0f, 3.0f, 10.0f },
        (Vector3){ 2.0f, 2.0f, 2.0f },
        30.0f,
        20.0f,
        BLUE
    );

    gw->chao = criarBloco(
        (Vector3){ 30.0f, 1.0f, 10.0f },
        (Vector3){ 60.0f, 2.0f, 20.0f },
        ORANGE
    );

    gw->camera = (Camera3D) {
        .position = { 30.0f, 25.0f, 40.0f },
        .target = gw->jogador.pos,
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    float delta = GetFrameTime();

    Jogador *jogador = &gw->jogador;
    Bloco *chao = &gw->chao;

    processarEntradaJogador( &gw->jogador );
    atualizarJogador( &gw->jogador, delta );
    resolverColisaoJogadorChao( jogador, chao );

    atualizarCamera( gw );

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    BeginMode3D( gw->camera );

    desenharJogador( &gw->jogador );
    desenharBloco( &gw->chao );

    EndMode3D();

    desenharHud( gw );

    EndDrawing();

}

void desenharHud( GameWorld *gw ) {

    Camera3D *camera = &gw->camera;

    DrawText( 
        TextFormat( "camera: x=%.2f, y=%.2f, z=%.2f", 
            camera->position.x, 
            camera->position.y, 
            camera->position.z
        ), 
        10, 10, 20, BLACK
    );

    DrawFPS( 10, 30 );

}

void atualizarCamera( GameWorld *gw ) {

    if ( IsKeyDown( KEY_UP ) ) {
        gw->camera.position.y++;
    } else if ( IsKeyDown( KEY_DOWN ) ) {
        gw->camera.position.y--;
    }

    /*if ( IsKeyDown( KEY_LEFT ) ) {
        gw->camera.position.x--;
    } else if ( IsKeyDown( KEY_RIGHT ) ) {
        gw->camera.position.x++;
    }*/

    if ( IsKeyDown( KEY_KP_ADD ) ) {
        gw->camera.position.z++;
    } else if ( IsKeyDown( KEY_KP_SUBTRACT ) ) {
        gw->camera.position.z--;
        if ( gw->camera.position.z <= gw->chao.pos.z ) {
            gw->camera.position.z = gw->chao.pos.z + 1;
        }
    }

    gw->camera.position.x = gw->jogador.pos.x;
    gw->camera.target = gw->jogador.pos;

}
