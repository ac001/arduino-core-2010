#!/bin/bash

echo "Pulling xbee-arduino"
svn checkout http://xbee-arduino.googlecode.com/svn/trunk/ ./libraries/xbee-arduino

echo "Remote- JSON"
svn checkout http://arduino-json.googlecode.com/svn/trunk/RemoteJSON ./libraries/RemoteJSON

echo "EDB - Extended Database"
svn checkout http://arduino-edb.googlecode.com/svn/trunk/ ./libraries/EDB

echo "Tone"
svn checkout http://arduino-tone.googlecode.com/svn/trunk/ ./libraries/Tone

