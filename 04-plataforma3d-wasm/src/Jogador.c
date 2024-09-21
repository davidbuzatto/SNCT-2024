#include "GameWorld.h"
#include "Jogador.h"
#include "Bloco.h"
#include "EstadoPosicao.h"
#include "ResourceManager.h"

#include "raylib/raylib.h"

Jogador criarJogador( Vector3 pos, Vector3 dim, float velocidadeCaminhada, float velocidadePulo, Color cor ) {
    return (Jogador) {
        .pos = pos,
        .vel = { 0 },
        .dim = dim,
        .velocidadeCaminhada = velocidadeCaminhada,
        .velocidadePulo = velocidadePulo,
        .velocidadeMaximaQueda = 30.0f,
        .cor = cor,
        .estadoPosicao = ESTADO_POSICAO_NO_CHAO
    };
}

void processarEntradaJogador( Jogador *jogador ) {

    if ( IsKeyDown( KEY_A ) ) {
        jogador->vel.x = -jogador->velocidadeCaminhada;
    } else if ( IsKeyDown( KEY_D ) ) {
        jogador->vel.x = jogador->velocidadeCaminhada;
    } else {
        jogador->vel.x = 0.0f;
    }

    if ( IsKeyDown( KEY_W ) ) {
        jogador->vel.z = -jogador->velocidadeCaminhada;
    } else if ( IsKeyDown( KEY_S ) ) {
        jogador->vel.z = jogador->velocidadeCaminhada;
    } else {
        jogador->vel.z = 0.0f;
    }

    if ( jogador->estadoPosicao == ESTADO_POSICAO_NO_CHAO && IsKeyPressed( KEY_SPACE ) ) {
        jogador->vel.y = jogador->velocidadePulo;
        PlaySound( rm.pulo );
    }

}

void atualizarJogador( Jogador *jogador, float delta ) {

    jogador->pos.x += jogador->vel.x * delta;
    jogador->pos.y += jogador->vel.y * delta;
    jogador->pos.z += jogador->vel.z * delta;

    if ( jogador->vel.y < 0.0f ) {
        jogador->estadoPosicao = ESTADO_POSICAO_CAINDO;
    } else if ( jogador->vel.y > 0.0f ) {
        jogador->estadoPosicao = ESTADO_POSICAO_PULANDO;
    }

    jogador->vel.y += -GRAVIDADE;

    if ( jogador->vel.y >= jogador->velocidadeMaximaQueda ) {
        jogador->vel.y = jogador->velocidadeMaximaQueda;
    }

}

void desenharJogador( Jogador *jogador ) {
    DrawCubeV( jogador->pos, jogador->dim, jogador->cor );
    DrawCubeWiresV( jogador->pos, jogador->dim, BLACK );
}

void resolverColisaoJogadorChao( Jogador *jogador, Bloco *chao ) {

    BoundingBox bbJogador = obterBoundingBoxJogador( jogador );
    BoundingBox bbChao = obterBoundingBoxBloco( chao );

    if ( CheckCollisionBoxes( bbJogador, bbChao ) ) {
        jogador->pos.y = chao->pos.y + chao->dim.y / 2 + jogador->dim.y / 2;
        jogador->vel.y = 0.0f;
        jogador->estadoPosicao = ESTADO_POSICAO_NO_CHAO;
    }

}

BoundingBox obterBoundingBoxJogador( Jogador *jogador ) {
    return (BoundingBox) {
        .min = {
            .x = jogador->pos.x - jogador->dim.x / 2,
            .y = jogador->pos.y - jogador->dim.y / 2,
            .z = jogador->pos.z - jogador->dim.z / 2
        },
        .max = {
            .x = jogador->pos.x + jogador->dim.x / 2,
            .y = jogador->pos.y + jogador->dim.y / 2,
            .z = jogador->pos.z + jogador->dim.z / 2,
        },
    };
}