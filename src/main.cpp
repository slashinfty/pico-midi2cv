/**
 * Base logic
 * ----------
 * There are two main working modes: if the sequencer is playing (receives clock
 * signal or uses internal clock) then the incoming MIDI data is used for
 * setting the sequencer notes. If the sequencer is not playing then the MIDI
 * input is converted to CV and gate output.
 *
 * Building blocks (classes)
 * -------------------------
 * MidiHandler
 * - Sets up uart for incoming MIDI
 * - Parses MIDI using midi_parser library
 * - Saves notes in a note stack for last-note-priority output
 *
 * MidiToCV
 * - Looks up the MIDI channel setting. Note that MIDI channel setting is only
 *   scanned at boot. If you change the MIDI channel then you have to reboot
 *   the system.
 * - Sets dac CV voltage based on the midi_handler note stack
 * - Sets gate gpio
 * - Saves settings for MIDI to CV conversion (if there's any)
 *
 * Connections
 * -----------
 * midi_to_cv.attach(midi_handler)
 * midi_to_cv.attach(dac)
 *
 * Flashing
 * --------
 * DISCONNECT FROM POWER BEFORE FLASHING!!!!
 */

/*
 * C++ headers
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cstring>

/*
 * Pico headers
 */
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/adc.h"
#include "hardware/uart.h"

/*
 * Custom libraries
 */
#include <mcp48x2.h>

/*
 * Project headers
 */
#include "settings.h"
#include "midi_handler.h"
#include "midi_to_cv.h"

Settings settings;
MCP48X2 dac;
MidiHandler midi_handler;
MidiToCV midi_to_cv;

int main() {
    stdio_init_all();

    sleep_ms(2000);
    dac.init(DAC_SPI_PORT, GP_DAC_CS, GP_DAC_SCK, GP_DAC_MOSI);
    midi_handler.init();
    midi_to_cv.init();

    midi_to_cv.attach(&midi_handler);
    midi_to_cv.attach(&dac);

    while (1) {
        midi_to_cv.process();
    }

    return 0;
}
