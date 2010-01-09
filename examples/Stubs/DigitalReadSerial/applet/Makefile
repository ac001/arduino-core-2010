compile: do_compile

TARGET = $(notdir $(CURDIR))
INSTALL_DIR = ../../..
PORT = /dev/tty.usb*
UPLOAD_RATE = 19200
AVRDUDE_PROGRAMMER = stk500v1
MCU = atmega168
F_CPU = 16000000


ARDUINO = $(INSTALL_DIR)/hardware/cores/arduino
AVR_TOOLS_PATH = $(INSTALL_DIR)/hardware/tools/avr/bin
SRC =  $(ARDUINO)/pins_arduino.c $(ARDUINO)/wiring.c \
$(ARDUINO)/wiring_analog.c $(ARDUINO)/wiring_digital.c \
$(ARDUINO)/wiring_pulse.c $(ARDUINO)/wiring_serial.c \
$(ARDUINO)/wiring_shift.c $(ARDUINO)/WInterrupts.c
CXXSRC = $(ARDUINO)/HardwareSerial.cpp $(ARDUINO)/WMath.cpp \
$(ARDUINO)/Print.cpp
FORMAT = ihex


MAKEFILE = Makefile

DEBUG = stabs

OPT = s

CDEFS = -DF_CPU=$(F_CPU)
CXXDEFS = -DF_CPU=$(F_CPU)

CINCS = -I$(ARDUINO)
CXXINCS = -I$(ARDUINO)

CSTANDARD = -std=gnu99
CDEBUG = -g$(DEBUG)
CWARN = -Wall -Wstrict-prototypes
CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums

CFLAGS = $(CDEBUG) $(CDEFS) $(CINCS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA)
CXXFLAGS = $(CDEFS) $(CINCS) -O$(OPT)
LDFLAGS = -lm


AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:applet/$(TARGET).hex
AVRDUDE_FLAGS = -V -F -C $(INSTALL_DIR)/hardware/tools/avr/etc/avrdude.conf \
-p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) \
-b $(UPLOAD_RATE)

CC = $(AVR_TOOLS_PATH)/avr-gcc
CXX = $(AVR_TOOLS_PATH)/avr-g++
OBJCOPY = $(AVR_TOOLS_PATH)/avr-objcopy
OBJDUMP = $(AVR_TOOLS_PATH)/avr-objdump
AR  = $(AVR_TOOLS_PATH)/avr-ar
SIZE = $(AVR_TOOLS_PATH)/avr-size
NM = $(AVR_TOOLS_PATH)/avr-nm
AVRDUDE = $(AVR_TOOLS_PATH)/avrdude
REMOVE = rm -f
MV = mv -f

OBJ = $(SRC:.c=.o) $(CXXSRC:.cpp=.o) $(ASRC:.S=.o) 

LST = $(ASRC:.S=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_CXXFLAGS = -mmcu=$(MCU) -I. $(CXXFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)


all: applet_files build sizeafter

build: elf hex 

applet_files: $(TARGET).$(EXT)
	test -d applet || mkdir applet
	echo '#include "WProgram.h"' > applet/$(TARGET).cpp
	cat $(TARGET).$(EXT) >> applet/$(TARGET).cpp
	cat $(ARDUINO)/main.cxx >> applet/$(TARGET).cpp

elf: applet/$(TARGET).elf
hex: applet/$(TARGET).hex
eep: applet/$(TARGET).eep
lss: applet/$(TARGET).lss 
sym: applet/$(TARGET).sym

upload: applet/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)


