/*
 * RemoteJSON.h
 * ----------------------------------------------------
 * 
 * Listens on port 80 for a command and generates a JSON response.
 *
 * Valid commands:
 *  read_eeprom ( int start, int finish )
 *  write_eeprom( int loc, int value )
 *  write_dpin( int pin, int val )
 *  write_shared( int loc, int value )
 *  read_dpin( int pin )
 *  read_adpin( int pin )
 *  read_shared()
 *
 *
 * Requests are made in the following format:
 *  GET /<command>/<arg1>/<arg2>/
 *
 * ----------------------------------------------------
 *
 * For example, to read EEPROM from location 0 to 5 from a device at 10.0.0.1:
 *  http://10.0.0.1/read_eeprom/0/5
 *  
 *  Expected Response like:
 *  { "eeprom" : [0,0,0,0,0] }
 *
 */

#ifndef RemoteJSON_h
#define RemoteJSON_h

#include <WiShield.h>
#include <EEPROM.h>

#define SHARED_LEN 16

class RemoteJSON {

public:
  unsigned int shared[SHARED_LEN];
  void init();
  void handleWeb();

private:
  void respond_read_eeprom(char* buffer, int start, int end);

  void send_true(char* buffer);
  void send_false(char* buffer);
  void send_int(char* buffer, int val);
  void send_int_arr(char* buffer, unsigned int* arr, int len);
};

extern WiShield WiFi;


#endif
