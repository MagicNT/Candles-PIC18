
//#//###############################//#//
//#//       Tony Nasr:  Candles     //#//
//#//###############################//#//

#include <p18cxxx.h>  // Import PIC18 Library

#define T    10             // Specify time variable in seconds

enum {OFF, ON}; // OFF=0 ON=1
unsigned char candle_status[8] = {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF}, // Array to store each candle status
              candle_time[8] = {T, T, T, T, T, T, T, T},                   // Array to store each candle time counter
              mask,                                                        // Mask to check which candle to turn ON
              i;                                                           // Variable for algorithm flow

//############################################################################

void setup(void);           // Initialize System Configurations
void ISR(void);             // Interrupt Service Routine
void select(unsigned char); // Update Candle Status based on indexing logic

//############################################################################

void main(void) { // Main Program Routine
    setup();      // Prepare System
    while(1);     // make an Infinite Loop to keep program running all time   
}

//############################################################################

void setup(void) {
    ANSELB = 0X00; TRISB = 0XFF;                // PORTB Digital Input
    ANSELC = 0X00; TRISC = 0X00; PORTC = 0x00;  // PORTC Digital Output & initial value = 00000000
    TMR0H = (65536 - 62500) / 256;              // 62,500 * 16us = 1sec
    TMR0L = (65536 - 62500) % 256;
    T0CON = 0b10010011;                         // 1/16 , 16-bit mode
    INTCON2bits.RBPU = 0;                       // Enable internal pull-ups
    INTCONbits.TMR0IE = 1;                      // Enable Local Mask
    INTCONbits.GIE = 1;                         // Enable Global Mask
}

#pragma code ISR = 0x0008  // ISR starts at 0x0008
#pragma interrupt ISR      // ISR is an interrupt

void ISR(void) {
    TMR0H = (65536 - 62500) / 256;         // 62,500 * 16us = 1 sec
    TMR0L = (65536 - 62500) % 256;
    INTCONbits.TMR0IF = 0;                 // Acknowledge interrupt 

    mask = PORTB ^ 0xFF;                   // Obtain mask from PORTB, by getting 1s where button pressed
    for (i = 0; i < 8; i++, mask >>= 1)    // Test each bit of the mask  
        if (candle_status[i] == ON)        // Check candle is ON
            if ((candle_time[i]-1) != 0)   // If time count-down not done yet
                candle_time[i]--;          // Decrease time by 1 sec
            else {                         // If Time is up for the candle
                candle_time[i] = T;        // Reset time to original T seconds
                candle_status[i] = OFF;    // Set candle status to OFF            
                select(OFF);               // Turn OFF corresponding LED candle
            }
        else if ((mask & 0x01) == 0x01) {  // If candle OFF, Turn it On for corresponding pressed button 
            select(ON);                    // Select with logic 1 to Turn ON
            candle_status[i] = ON;         // Update candle status to ON  
        }
}

//############################################################################

void select(unsigned char s) {
    switch(i) { // Change Candle status based on Indexing of the loop in ISR
        case 0: PORTCbits.RC0 = s; break; // LED0 pin
        case 1: PORTCbits.RC1 = s; break;
        case 2: PORTCbits.RC2 = s; break;
        case 3: PORTCbits.RC3 = s; break;
        case 4: PORTCbits.RC4 = s; break;
        case 5: PORTCbits.RC5 = s; break;
        case 6: PORTCbits.RC6 = s; break;        
        case 7: PORTCbits.RC7 = s; break; // LED7 pin
    } // Set LED status to s where s can be 1=ON or 0=OFF
}

//############################################################################



