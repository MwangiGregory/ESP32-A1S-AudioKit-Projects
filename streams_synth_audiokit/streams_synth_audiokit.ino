// This file contains the code for a synthesizer using the AudioKit library.

/**
 * Synthesizer - https://pschatzmann.github.io/arduino-audio-tools/classaudio__tools_1_1_synthesizer.html
 * GeneratedSoundStream - https://pschatzmann.github.io/arduino-audio-tools/classaudio__tools_1_1_generated_sound_stream.html
 * SynthesizerKey
 */
#include "AudioTools.h"
#include "AudioLibs/AudioBoardStream.h"

AudioBoardStream kit(AudioKitEs8388V1);        // Configure DAC
Synthesizer synthesizer;                       // generate sound having multiple keys pressed                                                                                                                                                   /**< Synthesizer object for sound generation */
GeneratedSoundStream<int16_t> in(synthesizer); // Source for reading generated tones
StreamCopy copier(kit, in);                    // Stream copy object for copying audio streams
// Arduino GPIO pins to note assossiation
SynthesizerKey keys[] = {{kit.getKey(1), N_C3}, {kit.getKey(2), N_D3}, {kit.getKey(3), N_E3}, {kit.getKey(4), N_F3}, {kit.getKey(5), N_G3}, {kit.getKey(6), N_A3}, {0, 0}}; /**< Array of synthesizer keys */

// Initializes the synthesizer and audio output.
void setup()
{
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // Setup output
  auto cfg = kit.defaultConfig(TX_MODE); // Board generates sound(is source of audio data)
  cfg.sd_active = false;)
  kit.begin(cfg);
  kit.setVolume(80);

  // define synthesizer keys for AudioKit
  synthesizer.setKeys(kit.audioActions(), keys, AudioActions::ActiveLow);
  synthesizer.setMidiName("AudioKit Synthesizer");

  // Setup sound generation & synthesizer based on AudioKit default settings
  in.begin(cfg);
}

/**
 * @brief
 */
void loop()
{
  // Loop function that continuously copies audio streams and processes audio actions.
  copier.copy();
  kit.processActions();
}