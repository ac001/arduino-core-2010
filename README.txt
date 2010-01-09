+++++++++++++++++++++++++++++++++++++++++++++++++
++ Arduino Staging Area
+++++++++++++++++++++++++++++++++++++++++++++++++

The idea of this repository is to create an initial staging
area for arduino core and its libraries. 
Ie without the Java. Min requirement is code, compile+libs and boot-up-loader.

Its realised that the maintanance can be extensive, so this 
is an idea for upstream, and experiment that will 
require comminity participation to be succesful.

* by pulling, from external resources, eg svn externals and automated scripts
* by library authors pushing
* make file maintanace tweaking
* installer configurations for various platforms
* skeleton configuration files

/bin - contains all executables
/etc - all configs - on windows this lot would end up in ~user
/hardware - all the hardware related stuff
/library - all the extras
/installers - where the fun starts

+++++
The structure of this repository is as stash and staging area, and is not a direct installation.
It is rather a central collection of binaries, headers, etc with a steady "master" head from all the branches.

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

