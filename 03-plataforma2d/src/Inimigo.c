#include "GameWorld.h"
#include "Inimigo.h"
#include "Animacao.h"
#include "SondaColisao.h"
#include "raylib/raylib.h"

Inimigo criarInimigo( Vector2 pos, Vector2 dim, float velocidadeCaminhada, Color cor, Animacao *animacaoEsquerda, Animacao *animacaoDireita ) {
    
    Inimigo novoInimigo = {
        .pos = pos,
        .dim = dim,
        .vel = { 0 },
        .velocidadeCaminhada = velocidadeCaminhada,
        .velocidadeMaximaQueda = 400.0f,
        .cor = cor,
        .estadoPosicao = ESTADO_POSICAO_INIMIGO_NO_CHAO,
        .vivo = true,
        .viradoDireita = false,
        .pontosAoSerMorto = 100,
        .animacaoEsquerda = animacaoEsquerda,
        .animacaoDireita = animacaoDireita
    };

    novoInimigo.sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_ESQUERDA] = criarSondaColisao( (Vector2) { 0 }, MAGENTA );
    novoInimigo.sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_DIREITA] = criarSondaColisao( (Vector2) { 0 }, MAGENTA );
    novoInimigo.sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_CIMA] = criarSondaColisao( (Vector2) { 0 }, MAGENTA );
    novoInimigo.sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_BAIXO] = criarSondaColisao( (Vector2) { 0 }, MAGENTA );

    return novoInimigo;

}

void atualizarInimigo( Inimigo *inimigo, float delta ) {

    if ( inimigo->vivo ) {

        inimigo->pos.x += inimigo->vel.x * delta;
        inimigo->pos.y += inimigo->vel.y * delta;

        if ( inimigo->viradoDireita ) {
            inimigo->vel.x = inimigo->velocidadeCaminhada;
        } else {
            inimigo->vel.x = -inimigo->velocidadeCaminhada;
        }

        if ( inimigo->vel.y > 0.0f ) {
            inimigo->estadoPosicao = ESTADO_POSICAO_INIMIGO_CAINDO;
        } else if ( inimigo->vel.y < 0.0f ) {
            inimigo->estadoPosicao = ESTADO_POSICAO_INIMIGO_PULANDO;
        }

        inimigo->vel.y += GRAVIDADE;

        if ( inimigo->vel.y >= inimigo->velocidadeMaximaQueda ) {
            inimigo->vel.y = inimigo->velocidadeMaximaQueda;
        }

        if ( inimigo->vel.x != 0.0f ) {
            if ( inimigo->vel.x >= 0.0f ) {
                inimigo->viradoDireita = true;
            } else {
                inimigo->viradoDireita = false;
            }
            atualizarAnimacao( inimigo->animacaoEsquerda, delta );
            atualizarAnimacao( inimigo->animacaoDireita, delta );
        } else {
            resetarAnimacao( inimigo->animacaoEsquerda );
            resetarAnimacao( inimigo->animacaoDireita );
        }

    }

}

void desenharInimigo( Inimigo *inimigo ) {

    if ( inimigo->vivo ) {

        if ( inimigo->viradoDireita ) {
            DrawTextureV( inimigo->animacaoDireita->texturaAtual, inimigo->pos, WHITE );
        } else {
            DrawTextureV( inimigo->animacaoEsquerda->texturaAtual, inimigo->pos, WHITE );
        }

        /*for ( int i = 0; i < 4; i++ ) {
            desenharSondaColisao( &inimigo->sondasColisao[i] );
        }*/

    }

}

void atualizarSondasColisaoInimigo( Inimigo *inimigo ) {

    float dimensaoSondaColisao = 4.0f;

    inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_ESQUERDA].pos = (Vector2) { inimigo->pos.x, inimigo->pos.y + inimigo->dim.y / 2 - dimensaoSondaColisao / 2 };
    inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_DIREITA].pos = (Vector2) { inimigo->pos.x + inimigo->dim.x - dimensaoSondaColisao, inimigo->pos.y + inimigo->dim.y / 2 - dimensaoSondaColisao / 2 };
    inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_CIMA].pos = (Vector2) { inimigo->pos.x + inimigo->dim.x / 2 - dimensaoSondaColisao / 2, inimigo->pos.y };
    inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_BAIXO].pos = (Vector2) { inimigo->pos.x + inimigo->dim.x / 2 - dimensaoSondaColisao / 2, inimigo->pos.y + inimigo->dim.y - dimensaoSondaColisao  };

}

void resolverColisaoInimigoBlocos( Inimigo *inimigo, int quantidadeLinhas, int quantidadeColunas, Bloco *blocos ) {

    for ( int i = 0; i < quantidadeLinhas; i++ ) {
        for ( int j = 0; j < quantidadeColunas; j++ ) {
            
            Bloco *bloco = &blocos[i*quantidadeColunas+j];

            if ( bloco->existe ) {

                TipoColisaoInimigo colisao = checarColisaoInimigoBloco( inimigo, bloco, true );

                switch ( colisao ) {
                    case TIPO_COLISAO_INIMIGO_ESQUERDA:
                        inimigo->pos.x = bloco->pos.x + bloco->dim.x + 2;
                        inimigo->viradoDireita = !inimigo->viradoDireita;
                        break;
                    case TIPO_COLISAO_INIMIGO_DIREITA:
                        inimigo->pos.x = bloco->pos.x - inimigo->dim.x - 2;
                        inimigo->viradoDireita = !inimigo->viradoDireita;
                        break;
                    case TIPO_COLISAO_INIMIGO_CIMA:
                        inimigo->pos.y = bloco->pos.y + bloco->dim.y;
                        break;
                    case TIPO_COLISAO_INIMIGO_BAIXO:
                        inimigo->pos.y = bloco->pos.y - inimigo->dim.y;
                        inimigo->vel.y = 0.0f;
                        inimigo->estadoPosicao = ESTADO_POSICAO_INIMIGO_NO_CHAO;
                        break;
                    default:
                        break;
                }

            }

        }

    }

}

TipoColisaoInimigo checarColisaoInimigoBloco( Inimigo *inimigo, Bloco *bloco, bool checarSondas ) {
    
    if ( checarSondas ) {

        if ( checarColisaoSondaColisaoBloco( &inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_ESQUERDA], bloco ) ) {
            return TIPO_COLISAO_INIMIGO_ESQUERDA;
        }

        if ( checarColisaoSondaColisaoBloco( &inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_DIREITA], bloco ) ) {
            return TIPO_COLISAO_INIMIGO_DIREITA;
        }

        if ( checarColisaoSondaColisaoBloco( &inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_CIMA], bloco ) ) {
            return TIPO_COLISAO_INIMIGO_CIMA;
        }

        if ( checarColisaoSondaColisaoBloco( &inimigo->sondasColisao[POSICAO_SONDA_COLISAO_INIMIGO_BAIXO], bloco ) ) {
            return TIPO_COLISAO_INIMIGO_BAIXO;
        }

    } else {

        bool col = CheckCollisionRecs(
            (Rectangle) {
                .x = inimigo->pos.x,
                .y = inimigo->pos.y,
                .width = inimigo->dim.x,
                .height = inimigo->dim.y,
            },
            (Rectangle) {
                .x = bloco->pos.x,
                .y = bloco->pos.y,
                .width = bloco->dim.x,
                .height = bloco->dim.y,
            }
        );

        if ( col ) {
            return TIPO_COLISAO_INIMIGO_INTERSECCAO;
        }

    }

    return TIPO_COLISAO_INIMIGO_NENHUMA;

}
