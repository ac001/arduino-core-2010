/*
  Twitter.cpp - Arduino library to Post messages to Twitter.
  Copyright (c) NeoCat 2009. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 */

#include "Twitter.h"

static uint8_t server[] = {128,121,146,228}; // IP addr of twitter.com

Twitter::Twitter(const char *user_and_passwd) : client(server, 80)
{
	mimeEncode(user_and_passwd);
}

static char mime_code(const char c)
{
	if (c < 26) return c+'A';
	if (c < 52) return c-26+'a';
	if (c < 62) return c-52+'0';
	if (c == 62) return '+';
	return '/';
}

void Twitter::mimeEncode(const char *buf)
{
	int i = 0, j = 0, c[3];
	while (j < 64 && buf[i]) {
		c[0] = buf[i++];
		c[1] = buf[i] ? buf[i++] : 0;
		c[2] = buf[i] ? buf[i++] : 0;
		mime[j++] = mime_code(c[0]>>2);
		mime[j++] = mime_code(((c[0]<<4)&0x30) | (c[1]>>4));
		mime[j++] = c[1] ? mime_code(((c[1]<<2)&0x3c) | (c[2]>>6)) : '=';
		mime[j++] = c[2] ? mime_code(c[2]&0x3f) : '=';
	}
	mime[j] = 0;
}

static int strlen(const char *msg)
{
	int i = 0;
	while (msg[i++]);
	return i-1;
}

bool Twitter::post(const char *msg)
{
	parseStatus = 0;
	statusCode = 0;
	if (client.connect()) {
		client.println("POST /statuses/update.json HTTP/1.0");
		client.print("Authorization: Basic ");
		client.println(mime);
		client.print("Content-Length: ");
		client.println(strlen(msg)+7);
		client.println();
		client.print("status=");
		client.println(msg);
	} else {
		return false;
	}
	return true;
}

bool Twitter::checkStatus(void)
{
	if (!client.connected()) {
		client.flush();
		client.stop();
		return false;
	}
	if (!client.available())
		return true;
	char c = client.read();
	switch(parseStatus) {
	case 0:
		if (c == ' ') parseStatus++; break;  // skip "HTTP/1.1 "
	case 1:
		if (c >= '0' && c <= '9') {
			statusCode *= 10;
			statusCode += c - '0';
		} else {
			parseStatus++;
		}
	}
	return true;
}

int Twitter::wait(void)
{
	while (checkStatus());
	return statusCode;
}
