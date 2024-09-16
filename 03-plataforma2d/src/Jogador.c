#include <stdbool.h>

#include "GameWorld.h"
#include "ResourceManager.h"
#include "Jogador.h"
#include "Bloco.h"
#include "Item.h"
#include "Inimigo.h"
#include "Animacao.h"
#include "EstadoPosicao.h"
#include "TipoColisao.h"
#include "raylib/raylib.h"

Jogador criarJogador( 
    Vector2 pos, Vector2 dim, 
    float velocidadeCaminhada, float velocidadePulo,
    Color cor, 
    Animacao *animacaoEsquerda, Animacao *animacaoDireita ) {

    Jogador novoJogador = {
        .pos = pos,
        .vel = { 0 },
        .dim = dim,
        .velocidadeCaminhada = velocidadeCaminhada,
        .velocidadeCorrida = velocidadeCaminhada * 1.5f,
        .velocidadePulo = velocidadePulo,
        .velocidadeMaximaQueda = 400.0f,
        .cor = cor,
        .estadoPosicao = ESTADO_POSICAO_NO_CHAO,
        .correndo = false,
        .viradoDireita = true,
        .quantidadeItensPegos = 0,
        .pontos = 0,
        .vida = 100,
        .vidaMaxima = 100,
        .sondasColisao = { 0 },
        .animacaoEsquerda = animacaoEsquerda,
        .animacaoDireita = animacaoDireita
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

    if ( IsKeyDown( KEY_LEFT_CONTROL ) ) {
        jogador->correndo = true;
    } else {
        jogador->correndo = false;
    }

    if ( IsKeyDown( KEY_LEFT ) ) {
        jogador->vel.x = jogador->correndo ? -jogador->velocidadeCorrida : -jogador->velocidadeCaminhada;
    } else if ( IsKeyDown( KEY_RIGHT ) ) {
        jogador->vel.x = jogador->correndo ? jogador->velocidadeCorrida : jogador->velocidadeCaminhada;
    } else {
        jogador->vel.x = 0.0f;
    }

    if ( IsKeyPressed( KEY_SPACE ) && jogador->estadoPosicao == ESTADO_POSICAO_NO_CHAO ) {
        jogador->vel.y = jogador->velocidadePulo;
        PlaySound( rm.pulo );
    }

}

void atualizarJogador( Jogador *jogador, float delta ) {

    jogador->pos.x += jogador->vel.x * delta;
    jogador->pos.y += jogador->vel.y * delta;

    if ( jogador->vel.y > 0.0f ) {
        jogador->estadoPosicao = ESTADO_POSICAO_CAINDO;
    } else if ( jogador->vel.y < 0.0f ) {
        jogador->estadoPosicao = ESTADO_POSICAO_PULANDO;
    }

    jogador->vel.y += GRAVIDADE;

    if ( jogador->vel.y >= jogador->velocidadeMaximaQueda ) {
        jogador->vel.y = jogador->velocidadeMaximaQueda;
    }

    if ( jogador->vel.x != 0.0f ) {
        if ( jogador->vel.x >= 0.0f ) {
            jogador->viradoDireita = true;
        } else {
            jogador->viradoDireita = false;
        }
        atualizarAnimacao( jogador->animacaoEsquerda, delta );
        atualizarAnimacao( jogador->animacaoDireita, delta );
    } else {
        resetarAnimacao( jogador->animacaoEsquerda );
        resetarAnimacao( jogador->animacaoDireita );
    }

}

void desenharJogador( Jogador *jogador ) {

    if ( jogador->viradoDireita ) {
        DrawTextureV( jogador->animacaoDireita->texturaAtual, jogador->pos, WHITE );
    } else {
        DrawTextureV( jogador->animacaoEsquerda->texturaAtual, jogador->pos, WHITE );
    }

    /*for ( int i = 0; i < 8; i++ ) {
        desenharSondaColisao( &jogador->sondasColisao[i] );
    }*/

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

void resolverColisaoJogadorBlocos( Jogador *jogador, int quantidadeLinhas, int quantidadeColunas, Bloco *blocos ) {

    for ( int i = 0; i < quantidadeLinhas; i++ ) {
        for ( int j = 0; j < quantidadeColunas; j++ ) {
            
            Bloco *bloco = &blocos[i*quantidadeColunas+j];

            if ( bloco->existe ) {

                TipoColisao colisao = checarColisaoJogadorBloco( jogador, bloco, true );

                switch ( colisao ) {
                    case TIPO_COLISAO_ESQUERDA:
                        jogador->pos.x = bloco->pos.x + bloco->dim.x;
                        break;
                    case TIPO_COLISAO_DIREITA:
                        jogador->pos.x = bloco->pos.x - jogador->dim.x;
                        break;
                    case TIPO_COLISAO_CIMA:
                        jogador->pos.y = bloco->pos.y + bloco->dim.y;
                        jogador->vel.y = 0.0f;
                        break;
                    case TIPO_COLISAO_BAIXO:
                        jogador->pos.y = bloco->pos.y - jogador->dim.y;
                        jogador->vel.y = 0.0f;
                        jogador->estadoPosicao = ESTADO_POSICAO_NO_CHAO;
                        break;
                    default:
                        break;
                }

            }

        }

    }

}

TipoColisao checarColisaoJogadorBloco( Jogador *jogador, Bloco *bloco, bool checarSondas ) {
    
    if ( checarSondas ) {

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_CIMA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_BAIXO], bloco ) ) {
            return TIPO_COLISAO_ESQUERDA;
        }

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_CIMA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_BAIXO], bloco ) ) {
            return TIPO_COLISAO_DIREITA;
        }

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_ESQUERDA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_DIREITA], bloco ) ) {
            return TIPO_COLISAO_CIMA;
        }

        if ( checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_ESQUERDA], bloco ) ||
            checarColisaoSondaColisaoBloco( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_DIREITA], bloco ) ) {
            return TIPO_COLISAO_BAIXO;
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
            return TIPO_COLISAO_INTERSECCAO;
        }

    }

    return TIPO_COLISAO_NENHUMA;

}

