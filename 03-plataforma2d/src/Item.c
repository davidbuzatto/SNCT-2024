#include "Item.h"
#include "Animacao.h"
#include "raylib/raylib.h"

Item criarItem( Vector2 pos, Vector2 dim, Color cor, Animacao *animacao ) {
    return (Item) {
        .pos = pos,
        .dim = dim,
        .cor = cor,
        .ativo = true,
        .pontosAoSerPego = 10,
        .animacao = animacao
    };
}

void atualizarItem( Item *item, float delta ) {
    atualizarAnimacao( item->animacao, delta );
}

void desenharItem( Item *item ) {
    if ( item->ativo ) {
        DrawTextureV( item->animacao->texturaAtual, item->pos, WHITE );
    }
}