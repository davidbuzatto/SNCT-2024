#pragma once

#include "raylib/raylib.h"

typedef struct Bloco {
    Vector2 pos;
    Vector2 dim;
    Color cor;
    Texture2D textura;
    bool existe;
} Bloco;

Bloco criarBloco( Vector2 pos, Vector2 dim, Color cor, Texture2D textura );
void desenharBloco( Bloco *bloco );