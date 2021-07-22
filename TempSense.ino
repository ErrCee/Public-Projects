
// Include the Libraries needed by the OLED Display Board
#include<Wire.h>
#include<Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>

// Include the libraries needed by the DS18B20 sensor
#include<SPI.h>
#include<OneWire.h>
#include<DallasTemperature.h>

// Signal pin D2 of Seeeduino XIAO is defined as bus
// Thus pin D2 acts the input port of the signals sent by the Sensor
#define bus 2

// The OLED Display has 8 pages, each containing 128 segments and 8 bits of data
//   thereby having a total of 8192 bits or 1KB memory.
#define scr_width 128       // Screen width or total segments of the Display
#define scr_height 64       // Total screen height or 8 pages of 8 bits

// Since the OLED Display used don't have a reset pin, send -1 to the constructor
//   so that no pin is used as the RESET for the Display
#define oled_rst -1

// The values defined above is passed to the initializer of the display module
Adafruit_SSD1306 display(scr_width, scr_height, &Wire, oled_rst);

// Create an OneWire object by passing the signal pin to the constructor
// This object enables us to communicate with any OneWire device
OneWire oneWire(bus);

// To communicate with the temperature sensor, create an object of DallasTemperature
//   and pass the reference of an OneWire object as parameter
DallasTemperature sensors(&oneWire);

// The setup code is put here to be run once
void setup() {
    // The connected devices are searched and set to 12 bit resolution by begin()
    sensors.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // The display is initialized with value 60
    display.clearDisplay();                     // The screen is cleared
    display.setTextSize(1);                     // Text Size  is set to 1
    display.setTextColor(WHITE);                // Text Color is set to White
    display.setCursor(16,32);                   // The Cursor is set to (16,32) coordinates
    display.println("Starting up...");          // A welcome message is shown
    display.display();                          // The text is finally displayed
}

// This is analogous to main(), except the fact that it runs continuously
void loop() {
    display.setCursor(0,0);                     // The Cursor is brought to the first bit
    display.clearDisplay();                     // The screen is cleared
    display.setTextSize(1);                     // Text size  is set to 1
    display.setTextColor(SSD1306_WHITE);        // Text color is set to white
    display.println("Current Temperature : ");

    // The command to transmit temperature signals is sent to the sensors
    sensors.requestTemperatures();

    // Since there is only one sensor attached to the bus, therefore the deviceIndex is 0
    // Had there been more sensors, they would go by index 1, 2, ... respectively
    display.print(sensors.getTempCByIndex(0));  // Print the returned temperature
    display.print(' ');                         // Print a space (' ') character
    display.print((char)247);                   // Print a degree character
    display.print('C');                         // 'C' denotes celcius
    display.display();                          // The final print command
}
