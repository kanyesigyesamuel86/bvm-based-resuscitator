#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "MAX30100_PulseOximeter.h"
#include "Wire.h"

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_BME280 bme;  // Create BME280 sensor object
PulseOximeter pox;

#define BME280_ADDRESS 0x76 // BME280 I2C address
#define MAX30100_ADDRESS 0x57 // MAX30100 I2C address
#define SEALEVELPRESSURE_HPA (1013.25) //regular_pressure. needs to be measured


int buzzer=2;
int maintain_power=9;
int power_read=10;
int breath_pulse=11;
int power_led=12;
int clock_pulse=13;

int forward_drive=14;
int backward_drive=15;

//  Buttons on A5
//  A on A2.
//  B on A3.
int subroutine= 0;
int list_0 = 0;
int list_1 = 0;
int list_2 = 0;
int list_3 = 0;
int d_lock = 0;
int lock_1 = 0;
int key = 0;
int s_busy = 0;
int k_busy=0;
int go = 0;
int count_1=0;
int power_off=0;
int count2=0;
int transition=0;
int vol = 0;
int forward = 0;
int backward = 0;
int step=0;
int drive=1;
int count_k=0;
int step_count=0;
int s_lock=0;
int A=0;
int B=0;
int initial=0;
int P=0;
int home=0;
int run=0;
int count_d=0;
int drive_enable = 0;
int k = 0;
int step_limit=20;
int p_time=800;
int t_lock=0;
int patient = 0;
int volume=100;
int rate = 40;
int terminate=0;

int list_position = 0;
int value=0;
int vol_display[] = {0, 0 , 0};
int rate_display[] = {2, 0};
int pulse = 0;
int prev_subroutine = 0;
String d_value[] = {"DEFAULT MODE", "ALARMS", "SP02 LEVEL", "PRESSURE", "RESET ALL"} ;
String sensors[] = {"OXIMETER", "LDR", "PRESSURE SENSOR", "BUZZER", "LED"};
int totalItems = sizeof(sensors) / sizeof(sensors[0]);
int index = 0;

// Variables to track the current position in the menu list
int currentTopItem = 0;
int visibleItems = 3; 
unsigned long start_time = 0;
unsigned long end_time = 0;
unsigned long elapsed_time = 0;
unsigned long t1 = 0;
unsigned long t2 = 0;
float hr = 0.0;
float spo2 = 0.0;


void setup() {
//   Wire.begin();
   lcd.begin(20, 4);
   pinMode(forward_drive,OUTPUT);
   pinMode(backward_drive,OUTPUT);   
   pinMode(buzzer,OUTPUT);
   pinMode(maintain_power,OUTPUT);  
   pinMode(power_led,OUTPUT);
   pinMode(breath_pulse,INPUT);
   pinMode(clock_pulse,INPUT);
   pinMode(power_read,INPUT);

   digitalWrite(maintain_power,1);
   digitalWrite(forward_drive,0);
   digitalWrite(backward_drive,0);  
   digitalWrite(power_led,1);


   digitalWrite(buzzer,1);
   delay(100);
   digitalWrite(buzzer,0);

   lcd.setCursor(0, 0);
   lcd.print("STARTING            ");   
   delay(500);   
   lcd.setCursor(0, 0);
   lcd.print("STARTING.           ");   
   delay(500);  
   lcd.setCursor(0, 0);
   lcd.print("STARTING..          ");   
   delay(500); 
   lcd.setCursor(0, 0);
   lcd.print("STARTING...         ");   
   delay(500);     
   lcd.setCursor(0, 0);
   lcd.print("STARTING            ");   
   delay(500);   
   lcd.setCursor(0, 0);
   lcd.print("STARTING.           ");   
   delay(500);  
   lcd.setCursor(0, 0);
   lcd.print("STARTING..          ");   
   delay(500); 
   lcd.setCursor(0, 0);
   lcd.print("STARTING...         ");   
   delay(500); 
   lcd.clear();
   lcd.print("No BME280 sensor!");
   delay(2000);

/*     
  lcd.setCursor(0, 0);
  if (!bme.begin(BME280_ADDRESS)) {
    lcd.print("No BME280 sensor!");
    delay(500); 
    while (1);
  }
  lcd.print("No BME280 sensor!");

  if (!pox.begin()) {
    lcd.print("No MAX30100 sensor!");
    delay(500); 
    while (1);
  }

 lcd.print("Sensors initialized!");
  delay(500);
  lcd.clear();
*/
}

