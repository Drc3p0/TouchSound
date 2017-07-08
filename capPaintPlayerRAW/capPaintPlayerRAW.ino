#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

/*
//with envelope included
// GUItool: begin automatically generated code
AudioPlaySdRaw           Raw1;     //xy=242,252
AudioPlaySdRaw           Raw2;     //xy=242,252
AudioPlaySdRaw           Raw3;     //xy=242,252
AudioPlaySdRaw           Raw4;     //xy=242,252
AudioEffectEnvelope      Env1;      //xy=420,250
AudioEffectEnvelope      Env2;      //xy=419,291
AudioEffectEnvelope      Env3;      //xy=425,330
AudioEffectEnvelope      Env4;      //xy=426,371
AudioMixer4              Mix1;         //xy=616,290
AudioOutputAnalog        Dac1;           //xy=756,289
AudioConnection          patchCord1(Raw1, 0, Env1, 0);
AudioConnection          patchCord2(Raw2, 0, Env2, 0);
AudioConnection          patchCord3(Raw3, 0, Env3, 0);
AudioConnection          patchCord4(Raw4, 0, Env4, 0);
AudioConnection          patchCord5(Env2, 0, Mix1, 1);
AudioConnection          patchCord6(Env1, 0, Mix1, 0);
AudioConnection          patchCord7(Env3, 0, Mix1, 2);
AudioConnection          patchCord8(Env4, 0, Mix1, 3);
AudioConnection          patchCord9(Mix1, Dac1);
AudioControlSGTL5000     sgtl5000_1;
// GUItool: end automatically generated code
*/

// GUItool: begin automatically generated code
AudioPlaySdRaw           Raw1;           //xy=318.7222137451172,461.7778072357178
AudioPlaySdRaw           Raw2;           //xy=320.9444351196289,508.4445037841797
AudioPlaySdRaw           Raw3;           //xy=323.1666488647461,548.444486618042
AudioPlaySdRaw           Raw4;           //xy=323.1666831970215,587.3333396911621
AudioEffectFade          fade2;          //xy=487.7778015136719,346.66666746139526
AudioEffectFade          fade1;          //xy=493.3333053588867,302.222261428833
AudioEffectFade          fade3;          //xy=498.888858795166,390.0000228881836
AudioEffectFade          fade4;          //xy=520.0000038146973,443.33336448669434
AudioMixer4              Mix1;           //xy=633.7777709960938,332
AudioOutputI2S           i2s2;           //xy=797.77783203125,335.5555450320244
AudioConnection          patchCord1(Raw2, fade2);
AudioConnection          patchCord2(Raw1, fade1);
AudioConnection          patchCord3(Raw3, fade3);
AudioConnection          patchCord4(Raw4, fade4);
AudioConnection          patchCord5(fade2, 0, Mix1, 1);
AudioConnection          patchCord6(fade1, 0, Mix1, 0);
AudioConnection          patchCord7(fade3, 0, Mix1, 2);
AudioConnection          patchCord8(fade4, 0, Mix1, 3);
AudioConnection          patchCord9(Mix1, 0, i2s2, 0);
AudioConnection          patchCord10(Mix1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=790.7777709960938,429
// GUItool: end automatically generated code


int P = 0;
int L = 0;
int A = 0;
int Y = 0;
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
 // #define SDCARD_CS_PIN    10
 // #define SDCARD_MOSI_PIN  7
 // #define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

void setup() {
  Serial.begin(9600);
pinMode(led, OUTPUT);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(50);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  Mix1.gain(1, 0.25);
  Mix1.gain(2, 0.25);
  Mix1.gain(3, 0.25);
  Mix1.gain(4, 0.25);

      SPI.setMOSI(SDCARD_MOSI_PIN);
      SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
}

void loop() {
digitalWrite(led, HIGH);
  pinP = touchRead(1);
  pinL = touchRead(0);
  pinA = touchRead(16);
  pinY = touchRead(17);
  Serial.print("   pinP = "); Serial.print(pinP);
  Serial.print("   pinL = "); Serial.print(pinL);
  Serial.print("   pinA = "); Serial.print(pinA);
  Serial.print("   pinY = "); Serial.print(pinY);
    loopP = Raw1.isPlaying();
//Serial.print(loopP);
//compareP[1]=compareP[0]; // set the old state of CompareP from entry 0 to entry 1 in the array
//compareP[0]=pinP>1000; // Check if current state is above threshold and assign 1 or 0 to first entry in CompareP array
//if(compareP[0]>compareP[1])//check that the threshold has just been crossed
  //{
    
    
if (pinP > 2000 && loopP == 0){
    Raw1.play("YEAH.raw");
    
  //noteOn.Env1(); //begin envelope attack phase
    Serial.print("P-ON"); 
    }
  
  
if (pinP < 2000 && loopP != 0){
    //begin noteOff.Env1() 
    Raw1.stop();
    Serial.print("P-OFF");

  }

  /////////////
  if (pinL > 2000 && Raw2.isPlaying() == 0) {
   fade2.fadeIn(1000);
    Raw2.play("BIRDS.raw");
    //Serial.print("L-ON");

  }
  if (pinL < 2000 && Raw2.isPlaying() != 0) {
    fade2.fadeOut(1000);
  //   Raw2.stop();
 //   Serial.print("L-OFF");

  }

  /////////////
  if (pinA > 2000 && Raw3.isPlaying() == 0) {
    fade3.fadeIn(1000);
    Raw3.play("CHIMES.raw");
  }

  if (pinA < 2000 && Raw3.isPlaying() != 0) {
    fade3.fadeOut(1000);
    //Raw3.stop();
 //   Serial.print("A-OFF");
  }

  //////////////
  if (pinY > 1800 && Raw4.isPlaying() == 0) {
    fade4.fadeIn(1000);
    Raw4.play("AMBIENT.raw");
//    Serial.print("Y-ON");

  }
  if (pinY < 1800 && Raw4.isPlaying() != 0) {
    fade4.fadeOut(1000);
  //  Raw4.stop();
   // Serial.print("Y-OFF");

  }

  Serial.println ("");
}


