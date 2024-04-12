// Play MP3 audio files from the SD card. Output is sent to any speaker channels and to line out port

/**
 * Full list of API
 *
 * class AudioBoardStream - https://pschatzmann.github.io/arduino-audio-tools/classaudio__tools_1_1_audio_board_stream.html
 * class AudioPlayer - https://github.com/pschatzmann/arduino-audio-tools/wiki/The-Audio-Player-Class
 * class AudioSourceSD - https://pschatzmann.github.io/arduino-audio-tools/classaudio__tools_1_1_audio_source_s_d.html
 *
 * I2SCodecConfig - cfg object class. https://pschatzmann.github.io/arduino-audio-tools/structaudio__tools_1_1_i2_s_codec_config.html
 */

#include "AudioTools.h" // https://github.com/pschatzmann/arduino-audio-tools
#include "AudioLibs/AudioBoardStream.h"
#include "AudioLibs/AudioSourceSD.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *startFilePath = "/";
const char *ext = "mp3"; // Audio files extension

AudioSourceSD source(startFilePath, ext, PIN_AUDIO_KIT_SD_CARD_CS); // AudioSource for AudioPlayer using an SD card as data source
AudioBoardStream kit(AudioKitEs8388V1);                             // Configures DAC to output to line out and speaker channels
MP3DecoderHelix decoder;                                            // Object used to decode mp3 to PCM
AudioPlayer player(source, kit, decoder);                           // Controls play back

// Audio PlayBack call back functions
void next(bool, int, void *)
{
   player.next();
}

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
   // If you need to see more details you can switch to the log level Debug and after things work,
   // you need to switch to Warning or Error to avoid any negative impact on the audio quality.
   AudioLogger::instance().begin(Serial, AudioLogger::Info);

   // setup output
   // Microcontroller is the Audio Source in TX_MODE or Audio Sink in RX_MODE. RXTX_MODE is Source and Sink at the same time!
   auto cfg = kit.defaultConfig(TX_MODE);
   cfg.sd_active = true; // Activate SD card
   kit.begin(cfg);       // Start line out with edited configuration

   // setup additional buttons
   kit.addDefaultActions(); // Setup the supported default actions (volume, headphone detection)
   kit.addAction(kit.getKey(1), startStop);
   kit.addAction(kit.getKey(4), next);
   kit.addAction(kit.getKey(3), previous);

   // setup player
   player.setVolume(0.7);
   player.begin();
}

void loop()
{
   // NOTE: Run very fast functions/logic and avoid delays to prevent slowing down data transfer to audio output device

   player.copy();        // Continuously copy data from sd to line out
   kit.processActions(); // Check for pressed keys. This is a bit sluggish, hold keys till action has been acted on.
}