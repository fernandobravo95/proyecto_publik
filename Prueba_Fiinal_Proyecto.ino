#include <Keypad.h>


////-------------------------------------- TECLADO -----------------------------------------------

const byte numRows= 4; //Numero de filas en el teclado
const byte numCols= 3; //Numero de columnas en el teclado

//El mapa de teclas define la tecla presionada de acuerdo con la fila y las columnas
char keymap[numRows][numCols]= 
{
  {'1', '2', '3'}, 
  {'4', '5', '6'}, 
  {'7', '8', '9'},
  {'*', '0', '#'}
};

//Código que muestra las conexiones del teclado a los terminales arduino
byte rowPins[numRows] = {16,17,18,19};
byte colPins[numCols]= {15,14,7};

//Inicializa una instancia de la clase de teclado
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

char teclaActual = ' ';
int  cantidadPresionadas = 0;
String frase = "";
char letraActual = '¿';
String autorizado = "NO";

String frase1 = "";

char actualizarLetraActual(){
  
  char letraInicial = '?';
  char letraFinal   = '?';
  int cantidadPresionadasLocal = 0;
  
  if(teclaActual=='1'){
    // AQUI NO SE HACE NADA
    
  }else if(teclaActual=='2' || teclaActual=='3' || teclaActual=='4' || teclaActual=='5' || teclaActual=='6' || teclaActual=='8'){

    cantidadPresionadasLocal = (cantidadPresionadas-1) % 3;

    if(teclaActual=='2'){
      letraInicial = 'A'; 
    }else if(teclaActual=='3'){
      letraInicial = 'D'; 
    }else if(teclaActual=='4'){
      letraInicial = 'G'; 
    }else if(teclaActual=='5'){
      letraInicial = 'J'; 
    }else if(teclaActual=='6'){
      letraInicial = 'M'; 
    }else if(teclaActual=='8'){
      letraInicial = 'T'; 
    }

    letraFinal = letraInicial + cantidadPresionadasLocal;

  }else if(teclaActual=='7' || teclaActual=='9'){
    // AQUI se puede presionar 4 veces

    cantidadPresionadasLocal = (cantidadPresionadas-1) % 4;
    //Serial.println("  cantidad presionadas " );
    //Serial.println(cantidadPresionadas);

    if(teclaActual=='7'){
      letraInicial = 'P'; 
    }else if(teclaActual=='9'){
      letraInicial = 'W'; 
    }

    letraFinal = letraInicial + cantidadPresionadasLocal;

  }else{
    // AQUI PRESIONE EL CERO
    letraFinal = '_';
  }
  return letraFinal;
}


void reiniciar(){
  frase = "";
  teclaActual = ' ';
  cantidadPresionadas = 0;
}

////-------------------------------------- DISPLAY -----------------------------------------------

byte frase_columnas[84] = {};
 
int TAMANO_ESPACIO = 1; 
int posicion_movil = 0; 
int desplazarce = 1;
int debug = 1;

