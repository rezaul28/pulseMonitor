#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>  

const int PulseWire = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;    // The on-board Arduino LED, close to PIN 13.

PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup()
{

    Serial.begin(9600); // For Serial Monitor

    // Configure the PulseSensor object, by assigning our variables to it.
    pulseSensor.analogInput(PulseWire);
    pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.

    // Double-check the "pulseSensor" object was created and "began" seeing a signal.
    if (pulseSensor.begin())
    {
        Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up,  or on Arduino reset.
    }
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
    oled.clearDisplay(); // clear display

    delay(2000); // wait for initializing

    oled.setTextSize(1);      // text size
    oled.setTextColor(WHITE); // text color
}

void loop()
{

    int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
    // "myBPM" hold this BPM value now.

    if (pulseSensor.sawStartOfBeat())
    {                                            // Constantly test to see if "a beat happened".
        Serial.println("HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
        Serial.print("BPM: ");                   // Print phrase "BPM: "
        Serial.println(myBPM);                   // Print the value inside of myBPM.
        oled.clearDisplay();                     // clear display

        oled.setCursor(0, 10); // position to display
        oled.setTextSize(1.5); // text size

        oled.println("HeartBeat Happened! \n "); // text to display
        oled.setTextSize(2.5);                   // text size

        oled.print("BPM: ");   // text to display
        oled.println(myBPM);   // text to display
        oled.setTextSize(1.5); // text size
        if(myBPM<60){
          oled.print("Your heartbeat is bellow average"); // text to display
        }
        else if (myBPM <= 100 && myBPM >= 60)
            oled.print("Your HeartBeat is normal"); // text to display
        else
            oled.print("Your above average"); // text to display
        oled.display();                           // show on OLED
    }

//    delay(20); // considered best practice in a simple sketch.
}
