#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <Arduino.h>

// interrupt variables (for timer)
volatile unsigned int timer_overflow_counter = 0;
volatile unsigned int timer_start = 0, timer_end = 0;

// timer variables
unsigned int timer_max = 0xffff;
double timer_sec = 0;

// print debug and info messages
void debug(char* msg) { Serial.println(msg); Serial.flush(); }

// print result
void result()
{
  // disable interrupts while calculate results
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    timer_sec = ((double)timer_start / (double)timer_max + timer_overflow_counter + (double)timer_end / (double)timer_max) / 4.0;
    Serial.print(timer_sec);
    Serial.println(" sec");
    Serial.flush();
  }
}

// interrupt events
ISR(TIMER1_OVF_vect)
{
  timer_overflow_counter++;
}

ISR(INT0_vect)
{
  timer_overflow_counter = 0;
  timer_start = TCNT1;
  debug("start");
}

ISR(INT1_vect)
{
  timer_end = TCNT1;
  debug("stop");
  result();
}

// loop
int main(void)
{
  Serial.begin(9600);
  debug("\ninit");

  // setup pins
  DDRD &= ~((1 << DDD2) | (1 << DDD3));
  PORTD |= (1 << PD2) | (1 << PD3);

  // setup timer
  TCCR1A = 0; // normal mode
  TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler: clk/64 (eig. komplett sinnlos)

  // setup timer interrupt
  TIMSK1 |= (1 << TOIE1);

  // setup external interrupts
  EICRA |= (1 << ISC10) | (1 << ISC00);
  EIMSK |= (1 << INT1) | (1 << INT0);

  // enable interrupts
  sei();
  debug("configuration finished");

  // wait for interrupts
  debug("wait forever");
  for(;;);

  debug("not possible output");
  return -1;
}
