/**
 * @file ResourceManager.c
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "ResourceManager.h"
#include "raylib/raylib.h"

ResourceManager rm = { 0 };

void loadResourcesResourceManager( void ) {
    rm.pulo = LoadSound( "resources/efeitosSonoros/pulo.wav" );
    rm.item = LoadSound( "resources/efeitosSonoros/item.wav" );
    rm.batida = LoadSound( "resources/efeitosSonoros/batida.wav" );
}

void unloadResourcesResourceManager( void ) {
    UnloadSound( rm.pulo );
    UnloadSound( rm.item );
    UnloadSound( rm.batida );
}