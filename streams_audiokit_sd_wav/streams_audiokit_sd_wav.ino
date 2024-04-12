// Demonstrates how to use an encoder to write to a file

/**
 * class AudioInfo - https://pschatzmann.github.io/arduino-audio-tools/structaudio__tools_1_1_audio_info.html
 * @author Phil Schatzmann
 * @brief
 * @version 0.1
 * @date 2023-05-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <SD.h>
#include <SPI.h>

#include "AudioTools.h"
#include "AudioLibs/AudioBoardStream.h"

#include "AudioLibs/AudioSourceSD.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *file_name = "/rec.wav";

/**
 * To specify the format of an audio stream we need to know:
 *    how many bits are used to represent the integer
 *    how many channels are available
 *    the sample rate
 *
 * In this library the format is represented with the AudioInfo class.
 */
AudioInfo info(16000, 1, 16);
AudioBoardStream in(AudioKitEs8388V1);           // Configures ADC from microphones and line in
File file;                                       // final output stream
EncodedAudioStream out(&file, new WAVEncoder()); // Encoder Object
StreamCopy copier(out, in);                      // copies data
uint64_t timeout;                                // Period to record Sound

void setup()
{
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // setup input
  auto cfg = in.defaultConfig(RX_MODE); // Audio Sink in RX_MODE(board consumes audio signal)
  cfg.sd_active = true;
  cfg.copyFrom(info);                 // Copy audio configuration (16KHz sample rate, 1 channel, 16bits)
  cfg.input_device = ADC_INPUT_LINE2; // microphone and line in
  in.begin(cfg);                      // Start input

  // Open SD drive
  if (!SD.begin(PIN_AUDIO_KIT_SD_CARD_CS)) // Set SPI chip select pin and start SPI
  {
    Serial.println("Initialization failed!");
    stop();
  }

  // Cleanup if necessary
  if (SD.exists(file_name))
    SD.remove(file_name);

  // open file
  file = SD.open(file_name, FILE_WRITE);
  if (!file)
  {
    Serial.println("file failed!");
    stop();
  }

  // setup output stream
  out.begin(info);

  // set timeout - recoring for 5 seconds
  timeout = millis() + 5000;
}

void loop()
{
  if (millis() < timeout)
  {
    // record to wav file. Copy from ADC, encode to WAV format and dumo encoded audio to SD
    copier.copy();
  }
  else
  {
    // close file when done
    if (file)
    {
      file.flush();
      Serial.print("File has ");
      Serial.print(file.size());
      Serial.println(" bytes");
      file.close();
    }
  }
}
