+++++++++++++++++++++++++++++++++++++++++++++++++
++ Arduino Staging Area
+++++++++++++++++++++++++++++++++++++++++++++++++

The idea of this repository is to create an initial staging
area for arduino and its libraries.

Its realised that the maintanance can be extensive, so this 
is an idea for upstream,..

* by pulling, from external resources, eg svn externals
* some consolidation of arduino's core
* skeleton configuration files
* installers for various platforms


/bin - contains all executables
/etc - all configs - on windows this lot would end up in ~user
/hardware - all the hardware related stuff
/library - all the extras
/installers - where the fun starts

+++++
The structure od this repository does not intend to replicate the installation,
it is rather the core requirements, so for example

* /etc/skel/settings.ini, could end on windows being at c:/user/docs/settings.ini, whilst with a prenguin at ~/.arduino/settings.ini
* whilst libraries may end up in /usr/lib/arduino/* ot c:\arduino\libraries\

