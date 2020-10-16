#ifndef INCLUDED_THERMOSTAT_UI
#define INCLUDED_THERMOSTAT_UI

#include <sstream>

#include <Adafruit_GFX.h> 
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSerifBold24pt7b.h>

#include "ThermostatState.h"
#include "OverrideAdafruit_SSD1675.h"

// 'fire-exp', 42x67px
const unsigned char fire [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x1c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x1c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x1c, 0x00, 0x00, 
  0x00, 0x01, 0x80, 0x1c, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x7c, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x7c, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x70, 0x7c, 0x00, 0x00, 0x00, 0x00, 
  0x71, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x71, 0xfc, 0x00, 0x00, 0x00, 0xc0, 0x73, 0xfc, 0x00, 0x00, 
  0x00, 0xc0, 0x77, 0xfc, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0xfc, 
  0x00, 0x00, 0x00, 0xf0, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x31, 
  0xff, 0xfc, 0x00, 0x00, 0x00, 0x31, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x33, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x33, 0xff, 0xff, 0x86, 0x00, 0x00, 0x37, 0xff, 0xff, 0xc6, 0x00, 0x00, 0x37, 0xff, 0xff, 
  0xc6, 0x00, 0x00, 0x37, 0xff, 0xff, 0xc6, 0x00, 0x18, 0x37, 0xff, 0xff, 0xe6, 0x00, 0x18, 0x3f, 
  0xff, 0xff, 0xe6, 0x00, 0x07, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x07, 0x3f, 0xff, 0xff, 0xfe, 0x00, 
  0x07, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x07, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x07, 0x3f, 0xf1, 0xff, 
  0xfe, 0x00, 0x07, 0x3f, 0xf1, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xef, 0xff, 0xfe, 0x00, 0x07, 0xff, 
  0xef, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xef, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xf7, 0xff, 0xfe, 0x00, 
  0x07, 0xff, 0xc9, 0x7f, 0xfe, 0x00, 0x07, 0xff, 0xc9, 0x3f, 0xfe, 0x00, 0x07, 0xff, 0xb6, 0xdf, 
  0xfe, 0x00, 0x07, 0xff, 0x6d, 0x6f, 0xfe, 0x00, 0x07, 0xff, 0xdb, 0xb7, 0xfe, 0x00, 0x07, 0xfe, 
  0xb6, 0xdb, 0xfe, 0x00, 0x07, 0xff, 0x5d, 0x6f, 0xfe, 0x00, 0x07, 0xff, 0x6b, 0xb7, 0xfe, 0x00, 
  0x07, 0xfd, 0xb6, 0xdb, 0xfe, 0x00, 0x07, 0xfa, 0xdb, 0x6f, 0xf8, 0x00, 0x07, 0xff, 0x6d, 0xb7, 
  0xf8, 0x00, 0x07, 0xf5, 0xb6, 0xdb, 0xf8, 0x00, 0x07, 0xfa, 0xdb, 0x6f, 0xf8, 0x00, 0x07, 0xfb, 
  0x6d, 0xb7, 0xc0, 0x00, 0x07, 0xfd, 0xb6, 0xd7, 0xc0, 0x00, 0x07, 0xfa, 0xdb, 0x6f, 0xc0, 0x00, 
  0x07, 0xfb, 0x6d, 0xbf, 0xc0, 0x00, 0x07, 0xff, 0xb6, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xff, 
  0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00
};


namespace Thermostat {

  struct Display {
    const static int SD_CS     = 14;
    const static int SRAM_CS   = 32;
    const static int EPD_CS    = 15;
    const static int EPD_DC    = 33;
    const static int EPD_RESET = -1; // can set to -1 and share with microcontroller Reset!
    const static int EPD_BUSY  = 27; // can set to -1 to not use a pin (will wait a fixed delay)
    OverrideAdafruit_SSD1675 epd;
    bool convert_temperature_to_f;

    // font for the temperature
    const GFXfont *temp_font = &FreeSerifBold24pt7b;
    
    // font for the function text
    const GFXfont *func_font = &FreeSans9pt7b;
    
    // font for detail text (NULL means default, which is small)
    const GFXfont *detail_font = NULL;

    Display() :epd(250, 122, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY) {
    }

    void setup() {
      epd.begin();
      epd.clearBuffer();
      epd.setTextWrap(false);
      epd.clearDisplay();
    }