HEXSIZE = $(SIZE) --target=$(FORMAT) applet/$(TARGET).hex
ELFSIZE = $(SIZE)  applet/$(TARGET).elf
sizebefore:
	@if [ -f applet/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f applet/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(HEXSIZE); echo; fi


COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 


coff: applet/$(TARGET).elf
	$(COFFCONVERT) -O coff-avr applet/$(TARGET).elf $(TARGET).cof


extcoff: $(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr applet/$(TARGET).elf $(TARGET).cof


.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

.elf.lss:
	$(OBJDUMP) -h -S $< > $@

.elf.sym:
	$(NM) -n $< > $@

	$(CC) $(ALL_CFLAGS) -o $@ applet/$(TARGET).cpp -L. applet/core.a $(LDFLAGS)

applet/core.a: $(OBJ)
	@for i in $(OBJ); do echo $(AR) rcs applet/core.a $$i; $(AR) rcs applet/core.a $$i; done



.cpp.o:
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

.c.o:
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 


.c.s:
	$(CC) -S $(ALL_CFLAGS) $< -o $@


.S.o:
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


%.d: %.c
	$(CC) -M $(ALL_CFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@

%.d: %.cpp
	$(CXX) -M $(ALL_CXXFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@


clean:
	$(REMOVE) applet/$(TARGET).hex applet/$(TARGET).eep applet/$(TARGET).cof applet/$(TARGET).elf \
	applet/$(TARGET).map applet/$(TARGET).sym applet/$(TARGET).lss applet/core.a \
	$(OBJ) $(LST) $(SRC:.c=.s) $(SRC:.c=.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.d)

.PHONY:	all build elf hex eep lss sym program coff extcoff clean applet_files sizebefore sizeafter

-e do_compile: do_build show_size
do_build: applet/$(TARGET).hex
applet/$(TARGET).hex: applet/$(TARGET).elf

ARDMAKE_BOARD=applet/board

applet/$(TARGET).elf: applet/$(TARGET).cpp applet/core.a
	$(CXX) $(ALL_CXXFLAGS) -Wl,--gc-sections $(LDFLAGS) -L. -Lapplet/ -o $@ $< applet/core.a
	@chmod a-x $@ >/dev/null 2>&1 || true

applet/$(TARGET).cpp: $(TARGET).$(EXT) $(ARDUINO)/main.cxx $(ARDUINO)/WProgram.h $(ARDMAKE_BOARD)
	echo '#include "WProgram.h"' >$@
	@echo '#line 1 "$<"' >>$@
	cat $(TARGET).$(EXT) >>$@
	@echo '#line 1 "$(ARDUINO)/main.cxx"' >>$@
	cat $(ARDUINO)/main.cxx >>$@

show_size:
	@echo
	@echo Program size:
	@$(HEXSIZE) | awk -v m="$(MAX_SIZE)" '{print;if(NR^1){s=$$4}} \
    END {printf("\n%d/%d bytes (%.1f%% of capacity, %d bytes left)\n\n",\
    s,m,s*100.0/m,m-s);}'

upload_autoreset: do_autoreset upload unreset

do_autoreset:
	@echo Sending reset to prepare for upload...
	( stty hupcl; sleep 0.1; true ) <$(PORT) 2>/dev/null
	@echo

unreset:
	@stty -hupcl <$(PORT) 2>/dev/null || true

$(OBJ): $(ARDMAKE_BOARD)
$(DEPS): $(ARDMAKE_BOARD)

$(APPC): applet/%.o: %.c
	$(CC) -c $(ALL_CFLAGS) -o $@ $<

$(APPCXX): applet/%.o: %.cpp
	$(CXX) -c $(ALL_CXXFLAGS) -o $@ $<

$(APPA): applet/%.o: %.S
	$(CC) -c $(ALL_ASFLAGS) -o $@ $<

$(APPC:.o=.d): applet/%.d: %.c
	$(CC) -M $(ALL_CFLAGS) $< | sed 's;^[^:]*:;applet/$*.o applet/$*.d:;' >$@

$(APPCXX:.o=.d): applet/%.d: %.cpp
	$(CXX) -M $(ALL_CXXFLAGS) $< | sed 's;^[^:]*:;applet/$*.o applet/$*.d:;' >$@

$(APPA:.o=.d): applet/%.d: %.S
	$(CC) -M $(ALL_ASFLAGS) $< | sed 's;^[^:]*:;applet/$*.o applet/$*.d:;' >$@

applet/$(TARGET).d: applet/$(TARGET).cpp

vpath %.c applet/ $(sort $(dir $(OBJC)))
vpath %.cpp applet/ $(sort $(dir $(OBJCXX)))
vpath %.S applet/ $(sort $(dir $(OBJA)))

include $(DEPS)
