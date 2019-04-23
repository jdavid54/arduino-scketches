/*
Stepper motor 28BYJ-48 Parameters
Model ： 28BYJ-48
Rated voltage ： 5VDC
Number of Phase ： 4
Speed Variation Ratio ： 1/64
Stride Angle ： 5.625° /64
Frequency : 100Hz
DC resistance ： 50Ω±7%(25℃)
Idle In-traction Frequency : > 600Hz
Idle Out-traction Frequency : > 1000Hz
In-traction Torque >34.3mN.m(120Hz)
Self-positioning Torque >34.3mN.m
Friction torque : 600-1200 gf.cm
Pull in torque : 300 gf.cm
Insulated resistance >10MΩ(500V)
Insulated electricity power ：600VAC/1mA/1s
Insulation grade ：A
Rise in Temperature <40K(120Hz)
Noise <35dB(120Hz,No load,10cm)

http://www.geeetech.com/wiki/index.php/Stepper_Motor_5V_4-Phase_5-Wire_%26_ULN2003_Driver_Board_for_Arduino
*/

int Blue = 8;   //blue
int Pink = 9;    // pink
int Yellow = 10;   // yellow
int Orange = 11;    // orange
int _step = 0;
int count = 0; 
boolean dir = false;// gre
int wait = 1;

void setup() 
{ 
 Serial.begin(9600); 
 pinMode(Blue, OUTPUT);  
 pinMode(Pink, OUTPUT);  
 pinMode(Yellow, OUTPUT);  
 pinMode(Orange, OUTPUT);  
} 
 void loop() 
{ 
  //Serial.print(_step);
  //Serial.println(count);
  if (count%6400==0) dir = !dir;   //800 loops
 // 8 steps
 switch(_step){ 
   case 0: 
     digitalWrite(Blue, LOW);  
     digitalWrite(Pink, LOW); 
     digitalWrite(Yellow, LOW); 
     digitalWrite(Orange, HIGH);
      
   break;  
   case 1: 
     digitalWrite(Blue, LOW);  
     digitalWrite(Pink, LOW); 
     digitalWrite(Yellow, HIGH); 
     digitalWrite(Orange, HIGH); 
     
   break;  
   case 2: 
     digitalWrite(Blue, LOW);  
     digitalWrite(Pink, LOW); 
     digitalWrite(Yellow, HIGH); 
     digitalWrite(Orange, LOW); 
      
   break;  
   case 3: 
     digitalWrite(Blue, LOW);  
     digitalWrite(Pink, HIGH); 
     digitalWrite(Yellow, HIGH); 
     digitalWrite(Orange, LOW); 
      
   break;  
   case 4: 
     digitalWrite(Blue, LOW);  
     digitalWrite(Pink, HIGH); 
     digitalWrite(Yellow, LOW); 
     digitalWrite(Orange, LOW); 
      
   break;  
   case 5: 
     digitalWrite(Blue, HIGH);  
     digitalWrite(Pink, HIGH); 
     digitalWrite(Yellow, LOW); 
     digitalWrite(Orange, LOW); 
     
   break;  
     case 6: 
     digitalWrite(Blue, HIGH);  
     digitalWrite(Pink, LOW); 
     digitalWrite(Yellow, LOW); 
     digitalWrite(Orange, LOW);
     
   break;  
   case 7: 
     digitalWrite(Blue, HIGH);  
     digitalWrite(Pink, LOW); 
     digitalWrite(Yellow, LOW); 
     digitalWrite(Orange, HIGH); 
     
   break;  
   default: 
     digitalWrite(Blue, LOW);  
     digitalWrite(Pink, LOW); 
     digitalWrite(Yellow, LOW); 
     digitalWrite(Orange, LOW); 
   break;  
 } 
 if(dir){ 
   _step++; 
   count++;
 }else{ 
   _step--;
   count--;
 } 
 if(_step>7){ 
  
   _step=0; 
 } 
 if(_step<0){ 
  
   _step=7; 
 } 
 delay(wait); 
 
}
