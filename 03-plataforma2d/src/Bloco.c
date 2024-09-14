#include "Bloco.h"
#include "raylib/raylib.h"

Bloco criarBloco( Vector2 pos, Vector2 dim, Color cor ) {
    return (Bloco) {
        .pos = pos,
        .dim = dim,
        .cor = cor
    };
}

void desenharBloco( Bloco *bloco ) {
    DrawRectangleV( bloco->pos, bloco->dim, bloco->cor );
}