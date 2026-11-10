#include "bsp/board_api.h"
#include "class/midi/midi_device.h"
#include <hardware/gpio.h>
#include <stdbool.h>
#include "tusb.h"

typedef struct {
    int pin;
    uint8_t note;
    bool pressed;
} controller_key_t;

// TODO: create an array of controller_key_t that contains the GPIO pins and note of each key.

void midi_send_key_event(bool on, uint8_t channel, uint8_t key, uint8_t velocity) {
    // TODO: write code to send a midi key on/off message.
}

int main() {
    board_init();
    tusb_init();

    // TODO: init buttons

    while (true) {
        tud_task();

        // TODO: monitor inputs and send midi message depending on them.
    }
    return 0;
}

