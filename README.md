# Serial-Controlled LED Shift Register with Arduino

This project demonstrates how to control an 8-segment LED display using a shift register (e.g., 74HC595) via serial communication. You can turn individual LEDs on or off and clear all LEDs using commands sent from the serial monitor.

## Components Used

- Arduino Uno
- 74HC595 Shift Register
- 8 LEDs
- 8 Resistors (220Ω recommended for each LED)
- Jumper wires
- Breadboard

## Pin Configuration

- **DATA_PIN**: connected to the data input of the shift register (Pin 8).
- **LATCH_PIN**: connected to the latch pin of the shift register (Pin 9).
- **CLOCK_PIN**: connected to the clock pin of the shift register (Pin 10).

## How It Works

- The Arduino receives commands via serial communication to control the LEDs connected through the shift register.
- You can send commands to turn specific LEDs on or off, or clear all LEDs.

## Code

```cpp
const int DATA_PIN  = 8;
const int LATCH_PIN = 9;
const int CLOCK_PIN = 10;

byte leds = 0b00000000;

void setup() {
    pinMode( DATA_PIN, OUTPUT );
    pinMode( LATCH_PIN, OUTPUT );
    pinMode( CLOCK_PIN, OUTPUT );

    Serial.begin( 9600 );
}

void loop() {

    if( Serial.available() ) {

        int led = Serial.read();

        if( led >= '0' && led <= '7' ) {

            led = led - '0';

            if( leds & (1 << led) ) {
                bitClear( leds, led );
                Serial.print( "LED off: " ); Serial.println( led );
            } else {
                bitSet( leds, led );
                Serial.print( "LED on: " ); Serial.println( led );
            }

        } else if( led == 'c' ) {

            leds = 0;
            Serial.println("Clear LED!");
        }

        update();
    }
}

void update() {

    digitalWrite( LATCH_PIN, LOW );

    for( int j = 0; j < 8; j++ ) {
        digitalWrite( DATA_PIN, leds & (1 << j) );
        digitalWrite( CLOCK_PIN, LOW );
        digitalWrite( CLOCK_PIN, HIGH );
    }

    digitalWrite( LATCH_PIN, HIGH );
}
```

## How to Use

1. Connect the shift register to the Arduino and LEDs as described in the pin configuration.
2. Open the Serial Monitor in the Arduino IDE.
3. Set the baud rate to 9600 bps.
4. Send commands to control the LEDs:
   - Send a digit (0 to 7) to toggle the corresponding LED on or off.
   - Send c to clear all LEDs.

## Features

- Control LEDs individually or clear all LEDs via serial commands.
- Useful for learning about shift registers and serial communication.

## License

This project is open-source and can be modified or distributed freely.
