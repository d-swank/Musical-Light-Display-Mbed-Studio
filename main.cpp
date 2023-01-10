#include "mbed.h"
#include "NHD_0216HZ.h"
#define SPEAKER D6

// Defines the frequency of the basic musical notes
# define Do     0.5
# define Re     0.45
# define Mi     0.4
# define Fa     0.36
# define So     0.335
# define La     0.31
# define Si     0.3
# define No     0 
# define L2     0.56

// Defines the beat length (whole note and half note) 
# define b1     0.5
# define b2     0.25
# define b3     0.125
# define b4     0.075
# define b5     0.1825
# define b6     0.06125

/*----------------------------------------------------------------------------
 Defines the Musical Piece of each song
 *----------------------------------------------------------------------------*/

// Jingle Bells
// float note[] = {Mi,No,Mi,No,Mi,No, Mi,No,Mi,No,Mi,No, Mi,No,So,No,Do,No,Re,No,Mi,No, Fa,No,Fa,No,Fa,No,Fa,No, Fa,No,Mi,No,Mi,No,Mi,No,Mi,No, Mi,Re,No,Re,Mi, Re,No,So,No};
// float beat[] = {b3,b3,b3,b3,b2,b2, b3,b3,b3,b3,b2,b2, b3,b3,b3,b3,b3,b3,b3,b3,b2,b1, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b4,b4,b4,b4, b2,b3,b3,b2,b2, b2,b2,b2,b2};

// Carol of the Bells
float note[] = {So,Fa,So,Mi, So,Fa,So,Mi, So,Fa,So,Mi, So,Fa,So,Mi, So,Fa,So,Mi, So,Fa,So,Mi, Mi,Mi,Mi,Re,Do, 
                Si,Si,Si,La,So, La,La,La,Si,La, Mi,Mi,Mi,Mi};
float beat[] = {b2,b3,b3,b2, b2,b3,b3,b2, b2,b3,b3,b2, b2,b3,b3,b2, b2,b3,b3,b2, b2,b3,b3,b2 ,b2,b3,b3,b3,b3, 
                b2,b3,b3,b3,b3, b2,b3,b3,b3,b3, b2,b3,b3,b2};

// Mary Had a Little Lamb
float note1[] = {Fa,No,Mi,No,Re,No,Mi,No, Fa,No,Fa,No,Fa,No, Mi,No,Mi,No,Mi,No, Fa,No,La,No,La,No, 
                Fa,No,Mi,No,Re,No,Mi,No, Fa,No,Fa,No,Fa,No,Fa,No, Mi,No,Mi,No,Fa,No,Mi,No, Re,No,Re,No};
float beat1[] = {b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b2,b2, b3,b3,b3,b3,b2,b2, b3,b3,b3,b3,b2,b1, 
                b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b2,b2,b2,b2};

// Ode to joy 
float note2[] = {Fa,No,Fa,No,So,No,La,No, La,No,So,No,Fa,No,Mi,No, Re,No,Re,No,Mi,No,Fa,No, Fa,No,Mi,No,Mi,No, 
                Fa,No,Fa,No,So,No,La,No, La,No,So,No,Fa,No,Mi,No, Re,No,Re,No,Mi,No,Fa,No, Fa,No,Mi,No,Mi,No, 
                Mi,No,Mi,No,Fa,No,Re,No,Mi,No,Fa,No,So,No,Fa,No,Re,No,Mi,No,Fa,No,So,No,Fa,No,Mi,No,Re,No,Mi,No,
                .465,No,Fa,No, Fa,No,Fa,No,So,No,La,No, La,No,So,No,Fa,No,Mi,No, Re,No,Re,No,Mi,No,Fa,No, 
                Fa,No,Mi,No,Mi,No};
float beat2[] = {b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b5,b5,b4,b4,b2,b2, 
                b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b5,b5,b4,b4,b2,b2, 
                b3,b3,b3,b3,b3,b3,b3,b3,b3,b3,b6,b6,b6,b6,b3,b3,b3,b3,b3,b3,b6,b6,b6,b6,b3,b3,b3,b3,b3,b3,b3,b3,
                b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b3,b3, b5,b5,b4,b4,b2,b2};

// Defines the PWM output for the speaker
PwmOut speaker(SPEAKER);

// Defines the InterruptIn's for the buttons
InterruptIn button1(D2);
InterruptIn button2(D3);
InterruptIn button3(D4);
InterruptIn button4(D5);

// Defines AnalogIn for the potentiometer
AnalogIn pent(A1);

