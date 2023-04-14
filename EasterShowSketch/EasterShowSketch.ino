#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  pinMode(1, OUTPUT); 
  pinMode(2, OUTPUT);
  randomSeed(analogRead(0));

  Serial.begin(9600);

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));

   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

  // list files
  printDirectory(SD.open("/"), 0);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(1,1);


}

void loop() {
int randNumber = random(1, 5);
 Serial.println(randNumber);
 if (randNumber == 1)
  {
   musicPlayer.playFullFile("/track002.mp3");
   delay(3000);
 } else if (randNumber == 2)
 {
   musicPlayer.playFullFile("/track003.mp3"); 
   delay(3000);
 } else if (randNumber == 3)
   {
    WindMillOn ();
    WindMillOff ();
    delay(3000);
 } else if (randNumber == 4)
   {
   musicPlayer.playFullFile("/track005.mp3");
   delay(3000);
 } else if (randNumber == 5)
  {
   musicPlayer.playFullFile("/track004.mp3");
   delay(3000);
 }
}

void WindMillOn () {
  digitalWrite(1, HIGH);  
  digitalWrite(2, HIGH);  
  musicPlayer.playFullFile("/track001.mp3");
}

void WindMillOff () {
  musicPlayer.stopPlaying();
  digitalWrite(1, LOW);  
  digitalWrite(2, LOW);  
}






void printDirectory(File dir, int numTabs) {
   while(true) {

     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
