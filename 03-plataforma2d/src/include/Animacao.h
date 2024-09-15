#pragma once

#include "raylib/raylib.h"

typedef struct Animacao {
    Texture2D *texturas;
    Texture2D texturaAtual;
    int quadroAtual;
    int maximoQuadros;
    float tempoParaProximoQuadro;
    float contadorTempoQuadro;
} Animacao;

Animacao* criarAnimacao( const Texture2D *texturas, int quantidadeTexturas, float tempoParaProximoQuadro );
void destruirAnimacao( Animacao *animacao );
void atualizarAnimacao( Animacao *animacao, float delta );
void resetarAnimacao( Animacao *animacao );
