/**
 * @file main.c
 * @author Prof. Dr. David Buzatto
 * @brief Exemplo da bolinha!
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "raylib/raylib.h"

typedef struct Bolinha {
    Vector2 pos;
    Vector2 vel;
    float raio;
    float atrito;
    float elasticidade;
    bool arrastando;
    Color cor;
} Bolinha;

const float GRAVIDADE = 50.0f;

void processarEntrada( void );
void atualizar( void );
void desenhar( void );
void desenharBolinha( void );

Bolinha bolinha = {0};
int deslocamentoX;
int deslocamentoY;

int main( void ) {

    SetConfigFlags( FLAG_MSAA_4X_HINT );
    InitWindow( 800, 450, "Bolinha!" );
    SetTargetFPS( 60 );

    bolinha = (Bolinha) {
        .pos = {
            GetScreenWidth() / 2,
            GetScreenHeight() / 2
        },
        .vel = {
            300,
            300
        },
        .raio = 50.0f,
        .atrito = 0.99f,
        .elasticidade = 0.90f,
        .arrastando = false,
        BLUE
    };

    while ( !WindowShouldClose() ) {
        processarEntrada();
        atualizar();
        desenhar();
    }

    CloseWindow();

    return 0;

}

void processarEntrada( void ) {

    if ( !bolinha.arrastando ) {

        if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {

            int xMouse = GetMouseX();
            int yMouse = GetMouseY();
            
            deslocamentoX = xMouse - bolinha.pos.x;
            deslocamentoY = yMouse - bolinha.pos.y;
            
            /*float distancia = hypotf( deslocamentoX, deslocamentoY );

            if ( distancia <= bolinha.raio ) {
                bolinha.arrastando = true;
            }*/
            
            if ( deslocamentoX * deslocamentoX + 
                 deslocamentoY * deslocamentoY <= bolinha.raio * bolinha.raio ) {
                bolinha.arrastando = true;
            }

        }

    }

    if ( IsMouseButtonReleased( MOUSE_BUTTON_LEFT ) ) {
        bolinha.arrastando = false;
    }

}

void atualizar( void ) {

    float delta = GetFrameTime();

    if ( !bolinha.arrastando ) {

        bolinha.pos.x += bolinha.vel.x * delta;
        bolinha.pos.y += bolinha.vel.y * delta;

        if ( bolinha.pos.x + bolinha.raio >= GetScreenWidth() ) {
            bolinha.pos.x = GetScreenWidth() - bolinha.raio;
            bolinha.vel.x = -bolinha.vel.x * bolinha.elasticidade;
        } else if ( bolinha.pos.x - bolinha.raio <= 0 ) {
            bolinha.pos.x = bolinha.raio;
            bolinha.vel.x = -bolinha.vel.x * bolinha.elasticidade;
        }

        if ( bolinha.pos.y + bolinha.raio >= GetScreenHeight() ) {
            bolinha.pos.y = GetScreenHeight() - bolinha.raio;
            bolinha.vel.y = -bolinha.vel.y * bolinha.elasticidade;
        } else if ( bolinha.pos.y - bolinha.raio <= 0 ) {
            bolinha.pos.y = bolinha.raio;
            bolinha.vel.y = -bolinha.vel.y * bolinha.elasticidade;
        }

        bolinha.vel.x = bolinha.vel.x * bolinha.atrito;
        bolinha.vel.y = bolinha.vel.y * bolinha.atrito + GRAVIDADE;

    } else {

        int xMouse = GetMouseX();
        int yMouse = GetMouseY();

        bolinha.pos.x = xMouse - deslocamentoX;
        bolinha.pos.y = yMouse - deslocamentoY;

        Vector2 mouseDelta = GetMouseDelta();
        bolinha.vel.x = mouseDelta.x / delta;
        bolinha.vel.y = mouseDelta.y / delta;

    }

}

void desenhar( void ) {

    BeginDrawing();
    ClearBackground( WHITE );

    desenharBolinha();

    EndDrawing();

}

void desenharBolinha( void ) {
    DrawCircleV( bolinha.pos, bolinha.raio, bolinha.cor );
}