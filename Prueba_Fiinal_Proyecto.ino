#include <Keypad.h>

////-------------------------------------- TECLADO
///-----------------------------------------------

const byte numRows = 4; // Numero de filas en el teclado
const byte numCols = 3; // Numero de columnas en el teclado

// El mapa de teclas define la tecla presionada de acuerdo con la fila y las
// columnas
char keymap[numRows][numCols] = { { '1', '2', '3' },
    { '4', '5', '6' },
    { '7', '8', '9' },
    { '*', '0', '#' } };

// Código que muestra las conexiones del teclado a los terminales arduino
byte rowPins[numRows] = { 16, 17, 18, 19 };
byte colPins[numCols] = { 15, 14, 7 };

// Inicializa una instancia de la clase de teclado
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

char teclaActual = ' ';
int cantidadPresionadas = 0;
String frase = "";
char letraActual = '¿';
String autorizado = "NO";

String frase1 = "";

char actualizarLetraActual()
{
    char letraInicial = '?';
    char letraFinal = '?';
    int cantidadPresionadasLocal = 0;

    if (teclaActual == '1') {
        // AQUI NO SE HACE NADA
    }
    else if (teclaActual == '2' || teclaActual == '3' || teclaActual == '4' || teclaActual == '5' || teclaActual == '6' || teclaActual == '8') {
        cantidadPresionadasLocal = (cantidadPresionadas - 1) % 3;

        if (teclaActual == '2') {
            letraInicial = 'A';
        }
        else if (teclaActual == '3') {
            letraInicial = 'D';
        }
        else if (teclaActual == '4') {
            letraInicial = 'G';
        }
        else if (teclaActual == '5') {
            letraInicial = 'J';
        }
        else if (teclaActual == '6') {
            letraInicial = 'M';
        }
        else if (teclaActual == '8') {
            letraInicial = 'T';
        }

        letraFinal = letraInicial + cantidadPresionadasLocal;
    }
    else if (teclaActual == '7' || teclaActual == '9') {
        // AQUI se puede presionar 4 veces

        cantidadPresionadasLocal = (cantidadPresionadas - 1) % 4;
        // Serial.println("  cantidad presionadas " );
        // Serial.println(cantidadPresionadas);

        if (teclaActual == '7') {
            letraInicial = 'P';
        }
        else if (teclaActual == '9') {
            letraInicial = 'W';
        }

        letraFinal = letraInicial + cantidadPresionadasLocal;
    }
    else {
        // AQUI PRESIONE EL CERO
        letraFinal = '_';
    }
    return letraFinal;
}

void reiniciar()
{
    frase = "";
    teclaActual = ' ';
    cantidadPresionadas = 0;
}

////-------------------------------------- DISPLAY
///-----------------------------------------------

byte frase_columnas[84] = {};

int TIEMPO_VISUALIZACION_LETRA = 20;
int TAMANO_ESPACIO = 1;
int posicion_movil = 0;
int desplazarce = 1;
int debug = 0;

