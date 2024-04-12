// Play MP3 audio files from the SD card. Output is sent to any speaker connected to line out port

#include "AudioTools.h"                 // Main library
#include "AudioLibs/AudioBoardStream.h" // Provides access to boards line in/out
#include "AudioLibs/AudioSourceSD.h"    // SD card library
#include "AudioCodecs/CodecMP3Helix.h"  // MP3 decoding/encoding library

const char *startFilePath = "/"; // Start path reading audio files
const char *ext = "mp3";         // Audio files extension

AudioSourceSD source(startFilePath, ext, PIN_AUDIO_KIT_SD_CARD_CS); // SD card
AudioBoardStream kit(AudioKitEs8388V1);                             // Audio source stream
MP3DecoderHelix decoder;                                            // Object used to decode mp3 to PCM

// Get audio data from sd, decode mp3 to PCM, then pass audio to line out(earphone, speaker channels)
AudioPlayer player(source, kit, decoder);

// Audio PlayBack call back functions
// Play next audio file
void next(bool, int, void *)
{
   player.next();
}

// Play previous audio file
void previous(bool, int, void *)
{
   player.previous();
}

// Toggle Play / Pause
void startStop(bool, int, void *)
{
   player.setActive(!player.isActive());
}

void setup()
{
   Serial.begin(115200);

   // Start logger at Level INFO
   AudioLogger::instance().begin(Serial, AudioLogger::Info);

   // setup output
   // Get default config and set kit to be source of Audio Data(TX_MODE)
   auto cfg = kit.defaultConfig(TX_MODE);
   cfg.sd_active = true; // Activate SD card
   kit.begin(cfg);       // Start line out

   // setup additional buttons
   kit.addDefaultActions();
   kit.addAction(kit.getKey(1), startStop);
   kit.addAction(kit.getKey(4), next);
   kit.addAction(kit.getKey(3), previous);

   // setup player
   player.setVolume(0.7);
   player.begin();
}

void loop()
{
   // Run very fast functions/logic and avoid delays to prevent slowing down data transfer to audio output device

   player.copy();        // Continuously copy data from sd to line out
   kit.processActions(); // Check for pressed keys
}