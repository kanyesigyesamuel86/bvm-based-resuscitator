
#include <LiquidCrystal.h>
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int buzzer=2;
int maintain_power=9;
int power_read=10;
int breath_pulse=11;
int power_led=12;
int clock_pulse=13;

int forward_drive=14;
int backward_drive=15;

//buttons on A7
//Voltage read on A2
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

void setup() {
  // put your setup code here, to run once:
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

}

void loop() {
  // put your main code here, to run repeatedly:



// key_event

  if(analogRead(A7)>0 and lock_1==0){
    lock_1=1;
    keys();
  }

  if(analogRead(A7)==0 and lock_1==1){
    lock_1=0;  
    d_lock=0;
  }


count_1++;
if(count_1==1){
    go=1;
  }
if(count_1==100){
  go=0;
  d_lock==0;
}

 if(count_1==120){
  count_1=0;
 }


//power off system
  if(digitalRead(power_read)==1 and power_off==0){
    power_off=1;
    k_busy=1;
    s_busy=1;
   lcd.clear();
  }



  if(power_off==1){  
   if(go==1 and d_lock==0){
    d_lock=1;
   lcd.setCursor(0, 0);
   lcd.print("  TURN OFF SYSTEM   ");  
   }
    if(go==0 and d_lock==1){
   lcd.setCursor(0, 0);
   lcd.print("                    ");  
   }

   lcd.setCursor(0, 3);
   lcd.print("NO               YES");
   
  

   if(key==3){
   digitalWrite(maintain_power,0);
   }

   if(key==1){
    transition=1;
    power_off=0;
   }

  }
  if(transition==1 and key==0){
    s_busy=0;
    k_busy=0;
    lcd.clear();
    transition=0;
  }

    
//subroutines section

if(subroutine==0){
if(k_busy==0){
    if(key==1){
      list_0--;
    }
    if(key==3){
      list_0++;
    }
    if(list_0==3){
      list_0=0;
    }
    if(list_0==-1){
      list_0=2;
    }
    
  if(key==2){
    lcd.clear();
    d_lock=1;
    transition=1;
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

//display menus

if(s_busy==0){
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
  if(subroutine==1){
    if(k_busy==0){
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
    k_busy=1;
    s_busy=1;
    lcd.clear();
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
  lcd.print("--> PATIENT-DRIVEN  ");
        lcd.setCursor(0, 1);
  lcd.print("    SELF-DRIVEN     "); 
  lcd.setCursor(0, 3);
  lcd.print("^v     SELECT   BACK");    
      }
      if(d_lock==0 and list_1==1){
        d_lock=1;
      lcd.setCursor(0, 0);
  lcd.print("    PATIENT-DRIVEN  ");
        lcd.setCursor(0, 1);
  lcd.print("--> SELF-DRIVEN     "); 
  lcd.setCursor(0, 3);
  lcd.print("^v     SELECT   BACK");    
      }
    }
    
  }
  if(subroutine==2){
    
  }
  if(subroutine==3){
    
  }
  if(subroutine==4){
    if(k_busy==0){
      if(key==1){
        k_busy=1;
        s_busy=1;
        transition=1;
        lcd.clear();
        subroutine=6;
        vol=100;
      }  
      if(key==3){
        k_busy=1;
        s_busy=1;
        transition=1;
        lcd.clear();
        subroutine=6;
        vol=500;
      }
      if(key==2){
        k_busy=1;
        s_busy=1;
        transition=1;
        lcd.clear();
        subroutine=1;
      }      
    }
  if(s_busy==0){
    if(d_lock==0){
      d_lock=1;
      lcd.setCursor(0, 1);
      lcd.print("   CHOOSE PATIENT   ");
      lcd.setCursor(0, 3);
      lcd.print("CHILD    BACK  ADULT");
    }
      
    }
  }

if(subroutine==6){
  if(k_busy==0){
    if(key==1){
      transition=1;
      subroutine=7;
      s_busy=1;
      k_busy=1;
      drive_enable=1;
      lcd.clear();
      d_lock=1;
      lcd.setCursor(0, 0);
      lcd.print("RESUSCITATING...    ");
      lcd.setCursor(0, 1);
      lcd.print("VOLUME: " + String(vol) + "mL");
      lcd.setCursor(0, 3);
      lcd.print("        STOP        ");
    }
  if(key==2){
    s_busy=1;
    k_busy=1;
    transition=1;
    subroutine=4;
    lcd.clear();
  }

  }
  if(s_busy==0){
    if(d_lock==0){
      d_lock=1;
      lcd.setCursor(0, 1);
      lcd.print("VOLUME: " + String(vol) + "mL");
      lcd.setCursor(0, 3);
      lcd.print("RUN    BACK   CHANGE");
    }

  }

}


if(subroutine==7){
while(drive_enable==1){

  if(analogRead(A7)>0 and lock_1==0){
    lock_1=1;
    keys();
  }

  if(analogRead(A7)==0 and lock_1==1){
    lock_1=0;  
    d_lock=0;
  }

  if(key==2){
    drive_enable=0;
    transition=1;
    digitalWrite(backward_drive,0);
    digitalWrite(forward_drive,0);
    forward=0;
    backward=0;
    subroutine=6;
  }


  if(analogRead(2)>200){
  A=1;
}else{
  A=0;
}

if(analogRead(3)>200){
  B=1;
}else{
  B=0;
}

if(A==1 and B==1){
  P=1;
}else{
  P=0;
}


if(P==0 and drive==0){
  drive=1;
  backward=1;
  forward=0;
}


if(forward==1 and backward==0){
if(A==1 and s_lock==0){
  step_count++;
  s_lock=1;
}
if(A==0 and s_lock==1){
  s_lock=0;
}
}
if(P==1 and home==0){
digitalWrite(backward_drive,0);
digitalWrite(forward_drive,1);
delay(40);
digitalWrite(forward_drive,0);
delay(1000);
run=1;
home=1;

}

if(P==1){
step_count=0;
}

if(step_count>30 and run==1){
digitalWrite(backward_drive,1);
delay(20);
digitalWrite(backward_drive,0);

  run=0;
  home=0;
  drive=0;

}

if(P==0 and home==0){
drive=1;
forward=0;
backward=1;
}



if(run==1){
drive=1;
forward=1;
backward=0;
}








if(drive==1 and power_off==0){
count_k++;

if(count_k==2){
if(forward==1){
digitalWrite(forward_drive,1);
}
if(backward==1){
digitalWrite(backward_drive,1);
}
}

if(count_k==10){
digitalWrite(forward_drive,0);
digitalWrite(backward_drive,0);
}

if(count_k > 15){
count_k=0;
}

}



}
}




//kill key
key = 0;
}


//reading keys
void keys(){

    if(analogRead(A7)>60 and analogRead(A7)<200){
      key=3;
    }
    if(analogRead(A7)>200 and analogRead(A7)<600){
      key=2;
    }
    if(analogRead(A7)>600 and analogRead(A7)<1024){
      key=1;
    }

  }