byte letras[27][7] = {
  { 0B111110, 0B001001, 0B001001, 0B111110, 0B000000, 0B000000, 0B000000 }, //A
  { 0B111111, 0B101001, 0B101001, 0B010110, 0B000000, 0B000000, 0B000000 }, //B
  { 0B011110, 0B100001, 0B100001, 0B010010, 0B000000, 0B000000, 0B000000 }, //C
  { 0B111111, 0B100001, 0B100001, 0B011110, 0B000000, 0B000000, 0B000000 }, //D
  { 0B111111, 0B100101, 0B100101, 0B100001, 0B000000, 0B000000, 0B000000 }, //E
  { 0B111111, 0B001001, 0B001001, 0B000001, 0B000000, 0B000000, 0B000000 }, //F
  { 0B011110, 0B100001, 0B101001, 0B011010, 0B000000, 0B000000, 0B000000 }, //G
  { 0B111111, 0B000100, 0B000100, 0B111111, 0B000000, 0B000000, 0B000000 }, //H  
  { 0B100001, 0B111111, 0B100001, 0B000000, 0B000000, 0B000000, 0B000000 } , //I 
  { 0B011000, 0B100000, 0B100001, 0B011111, 0B000000, 0B000000, 0B000000 }, //J
  { 0B111111, 0B000100, 0B001010, 0B110001, 0B000000, 0B000000, 0B000000 }, //K
  { 0B111111, 0B100000, 0B100000, 0B100000, 0B000000, 0B000000, 0B000000 }, //L
  { 0B111111, 0B000010, 0B001100, 0B000010, 0B111111, 0B000000, 0B000000 }, //M
  { 0B111111, 0B000010, 0B000100, 0B001000, 0B111111, 0B000000, 0B000000 }, //N
  { 0B011110, 0B100001, 0B100001, 0B011110, 0B000000, 0B000000, 0B000000 }, //O
  { 0B111111, 0B001001, 0B001001, 0B000110, 0B000000, 0B000000, 0B000000 }, //P
  { 0B001110, 0B010001, 0B010001, 0B101110, 0B000000, 0B000000, 0B000000 }, //Q
  { 0B111111, 0B001001, 0B001001, 0B110110, 0B000000, 0B000000, 0B000000 }, //R
  { 0B010110, 0B100101, 0B101001, 0B011010, 0B000000, 0B000000, 0B000000 }, //S
  { 0B000001, 0B000001, 0B111111, 0B000001, 0B000001, 0B000000, 0B000000 }, //T
  { 0B011111, 0B100000, 0B100000, 0B011111, 0B000000, 0B000000, 0B000000 }, //U
  { 0B001111, 0B010000, 0B100000, 0B010000, 0B001111, 0B000000, 0B000000 }, //V
  { 0B011111, 0B100000, 0B011000, 0B100000, 0B011111, 0B000000, 0B000000 }, //W
  { 0B110001, 0B001010, 0B000100, 0B001010, 0B110001, 0B000000, 0B000000 }, //X
  { 0B000011, 0B000100, 0B111000, 0B000100, 0B000011, 0B000000, 0B000000 }, //Y
  { 0B110001, 0B101001, 0B100101, 0B100011, 0B000000, 0B000000, 0B000000 }  //Z
  //{ 0B110001, 0B101001, 0B100101, 0B100011, 0B000000, 0B000000, 0B000000 }  //SPACE
};

byte tamanos[] = {
    4, // A
    4, // B
    4, // C
    4, // D
    4, // E
    4, // F
    4, // G
    4, // H
    3, // I
    4, // J
    4, // K
    4, // L
    5, // M
    5, // N
    4, // O
    4, // P
    4, // Q
    4, // R
    4, // S
    5, // T
    4, // U
    5, // V
    5, // W
    5, // X
    5, // Y
    4, // Z
};

byte area_display[6] = {
    0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
};

String frase_string = "NNNNN"; //aca va la frase a mostrar en display
int posicion_disponible = 0;

void inicializar()
{
    posicion_disponible = 0;

    int tamano = frase_string.length();

    // RECORRO CARACTER POR CARACTER PARA DIBUJARLA(BYTES) EN FRASE_COLUMNA
    for (int i = 0; i < tamano; i++) {
        // CHAR letra = 'C' --> 67 // la variable letra ya es codigo ASCCI(para usar
        // calculos matematicos)
        char letra = frase_string.charAt(i);
        // transformamos el ascci que inician en 0. para hacer uso del array de
        // letras(donde tengo los dibujos de cada letra"Bytes")
        int posicion_buscada = letra - 65;
        // byte letra_buscada[7] = letras[posicion_buscada];
        int tamano_buscado = tamanos[posicion_buscada];

        // cada letra esta compuesta por columnas, esas columnas son bytes, entonces
        // recorro los bytes(que componen la letra)
        // y seran escritos en "frase_columnas"
        for (int j = 0; j < tamano_buscado; j++) { // columna
            // Copiar

            for (int b = 0; b < 8; b++) { // cada uno de los bits de la columna

                // copio el bit de mi "letra" a "frase_columnas"
                bitWrite(frase_columnas[posicion_disponible], b,
                    bitRead(letras[posicion_buscada][j], b));
            }

            posicion_disponible++;
        }
        /*
// recorro para colocar una fila en blanco
for(int b = 0 ; b<8 ; b++){
    bitWrite(frase_columnas[posicion_disponible], b ,LOW);
}*/

        posicion_disponible += TAMANO_ESPACIO;
    }
}

void setup()
{
    Serial.begin(9600);

    if (debug == 1) {
        for (int j = 2; j < 17; j++) {
            pinMode(j, OUTPUT);
        }
    }
    else {
        for (int j = 0; j < 17; j++) {
            pinMode(j, OUTPUT);
        }
    }
}

int VELOCIDAD = 0;

