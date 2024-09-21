#include "Bloco.h"
#include "raylib/raylib.h"

Bloco criarBloco( Vector2 pos, Vector2 dim, Color cor, Texture2D textura ) {
    return (Bloco) {
        .pos = pos,
        .dim = dim,
        .cor = cor,
        .textura = textura,
        .existe = true
    };
}

void desenharBloco( Bloco *bloco ) {
    DrawTextureV( bloco->textura, bloco->pos, WHITE );
}