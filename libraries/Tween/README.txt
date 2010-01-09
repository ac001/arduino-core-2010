The Tween Class for AVR and Arduino

Part of LibInteract for AVR
Alexandre Quessy 2008 ~ BSD License (libre software)
http://wiki.dataflow.ws/LibInteract

This is a first working draft of a C class for motion tweening. It can be used to create chases with lights, or fades for audio. 

It works on Arduino. Just drop the whole "Tween" directory in your "<arduino directory>/hardware/librairies/" directory. 

The code is pure C, so you can rename *.cpp to *.c and use with a tiny AVR.
Doesn't use malloc nor free. This is a C class. It uses a C struct for storing the attributes. All function calls need a pointer to a variable of type Tween_t as a first argument. (such as &theVariable) Look for tutorials on pointers. 

The crucial maths are taken from the excellent easing equations from Robert Penner. Under a BSD-like License:
Easing Equations v1.5
  (c) 2003 Robert Penner, all rights reserved. May 1, 2003
  This work is subject to the terms in http://www.robertpenner.com/easing_terms_of_use.html.  

