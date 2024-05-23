#include <LiquidCrystal.h>
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; // I2C


int buzzer=2;
int maintain_power=9;
int power_read=10;
//int breath_pulse=11;
int power_led=12;
int clock_pulse=13;

int forward_drive=14;
int backward_drive=11;

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
int volume=100;
float pressure_past=0;
float pressure_present=0;
float s_value;
float p_difference=0;
float sum=0;
int i=0;
int rate=20;
int adult=0;
int motor_speed=200;
int p_trig=-8;
int key_tone=1;



const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
   lcd.begin(20, 4);
   pinMode(forward_drive,OUTPUT);
   pinMode(backward_drive,OUTPUT);   
   pinMode(buzzer,OUTPUT);
   pinMode(maintain_power,OUTPUT);  
   pinMode(power_led,OUTPUT);
  // pinMode(breath_pulse,INPUT);
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
   delay(200);   
   lcd.setCursor(0, 0);
   lcd.print("STARTING.           ");   
   delay(200);  
   lcd.setCursor(0, 0);
   lcd.print("STARTING..          ");   
   delay(200); 
   lcd.setCursor(0, 0);
   lcd.print("STARTING...         ");   
   delay(200);     
   lcd.setCursor(0, 0);
   lcd.print("STARTING            ");   
   delay(200);   
   lcd.setCursor(0, 0);
   lcd.print("STARTING.           ");   
   delay(200);  
   lcd.setCursor(0, 0);
   lcd.print("STARTING..          ");   
   delay(200); 
   lcd.setCursor(0, 0);
   lcd.print("STARTING...         ");   
   delay(200);   
   lcd.clear();  
   delay(200);  

 if (!bmp.begin(0x76)) {
     lcd.setCursor(0, 2);
     lcd.print("  sensors FAILED  ");  
while (1);
}

     lcd.setCursor(0, 0);
     lcd.print("  sensors  DETECTED  ");  
 delay(1000);
}

void loop() {
// key_event

if(analogRead(A1) > 50 and lock_1==0){
lock_1=1;
keys();
}
if(analogRead(A1)==0 and lock_1==1){
lock_1=0;  
d_lock=0;
}

if(digitalRead(power_read)==1 and power_off==0){      //   POWER OFF INITIALISER.
  digitalWrite(buzzer,1);
  delay(50);
  digitalWrite(buzzer,0);
  power_off=1;
  k_busy=1;
  s_busy=1;
  d_lock=0;
  lcd.clear();
}
if(power_off==1){                                     //   POWER OFF MENU.

  if(d_lock==0){
  d_lock=1;
  lcd.setCursor(0, 0);
  lcd.print("  TURN OFF SYSTEM   ");  
  lcd.setCursor(0, 3);
  lcd.print("NO               YES");
  }

  if(key==3){
  digitalWrite(maintain_power,0);
  }

  if(key==1){
  transition=1;
  power_off=0;
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






if(subroutine==0){                                    //   HOME SCREEN  OKAY
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    SELECT MODE     ");  
    lcd.setCursor(0, 3);
    lcd.print("<--     ENTER    -->"); 
    }
    if(list_0==1 and d_lock==0){
    d_lock=1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      SETTINGS      "); 
    lcd.setCursor(0, 3);
    lcd.print("<--     ENTER    -->"); 
    }

    if(list_0==2 and d_lock==0){
    d_lock=1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    ABOUT SYSTEM    "); 
    lcd.setCursor(0, 3);
    lcd.print("<--     ENTER    -->"); 
    }
  }
}


if(subroutine==1){                                    //   OPERATION MODE OPTIONS OKAY
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
    lcd.print("--> SELF_DRIVEN     "); 
    lcd.setCursor(0, 1);
    lcd.print("    PATIENT_DRIVEN  ");
    lcd.setCursor(0, 3);
    lcd.print(" ^     SELECT   BACK");    
    }
    if(d_lock==0 and list_1==1){
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("    SELF_DRIVEN     "); 
    lcd.setCursor(0, 1);
    lcd.print("--> PATIENT_DRIVEN  ");

    lcd.setCursor(0, 3);
    lcd.print(" ^     SELECT   BACK");    
    }
  } 
}


