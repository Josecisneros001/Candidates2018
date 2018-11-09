

#include <Ultrasonic.h>

int derecha1= 22; 
int derecha2= 23;
const int S0 = 12;  
const int S1 = 13;  
const int S2 = 11;  
const int S3 = 10;  
const int out = 9;  
int frecuenciaRoja = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;
int rojo = 0;
int azul = 0;
int verde = 0;
int LEDA=27;
int LEDV=26;
int LEDR=29;
char color = '0';
int izquierda1= 24; 
int izquierda2= 25;
int count=0;
//FRENTE
const int Trigger1 = 7;  
const int Echo1 = 8;
//DERECHA   
const int Trigger2 = 46;  
const int Echo2 = 48;   //Pin digital 3 para el echo del sensor
//IZQUIERDA   
const int Trigger3 = 50;   //Pin digital 2 para el Trigger del sensor
const int Echo3 = 52;   //Pin digital 3 para el echo del sensor
int voltsconst[]={53,45,48,52,28,47};
int groundsconst[]={44,49,51,28};
int potenciamotor1=6;
int potenciamotor=5;

void setup()
{
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode (derecha1, OUTPUT);   
  pinMode (derecha2, OUTPUT);   
  pinMode (izquierda1, OUTPUT);   
  pinMode (izquierda2, OUTPUT);  
  pinMode(potenciamotor,OUTPUT);
    pinMode(potenciamotor1,OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
   pinMode(LEDR, OUTPUT);
  pinMode(LEDV, OUTPUT);
  pinMode(LEDA, OUTPUT);
   pinMode(out, INPUT);
   digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  for(int i=0;i<6;i++){
    pinMode(voltsconst[i],OUTPUT);
    digitalWrite(voltsconst[i],HIGH);
  }
  for(int i=0;i<4;i++){
    pinMode(groundsconst[i],OUTPUT);
    digitalWrite(groundsconst[i],LOW);
  } 
  
  pinMode(Trigger1, OUTPUT); //pin como salida
  pinMode(Echo1, INPUT);  //pin como entrada
  pinMode(Trigger2, OUTPUT); //pin como salida
  pinMode(Echo2, INPUT);  //pin como entrada
  pinMode(Trigger3, OUTPUT); //pin como salida
  pinMode(Echo3, INPUT);  //pin como entrada

}
void cambiarpotenciamotores(int x,int dif){

    analogWrite(potenciamotor,x);
    
    analogWrite(potenciamotor1,x-dif);
  
}
void avanzar(){
  
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
  
}
void atras(){
  
   digitalWrite(derecha1, LOW);
   digitalWrite(derecha2, HIGH);
   digitalWrite(izquierda2, HIGH);
   digitalWrite(izquierda1, LOW);
  
}
void giroejeR(){
  
      cambiarpotenciamotores(0,0);
    delay(1000);
   digitalWrite(derecha2, HIGH);
   digitalWrite(derecha1, LOW);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
    while(getDistanceF()<25){
    cambiarpotenciamotores(240,0);
    }

   delay(300); 
    avanzar();
    
}
void giroejeL(){
  
     cambiarpotenciamotores(0,0);
    delay(1000);
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, LOW);
   digitalWrite(izquierda2, HIGH);
  while(getDistanceF()<25){
   cambiarpotenciamotores(240,0);
    }
   delay(300); 
    avanzar();
}
void giroejeR1(){
  
   cambiarpotenciamotores(0,0);
    delay(500);
   digitalWrite(derecha2, HIGH);
   digitalWrite(derecha1, LOW);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
    
    cambiarpotenciamotores(240,0);
    

   delay(800); 
    avanzar();
    
}
void giroejeL1(){
  cambiarpotenciamotores(0,0);
    delay(500);
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, LOW);
   digitalWrite(izquierda2, HIGH);
    
    cambiarpotenciamotores(240,0);
    

   delay(800); 
    avanzar();
}

