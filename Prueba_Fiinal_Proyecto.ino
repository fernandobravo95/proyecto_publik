byte frase_columnas[84] = {};

int posicion_movil = 0; 

byte letras[2][5] = {
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
  0B00010000,
  0B00010000,
  0B00011110,
  0B00010010,
  0B00010010,
  0B00010010
  /*0B00001100,
  0B00010010,
  0B00011110,
  0B00010010,
  0B00010010,
  0B00010010*/
};

String frase_string = "ABAB";
int posicion_disponible = 0;

void inicializar(){
  // pone la frase en blanco

  for(int c=0 ; c<84 ; c++){
    frase_columnas[c] = 0B00000000;
  }
  
  
  int tamano = frase_string.length();
  for(int i=0; i<tamano; i++){
    char letra = frase_string.charAt(i);
    int posicion_buscada = letra - 65;
    //byte letra_buscada[7] = letras[posicion_buscada];
    int tamano_buscado = tamanos[posicion_buscada];

    for(int j=0; j<tamano_buscado; j++) {
      // Copiar

      for(int b = 0 ; b<8 ; b++){
        //bitWrite(frase_columnas[posicion_disponible], 7 - b ,letras[posicion_buscada][b]);
        
       bitWrite(frase_columnas[posicion_disponible], b ,bitRead(letras[posicion_buscada][j],b));
         //bitWrite(area_display[c],                     7 - b ,!!bitRead(frase_columnas[c]       ,7-b));
        
       // bitWrite(frase_columnas[posicion_disponible], 7 - b ,HIGH);
      }
      
      posicion_disponible ++;
    } 
    for(int b = 0 ; b<8 ; b++){
        bitWrite(frase_columnas[posicion_disponible], b ,LOW);
    }
    posicion_disponible ++;
  }
}



void setup() {
  for (int j=0; j<17; j++){ 
  pinMode(j, OUTPUT);  
  }
}

int VELOCIDAD = 0;
void loop() {
  //inicializar();
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
  
  
}

int REPETIR = 0;
void actualizar_display(){
    if(posicion_movil == 0){
      
      // copiamos desde area total hacia area display
      // Se recorrren 7 columnas que son las que se pueden ver en el display
      
    }
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
          /*for(int b = 0 ; b<8 ; b++){
             //bitWrite(area_display[c], 7 - b ,!!bitRead(frase_columnas[c],7-b));
             bitWrite(area_display[c], 7 - b ,!!bitRead(frase_columnas[c],7-b));
          }*/
        
    }
   
  
}

int PIN_FILAS_INICIAL = 8;

void mostrar_display(){
  
  for (int f=0; f<6; f++){
    if(f==0){
      digitalWrite(PIN_FILAS_INICIAL+5,LOW);
    }else{
      digitalWrite(PIN_FILAS_INICIAL+f-1,LOW);
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
      digitalWrite(i, !bitRead(datos,7 - i)); 
      
    }
    digitalWrite(fila+PIN_FILAS_INICIAL, HIGH);
    //digitalWrite(fila+PIN_FILAS_INICIAL, LOW);
    //delay(500);
  }
}

void limpiar_fila(int fila) {
  digitalWrite(fila+PIN_FILAS_INICIAL, LOW);
  for(int c=0; c<8; c++){ //recorre columna  
    digitalWrite(c, LOW); 
  } 
}


void pintar_letra(byte letra[]){
  for(int i=0; i<6; i++){ //recorro los bytes(las filas que conforman la letra)
    pintar_fila(letra[i], i+PIN_FILAS_INICIAL);
    delay(5);
    digitalWrite(i+PIN_FILAS_INICIAL, LOW);
    delay(5);    
  }  
}