void resolverColisaoJogadorItens( Jogador *jogador, int quantidadeItens, Item *itens ) {

    for ( int i = 0; i < quantidadeItens; i++ ) {
            
        Item *item = &itens[i];

        if ( item->ativo && checarColisaoJogadorItem( jogador, item ) == TIPO_COLISAO_INTERSECCAO ) {
            jogador->quantidadeItensPegos++;
            item->ativo = false;
            jogador->pontos += item->pontosAoSerPego;
            PlaySound( rm.item );
            break;
        }

    }

}

TipoColisao checarColisaoJogadorItem( Jogador *jogador, Item *item ) {

    bool col = CheckCollisionRecs(
        (Rectangle) {
            .x = jogador->pos.x,
            .y = jogador->pos.y,
            .width = jogador->dim.x,
            .height = jogador->dim.y,
        },
        (Rectangle) {
            .x = item->pos.x,
            .y = item->pos.y,
            .width = item->dim.x,
            .height = item->dim.y,
        }
    );

    if ( col ) {
        return TIPO_COLISAO_INTERSECCAO;
    }

    return TIPO_COLISAO_NENHUMA;

}

void resolverColisaoJogadorInimigos( Jogador *jogador, int quantidadeInimigos, Inimigo *inimigos ) {

    for ( int i = 0; i < quantidadeInimigos; i++ ) {
            
        Inimigo *inimigo = &inimigos[i];

        if ( inimigo->vivo ) {

            TipoColisao colisao = checarColisaoJogadorInimigo( jogador, inimigo, true );

            switch ( colisao ) {
                case TIPO_COLISAO_ESQUERDA:
                    jogador->pos.x = inimigo->pos.x + inimigo->dim.x;
                    jogador->vida--;
                    break;
                case TIPO_COLISAO_DIREITA:
                    jogador->pos.x = inimigo->pos.x - jogador->dim.x;
                    jogador->vida--;
                    break;
                case TIPO_COLISAO_CIMA:
                    jogador->pos.y = inimigo->pos.y + inimigo->dim.y;
                    jogador->vel.y = 0.0f;
                    jogador->vida--;
                    break;
                case TIPO_COLISAO_BAIXO:
                    jogador->pos.y = inimigo->pos.y - jogador->dim.y;
                    jogador->vel.y = jogador->velocidadePulo;
                    inimigo->vivo = false;
                    jogador->pontos += inimigo->pontosAoSerMorto;
                    PlaySound( rm.batida );
                    break;
                default:
                    break;
            }

        }

    }

}

TipoColisao checarColisaoJogadorInimigo( Jogador *jogador, Inimigo *inimigo, bool checarSondas ) {
    
    if ( checarSondas ) {

        if ( checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_CIMA], inimigo ) ||
            checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_ESQUERDA_BAIXO], inimigo ) ) {
            return TIPO_COLISAO_ESQUERDA;
        }

        if ( checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_CIMA], inimigo ) ||
            checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_DIREITA_BAIXO], inimigo ) ) {
            return TIPO_COLISAO_DIREITA;
        }

        if ( checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_ESQUERDA], inimigo ) ||
            checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_CIMA_DIREITA], inimigo ) ) {
            return TIPO_COLISAO_CIMA;
        }

        if ( checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_ESQUERDA], inimigo ) ||
            checarColisaoSondaColisaoInimigo( &jogador->sondasColisao[POSICAO_SONDA_COLISAO_JOGADOR_BAIXO_DIREITA], inimigo ) ) {
            return TIPO_COLISAO_BAIXO;
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
                .x = inimigo->pos.x,
                .y = inimigo->pos.y,
                .width = inimigo->dim.x,
                .height = inimigo->dim.y,
            }
        );

        if ( col ) {
            return TIPO_COLISAO_INTERSECCAO;
        }

    }

    return TIPO_COLISAO_NENHUMA;

}
