# ESP32-A1S-AudioKit-Projects

This section contains a collection of well-documented Arduino starter sketches that utilize all the available audio functionality on the board.

## Dependencies

Install the following dependancies. Download the zip files from the following link:

- [arduino-audio-tools](https://github.com/pschatzmann/arduino-audio-tools) - This functionality provides the glue which makes different audio processing components and libraries work together.
- [arduino-audio-driver](https://github.com/pschatzmann/arduino-audio-driver) - An easy API to configure different audio codec chips. (AC101, ES8388, ES8311, CS43l22, ES7243)
- [arduino-libhelix](https://github.com/pschatzmann/arduino-libhelix) - A simple MP3 and AAC Decoder.
- [ESP32-A2DP](https://github.com/pschatzmann/ESP32-A2DP) - Provides an API for Bluetooth A2DP which can be used to receive sound data.

To install Arduino libraries from zip files, you have two options:

1. Using the Arduino IDE:

   - Open the Arduino IDE.
   - Go to "Sketch" > "Include Library" > "Add .ZIP Library".
   - Select the downloaded zip file and click "Open".
   - The library will be imported and ready to use.

2. Manually unzipping and copying the folder:
   - Locate your Arduino libraries folder. The default location is usually in your Documents folder under "Arduino/libraries".
   - Extract the contents of the downloaded zip file.
   - Copy the extracted folder into the Arduino libraries folder.
   - The library will be available for use in your Arduino sketches.

Remember to restart the Arduino IDE after installing the library.

# Basic Concepts

[Comprehensive guide to the arduino-audio-tools lib](https://github.com/pschatzmann/arduino-audio-tools/wiki)

Both the input and output of audio are handled via Arduino streams, so you can process them exactly the same way like files, Serial etc.

You can build your own sketch by replacing the input (source) and/or the output (sink) with an alternative implementation, or you can add a VolumeStream into the chain to control the volume.

For example, you can have an SD card source(input) and a CSV file stream as the output.

Here is a link to a list of the different implementations of audio sources and sinks:
[Audio-Sources-and-Sinks](https://github.com/pschatzmann/arduino-audio-tools/wiki/Audio-Sources-and-Sinks)

# Examples naming convention

All examples follow the following naming convention: "scenario type"-"source"-"destination". For the scenario types we might have base (using basic api functionality), stream for examples using Streams and test for the test cases.

For the source we currently have adc for analog input devices like analog microphones, i2s for digital input devices (e.g. digital microphones), file for SD files and a2dp for input from Bluetooth A2DP (e.g. from a Mobile Phone).

For the destination we use dac for analog output (e.g. to an amplifier), i2s for digital output devices (e.g. an external DAC), file for SD files and a2dp for output to Bluetooth A2DP (e.g. a Bluetooth Speaker).
