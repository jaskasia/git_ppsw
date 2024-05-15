#include <LPC21xx.H>
//gittest
#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define LED5_bm 1<<21

#define BUTTON0_bm 0x10
#define BUTTON1_bm 0x40
#define BUTTON2_bm 0x20
#define BUTTON3_bm 0x80

void Delay(unsigned int uiDelayInMs) {

    unsigned int uiForLoopCounter;

    for(uiForLoopCounter = 0; uiForLoopCounter < uiDelayInMs*5460; uiForLoopCounter++) {}
}

void LedInit() {

    IO1DIR = IO1DIR | (LED0_bm|LED1_bm|LED2_bm|LED3_bm|LED5_bm); ///konfiguruje piny 16-19 zawarte w porcie 1 jako wyjsciowe, 1 sprawia ze piny staja sie wyjsciowymi
    IO1SET = LED0_bm;

}

void LedOn(unsigned char ucLedIndeks) {
    IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm|LED5_bm;
    switch(ucLedIndeks) {

        case 0:

            IO1SET = LED0_bm;
            break;

        case 1:

            IO1SET = LED1_bm;
            break;

        case 2:

            IO1SET = LED2_bm;
            break;

        case 3:

            IO1SET = LED3_bm;
            break;

                case 4:

            IO1SET = LED5_bm;
            break;

        default: {}
        }
    }


enum KeyboardState {RELEASED,BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3};

enum KeyboardState eKeyboardRead() {

    if((IO0PIN&BUTTON0_bm)==0) {
        return BUTTON_0;
    }

    else if((IO0PIN&BUTTON1_bm)==0) { //wcisniety 0x0 puszczony 0x40
        return BUTTON_1;
    }

    else if((IO0PIN&BUTTON2_bm)==0) { //wcisniety 0x0 puszczony 0x20
        return BUTTON_2;
    }

    else if((IO0PIN&BUTTON3_bm)==0) {
        return BUTTON_3;
    }

    return RELEASED;
}

void KeyboardInit() {
    IO0DIR = IO0DIR & (~(BUTTON0_bm|BUTTON1_bm|BUTTON2_bm|BUTTON3_bm)); // konfiguruje piny 4-7 zawarte w porcie 0 jako wejsciowe, negujac DIR (podstawowo ustawiajacy na 1) podaje nam on 0, ktore ustawiaja piny na wejsciowe
}



enum StepDirection {LEFT,RIGHT};

void LedStep (enum StepDirection Kierunek){
    static unsigned int uiLedIndeks;
    if(Kierunek==RIGHT) {
        uiLedIndeks--;
    }
    else if (Kierunek==LEFT){
        uiLedIndeks++;
    }
    LedOn(uiLedIndeks%4);
}

void LedStepLeft(void) {
    LedStep(LEFT);
}
void LedStepRight(void) {
    LedStep(RIGHT);
}


int main(){

    LedInit();
    KeyboardInit();

    while (1){

    switch (eKeyboardRead()){
            case BUTTON_1:
                LedStepRight();
                break;
            case BUTTON_2:
                LedStepLeft();
                break;
            default:
                break;
        }
        Delay(500);
  }
}
//komentarz
