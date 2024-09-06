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