void loop()
{
    Serial.println("hola");
    while (true) {

        char keypressed = myKeypad.getKey();
    
        if (keypressed != NO_KEY) {
          
            Serial.println("Presionó algo");
    
            // AQUI QUIERO SABER SI PRESIONE 1 o 0
    
            if (keypressed == '0' || (keypressed >= '2' && keypressed <= '9')) {
                
                Serial.println("Presionó tecla del 0 al 9");
    
                // Estoy autorizado a ingresar valores?
                if (autorizado == "SI") {
                        
                        // la tecla que presione ya la habia presionado antes
                        if (keypressed == teclaActual) {
                            // Ocurre cuando estoy en la misma tecla
                            cantidadPresionadas++;
                        }
                        else {
                            // Ocurre cuando me cambio de tecla
                            teclaActual = keypressed;
                            cantidadPresionadas = 1;
                        }
                        // El usuario está escribiendo algo
                        // Serial.println("El usuario está escribiendo algo");
                        // Aqui digo que la letra actual es la tecla presionada
                        teclaActual = keypressed;
    
                        char a = actualizarLetraActual();

                        
                        frase_string = "";
                        frase_string = a;
                                               
                        Serial.println("==================*********");
                        Serial.println(frase_string);
                        Serial.println("==================");
                        Serial.println("");
                        Serial.println("");
                        Serial.println("");

                        inicializar();
                        actualizar_display();
                        desplazarce = 0;
                        
                        for(int i=0; i<TIEMPO_VISUALIZACION_LETRA; i++){
                            VELOCIDAD++;
                            mostrar_display();   
                            delay(1);
                            
                            if(VELOCIDAD==10){
                                actualizar_display();
                                VELOCIDAD = 0;
                            }                                              
                        }

                        frase_string = "";
                        limpiar_area_display();    
                        limpiar_frase_columnas();
                        mostrar_display();
                                            
                    
                }
                else {
                    Serial.println("Hey amigo calma, ha presionado AZULES PERO NO ESTA AUTORIZADO Oprima (1)");
                }
            }
            else {   //LE PARECE A DIEGOO QUE FALTA UN VALIDACION PARA SBER SI ANTES YA NO ESTABA UTORIZADO
                Serial.println("tecla de control");
                if (keypressed == '1') {            // 1 SIRVE PARA INICIAR LA CAPTURA DE LETRAS 
                    // Aqui se debe reiniciar todo
                    Serial.println("Ya está Aurizado, hagale mijo");
                    autorizado = "SI";
                    reiniciar();
                }
                else if (keypressed == '#') { //NUMERAL SIRVE PARA GUARDAR LETRA
                    if (autorizado == "SI") {
    
                        char nueva = actualizarLetraActual();
                        //Serial.println("variable nueva trae");
                        //Serial.println(nueva);
                        //Serial.println("");
                        //Serial.println("");
    
                        if (nueva != '_') {
                            frase1 = frase;
                            frase = frase + nueva;
                            String a = "Buena, ahora la longitud es: ";
                            a = a + frase.length();
                            Serial.println(a);
    
                            if (frase.length() > 12) {
                                Serial.println("la frase es muy larga - MAXIMO 12 Caracteres");
                            }
                        }
                        else {
                            Serial.println("Hey amigo calma, no ha presionado AZULES validas");
                            //Serial.println("Hey vierjo, que le voy a confirmar si no ha presionado nada??????");
                        }
    
                        teclaActual = '?';
                        cantidadPresionadas = 0;
                    }
                    else {
                        Serial.println("Hey amigo calma, ha presionado ROJAS PERO NO ESTA AUTORIZADO Oprima (A)");
                        //Serial.println("Hey amigo calma, ha presionado confirmar PERO NO ESTA AUTORIZADO Retroceda");
                    }
                }
                else if (keypressed == '*') {         //* SIRVE PARA MOSTRAR LAS LETRAS CAPTURADAS, LUEGO DE OPRIMIR * NO SE PUEDE ADICIONAR MAS LETRAS
                    if (autorizado == "SI") {
                        int len = frase.length();
                        if (len == 0) {
                            Serial.println("No ha ingresado nada");
                        }
                        else if (len < 4) {
                            Serial.println("la frase es muy corta - MINIMO 4 Caracteres");
                        }
                        else if (len > 12) {
                            Serial.println("la frase es muy larga - MAXIMO 12 Caracteres");
                            Serial.println(frase1);
                                                           
                            autorizado = "NO";
                        }
                        else {
    
                            //if (frase != '____________' ){
                            Serial.println(frase);
                            
                            //}else{
                            //Serial.println("La frase solo contiene espacios");
                            //}

              //puse de aca ************************
                            inicializar();
                            actualizar_display();
                            desplazarce = 1;
                            frase_string = frase;
                            Serial.println(frase_string);
                            
                            for(int i=0; i<TIEMPO_VISUALIZACION_LETRA; i++){
                                VELOCIDAD++;
                                mostrar_display();   
                                //delay(1);
                                
                                if(VELOCIDAD==100){
                                    actualizar_display();
                                    VELOCIDAD = 0;
                                }                                              
                            }
               // hasta aca ************************** 


                           autorizado = "NO";
                            
                        }
                    }
                    else {
                        Serial.println("Hey amigo calma, ha presionado ROJAS PERO NO ESTA AUTORIZADO Oprima (A)");
                    }
                }
                else  {
                    
                        Serial.println("ESTO NUNCA SE VERá");
                   
                }
            }
        } else {

          Serial.print(".");
          
        } 
    }// cierre while   

    
Serial.print("HOla ya pueden integrar");
/*// Esto es solo para Funcionamiento correcto del display
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
}*/

} // cierra loop

