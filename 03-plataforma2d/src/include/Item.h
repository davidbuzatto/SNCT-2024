#pragma once

#include "Animacao.h"

#include "raylib/raylib.h"

typedef struct Item {

    Vector2 pos;
    Vector2 dim;
    Color cor;

    bool ativo;
    int pontosAoSerPego;

    Animacao *animacao;

} Item;

Item criarItem( Vector2 pos, Vector2 dim, Color cor, Animacao *animacao );
void atualizarItem( Item *item, float delta );
void desenharItem( Item *item );