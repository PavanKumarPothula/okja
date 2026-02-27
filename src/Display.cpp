#include "Display.hpp"
#include "Arduino.h"

uint64_t count = 0;
lv_obj_t *display_text;

void ui_init()
{
    const auto screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x003a57), LV_PART_MAIN);

    display_text = lv_label_create(screen);
    lv_label_set_text(display_text, "Hello, world!");
    lv_obj_set_style_text_font(display_text, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(screen, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(display_text, LV_ALIGN_CENTER, 0, 0);
}

void setupDisplay()
{
    Display::init();
    ui_init();
}

void display_task(void *)
{
    setupDisplay();
    while (1)
    {
        ++count;
        std::array messages{"Oi!", "Bonjour!", "Hanloha!", "Ahoy!", "Aloha!", "Howdy!", "Hi-diddly-ho!"};
        lv_label_set_text(display_text, messages[count % messages.size()]);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}