int REPETIR = 0;
void actualizar_display()
{
    if (desplazarce == 0) { // MODO DE VISUALIZACIION DE FRASE ESTATICA

        posicion_movil = 0;

        // copiamos desde area total hacia area display
        // Se recorrren 7 columnas que son las que se pueden ver en el display

        for (int i = 0; i < 8; i++) {
            for (int c = 0; c < 8; c++) {
                bitWrite(area_display[i], c, bitRead(frase_columnas[7 - c], i));
                // bitWrite(area_display[i], 7 - c, HIGH);
            }
        }
        // posicion_movil = 8;
    }
    else { // FRASE DESPLAZAMIENTO SUAVE

        if (posicion_movil >= posicion_disponible) {
            posicion_movil = 0;
        }
        for (int f = 0; f < 6; f++) {
            area_display[f] = area_display[f] << 1;
        }
        // aqui ya desplacé todo a la izquierda

        // LLENAR VACIO
        for (int i = 0; i < 6; i++) {
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
            bitWrite(area_display[f], 7 - c, bitRead(area_display[f], 7 - (c +
  1)));
        }

      }
      //bitWrite(area_display[c], c ,HIGH);
        //--for(int b = 0 ; b<8 ; b++){
        //--   //bitWrite(area_display[c], 7 - b
  ,!!bitRead(frase_columnas[c],7-b));
        //--   bitWrite(area_display[c], 7 - b
  ,!!bitRead(frase_columnas[c],7-b));
        //--}

  }*/
}

int PIN_FILAS_INICIAL = 8;

void mostrar_display()
{
    for (int f = 0; f < 6; f++) {
        if (f == 0) {
            _digitalWrite(PIN_FILAS_INICIAL + 5, LOW);
        }
        else {
            _digitalWrite(PIN_FILAS_INICIAL + f - 1, LOW);
        }

        pintar_fila(area_display[f], f);
        // delay(10);
        // limpiar_fila(f);
        // delay(10);
    }
}

void pintar_fila(byte datos, int fila)
{
    int x = 0;
    while (x++ < 100) {
        for (int i = 0; i < 8; i++) { // recorre columna
            _digitalWrite(i, !bitRead(datos, 7 - i));
        }
        _digitalWrite(fila + PIN_FILAS_INICIAL, HIGH);
        //_digitalWrite(fila+PIN_FILAS_INICIAL, LOW);
        // delay(500);
    }
}

void limpiar_fila(int fila)
{
    _digitalWrite(fila + PIN_FILAS_INICIAL, LOW);
    for (int c = 0; c < 8; c++) { // recorre columna
        _digitalWrite(c, LOW);
    }
}

void limpiar_area_display(){
    for (int f=0; f<6; f++){
         area_display [f] = 0B00000000;        
    }  
}

void pintar_letra(byte letra[])
{
    for (int i = 0; i < 6;
         i++) { // recorro los bytes(las filas que conforman la letra)
        pintar_fila(letra[i], i + PIN_FILAS_INICIAL);
        delay(5);
        _digitalWrite(i + PIN_FILAS_INICIAL, LOW);
        delay(5);
    }
}

void _digitalWrite(int pin, bool valor)
{
    if (debug && (pin == 0 || pin == 1)) {
    }
    else {
        digitalWrite(pin, valor);
    }
}


void limpiar_frase_columnas() {
    int longitud = 0;

    longitud = sizeof(frase_columnas);

    for (int i=0; i<longitud; i++){
        frase_columnas [i] = 0B00000000;   
    }   
}
