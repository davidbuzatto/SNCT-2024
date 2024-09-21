#include "Bloco.h"

#include "raylib/raylib.h"

Bloco criarBloco( Vector3 pos, Vector3 dim, Color cor ) {
    return (Bloco) {
        .pos = pos,
        .dim = dim,
        .cor = cor
    };
}

void desenharBloco( Bloco *bloco ) {
    DrawCubeV( bloco->pos, bloco->dim, bloco->cor );
    DrawCubeWiresV( bloco->pos, bloco->dim, BLACK );
}

BoundingBox obterBoundingBoxBloco( Bloco *bloco ) {
    return (BoundingBox) {
        .min = {
            .x = bloco->pos.x - bloco->dim.x / 2,
            .y = bloco->pos.y - bloco->dim.y / 2,
            .z = bloco->pos.z - bloco->dim.z / 2
        },
        .max = {
            .x = bloco->pos.x + bloco->dim.x / 2,
            .y = bloco->pos.y + bloco->dim.y / 2,
            .z = bloco->pos.z + bloco->dim.z / 2,
        },
    };
}