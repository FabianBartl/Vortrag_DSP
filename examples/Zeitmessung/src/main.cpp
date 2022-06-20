#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <Arduino.h>

// interrupt variables (for timer)
volatile unsigned int timer_overflow_counter = 0;
volatile unsigned int timer_start = 0, timer_stop = 0;

// timer variables
unsigned int timer_max = 0xffff;
unsigned long int timer_ticks = 0;
double timer_sec = 0;

void info(char* msg) { Serial.println(msg); Serial.flush(); }

// print result
void result()
{
  // disable interrupts while calculate results
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    // timer_sec = ((double)timer_start / (double)timer_max + timer_overflow_counter + (double)timer_stop / (double)timer_max) / 4.0;
    timer_sec = ((double)timer_start / (double)timer_max + timer_overflow_counter + (double)timer_stop / (double)timer_max);
    timer_ticks = timer_max - timer_start + timer_overflow_counter * F_CPU + timer_stop;

    for (int i=0; i<10; i++) { Serial.println(" "); }
    Serial.print("clk ~ ");  Serial.println(timer_ticks);
    Serial.print("sec ~ ");  Serial.println(timer_sec);
    Serial.flush();
  }
}

// interrupt events
ISR(TIMER1_OVF_vect) { timer_overflow_counter++; }

ISR(INT0_vect)
{
  timer_overflow_counter = 0;
  timer_start = TCNT1;
  info("go");
}

ISR(INT1_vect)
{
  timer_stop = TCNT1;
  result();
}

// loop
int main(void)
{
  Serial.begin(9600);
  info("\ninit");

  // setup pins
  DDRD &= ~((1 << DDD2) | (1 << DDD3));
  PORTD |= (1 << PD2) | (1 << PD3);

  // setup timer
  TCCR1A = 0;               // normal mode
  TCCR1B |= (1 << CS10);    // no prescaler
  TIMSK1 |= (1 << TOIE1);   // overflow interrup

  // setup external interrupts
  EICRA |= (1 << ISC10) | (1 << ISC00);
  EIMSK |= (1 << INT1) | (1 << INT0);

  // enable interrupts
  info("conf");
  sei();

  // wait for interrupts
  for(;;);
  return -1;
}
