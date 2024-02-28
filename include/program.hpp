// Arreglos de programación
unsigned long prog0[31] = {
                            0b00000000000000000000000000000000, // 

                            0b10010010010000100100000000000000, // ***Escenario 1***

                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar
                            0b00000000010000100100000000000000, // Transición de Verde a Ambar
                            0b10010010010000100100000000000000, // Transición de Verde a Ambar

                            0b01001001010000100100000000000000, // Tiempo de ambar  

                            0b00100100110000110000000000000000, // ***Escenario 2***

                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar
                            0b00100100100000100000000000000000, // Transición de Verde a Ambar
                            0b00100100110000110000000000000000, // Transición de Verde a Ambar

                            0b00100100101000101000000000000000, // Tiempo de ambar  

                            0b00100110000110000100000000000000, // ***Escenario 3***

                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar
                            0b00100110000100000100000000000000, // Transición de Verde a Ambar
                            0b00100110000110000100000000000000, // Transición de Verde a Ambar

                            0b00100110000101000100000000000000  // Tiempo de ambar  
};    

int longitud0 = sizeof(prog0) / sizeof(prog0[0]);


// Arreglos de programación
unsigned long prog00[31] = {
                            0b00000000000000000000000000000000, // 
                            
                            0b00100100100110010000000000000000, // ***Escenario 1***

                            0b00000000000110010000000000000000, // Transición de Verde a Ambar
                            0b00100100100110010000000000000000, // Transición de Verde a Ambar
                            0b00000000000110010000000000000000, // Transición de Verde a Ambar
                            0b00100100100110010000000000000000, // Transición de Verde a Ambar
                            0b00000000000110010000000000000000, // Transición de Verde a Ambar
                            0b00100100100110010000000000000000, // Transición de Verde a Ambar
                            0b00000000000110010000000000000000, // Transición de Verde a Ambar
                            0b00100100100110010000000000000000, // Transición de Verde a Ambar

                            0b01001001000110010000000000000000, // Transición de Verde a Ambar

                            0b10010010000110000100000000000000, // ***Escenario 2***

                            0b10010010000010000000000000000000, // Transición de Verde a Ambar
                            0b10010010000110000100000000000000, // Transición de Verde a Ambar
                            0b10010010000010000000000000000000, // Transición de Verde a Ambar
                            0b10010010000110000100000000000000, // Transición de Verde a Ambar
                            0b10010010000010000000000000000000, // Transición de Verde a Ambar
                            0b10010010000110000100000000000000, // Transición de Verde a Ambar
                            0b10010010000010000000000000000000, // Transición de Verde a Ambar
                            0b10010010000110000100000000000000, // Transición de Verde a Ambar

                            0b10010010001010001000000000000000, // Transición de Verde a Ambar

                            0b10010000110000110000000000000000, // ***Escenario 3***

                            0b10010000110000010000000000000000, // Transición de Verde a Ambar
                            0b10010000110000110000000000000000, // Transición de Verde a Ambar
                            0b10010000110000010000000000000000, // Transición de Verde a Ambar
                            0b10010000110000110000000000000000, // Transición de Verde a Ambar
                            0b10010000110000010000000000000000, // Transición de Verde a Ambar
                            0b10010000110000110000000000000000, // Transición de Verde a Ambar
                            0b10010000110000010000000000000000, // Transición de Verde a Ambar
                            0b10010000110000110000000000000000, // Transición de Verde a Ambar

                            0b10010000110001010000000000000000  // Transición de Verde a Ambar

};

int longitud = sizeof(prog00) / sizeof(prog00[0]);

unsigned long time0[31] = {  
                            0,

                            10000,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            3000,

                            10000,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            3000,

                            12000,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            375,
                            3000
};

unsigned long prog1[3] = {
                            0b00000000000000000000000000000000,
                            0b00000000000000000000000000000000,
                            0b10010010010010010010000000000000 
};    

unsigned long time1[3] = {
                            0,
                            375,
                            375 
};    

int longitud1 = sizeof(prog1) / sizeof(prog1[0]);

// Variables de Programación
unsigned long EscOn   = 0b11111111111111111111111111111111; // Todo Apagado
unsigned long EscOff  = 0b00000000000000000000000000000000; // Todo Encendido
///////////////////////////////////*FIN Programación*//////////////////////////////////////////
//////////////////////////////////*ConfigProg*////////////////////////////////////////////////
unsigned long firstColumn[8]; // Array for the first column
int matrix[8][8]; // 8x8 matrix for the remaining columns


unsigned long escnArray1[] = {4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295};
int sizeEscn = sizeof(escnArray1)/sizeof(escnArray1[0]);

    // Define the array
int eventArray1[] = {12, 0, 1, 1};
int eventArray2[] = {12, 30, 2, 1};
int eventArray3[] = {12, 45, 2, 1};
int eventArray4[] = {0, 0, 0, 0};
int eventArray5[] = {0, 0, 0, 0};
int eventArray6[] = {0, 0, 0, 0};
int eventArray7[] = {0, 0, 0, 0};
int eventArray8[] = {0, 0, 0, 0};
int sizeEvent = sizeof(eventArray1)/sizeof(eventArray1[0]);

int cycleArray1[] = {70, 25, 25, 0, 0, 0, 0, 0};
int cycleArray2[] = {70, 20, 30, 0, 0, 0, 0, 0};
int cycleArray3[] = {70, 20, 30, 0, 0, 0, 0, 0};
int cycleArray4[] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray5[] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray6[] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray7[] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray8[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sizeCycle = sizeof(cycleArray1)/sizeof(cycleArray1[0]);

int sincroArray1[] = {70, 0, 0, 0, 0, 0, 0, 0, 0};
int sizeSincro = sizeof(sincroArray1)/sizeof(sincroArray1[0]);

// Declarar una variable para almacenar el índice del arreglo
int indice = 0;
