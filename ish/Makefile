CFLAGS  += -g -O1 -std=gnu99 -Wno-unused-result
LDFLAGS += -static

TARGET  = ish
OBJECTS = ish.o                   \
          ish_shell_utilities.o   \
          ish_cstring_utilities.o
SPECIAL_OBJECTS = ish_syscalls.o

.PHONY : all
all : $(TARGET)

$(TARGET) : $(OBJECTS) $(SPECIAL_OBJECTS)

$(OBJECTS) : %.o : %.c ish_common.h

$(SPECIAL_OBJECTS) : %.o : %.c ish_syscalls.amd64.c ish_syscalls.aarch64.c ish_common.h

.PHONY : clean
clean :
	rm -rf $(TARGET) $(OBJECTS) $(SPECIAL_OBJECTS)