void loop() {

// key_event

if(analogRead(A5)>0 and lock_1==0){
lock_1=1;
keys();
}
if(analogRead(A5)==0 and lock_1==1){
lock_1=0;  
d_lock=0;
}

count_1++;
if(count_1==1){
go=1;
}
if(count_1==2000){
go=0;
d_lock==0;
}

if(count_1==5000){
count_1=0;
}


if(digitalRead(power_read)==1 and power_off==0){      //   POWER OFF INITIALISER.
  power_off=1;
  k_busy=1;
  s_busy=1;
  lcd.clear();
}
if(power_off==1){                                     //   POWER OFF MENU.

  if(go==1 and t_lock==0){
  t_lock=1;
  lcd.setCursor(0, 1);
  lcd.print("  TURN OFF SYSTEM   ");  
  }
  if(go==0 and t_lock==1){
  t_lock=0;
  lcd.setCursor(0, 0);
  lcd.print("                    ");  
  }

  if(d_lock==0){
  d_lock=1;
  lcd.setCursor(0, 3);
  lcd.print("NO               YES");
  }
  if(key==3){
  digitalWrite(maintain_power,0);
  }

  if(key==1){
  transition=1;
  power_off=0;
  t_lock=0;
  lcd.clear();
  }

}

if(transition==1 and key==0){                         //   SUBROUTINE TRANSITION HANDLER
  s_busy=0;
  k_busy=0;
  d_lock=0;
  transition=0;
  delay(200); 
}

if(subroutine==0){                                    //   HOME SCREEN
  if(k_busy==0){         //   KEY ASSIGNMENT.
    if(key==1){
    list_0--;
    d_lock=0;
    }
    if(key==3){
    list_0++;
    d_lock=0;
    }
    if(list_0==3){
    list_0=0;
    }
    if(list_0==-1){
    list_0=2;
    }
        
    if(key==2){
    d_lock=1;
    transition=1;
    lcd.clear();
    k_busy=1;
        
    if(list_0==0){
    subroutine=1;
    }
    if(list_0==1){
    subroutine=2;
    }
    if(list_0==2){
    subroutine=3;
    }
    }
  }
  if(s_busy==0){         //   MESSAGE TO DISPLAY  
    if(list_0==0 and d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("    SELECT MODE     ");  
    lcd.setCursor(0, 3);
    lcd.print("<--     ENTER    -->"); 
    }
    if(list_0==1 and d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("      SETTINGS      "); 
    lcd.setCursor(0, 3);
    lcd.print("<--     ENTER    -->"); 
    }

    if(list_0==2 and d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("    SYSTEM CHECK    "); 
    lcd.setCursor(0, 3);
    lcd.print("<--     ENTER    -->"); 
    }
  }
}

if(subroutine==1){                                    //   OPERATION MODE OPTIONS
  if(k_busy==0){         //   KEY ASSIGNMENT.
    if(key==1){
    list_1++;
    d_lock=0;
    }
    if(list_1==2){
    list_1=0;
    }

    if(key==3){
    transition=1;
    subroutine=0;
    lcd.clear();
    k_busy=1;
    s_busy=1;
    }

    if(key==2){
     transition=1;
     k_busy=1;
     s_busy=1;
     lcd.clear();

     if(list_1==0){
     subroutine=4;
     }
     if(list_1==1){
     subroutine=5;
     }
    }

  }
  if(s_busy==0){
    if(d_lock==0 and list_1==0){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("---> PATIENT_DRIVEN ");
    lcd.setCursor(0, 1);
    lcd.print("     SELF_DRIVEN    "); 
    lcd.setCursor(0, 3);
    lcd.print(" ^     SELECT   BACK");    
    }
    if(d_lock==0 and list_1==1){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("     PATIENT_DRIVEN ");
    lcd.setCursor(0, 1);
    lcd.print("---> SELF_DRIVEN    "); 
    lcd.setCursor(0, 3);
    lcd.print(" ^     SELECT   BACK");    
    }
  } 
}
 
if(subroutine==2){                                    //   FREE
  //PUT CODE HERE. 
  if(k_busy==0){
    if(key==1){
      value++;
      d_lock= 0;
      lcd.clear();

    }
    if(value==4){
      value=0;
    }
    if(key==2){
      transition=1;
      k_busy=1;
      s_busy=1;
      lcd.clear();
      if(value==0){
        subroutine= 13;
      }
      if(value==1){
        subroutine=14;
      }
      if(value==2){
        subroutine=15;
      }
      if(value==3){
        subroutine=16;
      }
      if(value==4){
        subroutine=17;
      }

    }
    if(key==3){
     transition=1;
     k_busy=1;
     s_busy=1;
     lcd.clear();
     subroutine=0;

    }
  }
  if(s_busy==0){
    if(d_lock==0){
      d_lock=1;
      lcd.setCursor(4, 1);
      for(int i= 0; i<5; i++){
        if(value==i){
          lcd.print(d_value[i]);
        }
      }
      lcd.setCursor(0, 3);
      lcd.print("SELECT  ENTER  BACK");
    }

  }
}

if(subroutine==3){                                    
  if(k_busy==0){
    if(key==1){
      value++;
      d_lock=0;
      lcd.clear();
    }
    if(value==2){
      value=0;
    }

    if(key==2){
      transition=1;
      s_busy=1;
      k_busy=1;
      lcd.clear();
      if(value==0){
        subroutine=18;
      }
      if(value==1){
        subroutine=19;
      }
    }

    if(key==3){
      transition=1;
      s_busy=1;
      k_busy=1;
      lcd.clear();
      subroutine=0;
    }

  }
  if(s_busy==0){
    if(d_lock==0){
      d_lock=1;
      if(value==0){
        lcd.setCursor(0, 0);
        lcd.print("--> MOTOR");
        lcd.setCursor(0, 1);
        lcd.print("    SENSORS");
      }
      if(value==1){
        lcd.setCursor(0, 0);
        lcd.print("    MOTOR");
        lcd.setCursor(0, 1);
        lcd.print("--> SENSORS");
      }
      lcd.setCursor(0, 3);
      lcd.print("SELECT  ENTER   BACK");
    }
  }
}

if(subroutine==4){                                    //   SELECTING PATIENT FOR SELF DRIVEN MODE.
 if(k_busy==0){       //   KEY ASSIGNMENT
            
  if(key==1){        
  k_busy=1;      
  s_busy=1;                  
  transition=1;
  lcd.clear();
  subroutine=6;
  patient = 0;
  volume=100;
  step_limit=15;
  p_time=500;    

  }  

  if(key==2){
  k_busy=1;
  s_busy=1;
  transition=1;
  lcd.clear();
  subroutine=6;
  patient= 1;
  volume=200;
  step_limit=20;
  p_time=800;
  }

  if(key==3){
  k_busy=1;
  s_busy=1;
  transition=1;
  lcd.clear();
  subroutine=1;
  }   

 }
 if(s_busy==0){       //   MESSAGE TO DISPLAY
    if(d_lock==0){
    d_lock=1; 
    lcd.setCursor(0, 1);
    lcd.print("   CHOOSE PATIENT   ");
    lcd.setCursor(0, 3);
    lcd.print("CHILD   ADULT   BACK");
  }      
 }
}

//self driven mode
if(subroutine==5){                                   

  if(k_busy==0){       //   KEY ASSIGNMENT
              
    if(key==1){        
    k_busy=1;      
    s_busy=1;                  
    transition=1;
    lcd.clear();
    subroutine=8;
    patient= 0;
    volume=100;
    rate = 40;
    step_limit=15;
    p_time=500;              
    }  

    if(key==2){
    k_busy=1;
    s_busy=1;
    transition=1;
    lcd.clear();
    subroutine=8;
    patient=1;
    volume=200;
    rate = 25;
    step_limit=20;
    p_time=800;
    }

    if(key==3){
    k_busy=1;
    s_busy=1;
    transition=1;
    lcd.clear();
    subroutine=1;
    }   

  }
  if(s_busy==0){       //   MESSAGE TO DISPLAY
    if(d_lock==0){
    d_lock=1; 
    lcd.setCursor(0, 1);
    lcd.print("   CHOOSE PATIENT   ");
    lcd.setCursor(0, 3);
    lcd.print("CHILD   ADULT   BACK");
    }      
  }
}

if(subroutine==6){                                    //   START WINDOW FOR FOR PATIENT DRIVEN MODE.
 if(k_busy==0){                  //   KEY ASSIGNMENT
  if(key==2){
  transition=1;
  subroutine=7;
  s_busy=1;
  k_busy=1;
  home=0;
  run=0;
  lcd.clear();
  }

  if(key==1){
    transition=1;
    s_busy=1;
    k_busy=1;
    subroutine=10;
    prev_subroutine=6;
    lcd.clear();
    delay(200);
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("  ADJUST SETTINGS   ");
    lcd.setCursor(0, 3);
    lcd.print("VOLUME          DONE");

  }


  if(key==3){
  s_busy=1;
  k_busy=1;
  transition=1;
  lcd.clear();
  subroutine=4;
  }
 }

 if(s_busy==0){       //   MESSAGE TO DISPLAY
    if(d_lock==0){
    d_lock=1;
    s_lock=1;
    lcd.setCursor(0, 0);
    if(patient==0){
      lcd.print( "CHILD     VOL=" + String(volume) + " ml");
    }
    if(patient==1){
      lcd.print( "ADULT     VOL=" + String(volume) + " ml");
    }
    lcd.setCursor(0, 3);
    lcd.print("VOLUME   RUN   BACK");
    }   

  }

}

if(subroutine==7){                                    //   MOTOR DRIVING FOR PATIENT DRIVEN MODE.
  digitalWrite(forward_drive,0);
  digitalWrite(backward_drive,0);
  if(k_busy==0){
    if(key==3){
      transition=1;
      k_busy=1;
      s_busy=1;
      lcd.clear();
      subroutine = 6;
    }
  }

    while(home==0){                                   //   HOMING.
  
     count_k++;
     if(count_k==2){
     digitalWrite(backward_drive,1);
     }
     if(count_k==30){
     digitalWrite(backward_drive,0);
     }
     if(count_k > 50){
     count_k=0;
     }


     A=!digitalRead(16);
     B=!digitalRead(17);

     if(A==1 and B==1){
     P=1;
     }else{
     P=0;
     }

     if(P==1 and home==0){
     digitalWrite(backward_drive,0);
     digitalWrite(forward_drive,1);
     delay(40);
     digitalWrite(forward_drive,0);
     delay(p_time);
     home=1;
     }
    }


  if(digitalRead(breath_pulse)==0){

      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(" AWAITING A PULSE... ");
      lcd.setCursor(0, 3);
      lcd.print("                BACK");
  }

  if(digitalRead(breath_pulse)==1){
    run=1;
     count_k=1;
     step_count=0;
    if(s_lock==0){
      if(d_lock==0){
      s_lock=0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  RESUSCITATING...");
      lcd.setCursor(0, 1);
      lcd.print("SP02: "+ String(spo2)+ "%");
      lcd.setCursor(0, 0);
      lcd.print("Heartrate: "+ String(hr)+ "bpm");
      }
    }
      }

    while(run==1){                                         //   PRESSING BVM.
      hr = pox.getHeartRate();
      spo2 = pox.getSpO2();
     
     count_k++;
     if(count_k==2){
     digitalWrite(forward_drive,1);
     }
     if(count_k==12){
     digitalWrite(forward_drive,0);
     }
     if(count_k > 15){
     count_k=0;
     }
     
  

     if(analogRead(A2)>800 and s_lock==0){
     step_count++;
     s_lock=1;
     }
     if(analogRead(A2)<200 and s_lock==1){
     s_lock=0;
     }     

     if(step_count > step_limit){
     digitalWrite(forward_drive,0);
     count_k=0;
     home=0;
     run=0;
     }

    
    }

}

if(subroutine==8){                                    //   START WINDOW FOR FOR SELF DRIVEN MODE.
 if(k_busy==0){                  //   KEY ASSIGNMENT
  if(key==1){
    transition=1;
    s_busy=1;
    k_busy=1;
    subroutine=10;
    prev_subroutine=8;
    lcd.clear();
    delay(200);
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("  ADJUST SETTINGS   ");
    lcd.setCursor(0, 3);
    lcd.print("VOLUME  RATE    DONE");
  }
  if(key==2){
  transition=1;
  subroutine=9;
  s_busy=1;
  k_busy=1;
  lcd.clear();
  }

  if(key==3){
  s_busy=1;
  k_busy=1;
  transition=1;
  lcd.clear();
  subroutine=5;
  }
 }
 if(s_busy==0){       //   MESSAGE TO DISPLAY
    if(d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("RATE: " + String(rate) + "ppm");   
    lcd.setCursor(0, 1);
    lcd.print("VOL : " + String(volume)+ "ml"); 
    lcd.setCursor(0, 3);
    lcd.print("CHANGE  RUN    BACK");
    }

  }
}

if(subroutine==9){                                    //   MOTOR DRIVING FOR SELF DRIVEN MODE.
  digitalWrite(forward_drive,0);
  digitalWrite(backward_drive,0);

  while(home==0){                                   //   HOMING.
     count_k++;
     if(count_k==2){
     digitalWrite(backward_drive,1);
     }
     if(count_k==8){
     digitalWrite(backward_drive,0);
     }
     if(count_k > 15){
     count_k=0;
     }


     A=!digitalRead(16);
     B=!digitalRead(17);

     if(A==1 and B==1){
     P=1;
     t2 = millis();
     s_busy=0;
     d_lock=0;
     }else{
     P=0;
     }

     if(P==1 and home==0){
      d_lock=0;
     start_time = millis();
     digitalWrite(backward_drive,0);
     digitalWrite(forward_drive,1);
     delay(40);
     digitalWrite(forward_drive,0);
     delay(p_time);
     run=1;
     home=1;
     s_lock=0;
     count_k=1;
     step_count=0;
     }
    }

    
    while(run==1){                                         //   PRESSING BVM.

     
     count_k++;
     if(count_k==2){
     digitalWrite(forward_drive,1);
     }
     if(count_k==8){
     digitalWrite(forward_drive,0);
     }
     if(count_k > 15){
     count_k=0;
     }
     
  

     if(analogRead(A2)>800 and s_lock==0){
     step_count++;
     s_lock=1;
     }
     if(analogRead(A2)<200 and s_lock==1){
     s_lock=0;
     }     

     if(step_count > step_limit){
     end_time = millis();
      t1= millis();
     digitalWrite(forward_drive,0);
     count_k=0;
     home=0;
     run=0;
     s_busy=0;
     d_lock=0;
     }



    if(analogRead(A5)>0 and lock_1==0){
      lock_1=1;
      keys();
      }

      if(analogRead(A5)==0 and lock_1==1){
      lock_1=0;  
      d_lock=0;
      } 
  }

// terminate resuscitation
if(k_busy==0){
      s_busy=1;
      k_busy=1;
      if(key==2){
      terminate=1;
      transition=1;
      lcd.clear();
    } 
}
  
  if(s_busy==0){
     if(d_lock==0){
    d_lock=1;
      lcd.setCursor(0, 0);
      lcd.print("backward: " + String(t2 - end_time) + "ms");
      lcd.setCursor(0, 1);
      lcd.print("forward: " + String(end_time - start_time) + "ms");
      lcd.setCursor(0, 3);
      lcd.print("        STOP        ");      
     }
  }
}

  //confirm terminating
if(terminate==1){ 
    if(k_busy==0){
      if(key==3){                                       
        s_busy=1;
        k_busy=1;
        transition=1;
        lcd.clear();
        forward=0;
        backward=0;
        subroutine=8;
        terminate=0;
      }
      if(key==1){
        s_busy=1;
        k_busy=1;
        transition=1;
        lcd.clear();
        terminate=0;
      } 

    }
    if(s_busy==0){
      if(d_lock==0){
        d_lock=1;
        s_busy=1;
        lcd.setCursor(0, 1);
        lcd.print("    CONFIRM STOP    ");
        lcd.setCursor(0, 3);
        lcd.print("NO               YES");
      }
    }
}

if(subroutine==10){
  if(k_busy==0){
    if(key==1){
      k_busy=1;
      subroutine = 11;
      transition=1;
      lcd.clear();
    }
    if(key==2 and prev_subroutine==8){
      k_busy=1;
      s_busy=1;
      subroutine= 12;
      transition=1;
      lcd.clear();
      lcd.setCursor(0, 0);
    }
    if(key==3){
      s_busy=1;
      k_busy=1;
      transition=1;
      lcd.clear();
      subroutine=prev_subroutine;
    }
  }
}
if(subroutine== 11){
  if(k_busy==0){
    if(key==2){
      list_position++;
      value=0;
      d_lock=0;
      s_lock=0;
    }
    if(list_position==3){
      list_position=0;
    }
    if(key==1){
      value++;
      d_lock=0;
      s_lock=0;
    }
    if(value==10){
      value=0;
    }
    int new_vol = 0;
    for(int i=0; i<3; i++){
      if(list_position== i){
        vol_display[i]= value;
      }
      new_vol = 10*new_vol+vol_display[i];
    }
    volume = new_vol;
    if(key==3){
      k_busy=1;
      s_busy=1;
      transition=1;
      lcd.clear();
      subroutine=prev_subroutine;

    }


  }
  if(s_busy==0){
    if(d_lock==0){
      d_lock=1;
      s_lock=1;
      lcd.setCursor(0, 0);
      lcd.print("       VOLUME :" + String(volume));
      for(int i=0; i< 3; i++){
        lcd.setCursor(i+8,1);
        lcd.print(vol_display[i]);
      }
      lcd.setCursor(0, 3);
      lcd.print("V^     -->      DONE");
      }

  }

}


if(subroutine== 12){
  if(k_busy==0){
    if(key==2){
      list_position++;
      value=0;
      d_lock=0;
      s_lock=0;
    }
    if(list_position==2){
      list_position=0;
    }
    if(key==1){
      value++;
      d_lock=0;
      s_lock=0;
    }
    if(value==10){
      value=0;
    }
    int new_rate=0;
    for(int i=0; i<2; i++){
      if(list_position== i){
        rate_display[i]= value;
      }
      new_rate = 10*new_rate + rate_display[i];
    }
    rate = new_rate;


    if(key==3){
      k_busy=1;
      s_busy=1;
      transition=1;
      lcd.clear();
      subroutine=8;

    }


  }
  if(s_busy==0){
    if(d_lock==0){
      d_lock=1;
      s_lock=1;
      lcd.setCursor(0, 0);
      lcd.print("       RATE:" + String(rate) );
      for(int i=0; i< 2; i++){
        lcd.setCursor(i+9,1);
        lcd.print(rate_display[i]);
      }
      lcd.setCursor(0, 3);
      lcd.print("V^     -->      DONE");
      }

  }

}


//test motor

if(subroutine==18){
  if(k_busy==0){
    if(key==3){
      key=1;
    }
    if(key==1){
      digitalWrite(backward_drive,1);  
      delay(500);  
      digitalWrite(backward_drive,0); 
      digitalWrite(forward_drive,1);  
      delay(500); 
      digitalWrite(forward_drive,0); 
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.clear();
    }
    if(key==2){
      k_busy=1;
      s_busy=1;
      transition=1;
      subroutine=3;
      lcd.clear();

    }
  }
  if(s_busy==0){
    if(d_lock==0){
      d_lock==1;
      lcd.setCursor(0, 1);
      lcd.print("     MOTOR TEST     ");
      lcd.setCursor(0, 3);
      lcd.print("<--     BACK     -->");
    }
  }
}

//test sensors
if(subroutine==19){

  if(k_busy==0){

  if (key==1) {
    currentTopItem++;
    if (currentTopItem > totalItems-1){
      currentTopItem = 0;
    }
    lcd.clear();
  } 

  if(key==2){
    transition=1;
    s_busy=1;
    k_busy=1;
    d_lock= 1;
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print(sensors[currentTopItem]);      
  }

  if (key==3) {
    transition=1;
    s_busy=1;
    k_busy=1;
    subroutine=3;
    lcd.clear();
  }

  }

  if(s_busy==0){
    if(d_lock==0){
      for (int i = 0; i < visibleItems; i++) {
        index = currentTopItem + i;
        if (index < totalItems) {
          if(index ==  currentTopItem){
          lcd.setCursor(0, i);
          lcd.print("--> " + sensors[index]);           
          }
          lcd.setCursor(4, i);
          lcd.print(sensors[index]);
        } else {
          lcd.setCursor(0, i);
          lcd.print("                ");  
        }
      }
      lcd.setCursor(0, 3);
      lcd.print("SCROL   ENTER   BACK");
    }
  }
}

 key = 0;    // RESETTING KEY.
} 



void keys(){                                          //   KEY GENERATOR

  if(analogRead(A5)>60 and analogRead(A5)<200){
  key=3;
  }
  if(analogRead(A5)>200 and analogRead(A5)<600){
  key=2;
  }
  if(analogRead(A5)>600 and analogRead(A5)<1024){
  key=1;
  }

}





