// Records sound/audio input from microphones and line in,
// and replays it to speaker channele and line out

/**
 * class StreamCopy - https://pschatzmann.github.io/arduino-audio-tools/classaudio__tools_1_1_stream_copy.html
 */

#include "AudioTools.h"
#include "AudioLibs/AudioBoardStream.h"

AudioBoardStream kit(AudioKitEs8388V1); // Configures ADC and DAC
StreamCopy copier(kit, kit);

// Arduino Setup
void setup(void)
{
    Serial.begin(115200);
    AudioLogger::instance().begin(Serial, AudioLogger::Warning);

    // Setup input and output.
    // In RXTX_MODE is microcontroler is Source and Sink at the same time!
    auto cfg = kit.defaultConfig(RXTX_MODE);
    cfg.sd_active = false;
    cfg.input_device = ADC_INPUT_LINE2;
    kit.begin(cfg);
}

// Arduino loop - copy data
void loop()
{
    copier.copy(); // Copies all bytes from the input to the output.
}
