

#include <msp430>
#include "teclado.h"

const unsigned char teclado[4][4] PROGMEM = {{'1', '2', '3', 'F'},
                                              {'4', '5', '6', 'E'},
                                              {'7', '8', '9', 'D'},
                                              {'A', '0', 'B', 'C'}};

unsigned char ler_teclado{

    unsigned char n, j, tecla=0xFF, linha

    for(n=0;n<4;n++)
    }
}
