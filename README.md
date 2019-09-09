# midiKnobs
64 Knobs MIDI Controller
### This MIDI controller supports 64 analog knobs (analog pots 10 kΩ) and converts the analog levels to MIDI.

The 64 analog inputs are demultiplexed to 4 analog lines by using four 74HC4067 circuits. The schematic is stored in the documentation folder.

The three byte MIDI output has the following format:

    <0xBn><knob><value>

    n is the MIDI channel (0-15 configurable within the code)
    knob is the number of the analog input line (0-63)
    value is the analog level (0-127)

The program scans for pots with changed values and send the new values immediately. Regardless, all 64 values are updated within 16 seconds.
