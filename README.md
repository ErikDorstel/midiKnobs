# midiKnobs
64 Knobs MIDI Controller with color display
### This Teensy 3.2 based MIDI controller supports 64 analog knobs (analog pots 10 kΩ) and converts the analog levels to MIDI Out.

The 64 analog inputs are demultiplexed to 4 analog lines by using four 74HC4067 circuits. The schematic is stored in the documentation folder.

The three bytes MIDI output has the following format:

    <0xBn><knob><value>

    0xB is the MIDI control change prefix
    n is the MIDI channel (0-15 configurable within the code)
    knob is the number of the analog input line (0-63) and also the MIDI controller number
    value is the analog level (0-127)

The program quickly scans for pots with changed values and immediately sends updates with the new values. A second slower loop not depends on level changes and sends updates for all pots within a 16 seconds interval with 1 second steps.

Optionally, a touch color display with ILI9341 controller chip is supported. The display shows the set MIDI parameters as a bar graph. The names of the bars can be edited in the "Display.h" file. The display support requires the following libraries:
- https://github.com/PaulStoffregen/Optimized_ILI9341
- https://github.com/PaulStoffregen/XPT2046_Touchscreen