    void print_temperature(float temperature, int slot) {

      int display_temperature = int(temperature);
      std::string unit = "C";
      if (convert_temperature_to_f) {
        display_temperature = int((temperature * 9 / 5) + 32);
        unit = "F";
      }
      
      std::stringstream temperature_ss;
      temperature_ss << display_temperature;
      std::string temperature_str = temperature_ss.str();

      epd.setFont(temp_font);
      int16_t t_x,t_y;
      uint16_t t_w,t_h;
      epd.getTextBounds(temperature_str.c_str(), 0, 0, &t_x, &t_y, &t_w, &t_h);

      epd.setFont(func_font);
      int16_t u_x,u_y;
      uint16_t u_w,u_h;
      epd.getTextBounds(temperature_str.c_str(), 0, 0, &u_x, &u_y, &u_w, &u_h);

 
      // split display in 2, center in each half
      int offset_x = slot * (epd.width()/2);
      int center_x = epd.width()/4;
      int cursorx = offset_x + center_x - (t_w/2 + u_w/2);
      int cursory = epd.height()/2 + t_h/2;
      epd.setTextColor(EPD_BLACK);
      epd.setFont(temp_font);
      epd.setCursor(cursorx, cursory);
      epd.print(temperature_str.c_str());

      Serial.println("Temperature Text: " + String(cursorx) + " " + String(cursory) + " " + String(t_w) + " " + String(t_h));

      cursorx = offset_x + center_x - (t_w/2 + u_w/2) + t_w + 5;
      cursory = epd.height()/2 - t_h/2 + u_h;
      epd.setTextColor(EPD_BLACK);
      epd.setFont(func_font);
      epd.setCursor(cursorx, cursory);
      epd.print(unit.c_str());

      Serial.println("Unit Text: " + String(cursorx) + " " + String(cursory) + " " + String(u_w) + " " + String(u_h));

    }

    void draw_fixed_elements(int rect_height, int margin) {
      
      epd.drawRect(margin, margin, epd.width() - margin*2, epd.height() - margin*2, EPD_BLACK);
      epd.fillRect(margin*2, margin*2, epd.width() - margin*4, rect_height, EPD_BLACK);

      epd.setTextColor(EPD_INVERSE);
      epd.setFont(func_font);

      int16_t x,y;
      uint16_t w,h;

      epd.getTextBounds("ACTUAL", 0, 0, &x, &y, &w, &h);
      epd.setCursor(epd.width()/4 - w/2, (rect_height+margin*2)/2 + h/2);
      epd.print("ACTUAL");

      epd.getTextBounds("SET", 0, 0, &x, &y, &w, &h);
      epd.setCursor(epd.width()/4*3 - w/2, (rect_height+margin*2)/2 + h/2);
      epd.print("SET");
      
    }

    void print_humidity(float humidity, int rect_height, int margin) {
      
      epd.setTextColor(EPD_INVERSE);
      epd.setFont(func_font);

      int16_t x,y;
      uint16_t w,h;

      std::stringstream ss;
      ss << "Humidity: " << int(humidity) << "%";
      std::string str = ss.str();

      epd.getTextBounds(str.c_str(), 0, 0, &x, &y, &w, &h);
      epd.setCursor(epd.width()/2 - w/2, (epd.height() - margin*2 - rect_height/2) + h/2);
      epd.print(str.c_str());
    }

    void update(const State& state) {
      // start with the temperatures
      epd.clearBuffer();
      epd.setTextSize(1);
      int rect_height = 25;
      int margin = 2;
      
      draw_fixed_elements(rect_height, margin);
      print_temperature(state.actual_temperature, 0);
      print_temperature(state.set_temperature, 1);
      print_humidity(state.actual_humidity, rect_height, margin);

      if (state.relay_state) {
        epd.drawBitmap(epd.width()/2 - 42/2, epd.height()/2 - 67/2 + 1, fire, 42, 67, EPD_BLACK);
      }

      epd.display();
    }
  };

  struct PushButton {
    int pin;
    PushButton(int p) :pin(p) {
    }
    void setup() {
      pinMode(pin, INPUT);
    }
    bool is_pressed() {
      return digitalRead(pin) ? 1 : 0;
    }
  };

  struct UI {
    Display display;
    PushButton temp_down_button;
    PushButton temp_up_button;
    PushButton func_button;
    bool last_temp_up_button_state;
    bool last_temp_down_button_state;
    bool last_func_button_state;
    State last_displayed_state;
    UI() :temp_down_button(34), temp_up_button(39), func_button(36) {
    }
    void setup() {
      display.setup();
      temp_down_button.setup();
      temp_up_button.setup();
      func_button.setup();
    }
    void update(State &state) {
      // check button states
      bool must_update_screen = 0;
      if (last_temp_up_button_state ^ temp_up_button.is_pressed()) {
        if (!last_temp_up_button_state) {
          Serial.println("Temp up pressed");
          state.set_temperature++;
          must_update_screen = 1;
        }
        last_temp_up_button_state = !last_temp_up_button_state;
      }
      if (last_temp_down_button_state ^ temp_down_button.is_pressed()) {
        if (!last_temp_down_button_state) {
          Serial.println("Temp down pressed");
          state.set_temperature--;
          must_update_screen = 1;
        }
        last_temp_down_button_state = !last_temp_down_button_state;
      }
      if (last_func_button_state ^ func_button.is_pressed()) {
        if (!last_func_button_state) {
          Serial.println("Func pressed");
          display.convert_temperature_to_f = !display.convert_temperature_to_f;
          must_update_screen = 1;
        }
        last_func_button_state = !last_func_button_state;
      }
      // see if thermostat state changed enough to trigger an update
      if (abs(state.actual_temperature - last_displayed_state.actual_temperature) > 0.5 ||
          abs(state.actual_humidity - last_displayed_state.actual_humidity) > 2.5 ||
          state.relay_state != last_displayed_state.relay_state ||
          state.online != last_displayed_state.online) {
        must_update_screen = 1;
      }
      if (must_update_screen) {
        last_displayed_state = state;
        Serial.println("Will update Screen");
        display.update(state);
        Serial.println("Screen update complete");
      }
    }
  };

}

#endif