// Defines BusOut for the red, yellow, and green LEDS
BusOut leds(D7, D8, D9);

// Defines the time ticker
Ticker t;

// Static variable to iterate through note and beat arrays
static int k;
static int song;
static float volume;

/*----------------------------------------------------------------------------
 Button ISR Functions
 *----------------------------------------------------------------------------*/

// Defines the button ISR's
void button1_ISR() {
    
    k = 0;
    song = 1;
}

void button2_ISR() {
    
    k = 0;
    song = 2;
}

void button3_ISR() {
    
    k = 0;
    song = 3;
}

void button4_ISR() {
    
    k = 0;
    volume = 0;
    song = 0;
}

/*----------------------------------------------------------------------------
 Timer ISR Function
 *----------------------------------------------------------------------------*/

// Defines the ticker ISR 
void timer_ISR() {
    
    switch (song) {

    case 0:
        speaker = 0;
        k = 0;
        break;

    case 1:
        if (k < sizeof(beat) / sizeof(float)) {

            if (note[k] != No) {
                speaker.period(note[k] * 0.05 * 0.05);
                speaker = 0.5 * volume;
            }

            else {
                speaker = 0;
            }
            
            t.attach(&timer_ISR, beat[k]);
            k++;
        }

        else {
            k = 0;
        }

        break;

    case 2:
        if (k < sizeof(beat1) / sizeof(float)) {

            if (note1[k] != No) {
                speaker.period(note1[k] * 0.05 * 0.05);
                speaker = 0.5 * volume;
            }

            else {
                speaker = 0;
            }

            t.attach(&timer_ISR, beat1[k]);
            k++;
        }

        else {
            k = 0;
        }

        break;

    case 3:
        if (k < sizeof(beat2) / sizeof(float)) {

            if (note2[k] != No) {
                speaker.period(note2[k] * 0.05 * 0.05);
                speaker = 0.5 * volume;
            }

            else {
                speaker = 0;
            }

            t.attach(&timer_ISR, beat2[k]);
            k++;
        }

        else {
            k = 0;
        }

        break;

    default:
        k = 0;
        speaker = 0;
        break;
    }
}

float notef = 0;

/*----------------------------------------------------------------------------
 LED Function
 *----------------------------------------------------------------------------*/

// Defines the pattern of the lights in which flashes to the beat of the music
void LEDS() {

    int notei = 0;
    notei = int(notef * 1000);

    switch (notei) {
    case 500:
        leds = 1;
        break;
    case 450:
        leds = 2;
        break;
    case 400:
        leds = 4;
        break;
    case 360:
        leds = 3;
        break;
    case 335:
        leds = 6;
        break;
    case 310:
        leds = 5;
        break;
    case 300:
        leds = 7;
        break;
    default:
        leds = 0;
        break;
    }
}

/*----------------------------------------------------------------------------
 LCD Display function
 *----------------------------------------------------------------------------*/

// Defines what gets displayed on the LCD display such as the names of each song
void LCD_display() {

    // When initially starting the program, prints Merry Christmas
    if (song == 0) {

        notef = 0;
        init_spi();
        init_lcd();
        print_lcd("     Merry");
        set_cursor(0, 1);
        print_lcd("   Christmas!");
    }

    // When song 1 plays, Carol of the Bells prints to the LCD display
    else if (song == 1) {

        notef = note[k];
        init_spi();
        init_lcd();
        print_lcd("Carol of");
        set_cursor(0, 1);
        print_lcd("the Bells");
    }

    // When song 2 plays, Mary had a Little Lamb prints to the LCD display
    else if (song == 2) {

        notef = note1[k];
        init_spi();
        init_lcd();
        print_lcd("Mary had");
        set_cursor(0, 1);
        print_lcd("a Little Lamb");
    }

    // When song 3 plays, Ode to Joy prints to the LCD display
    else if (song == 3) {

        notef = note2[k];
        init_spi();
        init_lcd();
        print_lcd("Ode to Joy");
    }
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

// Start of the program
int main() {

    // Considers the first musical note
    k= 0;
    song = 0;

    t.attach(&timer_ISR, 1);

    // Allows the buttons to be pressed continuously
    button1.rise(&button1_ISR);
    button2.rise(&button2_ISR);
    button3.rise(&button3_ISR);
    button4.rise(&button4_ISR);

    // Initializes the speaker, volume, and leds to a default setting
    speaker = 0;
    volume = 0;
    leds = 0x7;

    // Infinitely loops the LED and LCD display functions 
    while (true) {
        
        volume = pent;
        __WFI();

        LCD_display();
        LEDS();
    }   
}