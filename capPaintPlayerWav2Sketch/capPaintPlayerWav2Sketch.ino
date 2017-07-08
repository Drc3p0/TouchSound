#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "AudioSampleAmbientwav.h"
#include "AudioSampleBirdswav.h"
#include "AudioSampleYeahwav.h"
#include "AudioSampleChimeswav.h"


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem1;       //xy=427.77777099609375,290
AudioPlayMemory          playMem2;       //xy=435.77777099609375,342
AudioPlayMemory          playMem4;       //xy=436.77777099609375,431
AudioPlayMemory          playMem3;       //xy=437.77777099609375,388
AudioMixer4              Mix1;           //xy=633.7777709960938,332
AudioOutputI2S           i2s2;           //xy=797.77783203125,335.5555450320244
AudioConnection          patchCord1(playMem1, 0, Mix1, 0);
AudioConnection          patchCord2(playMem2, 0, Mix1, 1);
AudioConnection          patchCord3(playMem4, 0, Mix1, 3);
AudioConnection          patchCord4(playMem3, 0, Mix1, 2);
AudioConnection          patchCord5(Mix1, 0, i2s2, 0);
AudioConnection          patchCord6(Mix1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=790.7777709960938,429
// GUItool: end automatically generated code


int loopP = 0;
int loopL = 0;
int loopA = 0;
int loopY = 0;
int pinP = 0;
int pinL = 0;
int pinA = 0;
int pinY = 0;
int led = 13;
//Ben added code
boolean compareP[2];
boolean compareL[2];
boolean compareA[2];
boolean compareY[2];
int threshold=1000;
// Use these with the Teensy Audio Shield
  #define SDCARD_CS_PIN    10
  #define SDCARD_MOSI_PIN  7
  #define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

void setup() {
  Serial.begin(9600);
pinMode(led, OUTPUT);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(30);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(.8);

  Mix1.gain(0, 0.25);
  Mix1.gain(1, 0.25);
  Mix1.gain(2, 0.25);
  Mix1.gain(3, 0.25);

  //    SPI.setMOSI(SDCARD_MOSI_PIN);
  //    SPI.setSCK(SDCARD_SCK_PIN);
  //if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
  //  while (1) {
   //   Serial.println("Unable to access the SD card");
   //   delay(500);
  //  }
 // }
  
}

void loop() {
digitalWrite(led, HIGH);
  pinP = touchRead(0);
  pinL = touchRead(1);
  pinA = touchRead(17);
  pinY = touchRead(16);
  Serial.print("   pinP = "); Serial.print(pinP);
  Serial.print("   pinL = "); Serial.print(pinL);
  Serial.print("   pinA = "); Serial.print(pinA);
  Serial.print("   pinY = "); Serial.print(pinY);
    loopP = playMem1.isPlaying();
    loopL = playMem2.isPlaying();
    loopA = playMem3.isPlaying();
    loopY = playMem4.isPlaying();

Serial.print(loopP);
compareP[1]=compareP[0]; // set the old state of CompareP from entry 0 to entry 1 in the array
compareP[0]=pinP>1000; // Check if current state is above threshold and assign 1 or 0 to first entry in CompareP array
if(pinP > 1000 && loopP == 0)//check that the threshold has just been crossed
  {
    playMem1.play(AudioSampleYeahwav);
    Serial.print("P-ON");  
  }
  
  if (pinP < 1000 && loopP != 0){
    playMem1.stop();
    Serial.print("P-OFF");

  }


/////////////
  if (pinL > 1000 && loopL == 0){
    playMem2.play(AudioSampleBirdswav);
  //noteOn.Env1(); //begin envelope attack phase
    Serial.print("L-ON");

  }
  if (pinL < 1000 && playMem2.isPlaying() != 0){
    //begin noteOff.Env1() 
    playMem2.stop();
    Serial.print("L-OFF");

  }
  
/////////////
  if (pinA > 1000 && loopA == 0){
    playMem3.play(AudioSampleChimeswav);
  //noteOn.Env1(); //begin envelope attack phase
    Serial.print("A-ON");

  }
  if (pinA < 1000 && playMem3.isPlaying() != 0){
    //begin noteOff.Env1() 
    playMem3.stop();
    Serial.print("A-OFF");

  }
//////////////
  if (pinY > 1000 && loopY == 0){
    playMem4.play(AudioSampleAmbientwav);
  //noteOn.Env1(); //begin envelope attack phase
    Serial.print("Y-ON");

  }
  if (pinY < 1000 && playMem4.isPlaying() != 0){
    //begin noteOff.Env1() 
    playMem4.stop();
    Serial.print("Y-OFF");

  }

Serial.println ("");
}


