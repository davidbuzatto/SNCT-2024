#pragma once

struct Inimigo;

#include "Bloco.h"
#include "raylib/raylib.h"

typedef struct SondaColisao {
    Vector2 pos;
    Vector2 dim;
    Color cor;
} SondaColisao;

SondaColisao criarSondaColisao( Vector2 pos, Color cor );
void desenharSondaColisao( SondaColisao *sondaColisao );
bool checarColisaoSondaColisaoBloco( SondaColisao *sondaColisao, Bloco *bloco );
bool checarColisaoSondaColisaoInimigo( SondaColisao *sondaColisao, struct Inimigo *inimigo );