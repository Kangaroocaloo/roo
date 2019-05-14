//installare librerie prima di compilare il programma:
//https://drive.google.com/open?id=1JpqNR1TKswXgOYet4EpvPJwi3Euitw9n


#include <dht_nonblocking.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
///--------------
Servo servino;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
static const int DHT_SENSOR_PIN = 1;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
///---------------
//pin digitali
const int rosso=10;
const int verde=8;
const int blu=9;
const int PIR=6;
const int bottone=7;
const int servo=13;
//pin analogici
const int rotella=0;
const int sensoreTemp=1;
const int fotoResistore=2;
///--------------
//variabili 
bool flag=false;
int tolleranza;
unsigned short int minuti;
unsigned short int secondi;
unsigned int conta;
unsigned int conta_max=conta;
int d=1000;
float ultimaTemperatura;
unsigned short int chiudi;
unsigned short int scelta;
////////////////
void setup() {
  delay(200);
  servino.attach(13);
  servino.write(0);
  pinMode(fotoResistore,INPUT);
  pinMode(PIR,INPUT);
  pinMode(bottone,INPUT);
  pinMode(rosso,OUTPUT);
  pinMode(blu, OUTPUT);
  pinMode(verde,OUTPUT);
  lcd.begin(16, 2);
  analogWrite(verde,255);
  do{
    lcd.setCursor(0, 0);
    scelta=analogRead(rotella);
    scelta= map(scelta, 0, 1023, 0, 5);
    
    if(scelta<1) {
      lcd.print("  Chiudi porta");
      lcd.setCursor(0,1);
      lcd.print(" con Cronometro ");
    }
    if(scelta==1) {
      lcd.print("  Chiudi porta");
      lcd.setCursor(0,1);
      lcd.print(" con Termometro ");
      scelta=1;
      }
     if(scelta==2) {
      lcd.print("  Apri   porta");
      lcd.setCursor(0,1);
      lcd.print("con sensore'PIR'");
    }
     if(scelta==3) {
      lcd.print("  Apri   porta");
      lcd.setCursor(0,1);
      lcd.print("con sensore luce");
    }
    if(scelta==4 || scelta==5) {
      lcd.print("  Apri   porta");
      lcd.setCursor(0,1);
      lcd.print("con sensore Umi.");
      }
  } while(digitalRead(bottone)!=1);
Serial.println(scelta);
lcd.setCursor(0,0);
lcd.print("                ");
lcd.setCursor(0,1);
lcd.print("                ");
  switch(scelta){
  case 0:delay(200);
         lcd.setCursor(0, 0);
         lcd.print("Minuti:");
         do{
         minuti=analogRead(rotella);
         minuti= map(minuti, 0, 1023, 0, 61);
         lcd.setCursor(0, 1);
         lcd.print("    ");
         lcd.setCursor(0, 1);
         lcd.print(minuti);
         }while(digitalRead(bottone)!=1);
         lcd.setCursor(0, 0);
         lcd.print("Secondi:");
         delay(200);
         do{
         secondi=analogRead(rotella);
         secondi= map(secondi, 0, 1023, 0, 61);
         lcd.setCursor(0, 1);
         lcd.print("    ");
         lcd.setCursor(0, 1);
         lcd.print(secondi);
         }while(digitalRead(bottone)!=1);
         servino.write(180);
         chiudi=1;
         if(secondi>30) chiudi=0;
         conta=(minuti*60)+secondi;
         conta_max=conta;
         Serial.println(conta);
         lcd.setCursor(0, 0);
         lcd.print("           ");
         lcd.setCursor(0, 1);
         lcd.print("           ");
         break;
  case 1:delay(200);
         servino.write(180);
         lcd.setCursor(0, 0);
         lcd.print("   Tolleranza  ");
         do{
         tolleranza=analogRead(rotella);
         tolleranza=map(tolleranza,0,1023,-40,125);
         lcd.setCursor(0, 1);
         lcd.print("      ");
         if(tolleranza>0) lcd.print("+");
         lcd.print(tolleranza);
         lcd.print("C");
         lcd.setCursor(0, 1);
         lcd.print("                 ");
         }while(digitalRead(bottone)!=1);
         lcd.setCursor(0,0);
         lcd.print("                ");
         lcd.setCursor(0,1);
         lcd.print("                ");
         break;
  case 2:delay(200);
         lcd.setCursor(0, 0);
         lcd.print("  Delay Porta: ");
         do{
         tolleranza=analogRead(rotella);
         tolleranza=map(tolleranza,0,1023,1,60);
         lcd.setCursor(0, 1);
         lcd.print("    ");
         lcd.print(tolleranza);
         if(tolleranza==1) lcd.print("ciclo");
         else lcd.print("cicli");
         lcd.setCursor(0, 1);
         lcd.print("                 ");
         }while(digitalRead(bottone)!=1);
         lcd.setCursor(0,0);
         lcd.print("                ");
         lcd.setCursor(0,1);
         lcd.print("                ");
         break;
  case 3:delay(200);
         lcd.setCursor(0, 0);
         lcd.print("   Tolleranza  ");
         do{
         tolleranza=map(analogRead(rotella),0,1023,0,12);
         lcd.setCursor(0, 1);            
         if(tolleranza<6) lcd.print("   Notte    ");
         if(tolleranza>5 && tolleranza<8) lcd.print("   Alb/Tra  ");
         if(tolleranza>7)lcd.print("   Giorno   ");
         if(tolleranza>9)lcd.setCursor(11,1);
         lcd.print(tolleranza);
         lcd.setCursor(0, 1);
         lcd.print("                 ");
         }while(digitalRead(bottone)!=1);
         servino.write(180);
         lcd.setCursor(0,0);
         lcd.print("                ");
         lcd.setCursor(0,1);
         lcd.print("                ");
         break;
  case 4:delay(200);
         lcd.setCursor(0, 0);
         lcd.print("   Tolleranza  ");
         do{
         tolleranza=map(analogRead(rotella),0,1023,0,101);
         lcd.setCursor(0, 1);
         lcd.print("     ");
         lcd.print(tolleranza);
         lcd.print("%");
         lcd.setCursor(0, 1);
         lcd.print("                 ");
         }while(digitalRead(bottone)!=1);
         servino.write(180);
         lcd.setCursor(0,0);
         lcd.print("                ");
         lcd.setCursor(0,1);
         lcd.print("                ");
         break;
 default:break;
 }
delay(200);
do{
    lcd.setCursor(0, 0);
    lcd.print("Delay Operazioni");
    d=analogRead(rotella);
    d=map(d,0,1023,990,2002);
    lcd.setCursor(0, 1);
    lcd.print("Tempo:");
    lcd.print(d);
    lcd.print("ms");
    lcd.setCursor(6,1);
    lcd.print("                ");
}while(digitalRead(bottone)!=1);
chiudi=1;
if(d>1500) chiudi=0;
delay(200);
}  //setup finito
                                               //Funzione reset