byte letras[7][7] = {
  { 0B111110,  0B001001, 0B001001, 0B111110, 0B000000, 0B000000, 0B000000 }, //A
  //{ 0B111111,  0B101001, 0B101001, 0B010110, 0B000000, 0B000000, 0B000000 }, //B
  //{ 0B011110,  0B100001, 0B100001, 0B010010, 0B000000, 0B000000, 0B000000 }, //C
  
  //{ 0B111110, 0B001111, 0B001001, 0B111110, 0B000000, 0B000000, 0B000000},
  { 0B111111, 0B101001, 0B101001, 0B010110, 0B000000, 0B000000, 0B000000},
  { 0B011110, 0B100001, 0B100001, 0B010010, 0B000000, 0B000000, 0B000000},

  { 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000 },
  { 0B00000000, 0B00000010, 0B01010101, 0B10101010, 0B11101010 },
  { 0B00011111, 0B00100100, 0B00100100, 0B00011111, 0B00000000 },
  { 0B00111111, 0B00100101, 0B00100101, 0B00011010, 0B00000000 }
  /*
  { B00110000, B01001000, B01001000, B01111000, B01001000, B01001000 }, //A
  { B01110000, B01001000, B01001000, B01110000, B01001000, B01110000 }, //B
  { B00110000, B01001000, B01000000, B01000000, B01001000, B00110000 }, //C
  { B01110000, B01001000, B01001000, B01001000, B01001000, B01110000 }, //D
  { B01111000, B01000000, B01110000, B01000000, B01000000, B01111000 }, //E
  { B01111000, B01000000, B01000000, B01110000, B01000000, B01000000 }, //F
  { B00110000, B01001000, B01000000, B01011000, B01001000, B00110000 }, //G
  { B01001000, B01001000, B01111000, B01001000, B01001000, B01001000 }, //H
  { B01110000, B00100000, B00100000, B00100000, B00100000, B01110000 }, //I
  { B00011000, B00001000, B00001000, B01001000, B01001000, B00110000 }, //J
  { B01001000, B01010000, B01100000, B01010000, B01001000, B01001000 }, //K
  { B01000000, B01000000, B01000000, B01000000, B01000000, B01111000 }, //L
  { B01000100, B01101100, B01010100, B01010100, B01000100, B01000100 }, //M
  { B01000100, B01100100, B01010100, B01001100, B01000100, B01000100 }, //N
  { B00110000, B01001000, B01001000, B01001000, B01001000, B00110000 }, //O
  { B01110000, B01001000, B01001000, B01110000, B01000000, B01000000 }, //P
  { B00110000, B01001000, B01001000, B01001000, B00110000, B00001000 }, //Q
  { B01110000, B01001000, B01001000, B01110000, B01001000, B01001000 }, //R
  { B00110000, B01001000, B01100000, B00011000, B01001000, B00110000 }, //S
  { B01111100, B00010000, B00010000, B00010000, B00010000, B00010000 }, //T
  { B01001000, B01001000, B01001000, B01001000, B01001000, B00110000 }, //U
  { B01000100, B01000100, B01000100, B01000100, B00101000, B00010000 }, //V
  { B01000100, B01000100, B01000100, B01010100, B01010100, B00101000 }, //W
  { B01000100, B00101000, B00010000, B00101000, B01000100, B01000100 }, //X
  { B01000100, B01000100, B00101000, B00010000, B00010000, B00010000 }, //Y
  { B01111000, B00001000, B00010000, B00100000, B01000000, B01111000 }  //Z  
  */
};

byte tamanos[] = {
  4,//A
  4,//B
  4,//C
  4,//D
  4,//E
  4,//F
  4,//G
  4,//H
  3,//I
  4,//J
  4,//K
  4,//L
  5,//M
  5,//N
  4,//O
  4,//P
  4,//Q
  4,//R
  4,//S
  5,//T
  4,//U
  5,//V
  5,//W
  5,//X
  5,//Y
  4,//Z
};

/*
byte letraA [] = {
  0B00011000,
  0B00100100,
  0B00100100,
  0B00111100,
  0B00100100,
  0B00100100
};
*/

byte area_display[6] = {
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  /*0B00111000,
  0B00010000,
  0B00011110,
  0B00010010,
  0B00010010,
  0B00010010*/
  /*0B00001100,
  0B00010010,
  0B00011110,
  0B00010010,
  0B00010010,
  0B00010010*/
};

String frase_string = "CAB";
int posicion_disponible = 0;



void inicializar(){
  //letras[0][0] = letras[0][0] << 2;
  // pone la frase en blanco
  /*
   frase_columnas[0] = c1;
   frase_columnas[1] = c2;
   frase_columnas[2] = c3;
   frase_columnas[3] = c4;
   frase_columnas[4] = c5;*/
  /*for(int c=0 ; c<84 ; c++){
    frase_columnas[c] = 0B00000000;
  }*/
  
  
  int tamano = frase_string.length();


  // RECORRO CARACTER POR CARACTER PARA DIBUJARLA(BYTES) EN FRASE_COLUMNA
  for(int i=0; i<tamano; i++){
    // CHAR letra = 'C' --> 67 // la variable letra ya es codigo ASCCI(para usar calculos matematicos)
    char letra = frase_string.charAt(i);
    // transformamos el ascci que inician en 0. para hacer uso del array de letras(donde tengo los dibujos de cada letra"Bytes")
    int posicion_buscada = letra - 65; 
    //byte letra_buscada[7] = letras[posicion_buscada];
    int tamano_buscado = tamanos[posicion_buscada];


     //cada letra esta compuesta por columnas, esas columnas son bytes, entonces recorro los bytes(que componen la letra) 
     //y seran escritos en "frase_columnas"  
    for(int j=0; j<tamano_buscado; j++) { //columna
      // Copiar

      for(int b = 0 ; b<8 ; b++){  // cada uno de los bits de la columna

        //copio el bit de mi "letra" a "frase_columnas"               
        bitWrite(frase_columnas[posicion_disponible], b ,bitRead(letras[posicion_buscada][j],b));
      }
      
      posicion_disponible ++;
    } 
    /*
    // recorro para colocar una fila en blanco
    for(int b = 0 ; b<8 ; b++){
        bitWrite(frase_columnas[posicion_disponible], b ,LOW);
    }*/
       
    posicion_disponible += TAMANO_ESPACIO;
  }
}



