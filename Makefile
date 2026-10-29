TARGET = screenflip
OBJS = src/main.o src/rotate.o

INCDIR =
CFLAGS = -O2 -G0 -Wall -Wextra
CXXFLAGS = $(CFLAGS)
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

LIBS = -lpspdebug -lpspdisplay -lpspctrl -lpspthreadman -lpspkernel

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = ScreenFlip 1.0 (prototype)

include $(PSPSDK)/lib/build.mak
