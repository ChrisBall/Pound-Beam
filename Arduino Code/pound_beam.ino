/*
   add large value decoupling cap across 5V & GND (to prevent issues with variable range(?))
*/

#include <U8g2lib.h>        //https://github.com/olikraus/u8g2/blob/master/cppsrc/U8g2lib.h - manages I2C display
#include <ScaleManager.h>   //https://github.com/ChrisBall/ScaleManager                     
#include <SoftwareSerial.h> //included with arduino

#define VS1053_BANK_DEFAULT 0x00
#define VS1053_BANK_DRUMS1 0x78
#define VS1053_BANK_DRUMS2 0x7F
#define VS1053_BANK_MELODY 0x79

#define MIDI_NOTE_ON  0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_CHAN_MSG 0xB0
#define MIDI_CHAN_BANK 0x00
#define MIDI_CHAN_VOLUME 0x07
#define MIDI_CHAN_PROGRAM 0xC0

#define MIDIMODE true  //whether to send out MIDI (true) or debug (false) over serial port
#define HAIRLESS true  //http://projectgus.github.io/hairless-midiserial/ use to send MIDI over USB serial port (at 115200 baud)

#define UP 0
#define LEFT 1
#define CENTRE 2
#define RIGHT 3
#define DOWN 4
#define NUM_BUTTONS 5

#define PWM_RANGE 4

long unsigned int range = 300;
long unsigned int startTime = 0;

int minRange = 301;
int maxRange = 900;

short int scaleRange = 8;
byte currentMidiNote = 128; //128 is 'inactive'
byte activeMidiNote = 128; //'playing' midi note (used when notes change to turn off the old note);
int outputScaleNote = 0;  //range scaled to note
boolean notePlaying = false;

int activeMenuInput = 0;
byte menuItems = 5;

int midiInstrument = 0;
byte midiVolume = 127;

U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   //page buffer = 256bytes (_1_ = 128, _2_ = 256, _F_ = 1024)
ScaleManager sm;
SoftwareSerial VS1053(0, 2); //RX, TX
SoftwareSerial MB1003(3, 0);

const byte buttonPins[] = {8, 9, 10, 11, 12}; //UP, LEFT, CENTRE, RIGHT, DOWN
byte buttonStates[NUM_BUTTONS];

void setup() {
  setupSM();
  u8g2.begin();  //can also use u8g2 to manage menu navigation
  drawMenu();
  setupPins();

  if (MIDIMODE) {
    if (HAIRLESS) {
      Serial.begin(115200);
    } else {
      Serial.begin(31250);
    }
  } else {
    Serial.begin(115200);
  }
  VS1053.begin(31250);
  MB1003.begin(9600);

  midiSetChannelBank(0, VS1053_BANK_MELODY);
  midiSetInstrument(0, midiInstrument);
  midiSetChannelVolume(0, 127);
}

void loop() {
  buttonUpdate();  //updates buttons states
  buttonActions(); //carries out actions from states
  rangeUpdate();   //checks for data from the range sensor and updates the value in range
  midiUpdate();    //sends midi messages as appropriate
  if (!MIDIMODE) {
    printDebug();    //prints debug messages
  }
}

void printDebug() {
  for (int i = 0; i < 5; i++) {
    Serial.print(buttonStates[i]);
  }
  Serial.print('\t');
  Serial.print(activeMenuInput);
  Serial.print('\t');
  Serial.print(range);
  Serial.print('\t');
  Serial.print(outputScaleNote);
  Serial.print('\t');
  Serial.print(minRange);
  Serial.print('\t');
  Serial.print(maxRange);

  Serial.println();
}

