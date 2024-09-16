#pragma once

#include "raylib/raylib.h"

typedef struct Bloco {
    Vector3 pos;
    Vector3 dim;
    Color cor;
} Bloco;

Bloco criarBloco( Vector3 pos, Vector3 dim, Color cor );
void desenharBloco( Bloco *bloco );
BoundingBox obterBoundingBoxBloco( Bloco *bloco );