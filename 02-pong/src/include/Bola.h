#pragma once

#include <stdbool.h>

#include "Jogador.h"
#include "raylib.h"

typedef enum ColisaoLateralBola {
    COLISAO_LATERAL_BOLA_NENHUMA,
    COLISAO_LATERAL_BOLA_ESQUERDA,
    COLISAO_LATERAL_BOLA_DIREITA
} ColisaoLateralBola;

typedef struct Bola {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;

Bola criarBola( Vector2 pos, Vector2 vel, float raio, Color cor );
ColisaoLateralBola atualizarBola( Bola *bola, float delta );
void desenharBola( Bola *bola );
bool verificarColisaoBolaJogador( Bola *bola, Jogador *jogador );