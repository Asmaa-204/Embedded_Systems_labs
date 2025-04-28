#include <avr/io.h>

volatile uint8_t tot_overflow;
uint8_t ADC_endconversion_Flag=0;


void adc_init()
{
  // AREF = AVcc
  ADMUX = (1<<REFS0);
  // ADC Enable and prescaler of 128
  // 16000000/128 = 125000
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) | (1 << ADIE);
  sei();
}

int16_t adc_read(uint8_t ch)
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
  if(ADC_endconversion_Flag==1){
    ADC_endconversion_Flag=0;
    return (ADC);
  }
  else
    return(-1);
}


ISR(ADC_vect)
{
  ADC_endconversion_Flag=1;
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
  // initialize timer
  timer2_init();

  uint16_t adc_result0;
  DDRB = 0x20;  // to connect led to PB5
  // initialize adc
  adc_init();

  while(1){
    // check if no. of overflows = 12
    if (tot_overflow >= 61)  // NOTE: '>=' is used
    {
      // check if the timer count reaches 53
      if (TCNT2 >= 8){
        adc_result0 = adc_read(0);
        if(adc_result0!=-1){
          Serial.println(adc_result0);
        }
        TCNT2 = 0;
        tot_overflow = 0;
      }
    }
  }
}

