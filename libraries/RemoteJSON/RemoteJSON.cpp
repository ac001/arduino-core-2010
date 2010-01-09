/*
 * RemoteJSON.cpp
 *
 */

#include <WiShield.h>
#include "WProgram.h"
#include <EEPROM.h>
#include <stdio.h>
#include "RemoteJSON.h"

char JSON_RESPONSE[] = {"{\"result\":"};
char JSON_TRUE[] = { "true }" };
char JSON_FALSE[] = { "false}" };

void RemoteJSON::init() {
  for (int i=0; i<SHARED_LEN; i++)
    shared[i] = 0;

  WiFi.init();
  WiFi.server_listen(8181);
}

void RemoteJSON::handleWeb() {
  unsigned int data_len;

  WiFi.driver_task();
  WiFi.stack_task();
  
  char* data = (char*)WiFi.data_available(&data_len);

  if (data_len > 0) {
    Serial.println(data);

    // Only handle GET requests
    if (memcmp(data, "GET /", 5) == 0) {

      unsigned int slash_count = 0;
      unsigned int space_count = 0;
      char c;
      char *cmd = NULL;
      char *arg1 = NULL;
      char *arg2 = NULL;
   
      for(int i=0; (c = *(data+i)); ++i) {
	if (c == '/') {

	  // parse cmd
	  if (slash_count == 0) {
	    cmd = (data+i+1);

	    // parse arg1
	  } else if (slash_count == 1) {
	    arg1 = (data+i+1);
	    *(data+i) = '\0';

	    // parse arg2
	  } else if (slash_count == 2) {
	    arg2 = (data+i+1);
	    *(data+i) = '\0';

	    // mark end arg2
	  } else if (slash_count == 3) {
	    *(data+i) = '\0';
	  }

	  slash_count++; 

	} else if (c == ' ') {
	  space_count++;
	}

	if (slash_count > 3 || space_count > 1)
	  break;
      }

      /* Serial.println("CMD:");
      Serial.println(cmd);

      Serial.println("ARGS:");
      Serial.println(arg1);
      Serial.println(arg2); */

      if (slash_count > 3 && (cmd) && (arg1) && (arg2)) {

	// commands with 2 args
	if (memcmp(cmd, "read_eeprom", 11) == 0) {
	  respond_read_eeprom(data, atoi(arg1), atoi(arg2));

	} else if (memcmp(cmd, "write_eeprom", 12) == 0) {
	  EEPROM.write(atoi(arg1), atoi(arg2));
	  send_true(data);

	} else if (memcmp(cmd, "write_dpin", 10) == 0) {
	  digitalWrite(atoi(arg1), atoi(arg2));
	  send_true(data);

	} else if (memcmp(cmd, "write_shared", 12) == 0) {
	  if (atoi(arg1) < SHARED_LEN) {
	    shared[atoi(arg1)] = atoi(arg2);
	    send_true(data);
	  } else {
	    send_false(data);
	  }

	} else {
	  send_false(data);
	}

	// commands with only one arg
      } else if (slash_count > 2 && (cmd) && (arg1)) {
	if (memcmp(cmd, "read_dpin", 9) == 0) {
	  send_int(data, digitalRead(atoi(arg1)));

	} else if (memcmp(cmd, "read_apin", 9) == 0) {
	  send_int(data, analogRead(atoi(arg1)));

	} else {
	  send_false(data);
	}

	// commands with no args
      } else if (slash_count > 1 && (cmd)) {
	if (memcmp(cmd, "read_shared", 11) == 0) {
	  send_int_arr(data, shared, SHARED_LEN);
	} else {
	  send_false(data);
	}
      }

      WiFi.stack_task();
    }
  }
}
   
void RemoteJSON::respond_read_eeprom(char* buffer, int start, int end) {
  int pos = strlen(JSON_RESPONSE);
  memcpy(buffer, JSON_RESPONSE, pos);

  *(buffer + pos++) = '[';

  for (int i = start; i<=end; i++) {
    pos += sprintf((buffer + pos), "%u", EEPROM.read(i));
    if ((i + 1) <= (end))
      *(buffer + pos++) = ',';

    /*    if (pos > 400) {
      U16 data_avail;
      WiFi.send_data(pos);
      WiFi.set_more_data(0);
      WiFi.stack_task();

      buffer = (char*) WiFi.data_available(&data_avail);
      WiFi.driver_task();
      WiFi.stack_task();
      pos = 0;
      }*/
  }

  // Close brackets
  *(buffer + pos++) = ']';
  *(buffer + pos++) = '}';

  WiFi.send_data(pos);
  WiFi.set_more_data(1);
}

void RemoteJSON::send_true(char* buffer) {
  int len1 = strlen(JSON_RESPONSE);
  int len2 = strlen(JSON_TRUE);
  memcpy(buffer, JSON_RESPONSE, len1);
  memcpy((buffer+len1), JSON_TRUE, len2);

  WiFi.send_data(len1+len2);
  WiFi.set_more_data(1);
}

void RemoteJSON::send_false(char* buffer) {
  int len1 = strlen(JSON_RESPONSE);
  int len2 = strlen(JSON_FALSE);
  memcpy(buffer, JSON_RESPONSE, len1);
  memcpy((buffer+len1), JSON_FALSE, len2);

  WiFi.send_data(len1+len2);
  WiFi.set_more_data(1);
}

void RemoteJSON::send_int(char* buffer, int val) {
  int pos = strlen(JSON_RESPONSE);
  memcpy(buffer, JSON_RESPONSE, pos);
  pos += sprintf((buffer + pos), "%u", val);

  // Close brackets
  *(buffer + pos++) = ']';
  *(buffer + pos++) = '}';

  WiFi.send_data(pos);
  WiFi.set_more_data(1);
}

void RemoteJSON::send_int_arr(char* buffer, unsigned int* arr, int len) {
  int pos = strlen(JSON_RESPONSE);
  memcpy(buffer, JSON_RESPONSE, pos);

  *(buffer + pos++) = '[';

  for (int i = 0; i<len; i++) {
    pos += sprintf((buffer + pos), "%u", *(arr+i));
    if ((i + 1) < (len))
      *(buffer + pos++) = ',';
  }

  // Close brackets
  *(buffer + pos++) = ']';
  *(buffer + pos++) = '}';

  Serial.println(buffer);

  WiFi.send_data(pos);
  WiFi.set_more_data(1);
 
}
