/**
 * @file ResourceManager.h
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Animacao.h"

#include "raylib/raylib.h"

typedef struct ResourceManager {

    Texture2D tileA;
    Texture2D tileB;
    Texture2D tileC;
    Texture2D tileD;
    Texture2D tileE;
    Texture2D tileF;
    Texture2D tileG;
    Texture2D tileH;
    Texture2D tileI;

    Texture2D jogadorE0;
    Texture2D jogadorE1;
    Texture2D jogadorD0;
    Texture2D jogadorD1;

    Texture2D item0;
    Texture2D item1;
    Texture2D item2;
    Texture2D item3;

    Texture2D inimigoE0;
    Texture2D inimigoE1;
    Texture2D inimigoD0;
    Texture2D inimigoD1;

    Sound pulo;
    Sound item;
    Sound batida;

    Music musica;

    Animacao *animacaoJogadorEsquerda;
    Animacao *animacaoJogadorDireita;
    
    Animacao *animacaoItem;

    Animacao *animacaoInimigoEsquerda;
    Animacao *animacaoInimigoDireita;

} ResourceManager;

/**
 * @brief Global ResourceManager instance.
 */
extern ResourceManager rm;

/**
 * @brief Load global game resources, linking them in the global instance of
 * ResourceManager called rm.
 */
void loadResourcesResourceManager( void );

/**
 * @brief Unload global game resources.
 */
void unloadResourcesResourceManager( void );