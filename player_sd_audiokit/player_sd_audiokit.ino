// Play MP3 audio files from the SD card. Output is sent to any speaker connected to line out port

#include "AudioTools.h"
#include "AudioLibs/AudioBoardStream.h"
#include "AudioLibs/AudioSourceSD.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *startFilePath = "/";
const char *ext = "mp3";
AudioSourceSD source(startFilePath, ext, PIN_AUDIO_KIT_SD_CARD_CS);
AudioBoardStream kit(AudioKitEs8388V1);
MP3DecoderHelix decoder;
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
   AudioLogger::instance().begin(Serial, AudioLogger::Info);

   // setup output
   auto cfg = kit.defaultConfig(TX_MODE);
   // sd_active is setting up SPI with the right SD pins by calling
   // SPI.begin(PIN_AUDIO_KIT_SD_CARD_CLK, PIN_AUDIO_KIT_SD_CARD_MISO, PIN_AUDIO_KIT_SD_CARD_MOSI, PIN_AUDIO_KIT_SD_CARD_CS);
   cfg.sd_active = true;
   kit.begin(cfg);

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

   player.copy();
   kit.processActions();
}