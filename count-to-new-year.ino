/* Referenced https://www.instructables.com/Using-a-4-digit-7-segment-display-with-arduino/
Had to reverse the pins 11 and 12 or you can swap them in segmentPins
This countdown is hardcoded and will have to click the reset button at the right time, not exactly ideal but was a fun project getting started
*/

#include "SevSeg.h"

SevSeg sevseg;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;
int countdownSeconds = 6 * 60 * 60;
bool blinkState = false;

void setup() {
    byte numDigits = 4;  
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0;
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(50);
}

void loop() {
    unsigned long currentMillis = millis();

    if (countdownSeconds > 0) {
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            countdownSeconds--;
        }

        if (countdownSeconds >= 3600) {
            int hours = countdownSeconds / 3600;
            int minutes = (countdownSeconds % 3600) / 60;
            int timeToDisplay = hours * 100 + minutes;
            sevseg.setNumber(timeToDisplay, 2);
        } else {
            int minutes = countdownSeconds / 60;
            int seconds = countdownSeconds % 60;
            int timeToDisplay = minutes * 100 + seconds;
            sevseg.setNumber(timeToDisplay, 2);
        }
    } else {
        // Blinking logic when countdown ends
        if (currentMillis - previousMillis >= 500) {
            previousMillis = currentMillis;
            blinkState = !blinkState;
        }

        if (blinkState) {
            sevseg.setNumber(0, 2);
        } else {
            sevseg.blank();
        }
    }

    sevseg.refreshDisplay();
}
