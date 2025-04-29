#include "esphome.h"
char hexadecimal[10];

float string_to_float(String payload, int payload_len, float divider){
  String result;
  for (int i=payload_len-2;i>=0;i--){
      if(i%2 ==0){
        result = result+payload[i]+payload[i+1];

      }
  }
  return result.toInt()/divider;
}

char * decToHexa(int n) {
  // char array to store hexadecimal number
  char hexaDeciNum_invert[100];
  // counter for hexadecimal number array
  int i = 0;
  if (n == 0){
    hexadecimal[0] = '0';
    hexadecimal[1] = '0';
    hexadecimal[2] = '\0';
    return hexadecimal;
  }
  while (n != 0) {
    // temporary variable to store remainder
    int temp = 0;

    // storing remainder in temp variable.
    temp = n % 16;

    // check if temp < 10
    if (temp < 10) {
      hexaDeciNum_invert[i] = temp + 48;
    }
    else {
      hexaDeciNum_invert[i] = temp + 55;
    }
    i++;
    n = n / 16;
  }
  if (i<2){
    int i_old = i+(2-i);
    for (int j=i;j<i_old;j++){
      hexaDeciNum_invert[j] = '0';
      i++;
    }
  }
  //ESP_LOGD("custom","i int = %d", i);
  for (int j = i-1; j>=0;j--)
    hexadecimal[i-j-1] = hexaDeciNum_invert[j];
  hexadecimal[i] = '\0';
  //ESP_LOGD("custom","hexadeciaml = %s", hexadecimal);
  //ESP_LOGD("custom","hexaDeciNum_invert = %s", hexaDeciNum_invert);
  return hexadecimal;
}

namespace esphome {
  namespace zmai_90 {

void zmai_90::setup() {
    // This will be called by App.setup()
}
void zmai_90::update() {
  // This boooo
}

int zmai_90::readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;
  char* b;
  if (pos !=2 && buffer[pos-2] == 'F' && buffer[pos-1] == 'E'){
    ESP_LOGD("custom","pos = %d, buffer = %s", pos, buffer);
    buffer[0] = 'F';
    buffer[1] = 'E';
    buffer[2] =0;
    pos = 2;
  }
  switch (readch) {
    case '\n': // Ignore new-lines
      rpos = pos;
      pos = 0;  // Reset position index ready for next time
      return rpos;
    default:
      if (pos < len-1) {
        b = decToHexa(readch);
        //ESP_LOGD("custom","b = %s", b);
        for (int i=0; i<sizeof(b);i++){
          if (b[i] == '\0'){
            break;
          }
          buffer[pos++] = b[i];
        }
        buffer[pos] = 0;
      }
  }
  if (pos>72){
    rpos = pos;
    pos = 0; // Reset position index ready for next time
    return rpos;
  }
  // No end of line has been found, so return -1.
  return -1;
}


void zmai_90::loop() {
  const int max_line_length = 150;
  static char buffer[max_line_length];
  static int d;
  while (available()) {
    if (readline(read(), buffer, max_line_length)>0){
      //ESP_LOGD("custom","so entrato");
      String serial_result = String(buffer);
      serial_result.trim();
      if(serial_result[0] == 'F' && serial_result[1] == 'E' &&
        serial_result[2] == '0' && serial_result[3] == '1'){
  
      if (this-> voltage_sensor_ != nullptr)
        this-> voltage_sensor_->publish_state(string_to_float(serial_result.substring(14,22),8,10.0));
      if (this-> current_sensor_ != nullptr)
        this-> current_sensor_->publish_state(string_to_float(serial_result.substring(22,30),8,10000.0));
      if (this-> frequency_sensor_ != nullptr)
        this->frequency_sensor_->publish_state(string_to_float(serial_result.substring(30,38),8,100.0));
      if (this-> active_power_sensor_ != nullptr)
        this -> active_power_sensor_ ->publish_state(string_to_float(serial_result.substring(38,46),8,100.0));
      if (this-> reactive_power_sensor_ != nullptr)
        this-> reactive_power_sensor_ ->publish_state(string_to_float(serial_result.substring(46,54),8,100.0));
      if (this-> apparent_power_sensor_ != nullptr)
        this->apparent_power_sensor_ ->publish_state(string_to_float(serial_result.substring(54,62),8,100.0));
      if (this-> power_factor_sensor_ != nullptr)
        this-> power_factor_sensor_ ->publish_state(string_to_float(serial_result.substring(62,70),8,10.0));
      if (this-> consumed_energy_sensor_ != nullptr)
        this -> consumed_energy_sensor_->publish_state(string_to_float(serial_result.substring(6,14),8,100.0));
    }
  }

  }
  
}
  }
}