int getDistance(int t1,int ec1){
     long t; //timepo que demora en llegar el eco
      long d; //distancia en centimetros
      digitalWrite(t1, LOW);
       delayMicroseconds(10);          //Enviamos un pulso de 10us
      digitalWrite(t1, LOW);
      digitalWrite(t1, HIGH);
      delayMicroseconds(10);          //Enviamos un pulso de 10us
      digitalWrite(t1, LOW);
      t = pulseIn(ec1, HIGH); //obtenemos el ancho del pulso
       d = t/59; 
       return d;
  }
  int getDistanceF(){
     return getDistance(Trigger1,Echo1);
    }
    int getDistanceR(){
     return getDistance(Trigger2,Echo2);
    }
    int getDistanceL(){
     return getDistance(Trigger3,Echo3);
    }

    void calibrarcolor(){
               //CALIBRACION
        
         //COLOR ROJO 
         
           digitalWrite(S2,LOW );
           digitalWrite(S3,LOW);
         
           frecuenciaRoja = pulseIn(out, LOW);
         
           Serial.print(" R = ");
           Serial.print(frecuenciaRoja);
           delay(500);
        
          //VERDE
          
           digitalWrite(S2,HIGH);
           digitalWrite(S3,HIGH);
        
           frecuenciaVerde = pulseIn(out, LOW);
           
           Serial.print(" V = ");
           Serial.print(frecuenciaVerde);
           delay(500);
        
          //AZUL
           digitalWrite(S2,LOW);
           digitalWrite(S3,HIGH);
          
           frecuenciaAzul = pulseIn(out, LOW);
           
           Serial.print(" A = ");
           Serial.println(frecuenciaAzul);
           delay(500);
        
          // Constrains??
            }
           char getColor(){
          digitalWrite(S2,LOW);
          digitalWrite(S3,LOW);
          
          // Se lee el valor de la frecuencia 
          frecuenciaRoja = pulseIn(out, LOW);
          
         // Filtro para que no tome valores más grandes que los máx y mínimos
        if(frecuenciaRoja>115 || frecuenciaRoja<20){
          rojo = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaRoja>=29 && frecuenciaRoja<=115){
          rojo  = map(frecuenciaRoja,20,115,255,0);
         }
        
          // Ajustando los filtros verdes de los fotodiodos para que sean leídos 
          digitalWrite(S2,HIGH);
          digitalWrite(S3,HIGH);
         
          // Se lee el valor de la frecuencia 
        frecuenciaVerde = pulseIn(out, LOW);
        
         // Filtro para que no tome valores más grandes que los máx y mínimos
          if(frecuenciaVerde>166 || frecuenciaVerde<44){
          verde = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaVerde>=44 && frecuenciaVerde<=166){
          verde = map(frecuenciaVerde,44,166,255,0);
         }
         
          // Ajustando los filtros azules de los fotodiodos para que sean leídos 
          digitalWrite(S2,LOW);
          digitalWrite(S3,HIGH);
          
          // Se lee el valor de la frecuencia
          frecuenciaAzul = pulseIn(out, LOW);
        
        // Filtro para que no tome valores más grandes que los máx y mínimos
        if(frecuenciaAzul>119 || frecuenciaAzul<25){
          azul = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaAzul>=25 && frecuenciaAzul<=119){
          azul = map(frecuenciaAzul,25,119,255,0);
         }
        
        //Impresion de los valores de cada color
       /* Serial.print(" R = ");
         Serial.print(rojo);
          Serial.print("  ");
         
         Serial.print(" A = ");
         Serial.print(azul);
          Serial.print("  ");
         
         Serial.print(" V = ");
         Serial.print(verde);
         */
          digitalWrite(LEDR,LOW);
           digitalWrite(LEDA,LOW);
            digitalWrite(LEDV,LOW);
               if (rojo>azul && rojo>verde){
                digitalWrite(LEDR,HIGH);
      //    Serial.println("¡Color Rojo!");
          color = 'r';
          
          delay(200);
          }
          if (azul>rojo && azul>verde){
            digitalWrite(LEDA,HIGH);
            Serial.println("¡Color Azul!");
            color = 'a';
              delay(200);
          }
          if (verde>rojo && verde>azul){
            digitalWrite(LEDV,HIGH);
      //      Serial.println("¡Color Verde!");
            color = 'v';
              delay(200);
          }
          if(azul==rojo && rojo==verde && rojo==0){
             digitalWrite(LEDV,HIGH);
              digitalWrite(LEDA,HIGH);
              color = 'n';
             //  digitalWrite(LEDR,HIGH);
            }
            return color;
    }
    const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
