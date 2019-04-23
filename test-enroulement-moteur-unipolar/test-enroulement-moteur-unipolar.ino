#define VELOCIDAD 1700

int blue = 2;
int orange = 3;
int blanc = 4;
int gris = 5;
int steps = 13;
int direccion = 9;
int reset = 10;
int pasos = 3500;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(blue, OUTPUT); 
  pinMode(orange, OUTPUT);
  pinMode(blanc, OUTPUT); 
  pinMode(gris, OUTPUT);   

  //pinMode(reset, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(blue, LOW);    
  delay(1000);
  digitalWrite(blue, HIGH);
  delay(1000);   
  digitalWrite(orange, LOW);    
  delay(1000);
  digitalWrite(orange, HIGH);
  delay(1000);  
  digitalWrite(blanc, LOW);    
  delay(1000);
  digitalWrite(blanc, HIGH);
  delay(1000); 
  digitalWrite(gris, LOW);    
  delay(1000);
  digitalWrite(gris, HIGH); 
  delay(1000);
  //Serial.println("Sens 1");
/*    

  for (int i = 0; i<pasos; i++)       //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
    digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
    digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.  
    delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

  } 
  
  digitalWrite(reset, LOW);   //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delay(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, LOW);
  Serial.println("Sens 2");

  for (int i = 0; i<pasos; i++)       //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
      
    digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden
    digitalWrite(steps, HIGH);    // al A4988 de avanzar una vez por cada pulso de energia.
    delayMicroseconds(VELOCIDAD);         // Regula la velocidad, cuanto mas bajo mas velocidad.
  }
 */
}





