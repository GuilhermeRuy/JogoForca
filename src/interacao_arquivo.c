#include "interacao_arquivo.h"
#include <dstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Palavra pegar_palavra( char *arquivo_palavra, unsigned int linha_palavra );
Dica pegar_dica( char *arquivo_dica, unsigned int linha_dica );

void ir_para_linha( FILE *arquivo, unsigned int linha );
String *ler_string( FILE *arquivo );

unsigned int pegar_total_linhas( char *arquivo_palavra );
unsigned int sortear_linha( unsigned int quantidade_linhas );

Palavra sortear_palavra( char *arquivo_palavra, char *arquivo_dica ) {
    Palavra palavra;

    palavra =
        pegar_palavra( arquivo_palavra, sortear_linha( pegar_total_linhas( arquivo_palavra ) ) );

    palavra.dica = pegar_dica( arquivo_dica, palavra.fk_dica );

    return palavra;
}

Palavra pegar_palavra( char *arquivo_palavra, unsigned int linha_palavra ) {
    FILE *arquivo;

    Palavra palavra;

    arquivo = fopen( arquivo_palavra, "r" );
    if( !arquivo ) {
        return palavra;
    }

    ir_para_linha( arquivo, linha_palavra );

    fscanf( arquivo, "%d", &palavra.fk_dica );

    fscanf( arquivo, "%*c" );

    palavra.palavra = ler_string( arquivo );

    fclose( arquivo );

    return palavra;
}

Dica pegar_dica( char *arquivo_dica, unsigned int linha_dica ) {
    FILE *arquivo;

    Dica dica;

    arquivo = fopen( arquivo_dica, "r" );
    if( !arquivo ) {
        return dica;
    }

    ir_para_linha( arquivo, linha_dica );
    dica.dica = ler_string( arquivo );

    fclose( arquivo );

    return dica;
}

unsigned int sortear_linha( unsigned int quantidade_linhas ) {
    srand( time( NULL ) );
    return rand() % quantidade_linhas;
}

unsigned int pegar_total_linhas( char *arquivo_palavra ) {
    FILE *arquivo;
    unsigned int quantidade_linhas = 0;

    arquivo = fopen( arquivo_palavra, "r" );
    if( !arquivo ) {
        return -1;
    }

    while( EOF != fscanf( arquivo, "%*[^\n]" ) ) {
        fscanf( arquivo, "%*c" );
        quantidade_linhas++;
    }

    fclose( arquivo );

    return quantidade_linhas;
}

void ir_para_linha( FILE *arquivo, unsigned int linha ) {
    unsigned int i = 0;

    while( linha != i ) {
        fscanf( arquivo, "%*[^\n]" );
        fscanf( arquivo, "%*c" );
        i++;
    }
}

String *ler_string( FILE *arquivo ) {
    char tmp[101];

    String *string = string_new();

    if( !string ) {
        return NULL;
    }

    while( fscanf( arquivo, "%100[^\n]", tmp ) ) {
        string_concat_char_array( string, tmp );
    }

    return string;
}
