#include <stdbool.h>

#include "GameWorld.h"
#include "Jogador.h"
#include "Bloco.h"
#include "raylib/raylib.h"

Jogador criarJogador( 
    Vector2 pos, Vector2 vel, Vector2 dim, 
    float velocidadeCaminhada, float velocidadePulo,
    Color cor ) {

    Jogador novoJogador = {
        .pos = pos,
        .vel = vel,
        .dim = dim,
        .velocidadeCaminhada = velocidadeCaminhada,
        .velocidadePulo = velocidadePulo,
        .velocidadeMaximaQueda = 400.0f,
        .cor = cor,
        .estadoPosicao = ESTADO_POSICAO_JOGADOR_NO_CHAO,
        .sondasColisao = { 0 } 
    };

    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_CIMA] = criarSondaColisao( (Vector2) { 0 }, YELLOW );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_BAIXO] = criarSondaColisao( (Vector2) { 0 }, YELLOW );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_CIMA] = criarSondaColisao( (Vector2) { 0 }, MAGENTA );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_BAIXO] = criarSondaColisao( (Vector2) { 0 }, MAGENTA );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_ESQUERDA] = criarSondaColisao( (Vector2) { 0 }, SKYBLUE );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_DIREITA] = criarSondaColisao( (Vector2) { 0 }, SKYBLUE );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_ESQUERDA] = criarSondaColisao( (Vector2) { 0 }, LIME );
    novoJogador.sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_DIREITA] = criarSondaColisao( (Vector2) { 0 }, LIME );

    return novoJogador;

}

void processarEntradaJogador( Jogador *jogador ) {

    if ( IsKeyDown( KEY_LEFT ) ) {
        jogador->vel.x = -jogador->velocidadeCaminhada;
    } else if ( IsKeyDown( KEY_RIGHT ) ) {
        jogador->vel.x = jogador->velocidadeCaminhada;
    } else {
        jogador->vel.x = 0.0f;
    }

    if ( IsKeyPressed( KEY_SPACE ) && jogador->estadoPosicao == ESTADO_POSICAO_JOGADOR_NO_CHAO ) {
        jogador->vel.y = jogador->velocidadePulo;
    }

}

void atualizarJogador( Jogador *jogador, float delta ) {

    jogador->pos.x += jogador->vel.x * delta;
    jogador->pos.y += jogador->vel.y * delta;

    if ( jogador->vel.y > 0.0f ) {
        jogador->estadoPosicao = ESTADO_POSICAO_JOGADOR_CAINDO;
    } else if ( jogador->vel.y < 0.0f ) {
        jogador->estadoPosicao = ESTADO_POSICAO_JOGADOR_PULANDO;
    }

    jogador->vel.y += GRAVIDADE;

    if ( jogador->vel.y >= jogador->velocidadeMaximaQueda ) {
        jogador->vel.y = jogador->velocidadeMaximaQueda;
    }

}

void desenharJogador( Jogador *jogador ) {

    DrawRectangleV( jogador->pos, jogador->dim, jogador->cor );

    for ( int i = 0; i < 8; i++ ) {
        desenharSondaColisao( &jogador->sondasColisao[i] );
    }

}

void atualizarSondasColisaoJogador( Jogador *jogador ) {

    float dimensaoSondaColisao = 4.0f;

    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_CIMA].pos = (Vector2) { jogador->pos.x, jogador->pos.y + jogador->dim.y / 3 - dimensaoSondaColisao / 2 };
    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_BAIXO].pos = (Vector2) { jogador->pos.x, jogador->pos.y + jogador->dim.y - jogador->dim.y / 3 };

    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_CIMA].pos = (Vector2) { jogador->pos.x + jogador->dim.x - dimensaoSondaColisao, jogador->pos.y + jogador->dim.y / 3 - dimensaoSondaColisao / 2 };
    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_BAIXO].pos = (Vector2) { jogador->pos.x + jogador->dim.x - dimensaoSondaColisao, jogador->pos.y + jogador->dim.y - jogador->dim.y / 3 };

    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_ESQUERDA].pos = (Vector2) { jogador->pos.x + jogador->dim.x / 3 - dimensaoSondaColisao / 2, jogador->pos.y };
    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_DIREITA].pos = (Vector2) { jogador->pos.x + jogador->dim.x - jogador->dim.x / 3 - dimensaoSondaColisao / 2, jogador->pos.y };

    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_ESQUERDA].pos = (Vector2) { jogador->pos.x + jogador->dim.x / 3 - dimensaoSondaColisao / 2, jogador->pos.y + jogador->dim.y - dimensaoSondaColisao };
    jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_DIREITA].pos = (Vector2) { jogador->pos.x + jogador->dim.x - jogador->dim.x / 3 - dimensaoSondaColisao / 2, jogador->pos.y + jogador->dim.y - dimensaoSondaColisao  };

}

void resolverColisaoJogadorBlocos( Jogador *jogador, int quantidadeBlocos, Bloco *blocos ) {

    for ( int i = 0; i < quantidadeBlocos; i++ ) {

        Bloco *bloco = &blocos[i];
        TipoColisaoJogadorBloco colisao = checarColisaoJogadorBloco( jogador, bloco, true );

        switch ( colisao ) {
            case TIPO_COLISAO_JOGADOR_BLOCO_ESQUERDA:
                jogador->pos.x = bloco->pos.x + bloco->dim.x;
                break;
            case TIPO_COLISAO_JOGADOR_BLOCO_DIREITA:
                jogador->pos.x = bloco->pos.x - jogador->dim.x;
                break;
            case TIPO_COLISAO_JOGADOR_BLOCO_CIMA:
                jogador->pos.y = bloco->pos.y + bloco->dim.y;
                jogador->vel.y = 0.0f;
                break;
            case TIPO_COLISAO_JOGADOR_BLOCO_BAIXO:
                jogador->pos.y = bloco->pos.y - jogador->dim.y;
                jogador->vel.y = 0.0f;
                jogador->estadoPosicao = ESTADO_POSICAO_JOGADOR_NO_CHAO;
                break;
            default:
                break;
        }

        /*if ( colisao != TIPO_COLISAO_JOGADOR_BLOCO_NENHUMA ) {
            break;
        }*/

    }

}

TipoColisaoJogadorBloco checarColisaoJogadorBloco( Jogador *jogador, Bloco *bloco, bool checarSondas ) {
    
    if ( checarSondas ) {

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_CIMA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_BAIXO], bloco ) ) {
            return TIPO_COLISAO_JOGADOR_BLOCO_ESQUERDA;
        }

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_CIMA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_BAIXO], bloco ) ) {
            return TIPO_COLISAO_JOGADOR_BLOCO_DIREITA;
        }

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_ESQUERDA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_DIREITA], bloco ) ) {
            return TIPO_COLISAO_JOGADOR_BLOCO_CIMA;
        }

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_ESQUERDA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_DIREITA], bloco ) ) {
            return TIPO_COLISAO_JOGADOR_BLOCO_BAIXO;
        }

    } else {

        bool col = CheckCollisionRecs(
            (Rectangle) {
                .x = jogador->pos.x,
                .y = jogador->pos.y,
                .width = jogador->dim.x,
                .height = jogador->dim.y,
            },
            (Rectangle) {
                .x = bloco->pos.x,
                .y = bloco->pos.y,
                .width = bloco->dim.x,
                .height = bloco->dim.y,
            }
        );

        if ( col ) {
            return TIPO_COLISAO_JOGADOR_BLOCO_INTERSECCAO;
        }

    }

    return TIPO_COLISAO_JOGADOR_BLOCO_NENHUMA;

}
