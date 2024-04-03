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

int key=0;
int lock1=0;
int count1=0;
int menu=1;
int d_lock=0;
int enter=0;
int go=0;
int menu_lock=0;
int power_off=0;
int sc=0;
int test_motor=0;
int list_display = 0;
int list_counter = 0;
int submenu_lock = 0;
int test_sensors = 0;
int blinker = 0;
int count2=0;
int show_modes = 0;
int patient_driven = 0;
int self_driven = 0;
int counter =0;
int dots=0;
int resuscitating_trigger=0;
int resuscitate=0;
int stop_screen=0;
int breathrate=20;
int spo2 = 0;
int resuscitate1=0;

void setup() {
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

// key_event

    if(analogRead(A7)>0 and lock1==0){
      lock1=1;
      keys();
    }

    if(analogRead(A7)==0 and lock1==1){
      lock1=0;  
    }
    

  count1++;
  if(count1==1){
    go=1;
  }
if(count1==100){
  go=0;
}

 if(count1==120){
  count1=0;
 }

count2++;
if (count2 >= 0 && count2 < 30) {
  blinker = 1;
} 
if (count2 >= 30 && count2 < 60) {
  blinker = 0;
}

if (count2 == 60) {
  count2 = 0;
}


  counter++;
  if(counter >=0 and counter < 40){
  dots=0;
  }
  if(counter >= 40 and counter < 80){
  dots=1;
  }

  if(counter >= 80 and counter < 120){
  dots=2;
  }
  if(counter >= 120 and counter < 160){
  dots=3;
  }

  if(counter==160){
    resuscitating_trigger++;
    counter=0;
    }
  
  if(resuscitating_trigger==10){
    resuscitating_trigger=0;
  }
  if( resuscitating_trigger <= 5){
    resuscitate=1;
  }
  if( resuscitating_trigger > 5){
    resuscitate=0;
  }
  



  if(digitalRead(power_read)==1 and power_off==0){
    power_off=1;
    menu_lock==1;
    submenu_lock=1;
    
   lcd.clear();
  }



  if(power_off==1){  
   if(go==1){
   lcd.setCursor(0, 0);
   lcd.print("  TURN OFF SYSTEM   ");  
   }
      if(go==0){
   lcd.setCursor(0, 0);
   lcd.print("                    ");  
   }

   lcd.setCursor(0, 3);
   lcd.print("NO               YES");
   
  

   if(key==3){
   digitalWrite(maintain_power,0);
   }

   if(key==1){
    menu_lock=0;
    power_off=0;
   }

  }




  if(key==1 and enter==0){
    menu--;
    d_lock=0;
    lcd.clear();
  }
  if(key==3 and enter==0){
    menu++;
    d_lock=0;
    lcd.clear();
  }

if(menu==4){
  menu=1;
}

if(menu==0){
  menu=3;
}


if(menu==1 and menu_lock==0){
if(d_lock==0){
  d_lock=1;
  lcd.setCursor(0, 0);
  lcd.print("    SELECT MODE     ");  
  lcd.setCursor(0, 3);
  lcd.print("<--     ENTER    -->"); 
  }

if(key==2){
    show_modes = 1;
    d_lock=0;
    enter=1;
    menu_lock=1;
    submenu_lock=0;
    delay(200);
    key=0;
  lcd.clear();
}

}
if(show_modes==1 and submenu_lock==0){
  if(list_counter==0){
  lcd.setCursor(0, 0);
  lcd.print("    SELECT MODE    ");  
  lcd.setCursor(0, 1);
  lcd.print("[*] PATIENT-DRIVEN ");
  lcd.setCursor(0, 2);
  lcd.print("[ ] SELF-DRIVEN    ");
  lcd.setCursor(0, 3);
  lcd.print("SELECT   BACK    OK");
  }

  if(list_counter==1){
  lcd.setCursor(0, 0);
  lcd.print("    SELECT MODE    ");  
  lcd.setCursor(0, 1);
  lcd.print("[ ] PATIENT-DRIVEN ");
  lcd.setCursor(0, 2);
  lcd.print("[*] SELF-DRIVEN    ");
  lcd.setCursor(0, 3);
  lcd.print("SELECT   BACK    OK");
  } 

  if(key==1){
    select();
  }

  if(key==2){
  d_lock=0;
  show_modes=0;
  submenu_lock=1;
  menu_lock=0;
  enter=0;
  delay(200);
  lcd.clear();
  menu=1;
  key=0;

}
  


  if(key==3 and list_counter==0){
  patient_driven=1;
  d_lock=0;
  enter=1;
  menu_lock=1;
  delay(200);
  key=0;
  lcd.clear();
  }
  if(key==3 and list_counter==1){
    self_driven=1;
    d_lock=0;
  enter=1;
  menu_lock=1;
  delay(200);
  key=0;
  lcd.clear();
  }
}

if(patient_driven==1){
  if(d_lock==0){
    submenu_lock=1;

    lcd.setCursor(0,0);
    lcd.print("   PATIENT DRIVEN   ");
    if(digitalRead(breath_pulse)==0 and resuscitate==0){
    lcd.setCursor(0,1);
    lcd.print("Waiting for a pulse ");
    if(dots ==0){
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    }
    if(dots ==1){
    lcd.setCursor(0, 2);
    lcd.print(".                   ");
    }
    if(dots==2){
    lcd.setCursor(0, 2);
    lcd.print("..                  ");
    }
    if(dots==3){
    lcd.setCursor(0, 2);
    lcd.print("...                 ");
    }
    lcd.setCursor(0, 3);
    lcd.print("        BACK        ");

    if(key==2){
    patient_driven=0;
    submenu_lock=0;
    menu=1;
    key=0;
    delay(200);
    lcd.clear();
  }
    }
    if(digitalRead(breath_pulse)==1 or resuscitate==1){
    if(dots ==0){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating ");
    }
    if(dots ==1){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating.      ");
    }
    if(dots==2){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating..     ");
    }
    if(dots==3){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating...    ");
    }
    lcd.setCursor(0, 2);
    lcd.print("Rate(ppm):          ");
    lcd.setCursor(0, 3);
    lcd.print("        STOP        ");

    if(key==2){
      stop_screen=1;
      key=0;
      lcd.clear();
      
  }
}
  }


}
if(stop_screen==1){
  if(d_lock==0){
    d_lock=1;
      lcd.setCursor(0, 1);
      lcd.print("Stop Resuscitating? ");
      lcd.setCursor(0, 3);
      lcd.print("NO               YES");
  }
  if(key==3){
    patient_driven=0;
    self_driven=0;
    resuscitate1=0;
    submenu_lock=0;
    menu=1;
    d_lock=0;
    stop_screen=0;
    key=0;
    delay(200);
    lcd.clear();
  }
  if(key==1 and patient_driven==1){
    submenu_lock=1;
    self_driven=0;
    stop_screen=0;
    menu=1;
    d_lock=0;
    key=0;
    lcd.clear();
  }

  if(key==1 and resuscitate1==1){
    submenu_lock=1;
    patient_driven=0;
    stop_screen=0;
    menu=1;
    d_lock=0;
    key=0;
    lcd.clear();
  }
}


if(self_driven==1){
  if(d_lock==0){
    submenu_lock=1;
    lcd.setCursor(0, 0);
    lcd.print("     SELF DRIVEN    ");
    lcd.setCursor(0, 1);
    lcd.print("  Set Breath rate:  ");
    lcd.setCursor(0, 2);
    lcd.print("        " + String(breathrate) + " ppm"     );
    lcd.setCursor(0, 3);
    lcd.print("CHANGE   BACK     OK");
    d_lock=1;
  }

  if(key==1){
    d_lock=0;
    breathrate++;
    key=0;
    delay(200);
    lcd.clear();
  }
  if(breathrate==60){
    breathrate=20;
  }
if(key==2){
  d_lock=1;
  self_driven=0;
  submenu_lock=0;
  menu=1;
  key=0;
  lcd.clear();
}

  if(key==3){
    d_lock=0;
    resuscitate1=1;
    self_driven=0;
    key=0;
    lcd.clear();
}
}
if(resuscitate1==1){
    submenu_lock=1;
   if(d_lock==0){
    lcd.setCursor(0,0);
    lcd.print("     SELF DRIVEN    ");
    if(dots ==0){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating       ");
    }
    if(dots ==1){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating.      ");
    }
    if(dots==2){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating..     ");
    }
    if(dots==3){
    lcd.setCursor(0,1);
    lcd.print("Resuscitating...    ");
    }
    lcd.setCursor(0, 2);
    lcd.print("Rate:" + String(breathrate) +"ppm; "+ "spo2:"+ spo2 + "%");
    lcd.setCursor(0, 3);
    lcd.print("        STOP        ");

  }

    if(key==2){
    stop_screen=1;
    key=0;
    lcd.clear(); 
  }
}




if(menu==2 and menu_lock==0){
if(d_lock==0){
  d_lock=1;
  lcd.setCursor(0, 0);
  lcd.print("      SETTINGS      ");  
  lcd.setCursor(0, 3);
  lcd.print("<--     ENTER    -->"); 
  }

}

if(menu==3 and menu_lock==0){
if(d_lock==0){
  d_lock=1;
  lcd.setCursor(0, 0);
  lcd.print("   SYSTEM CHECK    ");  
  lcd.setCursor(0, 3);
  lcd.print("<--     ENTER    -->"); 
  }

  if(key==2){
    list_display = 1;
    d_lock=0;
    enter=1;
    menu_lock=1;
    submenu_lock=0;
    delay(200);
    key=0;
  lcd.clear();
}
}


if(list_display==1 and submenu_lock==0){
  if(list_counter==0){
  lcd.setCursor(0, 0);
  lcd.print("   SYSTEM CHECK    ");  
  lcd.setCursor(0, 1);
  lcd.print("[*] MOTOR          ");
  lcd.setCursor(0, 2);
  lcd.print("[ ] SENSORS        ");
  lcd.setCursor(0, 3);
  lcd.print("SELECT   BACK    OK");
  }

  if(list_counter==1){
  lcd.setCursor(0, 0);
  lcd.print("   SYSTEM CHECK    ");  
  lcd.setCursor(0, 1);
  lcd.print("[ ] MOTOR          ");
  lcd.setCursor(0, 2);
  lcd.print("[*] SENSORS        ");
  lcd.setCursor(0, 3);
  lcd.print("SELECT   BACK    OK");
  } 

  if(key==1){
    select();
  }

  if(key==2){
  d_lock=0;
  list_display=0;
  submenu_lock=1;
  menu_lock=0;
  enter=0;
  delay(200);
  lcd.clear();
  menu=3;
  key=0;

}
  


  if(key==3 and list_counter==0){
  test_motor=1;
  d_lock=0;
  enter=1;
  menu_lock=1;
  delay(200);
  key=0;
  lcd.clear();
  }
  if(key==3 and list_counter==1){
    test_sensors=1;
      d_lock=0;
  enter=1;
  menu_lock=1;
  delay(200);
  key=0;
  lcd.clear();
  }
}







if(test_motor==1 and power_off==0){
if(d_lock==0){
  d_lock=1;
  submenu_lock=1;
  enter=1;
  lcd.setCursor(0, 0);
  lcd.print("    DRIVE MOTOR     ");  
  lcd.setCursor(0, 3);
  lcd.print("<--     BACK     -->"); 
  }


if(key==1){

      digitalWrite(forward_drive,1);  
      //delay(100); 
  }
  if(key==3){
      digitalWrite(backward_drive,1);  
       // delay(100);  
}



if(key==2){
  d_lock=0;
  test_motor=0;
  submenu_lock=0;
  enter=0;
  delay(200);
  lcd.clear();
  menu=3;
  key=0;

}

if(analogRead(A7)==0){
  key=0;
   digitalWrite(forward_drive,0);  
     digitalWrite(backward_drive,0);   
}


}

if(test_sensors==1){
  if(d_lock==0){
    menu_lock=1;
    submenu_lock=1;
    enter=1;
  
    if(list_counter==1){
      if(blinker ==0){
      lcd.setCursor(0, 0);
      lcd.print("    TEST SENSORS    ");
      lcd.setCursor(0,1);
      lcd.print("=> OXIMETER         "); 
      lcd.setCursor(0,2);
      lcd.print("=> LDR              ");
      lcd.setCursor(0, 3);
      lcd.print("SELECT   BACK     OK");
      
      }
      if(blinker ==1){
      lcd.setCursor(0, 0);
      lcd.print("    TEST SENSORS    ");
      lcd.setCursor(0,1);
      lcd.print("   OXIMETER         "); 
      lcd.setCursor(0,2);
      lcd.print("=> LDR              ");
      lcd.setCursor(0, 3);
      lcd.print("SELECT   BACK     OK");
      }

    }

    if(list_counter==0){
      if(blinker ==0){
      lcd.setCursor(0, 0);
      lcd.print("    TEST SENSORS    ");
      lcd.setCursor(0,1);
      lcd.print("=> OXIMETER         "); 
      lcd.setCursor(0,2);
      lcd.print("=> LDR              ");
      lcd.setCursor(0, 3);
      lcd.print("SELECT   BACK     OK");
      }
      if(blinker ==1){
      lcd.setCursor(0, 0);
      lcd.print("    TEST SENSORS    ");
      lcd.setCursor(0,1);
      lcd.print("=> OXIMETER         "); 
      lcd.setCursor(0,2);
      lcd.print("   LDR              ");
      lcd.setCursor(0, 3);
      lcd.print("SELECT   BACK     OK");
      }

    }
    if(key==1){
      select();
    }
  }


if(key==2){
  d_lock=0;
  test_sensors=0;
  submenu_lock=0;
  enter=2;
  delay(200);
  lcd.clear();
  menu=3;
  key=0;

}
}









if(enter==0){
key=0;
} 

}







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

void select(){
    list_counter--;
    key=0;
    lcd.clear();
    if(list_counter==2){
    list_counter=0;
  }
    if(list_counter==-1){
    list_counter=1;
  }
}







