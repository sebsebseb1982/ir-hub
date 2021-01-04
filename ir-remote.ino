const int IR_SENSOR = 9;
const int IR_LED = 10;
const int LED = 11;
#include <Arduino.h>

#define IRMP_INPUT_PIN IR_SENSOR
#define LED_BUILTIN LED
#define IRMP_PROTOCOL_NAMES 1
#include <irmpSelectMain15Protocols.h>
#include <irmp.c.h>
IRMP_DATA irmp_data;

void setup()
{
    Serial.begin(115200);
    irmp_init();
}

long high = 0;
long low = 0;

void loop()
{
  if (irmp_get_data(&irmp_data)) {
        /*
         * Skip repetitions of command
         */
        if (!(irmp_data.flags & IRMP_FLAG_REPETITION)) {
            /*
             * Here data is available and is no repetition -> evaluate IR command
             */
            switch (irmp_data.command) {
            case 0x48:
                digitalWrite(LED_BUILTIN, LOW);
                delay(4000);
                break;
            default:
                digitalWrite(LED_BUILTIN, HIGH);
                break;
            }
        }
        irmp_result_print(&irmp_data);
    }
}
