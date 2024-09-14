#include "SondaColisao.h"
#include "Bloco.h"
#include "raylib/raylib.h"

SondaColisao criarSondaColisao( Vector2 pos, Color cor ) {
    return (SondaColisao) {
        .pos = pos,
        .dim = {
            .x = 4.0f,
            .y = 4.0f,
        },
        .cor = cor
    };
}

void desenharSondaColisao( SondaColisao *sondaColisao ) {
    DrawRectangleV( sondaColisao->pos, sondaColisao->dim, sondaColisao->cor );
}

bool checarColisaoSondaColisaoBloco( SondaColisao *sondaColisao, Bloco *bloco ) {
    
    return CheckCollisionRecs(
        (Rectangle) {
            .x = sondaColisao->pos.x,
            .y = sondaColisao->pos.y,
            .width = sondaColisao->dim.x,
            .height = sondaColisao->dim.y,
        },
        (Rectangle) {
            .x = bloco->pos.x,
            .y = bloco->pos.y,
            .width = bloco->dim.x,
            .height = bloco->dim.y,
        }
    );

}