void setup() {

  Serial.begin(9600);
  
  if (debug == 1 ) {

    for (int j=2; j<17; j++){ 
    pinMode(j, OUTPUT);  
    }

  } else {
    for (int j=0; j<17; j++){ 
    pinMode(j, OUTPUT);  
    }
  }  
}

int VELOCIDAD = 0;

void loop() {
   
  Serial.print("HOla ya pueden integrar");
  // Esto es solo para Funcionamiento correcto del display
  inicializar();
  actualizar_display();
  while(true){    

    VELOCIDAD++;
    
    mostrar_display();
    
    
    delay(10);
    if(VELOCIDAD==10){
      actualizar_display();
      VELOCIDAD = 0;
    }
    //delay(30);
  }

  


  
  
} //cierra loop


int REPETIR = 0;
void actualizar_display(){
    if(desplazarce == 0){     //MODO DE VISUALIZACIION DE FRASE ESTATICA

      posicion_movil = 0;
            
      // copiamos desde area total hacia area display
      // Se recorrren 7 columnas que son las que se pueden ver en el display

      for(int i=0 ; i<8 ; i++){
        for(int c=0; c<8; c++){
          bitWrite(area_display[i], c, bitRead(frase_columnas[7-c], i));
          //bitWrite(area_display[i], 7 - c, HIGH);
        }
      }
      //posicion_movil = 8;     
      
    }else{    // FRASE DESPLAZAMIENTO SUAVE
  
    if(posicion_movil >= posicion_disponible){
      posicion_movil = 0;
    }   
      for(int f=0; f<6; f++){
        area_display[f] = area_display[f] << 1;
      }
      // aqui ya desplacé todo a la izquierda 

        //LLENAR VACIO
        for(int i=0 ; i<6 ; i++){
          bitWrite(area_display[i], 0, bitRead(frase_columnas[posicion_movil], i));
        }
         posicion_movil++;    
             
     }

    
    /*
    for(int f = 0 ; f<7 ; f++){
        int temp = bitRead(area_display[f], 7);
        for(int c=0; c<8; c++){
          if(c==7){
              bitWrite(area_display[f], 7 - c, temp);
          }else{
              bitWrite(area_display[f], 7 - c, bitRead(area_display[f], 7 - (c + 1)));
          }
          
        } 
        //bitWrite(area_display[c], c ,HIGH);
          //--for(int b = 0 ; b<8 ; b++){
          //--   //bitWrite(area_display[c], 7 - b ,!!bitRead(frase_columnas[c],7-b));
          //--   bitWrite(area_display[c], 7 - b ,!!bitRead(frase_columnas[c],7-b));
          //--}
        
    }*/
   
  
}

int PIN_FILAS_INICIAL = 8;

void mostrar_display(){
  
  for (int f=0; f<6; f++){
    if(f==0){
      _digitalWrite(PIN_FILAS_INICIAL+5,LOW);
    }else{
      _digitalWrite(PIN_FILAS_INICIAL+f-1,LOW);
    }
    
    pintar_fila(area_display[f], f);
    //delay(10);
    //limpiar_fila(f);
    //delay(10);  
  }
}


void pintar_fila(byte datos, int fila) {

int x=0;
  while(x++<100){
    for(int i=0; i<8; i++){ //recorre columna  
      _digitalWrite(i, !bitRead(datos,7 - i)); 
      
    }
    _digitalWrite(fila+PIN_FILAS_INICIAL, HIGH);
    //_digitalWrite(fila+PIN_FILAS_INICIAL, LOW);  
    //delay(500);
  }
}

void limpiar_fila(int fila) {
  _digitalWrite(fila+PIN_FILAS_INICIAL, LOW);
  for(int c=0; c<8; c++){ //recorre columna  
    _digitalWrite(c, LOW); 
  } 
}


void pintar_letra(byte letra[]){
  for(int i=0; i<6; i++){ //recorro los bytes(las filas que conforman la letra)
    pintar_fila(letra[i], i+PIN_FILAS_INICIAL);
    delay(5);
    _digitalWrite(i+PIN_FILAS_INICIAL, LOW);
    delay(5);    
  }  
}

void _digitalWrite(int pin, bool valor){
  if (debug && (pin == 0 || pin == 1)){
    
  }else{
    digitalWrite(pin,valor);  
  }
}