if(subroutine==2){                                    //   SETTINGS   OKAY
  if(s_busy==0){       //   MESSAGE TO DISPLAY

    if(list_2==0){
      lcd.setCursor(0, 0);
      lcd.print("--> MOTOR SPEED     ");
      lcd.setCursor(0, 1);
      lcd.print("    PRESSURE TRIGGER");
      lcd.setCursor(0, 2);
      lcd.print("    KEY TONE_ ON/OFF");
    }
    if(list_2==1){
      lcd.setCursor(0, 0);
      lcd.print("    MOTOR SPEED     ");
      lcd.setCursor(0, 1);
      lcd.print("--> PRESSURE TRIGGER");
      lcd.setCursor(0, 2);
      lcd.print("    KEY TONE_ ON/OFF"); 
    }
    if(list_2==2){
      lcd.setCursor(0, 0);
      lcd.print("    MOTOR SPEED     ");
      lcd.setCursor(0, 1);
      lcd.print("    PRESSURE TRIGGER");
      lcd.setCursor(0, 2);
      lcd.print("--> KEY TONE_ ON/OFF");
    }


 if(k_busy==0){       //   KEY ASSIGNMENT

   if(key==1){
    list_2++;
   }
 
   if(key==3){
    d_lock=1;
    transition=1;
    subroutine=0;
    lcd.clear();
    k_busy=1;
    s_lock=1;   
   }

   if(list_2==3){
    list_2=0;
   }

   if(list_2==-1){
    list_2=1;
   }
    if(key==2){
    d_lock=1;
    transition=1;
    lcd.clear();
    k_busy=1;
    s_lock=1;
    if(list_2==0){
    subroutine=14;
    }
    if(list_2==1){
    subroutine=15;
    }
    if(list_2==2){
    subroutine=16;
    }
   }
 
   }

   if(d_lock==0){
    d_lock=1; 
    lcd.setCursor(0, 3);
    lcd.print(" ^     SELECT  BACK");
   }      
 }

}

if(subroutine==3){                                    //  SYSTEM INFO  OKAY
  if(k_busy==0){       //   KEY ASSIGNMENT
    if(key==1){
      list_3--;
    }
    if(key==2){
      list_3++;
    }

    if(key==3){
     d_lock=1;
    transition=1;
    subroutine=0;
    lcd.clear();
    k_busy=1;
    s_lock=1;     
    }

  }

  if(list_3 < 0){
    list_3=3;
  }
  if(list_3>3){
    list_3=0;
  }


  if(s_busy==0){       //   KEY ASSIGNMENT
    if(list_3==0){
    lcd.setCursor(0, 0);
    lcd.print("MICROCONTROLLER    ");  
    lcd.setCursor(0, 1);
    lcd.print(" - ATMEGA328P      ");  
    lcd.setCursor(0, 2);
    lcd.print(" - CLOCKED AT 20MHz");   
    }

    if(list_3==1){
    lcd.setCursor(0, 0);
    lcd.print("OPERATING SYSTEM    ");  
    lcd.setCursor(0, 1);
    lcd.print(" - KAMU 1.03        ");  
    lcd.setCursor(0, 2);
    lcd.print(" - 24192 Bytes      ");   
    }

    if(list_3==2){
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM SENSORS      ");  
    lcd.setCursor(0, 1);
    lcd.print(" - OXIMATOR         ");  
    lcd.setCursor(0, 2);
    lcd.print(" - bmp280           ");   
    }

    if(list_3==3){
    lcd.setCursor(0, 0);
    lcd.print("DESIGNED BY,        ");  
    lcd.setCursor(0, 1);
    lcd.print(" - KANYESIGYE SAMUEL");  
    lcd.setCursor(0, 2);
    lcd.print(" - MUTUMBA WILLIAM  ");   
    }

    lcd.setCursor(0, 3);
    lcd.print(" <       >      BACK");  
  }
}

