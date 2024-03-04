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

// Time array
unsigned int time0[31] = {  
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
// Complete time array
unsigned int timeArray[31][8] = {  
                            {0, 0, 0, 0, 0, 0, 0, 0},

                            {10000, 15000, 20000, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {3000, 3000, 3000, 0, 0, 0, 0, 0},

                            {10000, 15000, 20000, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {3000, 3000, 3000, 0, 0, 0, 0, 0},

                            {12000, 15000, 20000, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {375, 375, 375, 0, 0, 0, 0, 0},
                            {3000, 3000, 3000, 0, 0, 0, 0, 0}
};
int sizetimeEsc_ = sizeof(timeArray)/sizeof(timeArray[0]);
// Events Array
int eventArray[8][4] = {
                            {12, 0, 1, 1},
                            {12, 30, 2, 1},
                            {12, 45, 2, 1},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}
};
int sizeEvent_ = sizeof(eventArray)/sizeof(eventArray[0]);
// Cycle array
int cycleArray[8][8] = {
                            {70, 25, 25, 0, 0, 0, 0, 0},
                            {70, 20, 30, 0, 0, 0, 0, 0},
                            {70, 20, 30, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0}
};
int sizeCycle_ = sizeof(cycleArray)/sizeof(cycleArray[0]);

// Sicro Array
int sincroArray[8] = {70, 0, 0, 0, 0, 0, 0, 0};
int sizeSincro_ = sizeof(sincroArray)/sizeof(sincroArray[0]);


unsigned long prog1[3] = {
                            0b00000000000000000000000000000000,
                            0b00000000000000000000000000000000,
                            0b10010010010010010010000000000000 
};    

unsigned int time1[3] = {
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
unsigned long firstColumn[8]; // Array for the first column // Array de JSON
int matrix[8][8]; // 8x8 matrix for the remaining columns

// Arreglo de Escenarios
unsigned long escnArray1[8] = {4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295};
int sizeEscn = sizeof(escnArray1)/sizeof(escnArray1[0]);
// Arreglo de Tiempo de Escenarios
unsigned int timeEsc[8] = {10, 10, 12, 10, 10, 10, 10, 10};
int sizetimeEsc = sizeof(timeEsc)/sizeof(timeEsc[0]);
// Arreglos de Eventos
int eventArray1[4] = {12, 0, 1, 1};
int eventArray2[4] = {12, 30, 2, 1};
int eventArray3[4] = {12, 45, 2, 1};
int eventArray4[4] = {0, 0, 0, 0};
int eventArray5[4] = {0, 0, 0, 0};
int eventArray6[4] = {0, 0, 0, 0};
int eventArray7[4] = {0, 0, 0, 0};
int eventArray8[4] = {0, 0, 0, 0};
int sizeEvent = sizeof(eventArray1)/sizeof(eventArray1[0]);
// Arreglos de Ciclos
int cycleArray1[8] = {70, 25, 25, 0, 0, 0, 0, 0};
int cycleArray2[8] = {70, 20, 30, 0, 0, 0, 0, 0};
int cycleArray3[8] = {70, 20, 30, 0, 0, 0, 0, 0};
int cycleArray4[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray5[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray6[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray7[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int cycleArray8[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sizeCycle = sizeof(cycleArray1)/sizeof(cycleArray1[0]);
// Arreglo de Sincronías
int sincroArray1[8] = {70, 0, 0, 0, 0, 0, 0, 0};
int sizeSincro = sizeof(sincroArray1)/sizeof(sincroArray1[0]);

// Declarar una variable para almacenar el índice del arreglo
//int indice = 0;
