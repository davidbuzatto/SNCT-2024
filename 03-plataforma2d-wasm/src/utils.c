/**
 * @file utils.c
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "raylib/raylib.h"

double toRadians( double degrees ) {
    return degrees * PI / 180.0;
}

double toDegrees( double radians ) {
    return radians * 180.0 / PI;
}

Texture2D inverterTextura2DHorizontal( Texture2D textura ) {
    Image img = LoadImageFromTexture( textura );
    ImageFlipHorizontal( &img );
    Texture2D novaTextura = LoadTextureFromImage( img );
    UnloadImage( img );
    return novaTextura;
}