void(*resetFunc)(void)=0;
                                       //Funzione rgb
void rgb(int r, int g, int b){
analogWrite(rosso,r);
analogWrite(verde,g);
analogWrite(blu,b);  
} 
                         //Funzione sensore dht11
static bool misura_ambiente( float *temperature, float *humidity, int d ){
static unsigned long measurement_timestamp = millis( );
if( millis( ) - measurement_timestamp > (d)*1ul ) 
rgb(0,0,0);
  {
  if( dht_sensor.measure( temperature, humidity ) == true ) 
    {
    measurement_timestamp = millis( );
    return( true );
    }
  }
return( false );
}

void loop() { //////////////////////////////////loop////////////////
  int leggiAnalogico;
  int leggiPotenziometro;
  int buttonState=digitalRead(bottone);
  int stopState;
  float temperatura=0;
  float umidita=0;
  switch(scelta){
case 0: //girare il potenziometro e premere il bottone 
        // per arrestare il processo
        if(conta==0 && digitalRead(bottone)==1) resetFunc();
        Serial.print(conta);
        Serial.println(" Secondi rimasti");
        if(buttonState==1 && conta>0) {
        lcd.setCursor(0, 0);
        lcd.print("     Stop!");
        delay(200);
        }
        do{
        leggiPotenziometro=analogRead(rotella);
        leggiPotenziometro=map(leggiPotenziometro,0,1023,0,2);
        stopState=digitalRead(bottone);
        lcd.setCursor(5, 1);
        if(conta>0) lcd.print("00:00");
        if(minuti>0){
        lcd.setCursor(5, 1);
        minuti=conta/60;
        if(minuti<10) lcd.setCursor(6, 1);
        lcd.print(minuti);
        }
        lcd.setCursor(8, 1);
        secondi=conta-minuti*60;
        if(secondi<10) lcd.setCursor(9, 1);
        if(conta>0)lcd.print(secondi);
        if(conta>conta_max/2){
        rgb(0,0,255);
        delay(d/2);
        rgb(0,0,0);
        delay(d/2);
        }
        else if(conta>0){
        if(buttonState!=1){
        lcd.setCursor(0, 1);
        lcd.print("  ");
        lcd.setCursor(0, 0);
        lcd.print("  -Meta' tempo");
        }
        rgb(255,255,255);
        delay(d/2);
        rgb(255,165,0);
        delay(d/2);
        }
        if(conta==0){
        flag=true;
        servino.write(0);
        lcd.setCursor(0, 1);
        lcd.print("  ");
        lcd.setCursor(0, 0);
        lcd.print(" Tempo scaduto! ");
        rgb(255,0,0);
        delay(d/2);
        rgb(0,0,0);
        delay(d/2);
        }
        if(stopState==buttonState) buttonState=0;
        }while(buttonState==1);
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        if(conta>0) conta-=1;
        //chiusura forzata con potenziometro
        if(leggiPotenziometro==chiudi && conta>0){ 
        lcd.setCursor(0, 0);
        lcd.print("               ");
        lcd.setCursor(0, 0);
        lcd.print("Chiusura forzata");
        servino.write(0);
        for(int i=0; i<4; i++){
        rgb(255,255,255);
        delay(1000);
        rgb(0,0,0);
        }
        conta=0;
        }
        break;
case 1: //premere il bottone per arrestare il processo
        //girare il potenziometro a destra per diminuire il delay
        leggiPotenziometro=map(analogRead(rotella),0,1023,0,d);
        if(buttonState==1) resetFunc();
        if( misura_ambiente( &temperatura, &umidita, d-leggiPotenziometro) == true )
        {
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0, 0);
          if(temperatura<10) lcd.print("   Freddo");
          if(temperatura>10 && temperatura<25) lcd.print("   Tiepido");
          if(temperatura>24) lcd.print("   Caldo");
          lcd.setCursor(0, 1);
          lcd.print("Temp.:");
          lcd.print(temperatura,1);
          lcd.print("'C");
          if(temperatura<tolleranza){
          if(flag==true){
          servino.write(180);
          flag=false;
          }
          rgb(0,255,0);
          }
          else if(temperatura>tolleranza){
          if (flag==false){
          servino.write(0);
          flag=true;
          }
          lcd.setCursor(0,0);
          lcd.print("Temper.superata!");
          lcd.setCursor(11,1);
          lcd.print(">");
          lcd.print(tolleranza);
          rgb(255,0,0);
          }
          ultimaTemperatura=temperatura;
        }
        break;
case 2: //premere il bottone per arrestare il processo
        //girare il potenziometro a destra per diminuire il delay
        leggiPotenziometro=analogRead(rotella);
        leggiPotenziometro=map(leggiPotenziometro,0,1023,0,d);
        if(buttonState==1) resetFunc();
        lcd.setCursor(0, 0);
        lcd.print("   Movimento:");
        lcd.setCursor(0, 1);
        if(digitalRead(PIR)==0){
        lcd.print("    Assente"); 
        if (flag==false){
        servino.write(180);
        flag=true;
        }
        rgb(255,0,0);
        }
        else if(digitalRead(PIR)==1){
        rgb(0,255,0);
        flag=false;
        lcd.print("    Presente!"); 
        servino.write(0);
        delay(d);
        lcd.setCursor(0,0);
        lcd.print("  Stato Porta:");
        lcd.setCursor(0,1);
        lcd.print("     Aperta   ");
        for(int i=0; i<tolleranza;i++){
        rgb(255,255,255);
        delay(d-leggiPotenziometro);
        rgb(0,0,0);
        }
        rgb(255,0,0);
        lcd.print("   Chiusa");
        servino.write(180);
        }
        delay(d-leggiPotenziometro);
        rgb(0,0,0);
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        break;
case 3: //premere il bottone per arrestare il processo
        //girare il potenziometro a destra per diminuire il delay
        //leggi il valore del pin analogico del fotoreisistore
        leggiAnalogico=map(analogRead(fotoResistore),0,1023,0,12);
        leggiPotenziometro=map(analogRead(rotella),0,1023,0,d);
        if(buttonState==1) resetFunc();
        lcd.setCursor(0, 0);            
        if(leggiAnalogico<6) lcd.print("   Notte    ");
        if(leggiAnalogico>5 && leggiAnalogico<8) lcd.print("   Alb/Tra  ");
        if(leggiAnalogico>7)lcd.print("   Giorno   ");
        lcd.setCursor(0, 1);
        lcd.print("St.Porta=");
        if(leggiAnalogico>tolleranza){
          servino.write(180);
          lcd.print("Chiusa");
          rgb(255,0,0);
         }
        else {
        servino.write(0);
        lcd.print("Aperta");
        rgb(0,255,0);
        }
        delay(d-leggiPotenziometro);
        lcd.setCursor(0,0);
        lcd.print("                 ");
        lcd.setCursor(0,1);
        lcd.print("                 ");
        break;
case 4: //premere il bottone per arrestare il processo
        //girare il potenziometro a destra per diminuire il delay
        leggiPotenziometro=map(analogRead(rotella),0,1023,0,d);
        if(buttonState==1) resetFunc();
        if( misura_ambiente( &temperatura, &umidita, d-leggiPotenziometro) == true )
        {
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0, 0);
          Serial.println(umidita);
          if(umidita<20) lcd.print("   Secco");
          if(temperatura>19 && temperatura<60) lcd.print("   Normale");
          if(temperatura>59) lcd.print("   Umido");
          lcd.setCursor(0, 1);
          lcd.print("Umid.:");
          lcd.print(umidita,1);
          lcd.print("%");
          if(umidita<tolleranza){
          if(flag==true){
          servino.write(0);
          flag=false;
          }
          rgb(0,255,0);
          }
          else if(umidita>tolleranza){
          if(flag==false){
          servino.write(180);
          flag=1;
          }
          lcd.setCursor(0,0);
          lcd.print("Umidita superata!");
          lcd.setCursor(11,1);
          lcd.print(">");
          lcd.print(tolleranza);
          rgb(255,0,0);
          
          }
        }
        break;
default:break;
  }
        
}//fine loop
//FUNZIONI
void pulisci(){
Serial.println("pulisco schermo");
lcd.setCursor(0,0);
lcd.print("                ");
lcd.setCursor(0,1);
lcd.print("                ");
}




