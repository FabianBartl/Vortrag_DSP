#define F_CPU 16000000UL

#define PIN_START 9
#define PIN_STOP 10
#define LED_R 3
#define LED_G 4
#define LED_B 5

#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

void toggle_pin(int pin) { digitalWrite(pin, digitalRead(pin) == LOW ? HIGH : LOW); }
void blink_led(int led) { toggle_pin(led); _delay_ms(50); toggle_pin(led); }


// loop
int main(void)
{
  // setup variables
  int a=0, b=2, c;

  // setup pins for start/stop
  pinMode(PIN_START, OUTPUT);
  pinMode(PIN_STOP, OUTPUT);
  digitalWrite(0, PIN_START);
  digitalWrite(0, PIN_STOP);

  // setup pins for info
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(0, LED_R);
  digitalWrite(0, LED_G);
  digitalWrite(0, LED_B);

  _delay_ms(500);

  toggle_pin(PIN_START);
  _delay_ms(5000);
  toggle_pin(PIN_STOP);

  return 0;

  // start signal
  blink_led(LED_R);
  toggle_pin(LED_B);
  toggle_pin(PIN_START);

  // calculation loop
  for (c=0; c<10000; b++, c++)
  {
    a += b * c;
  }

  // stop signal
  toggle_pin(PIN_STOP);
  toggle_pin(LED_B);
  blink_led(LED_G);

  for(;;);
  return -1;
}
