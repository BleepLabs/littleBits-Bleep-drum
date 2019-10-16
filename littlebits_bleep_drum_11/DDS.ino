void DDS()
{
 //PORTD |= _BV(PORTD3);


    snare_sample = (pgm_read_byte(&snare_table[(index1)]))-127;
    kick_sample = (pgm_read_byte(&kick_table[(index2)]))-127;
    tick_sample = (pgm_read_byte(&tick_table[(index3)]))-127;
    clap_sample = (((pgm_read_byte(&bass_table[(index4)]))))-127;


    

    sample= (snare_sample+kick_sample+tick_sample+clap_sample)+127;

    if(sample>254){
      sample=254;
    }
    if(sample<1){
      sample=1;
    }

uint16_t dac_out = (0 << 15) | (1 << 14) | (1<< 13) | (1 << 12) | ( sample<<4 ); 

PORTB &= ~_BV(PORTB2);
SPI.transfer(dac_out>>8);
SPI.transfer(dac_out & 255);
PORTB |= _BV(PORTB2);

  ///////////////////////////////////////////////////////////////////////////////

  
  if (B1_latch==1){
    accumulator1 += snare_pitch;
    index1=(accumulator1 >> (6));  
    if (index1>snare_length){
      index1=0;
      accumulator1=0;
      B1_latch=0;
    }
  }

  if (B2_latch==1){
    accumulator2 += kick_pitch;
    index2=(accumulator2 >> (6));  
    if (index2>kick_length){
      index2=0;
      accumulator2=0;
      B2_latch=0;
    }
  }

  if (B3_latch==1){
    accumulator3 += tick_pitch;
    index3=(accumulator3 >> (6));  
    if (index3>tick_length){
      index3=0;
      accumulator3=0;
      B3_latch=0;
    }
  }

  if (B4_latch==1){
    accumulator4 += bass_pitch;
    index4=(accumulator4 >> (6));  
    if (index4>bass_length){
      index4=0;
      accumulator4=0;
      B4_latch=0;
    }
  }

 // PORTD &= ~_BV(PORTD3);

}
