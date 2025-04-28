#include <avr/io.h>

volatile uint8_t tot_overflow; 

void adc_init()
{
  // AREF = AVcc
  ADMUX = (1<<REFS0);
  // ADC Enable and prescaler of 128
  // 16000000/128 = 125000
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

void adc_read(uint8_t ch)
{
  // select the corresponding channel 0~5
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 5
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
  // start single conversion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC);
  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));
  Serial.println(ADC);
}


ISR(TIMER2_OVF_vect)
{
  // keep a track of number of overflows
  tot_overflow++;
}


void timer2_init(){
  // set up timer with prescaler = 1024
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  // initialize counter
  TCNT2 = 0;
  // enable overflow interrupt
  TIMSK2 |= (1 << TOIE2);
  // enable global interrupts
  sei();
  // initialize overflow counter variable
  tot_overflow = 0;
} 

int main()
{
  Serial.begin(9600);

  timer2_init();
  adc_init();

  while(1){
    if (tot_overflow >= 61)  // NOTE: '>=' is used
    {
      if (TCNT2 >= 8){
        adc_read(0);
        TCNT2 = 0;
        tot_overflow = 0;
      }
    }
  }
}
