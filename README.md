# Virtual Candles Manager on PIC18


## Description
This project *candles* utilizes the PIC18f45k22 microcontroller from Microchip. The purpose behind this project is to lighten up 8 LED (candles) through means of pressing 8 buttons each linked to 1 of the LEDs. Once one or many of the buttons are pressed, the corresponding LED will turn ON for exactly, an amount of T seconds decided on earlier by the user through the code. When LED(s) is/are on, its corresponding button(s) will no longer affect the LED(s) until the T period expires and thus the button(s) can be pressed again, if willing to be, by the user. We will notice that if many buttons are pressed, the LEDs will turn ON and OFF in an orderly fashion, knowing that each of their time count-down will expire in different moments. We must note that during the design of this project, only one internal timer was used and NOT 8 timers which is highly efficient.


## Requirements / Environment
- MPLAB X IDE
- Proteus Design Suite


## Algorithm flow
The basic concept behind the algorithm of this design is to create 2 global arrays to hold within each candle’s timer count-down and status (ON/OFF). The main routine will run infinitely, and there is an Interrupt Service Routine managing the timer (allowing 1 seconds count). Inside this ISR, I have implemented the main algorithm which will run an 8-rounds loop on each interrupt, checking the PORTB input using a mask technique, to detect which bits have been altered, in other words, check which buttons were pressed. If one or more buttons have been pressed, the code will then enable the corresponding LED(s) through a custom “select” function to control the PORTC pins which are the LED output pins. Inside this loop, I will also check for the turned ON LED(s) and correspondingly decrement each of their timer count-downs saved in the global array “candles_time”. Once one or more of these count-downs expire, I proceed to reset the timer to the original T amount and also reset the status of the LED to OFF in the global array *candles_status*. 


## Hardware layout

![h1](https://user-images.githubusercontent.com/86275885/122961690-038d2b00-d35b-11eb-9190-b46cae0d27a2.png)


![h2](https://user-images.githubusercontent.com/86275885/122961689-02f49480-d35b-11eb-9e5d-8858253f7bd5.png)

![h3](https://user-images.githubusercontent.com/86275885/122961687-025bfe00-d35b-11eb-9cb5-aa34f325d6e6.png)


## Conclusion
At the end of this project, we have seen a powerful ability that makes the microcontroller a highly reliable piece of hardware and that is the usage of built-in inner timer. This timer can simulate the strength of multitasking and multiprocessing by organizing tasks and timing them to seem as if they are running in the same exact moment. The “candles” project is a great example to demonstrate this by allowing us to see we can turn on 8 LEDs and keep running for a fixed period of time where each one has its unique time delay to stay on and all of that is managed by 1 single timer instead of 8 timers to pull off the job.

