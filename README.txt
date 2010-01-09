+++++++++++++++++++++++++++++++++++++++++++++++++
++ Arduino Staging Area
+++++++++++++++++++++++++++++++++++++++++++++++++

The intention of this repository is to create an initial staging
area for arduino core and its libraries. 

All libraries to be split up into packages eg
* Min requirement is code, compile+libs and boot-up-loader.
* without the Java. or IDE

This is an Experiment and is looking also at this project
http://www.arduino.cc/playground/Linux/Debian
http://git.debian.org/?p=collab-maint/arduino.git
Also links from here
* http://wiki.hands.com/chezfil/
** http://www.sjbaker.org/wiki/index.php?title=Command_line_Arduino
** http://www.johanneshoff.com/arduino-command-line.html
** http://mjo.tc/atelier/2009/02/arduino-cli.html


However, this project goes a bit further by including all the libraries also.
Such as servo timers, tcikers, pid, etc etc
In due source the API documentation (cunning plan).

Its realised that the maintanance can be extensive, so this 
is an idea for upstream, and experiment that will 
require community participation to be succesful.

* by pulling, from external resources, eg svn externals and automated scripts, tarballs
* by library authors, programmers and users pushing libs, examples, corrections, snippets.
* Makefile maintanace tweaking, arduino_make.sh
* installer configurations for various platforms
* skeleton configuration files

/bin - contains all executables
/etc - all configs - on windows this lot would end up in ~user
/hardware - all the hardware related stuff
/library - all the extras
/installers - where the fun starts

================================================================================================
The structure of this repository is as stash and staging area, and is not a direct installation.
It is rather a central collection of binaries, headers, etc with a steady "master" head from 
all the branches. Indeed it may end up being a bunch of script to checkout.

* /etc/skel/settings.ini, could end on windows being at c:/user/docs/settings.ini, whilst with a prenguin at ~/.arduino/settings.ini
* whilst libraries may end up in /usr/lib/arduino/* ot c:\arduino\libraries\

Means all of us need to be able to "push" here.. ;-))))

==============================
Deployment
============
its not sure the destination target of the files,
Thats where the installers/ will come in.

NSIS - windows
MSI - windows
deb - ubuntu and debian
rpm - yawn

more to follow....


