#pragma once

#include "raylib/raylib.h"

typedef struct Bloco {
    Vector2 pos;
    Vector2 dim;
    Color cor;
} Bloco;

Bloco criarBloco( Vector2 pos, Vector2 dim, Color cor );
void desenharBloco( Bloco *bloco );