# midiKnobs
64 Knobs MIDI Controller
### This Teensy 3.2 based MIDI controller supports 64 analog knobs (analog pots 10 kΩ) and converts the analog levels to MIDI Out.

The 64 analog inputs are demultiplexed to 4 analog lines by using four 74HC4067 circuits. The schematic is stored in the documentation folder.

The three bytes MIDI output has the following format:

    <0xBn><knob><value>

    n is the MIDI channel (0-15 configurable within the code)
    knob is the number of the analog input line (0-63)
    value is the analog level (0-127)

The program quickly scans for pots with changed values and immediately sends updates with the new values. A second slower loop not depends on level changes and sends updates for all pots within a 16 seconds interval with 1 second steps.
