#define PIN_LED 5
#define PIN_BUZZER 6
#define PIN_BUTTON 7
#define PIN_DIGI_SENSOR 8
#define SLEEP_TIME 5 * 1000 * 60

// How long should the alarm state last
//#define ALARM_TIME 8 * 1000
#define ALARM_TIME 4800

#define BEEP_TIME 600
#define BREAK_TIME 1000


void setup() {
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    pinMode(PIN_DIGI_SENSOR, INPUT);
}

void enable_alarm() {
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
}

void disable_alarm() {
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_BUZZER, LOW);
}

void loop() {

    if (digitalRead(PIN_DIGI_SENSOR) == LOW) {
        // Smoke detected
        unsigned long entryTime = millis();
        unsigned long currentTime = entryTime;

        unsigned long buzzTime = entryTime;

        unsigned long timeDiff = 0;
        bool buzzing = true;


        enable_alarm();

        while (timeDiff < ALARM_TIME)
        {
            if (digitalRead(PIN_BUTTON) == LOW)
            {
                // Button is pressed, faster exit
                break;
            }

            currentTime = millis();
            timeDiff = currentTime - entryTime;

            // Blinky stuff
            if (buzzing) {
                if (currentTime - buzzTime > BEEP_TIME) {
                    disable_alarm();
                    buzzing = false;
                    buzzTime = currentTime;
                }
            } else {
                if (currentTime - buzzTime > BREAK_TIME) {
                    enable_alarm();
                    buzzing = true;
                    buzzTime = currentTime;
                }
            }
        }

        disable_alarm();

        // Crisis is averted, wait for the air to clear up
        delay(SLEEP_TIME);
    }

    delay(500);
}
