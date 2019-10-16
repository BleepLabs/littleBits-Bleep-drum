byte mc,led_mode,btrig,master_trigg,modea;
long sigprev,bcnt;
int rc1,rc2;
int read_bank[4];
byte read_trig,read_cnt,loop_tick;
static byte base_cutoff=50;
int rled,gled,bled;
void loop() {


  //int pot1tt=analogRead(ANALOG_POT_PIN);

  //pot1=0;

  //PORTD |= _BV(PORTD3);

  read_bank[3]=read_bank[2];
  read_bank[2]=read_bank[1];
  read_bank[1]=read_bank[0];



  byte r1 = analogRead(ANALOG_INPUT_PIN);  // slows down the loop and for a better reading
  byte r2 = analogRead(ANALOG_INPUT_PIN);
  //byte r3 = analogRead(ANALOG_INPUT_PIN);
  read_bank[0]=analogRead(ANALOG_INPUT_PIN);

  //PORTD &= ~_BV(PORTD3);


  loop_tick++;
  if(loop_tick>4){
   loop_tick=0;
 }
 if(loop_tick==0){
//  Serial.println(read_bank[0]);
    ppot1=pot1;

  int pot1t=readChange(0,analogRead(ANALOG_POT_PIN));

  pot1=(pot1t-1024)*-1;
/*
  if ((millis()-prevp)>6000){
    prevp=millis();
    //  Serial.println(pot_mode);
  Serial.println(snare_pitch);

  Serial.println(kick_pitch);

  }

  */
}


if (read_bank[0] <base_cutoff){

  led_mode=0;  
}  


if (pot1<16){
  pot_mode=0; 


  if (read_bank[1]>base_cutoff && read_bank[2]<base_cutoff){
    signal_stable=read_bank[0];



    if (signal_stable >base_cutoff && signal_stable<271){
     ident=200;
     //snare_pitch=50;
 //    snare_pitch= map (signal_stable,base_cutoff,255,20,250);
     snare_pitch=knee_map(signal_stable,16,271,0,280,171,50);

     accumulator1=0;
     B1_latch=1;
     led_mode=1;  
   }

   if (signal_stable >=271 && signal_stable<521){

    ident=220;
    //kick_pitch= map (signal_stable,271,521,20,400);
    kick_pitch=knee_map(signal_stable,271,521,40,500,421,100);

    //kick_pitch= 50;
    accumulator2=0;
    B2_latch=1;  
    led_mode=2;  

  }

  if (signal_stable >=521 && signal_stable<771){


    ident=240;
    //tick_pitch= map (signal_stable,521,771,20,400);
    tick_pitch=knee_map(signal_stable,521,771,5,330,672,100);

    //tick_pitch=50;
    accumulator3=0;
    B3_latch=1; 
    led_mode=3;  

  }

  if (signal_stable >=771){

    ident=255;
    //bass_pitch= map (signal_stable,771,1023,20,400);
    bass_pitch=knee_map(signal_stable,771,1023,18,900,921,250);

    //bass_pitch=50;
    accumulator4=0;
    B4_latch=1; 

    led_mode=4;  
  }

}

}

if (pot1>16){
  pot_mode=1; 
}
// external tirggers 

  if (read_bank[0]>base_cutoff && read_bank[3]<base_cutoff){
btrig=1;
bcnt=0;
  }

if (btrig==1){
bcnt++;
}

if (btrig==0){
bcnt=0;
}


if (bcnt>25 && read_bank[0]>base_cutoff){ //if it's n cycles later and we're still high
master_trigg=1;
btrig=0;
bcnt=0;

}

if (master_trigg==1){
       if (pot1>=16 && pot1<271){
        pot_mode=1; 

     snare_pitch=knee_map(pot1,16,271,0,280,171,50);
        //snare_pitch=knee_map(pot1,21,255,30,250);
        led_mode=1;  

        accumulator1=0;
        B1_latch=1;  
        master_trigg=0;

      }

      if (pot1>=271 && pot1<521){
        pot_mode=2; 
        //kick_pitch= map (pot1,255,512,20,400);
    kick_pitch=knee_map(pot1,271,521,40,500,421,100);

        led_mode=2; 
        accumulator2=0;
        B2_latch=1;
        master_trigg=0;  

      }

      if (pot1>=521 && pot1<771){
        pot_mode=3; 
        //tick_pitch= map (pot1,512,768,20,400);
    tick_pitch=knee_map(pot1,521,771,5,330,672,100);
        led_mode=3;
        accumulator3=0;
        B3_latch=1;
        master_trigg=0;  

      }

      if (pot1>=771){
        pot_mode=4; 
        //bass_pitch= map (pot1,768,1024,20,400);
    bass_pitch=knee_map(pot1,771,1023,18,900,921,250);
        led_mode=4;  
        accumulator4=0;
        B4_latch=1;
        master_trigg=0;  


      }

}




if (led_mode==0){
  bled=255;
  gled=255;
  rled=255;
}


if (led_mode==1){ //snare
  bled=255;
  gled=255-16;
  rled=255-64;
}

if (led_mode==2){ //kick


  bled=255-16;
  gled=255-16;
  rled=255;
}

if (led_mode==3){ //tick
  bled=255-0;
  gled=255-0;
  rled=255-64;
}

if (led_mode==4){ //bass
  bled=255-0;
  gled=255-16;
  rled=255-0;
}


if (pot_mode==0){
  modea=0;
}

if (pot_mode>0){
  modea=0;
}


//int inv_red=((rled)-255)*-1;
analogWrite(RED_LED_PIN, rled-modea); //red

//int inv_b=((bled)-255)*-1;
analogWrite(BLUE_LED_PIN, bled-modea); //blue

//int inv_g=-((gled)-255)*-1;
analogWrite(GREEN_LED_PIN, gled-modea); //green


}



int knee_map(int input, int inlow,int inhi,int outlow, int outhigh,int inknee, int outchg){ 
  //int inhi=4095;
  //int inlow=0;
  //int outhi=350;
  //int outlow=5;

  //int inknee=(((inhi-inlow)>>2)*3)+inlow;
 //int outchg=(((outhigh-outlow)<<1)/3)+inlow;
//  int inknee=((inhi-inlow)>>1)+inlow;
//  int outchg=((outhigh-outlow)>>2)+outlow;

  int out;
  
 if (input<inknee){
   out=map(input,inlow,inknee,outlow,outchg);
   //digitalWrite(9,HIGH);

 }

  
 if (input>=inknee){
   out=map(input,inknee,inhi,outchg,outhigh);
   //digitalWrite(9,LOW);

 } 
  
 return out;
   
}
