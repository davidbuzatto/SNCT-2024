#include <stdlib.h>

#include "Animacao.h"
#include "raylib/raylib.h"

Animacao* criarAnimacao( const Texture2D *texturas, int quantidadeTexturas, float tempoParaProximoQuadro ) {

    Animacao *novaAnimacao = (Animacao*) calloc( 1, sizeof( Animacao ) );

    novaAnimacao->texturas = (Texture2D*) malloc( quantidadeTexturas * sizeof( Texture2D ) );
    for ( int i = 0; i < quantidadeTexturas; i++ ) {
        novaAnimacao->texturas[i] = texturas[i];
    }
    
    novaAnimacao->maximoQuadros = quantidadeTexturas;
    novaAnimacao->tempoParaProximoQuadro = tempoParaProximoQuadro;
    
    resetarAnimacao( novaAnimacao );

    return novaAnimacao;

}

void destruirAnimacao( Animacao *animacao ) {
    free( animacao->texturas );
    free( animacao );
}

void atualizarAnimacao( Animacao *animacao, float delta ) {

    animacao->contadorTempoQuadro += delta;

    if ( animacao->contadorTempoQuadro >= animacao->tempoParaProximoQuadro ) {
        animacao->contadorTempoQuadro = 0;
        animacao->quadroAtual = ( animacao->quadroAtual + 1 ) % animacao->maximoQuadros;
        animacao->texturaAtual = animacao->texturas[animacao->quadroAtual];
    }

}

void resetarAnimacao( Animacao *animacao ) {
    animacao->contadorTempoQuadro = 0.0f;
    animacao->quadroAtual = 0;
    animacao->texturaAtual = animacao->texturas[animacao->quadroAtual];
}