const int LDRPin = A0;   //Pin del LDR
const int LDRPin2 = A3;  //Pin del LDR2
const int LDRPin3 = A5;  //Pin del LDR3
 
int V;
int V2;
int V3;
int ilum;
    void LDR(){
   V2 = analogRead(LDRPin2);
  ilum = V2;
  //Duda acerca de la altura donde este los sensores
  
 ilum = map(ilum,2010,2222,0,255); 
  Serial.println("Fotoresistor2 ");
   Serial.println(V2);
   delay(100);
   
   if ( ilum>200 && ilum<=255){
    Serial.println("Linea Blanca!");
    Serial.println(ilum);
   }
    if ( ilum<200 && ilum>=0){
    Serial.println("Color Verde");
    Serial.println(ilum);
   }
  
  // Serial.println(ilum);   
   delay(1000);
      }
      int sensorlinea(){
        Serial.print("Lectura: ");
        Serial.println(analogRead(A0));
  return (analogRead(A0)); //Imprime el valor de la lectura del canal A0
  delay(2000); //retardo de 2 segundos entre lectura
  
        }

        bool sensorbola(){
          return true;
          }
          int fase=1;
          int rampa=0;
          bool derecha=false;
void loop()
{
 // LDR();
 // return;

  if(getColor()=='v'){
    fase=2;
    }else if(sensorlinea()>600){
     fase=3;
      }else{
        fase=1;
        }
   /*
    Serial.println((String)"F"+getDistanceF());
    Serial.println((String)"L"+getDistanceL());
    Serial.println((String)"R"+getDistanceR());
 */   
 Serial.print(fase);
  //  delay(1000);
  if(fase==1){
    avanzar();
    cambiarpotenciamotores(150,40);
    delay(1000);
 
        int count=0;
            while(getColor()!='v' || count<2){
              count++;
    cambiarpotenciamotores(0,0);
  delay(800);
  if(count!=1){
   if(getDistanceF()<10){
      if((getDistanceL()<8) && (getDistanceR()<8)){
        giroejeR();
        }else if(getDistanceL()<8){
          giroejeR();
       
          }else{
            giroejeL();
            }
    }else{
      avanzar();
      } 
    }else{
        if(sensorbola()){
        giroejeR1();
        }else{
          giroejeL1();
       
          }
    } 
      
      while(getDistanceF()>10 ){
     //   Serial.print(getDistanceF());
        //110 25
        //255 20
   cambiarpotenciamotores(125,40);
   
     }}
      
    fase++;
      }
  
    
  while(fase==2){
      cambiarpotenciamotores(0,0);
  delay(300);
   if(sensorlinea()>500){
      if(getDistanceL()< getDistanceR()){
        giroejeR();
        }else{
            giroejeL();
            }
    }else{
      avanzar();
      } 
      while(getDistanceF()>10 ){
   cambiarpotenciamotores(125,40);
    
    fase++;
    break;
    }
  }
    while(fase==3){
      Serial.println(getDistanceF());
    cambiarpotenciamotores(0,0);
  delay(800);
   if(getDistanceF()<10){
      if((getDistanceL()<8) && (getDistanceR()<8)){
        giroejeR();
        if(rampa==1){break;}
        }else if(getDistanceL()<8){
          giroejeR();
          if(rampa==1){break;}

          }else{
            giroejeL();
            if(rampa==1){break;}

            }
    }else{
      avanzar();
      } 
      while(getDistanceF()>10 ){
     //   Serial.print(getDistanceF());
        //110 25
        //255 20
   cambiarpotenciamotores(140,40);
    //sensorcolor();
    if(getColor()=='r'){
      rampa=1;
      }
     }
      }
      
     avanzar();
      cambiarpotenciamotores(200,40);
}