if(subroutine==4){                                    //   SELF DRIVEN;  SELECTING PATIENT  OKAY
 if(k_busy==0){       //   KEY ASSIGNMENT
            
  if(key==1){        
   k_busy=1;      
   s_busy=1;                  
   transition=1;
   lcd.clear();
   subroutine=6;
   volume=150;
   rate=25;
   adult=0;             
  }  

  if(key==2){
   k_busy=1;
   s_busy=1;
   transition=1;
   lcd.clear();
   subroutine=6;
   volume=400;
   rate=15;
   adult=1;
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


if(subroutine==5){                                    //   START WINDOW FOR FOR PATEINT DRIVEN MODE.
 if(k_busy==0){       //   KEY ASSIGNMENT
            
  if(key==1){        
   k_busy=1;      
   s_busy=1;                  
   transition=1;
   lcd.clear();
   subroutine=11;
   volume=150;
   rate=40;
   adult=0;
   p_time=500;              
  }  

  if(key==2){
   k_busy=1;
   s_busy=1;
   transition=1;
   lcd.clear();
   subroutine=11;
   volume=350;
   rate=25;
   adult=1;
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



if(subroutine==6){                                    // SELF DRIVEN; START WINDOW OKAY
 if(k_busy==0){                                       //   KEY ASSIGNMENT

  if(key==1){
    transition=1;
    subroutine=8;
    k_busy=1;
    s_busy=1;
    lcd.clear();
    delay(200);
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("  ADJUST SETTINGS   ");
    lcd.setCursor(0, 3);
    lcd.print("VOLUME  RATE    BACK");
  }

  if(key==2){
   transition=1;
   subroutine=7;
   step_limit = (volume+134.26)/21.2465;
    p_time = 1000*(60/rate - 0.0656*step_limit- 0.5);
   s_busy=1;
   k_busy=1;
   home=0;
   run=0;
   lcd.clear();
   delay(200);
   d_lock=1;
   if(adult==1){
    lcd.setCursor(0, 0);
    lcd.print("RESUSCITATING_ ADULT");
   }
   if(adult==0){
    lcd.setCursor(0, 0);
    lcd.print("RESUSCITATING_ CHILD");
   }
   lcd.setCursor(0, 1);
   lcd.print("VOL:   mL RATE:  bpm");
      lcd.setCursor(4, 1);
   lcd.print(volume);
   lcd.setCursor(15, 1);
   lcd.print(rate);
   lcd.setCursor(0, 3);
   lcd.print("        STOP        ");
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
    if(adult==1){
    lcd.setCursor(0, 0);
    lcd.print("ADULT.  VOL : ");
    lcd.setCursor(15, 0);
    lcd.print(volume);
    lcd.setCursor(18, 0);
    lcd.print("ml");
    lcd.setCursor(0, 1);
    lcd.print("        RATE: "); 
    lcd.setCursor(15, 1);
    lcd.print(rate); 
    lcd.setCursor(17, 1);
    lcd.print("bpm"); 
    }
    if(adult==0){
    lcd.setCursor(0, 0);
    lcd.print("CHILD.  VOL : ");
    lcd.setCursor(15, 0);
    lcd.print(volume);
    lcd.setCursor(18, 0);
    lcd.print("ml");
    lcd.setCursor(0, 1);
    lcd.print("        RATE: "); 
    lcd.setCursor(15, 1);
    lcd.print(rate); 
    lcd.setCursor(17, 1);
    lcd.print("bpm"); 
    }    
    lcd.setCursor(0, 3);
    lcd.print("ADJUST   RUN    BACK");
    }

  }
}

if(subroutine==7){                                    //   SELF DRIVEN MODE; RESUSCITATING. OKAY 

    while(home==0){                                   //   HOMING.
  
     count_k++;
     if(count_k==2){
     digitalWrite(backward_drive,1);
     }
     if(count_k==motor_speed){
     digitalWrite(backward_drive,0);
     }
     if(count_k > 300){
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
     run=1;
     s_lock=0;
     count_k=1;
     step_count=0;
     }
    }


  key=0;
  if(analogRead(A1)>50 and lock_1==0){
  lock_1=1;
  keys();
  }

  if(analogRead(A1)==0 and lock_1==1){
  lock_1=0;  
  d_lock=0;
  }

    if(key==2){                                       //   LOOP TERMINATOR.

      s_busy=1;
      k_busy=1;
      run=0;
      transition=1;
      lcd.clear();
      subroutine=6;
    } 

    while(run==1){                                         //   PRESSING BVM.

     count_k++;
     if(count_k==2){
     digitalWrite(forward_drive,1);
     }
     if(count_k==motor_speed){
     digitalWrite(forward_drive,0);
     }
     if(count_k > 300){
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
     delay(500);
     }

    
    }
}

if(subroutine==8){                                   //    SELF DRIVEN MODE; SELECT PARAMETERS TO CHANGE OKAY
 if(k_busy==0){                                       //   KEY ASSIGNMENT

  if(key==1){
   transition=1;
   subroutine=9;
   s_busy=1;
   k_busy=1; 
   lcd.clear(); 
  }

  if(key==2){
   transition=1;
   subroutine=10;
   s_busy=1;
   k_busy=1;   
   lcd.clear();
  }

  if(key==3){
   transition=1;
   subroutine=6;
   s_busy=1;
   k_busy=1;

  }
 }
}

if(subroutine==9){                                    //   SELF DRIVEN MODE;   VOLUME CHANGE OKAY
 if(k_busy==0){ 
  if(key==1){
    s_busy=0;
    d_lock=0;
    lcd.clear();
   volume=volume-10;
  }
  if(key==2){
   volume= volume+10;
    s_busy=0;
    d_lock=0;
    lcd.clear();
  }
  if(key==3){
   transition=1;
   subroutine=6;
   s_busy=1;
   k_busy=1; 
  }

 }

 if(adult==1 and volume > 600){
 volume=600;
 }
 if(adult==1 and volume < 300){
 volume=300;
 }

 if(adult==0 and volume > 400){
 volume=400;
 }
 if(adult==0 and volume < 100){
 volume=100;
 }

 if(s_busy==0){ 
  if(d_lock==0){
    d_lock=1; 
    s_busy=1;
    lcd.setCursor(0, 0);
    lcd.print("Volume =    ml");
    lcd.setCursor(9, 0);
    lcd.print(volume);
    lcd.setCursor(0, 3);
    lcd.print("  -      +      DONE");
  }
 }
  
}

if(subroutine==10){                                   //   SELF DRIVEN MODE;  RATE CHANGE OKAY
 if(k_busy==0){ 
  if(key==1){
   rate--;
  }
  if(key==2){
   rate++;
  }
  if(key==3){
   transition=1;
   subroutine=6;
   s_busy=1;
   k_busy=1; 
  }

 }

 if(adult==1 and rate > 30){
 rate=30;
 }
 if(adult==1 and rate < 8){
 rate=8;
 }
 if(adult==0 and rate > 45){
 rate=45;
 }
 if(adult==0 and rate < 15){
 rate=15;
 }

 if(s_busy==0){ 
  if(d_lock==0){
    d_lock=1; 
    lcd.setCursor(0, 0);
    lcd.print("Rate =    bpm");
    lcd.setCursor(7, 0);
    lcd.print(rate);
    lcd.setCursor(0, 3);
    lcd.print("  -      +      DONE");
  } 
 }


}


if(subroutine==11){                                   //  PATIENT DRIVEN MODE; START WINDOW  OKAY
 if(k_busy==0){                                       //   KEY ASSIGNMENT

  if(key==1){
    transition=1;
    subroutine=13;
    k_busy=1;
    s_busy=1;
    lcd.clear();
    delay(200);
    d_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("VOLUME = " + String(volume) + "ml");
    lcd.setCursor(0, 3);
    lcd.print("  -      +      DONE");
  }

  if(key==2){
  transition=1;
  subroutine=12;
  step_limit = (volume+134.26)/21.2465;
  s_busy=1;
  k_busy=1;
  home=0;
  run=0;
  lcd.clear();
  delay(200);
  d_lock=1;
  if(adult==1){
  lcd.setCursor(0, 0);
  lcd.print("RESUSCITATING_ ADULT");
  }
  if(adult==0){
  lcd.setCursor(0, 0);
  lcd.print("RESUSCITATING_ CHILD");
  }
  lcd.setCursor(0, 1);
  lcd.print("VOLUME: " + String(volume) + "mL");
  lcd.setCursor(0, 3);
  lcd.print("        STOP        ");
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

    if(adult==1){
    lcd.setCursor(0, 0);
    lcd.print("ADULT.              ");
    lcd.setCursor(0, 1);
    lcd.print("         VOL : " ); 
    lcd.setCursor(14, 1);
    lcd.print(volume); 

    }
    if(adult==0){
    lcd.setCursor(0, 0);
    lcd.print("CHILD.              ");
    lcd.setCursor(0, 1);
     lcd.setCursor(0, 1);
    lcd.print("         VOL : " ); 
    lcd.setCursor(14, 1);
    lcd.print(volume); 
    } 
    lcd.setCursor(0, 3);
    lcd.print("ADJUST   RUN    BACK");
    }
 

  }
}
if(subroutine==12){                                    //   PATIENT-DRIVEN MODE; RESUSCITATING

    while(home==0){                                   //   HOMING.
  
     count_k++;
     if(count_k==2){
     digitalWrite(backward_drive,1);
     }
     if(count_k==motor_speed){
     digitalWrite(backward_drive,0);
     }
     if(count_k > 300){
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
     s_lock=0;
     count_k=1;
     step_count=0;
     }
    }


   pressure_present = bmp.readPressure();
   p_difference = pressure_present - pressure_past;
   lcd.setCursor(0, 2);
   lcd.print("Pressure = " + String(pressure_present) );  

   if( p_difference < p_trig){
   run=1;
   }
   delay(1);
   pressure_past = pressure_present;
   delay(1);

   key=0;
   if(analogRead(A1)>50 and lock_1==0){
   lock_1=1;
   keys();
   }

   if(analogRead(A1)==0 and lock_1==1){
   lock_1=0;  
   d_lock=0;
   }

    if(key==2){                                       //   LOOP TERMINATOR.
     s_busy=1;
     k_busy=1;
     run=0;
     transition=1;
     subroutine=11;
     lcd.clear();
    } 

    while(run==1){                                         //   PRESSING BVM.

     count_k++;
     if(count_k==2){
     digitalWrite(forward_drive,1);
     }
     if(count_k==motor_speed){
     digitalWrite(forward_drive,0);
     }
     if(count_k > 300){
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
     delay(500);
     }

    } 

} 

if(subroutine==13){                                    //  PATIENT-DRIVEN MODE;   VOLUME CHANGE
 if(k_busy==0){ 
  if(key==1){
   volume= volume-10;
   lcd.clear();
  }
  if(key==2){
   volume= volume+10;
   lcd.clear();
  }
  if(key==3){
   transition=1;
   subroutine=11;
   s_busy=1;
   k_busy=1; 
   lcd.clear();
  }

 }

 if(adult==1 and volume > 600){
 volume=600;
 }
 if(adult==1 and volume < 300){
 volume=300;
 }

 if(adult==0 and volume > 400){
 volume=400;
 }
 if(adult==0 and volume < 100){
 volume=100;
 }

 if(s_busy==0){ 
  if(d_lock==0){
    d_lock=1;  
    lcd.setCursor(0, 3);
    lcd.print("  -      +      DONE");
  }
    lcd.setCursor(0, 0);
    lcd.print("VOLUME = " ); 
    lcd.setCursor(9, 0);
    lcd.print(volume); 

 }

}

if(subroutine==14){                                    //     SPEED CHANGE
 if(k_busy==0){ 
  if(key==1){
   motor_speed--;
   lcd.clear();
  }
  if(key==2){
   motor_speed++;
   lcd.clear();
  }
  if(key==3){
       lcd.clear();
   transition=1;
   subroutine=2;
   s_busy=1;
   k_busy=1; 
  }

 }

 if(motor_speed > 250){
 motor_speed=250;
 }
 if(motor_speed < 50){
 motor_speed=50;
 }
    lcd.setCursor(0, 0);
    lcd.print("MOTOR SPEED = " ); 
    lcd.setCursor(14, 0);
    lcd.print(motor_speed); 

 if(s_busy==0){ 
  if(d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 3);
    lcd.print("  -      +      DONE");
  }  
 }

}

if(subroutine==15){                                    //     PRESSURE TRIGGER CHANGE
 if(k_busy==0){ 
  if(key==1){
   p_trig++;
      lcd.clear();
  }
  if(key==2){
   p_trig--;
      lcd.clear();
  }
  if(key==3){
   lcd.clear();
   transition=1;
   subroutine=2;
   s_busy=1;
   k_busy=1; 
  }

 }

 if(p_trig > 0){
 p_trig=0;
 }
 if(p_trig < -20){
 p_trig=-20;
 }


 if(s_busy==0){ 
  if(d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 3);
    lcd.print("  -      +      DONE");
  }
    lcd.setCursor(0, 0);
    lcd.print("PRESSURE TRIG = " ); 
    lcd.setCursor(16, 0);
    lcd.print(p_trig);  

 }

}


if(subroutine==16){                                    //     KEY TONE  SETTING      (OK)
 if(k_busy==0){ 
  if(key==1){
   key_tone=0;
  }
  if(key==2){
   key_tone=1;
  }
  if(key==3){
   lcd.clear();
   transition=1;
   subroutine=2;
   s_busy=1;
   k_busy=1; 
  }

 }

  if(s_busy==0){ 
  if(d_lock==0){
    d_lock=1;
    lcd.setCursor(0, 3);
    lcd.print("  OFF    ON     DONE");
   }

    if(key_tone==0){
    lcd.setCursor(0, 0);
    lcd.print("TURN KEY TONE -> OFF"); 
    }

    if(key_tone==1){
    lcd.setCursor(0, 0);
    lcd.print("TURN KEY TONE -> ON "); 
    } 
  }
 
}







key =0;  
}




void keys(){                                          //   KEY GENERATOR

  if(analogRead(A1)>60 and analogRead(A1)<200){
  key=3;
  }
  if(analogRead(A1)>200 and analogRead(A1)<600){
  key=2;
  }
  if(analogRead(A1)>600 and analogRead(A1)<1024){
  key=1;
  }

  if(key_tone==1){
  digitalWrite(buzzer,1);
  delay(50);
  digitalWrite(buzzer,0);
  }

}


