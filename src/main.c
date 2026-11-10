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

controller_key_t keys[] = {
    {.pin = 9,      .note = 60}, // C
    {.pin = 10,     .note = 62}, // D
    {.pin = 11,     .note = 64}, // E
    {.pin = 12,     .note = 65}, // F
    {.pin = 13,     .note = 67}, // G
    {.pin = 14,     .note = 69}, // A
    {.pin = 15,     .note = 71}, // B
};

void midi_send_key_event(bool on, uint8_t channel, uint8_t key, uint8_t velocity) {
    channel &= 0b00001111;
    key &= 0b01111111;
    velocity &= 0b01111111;

    // read incoming midi events
    while (tud_midi_available()) {
        uint8_t packet[4];
        tud_midi_packet_read(packet);
    }

    uint8_t message[3] = { (on ? 0x90 : 0x80) | channel, key, velocity };

    tud_midi_stream_write(0, message, 3);
}

int main() {
    board_init();
    tusb_init();

    // init buttons
    for (size_t i = 0; i < 7; i++) {
        gpio_init(keys[i].pin);
        gpio_set_dir(keys[i].pin, false); // false for input
        gpio_pull_down(keys[i].pin);
    }

    while (true) {
        tud_task();

        for (size_t i = 0; i < 7; i++) {
            bool state = gpio_get(keys[i].pin);

            // from off to on
            if (!keys[i].pressed && state) {
                midi_send_key_event(true, 0, keys[i].note, 100);
            }

            // from on to off
            if (keys[i].pressed && !state) {
                midi_send_key_event(false, 0, keys[i].note, 100);
            }

            keys[i].pressed = state;
        }
    }
    return 0;
}
