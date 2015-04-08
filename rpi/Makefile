# ------------------------------------------------
# iHome Makefile
# Author: elmehdi@elfakir.me
# Date  : 12/01/2015
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = iHome_Start

# CC       = gcc
CC	= arm-linux-gcc
#CC	= arm-ihome-linux-gnueabi-gcc
#CC	= arm-ihome-linux-uclibcgnueabi-gcc
# compiling flags here
CFLAGS   = -std=c99 -g -O0 -Wall -I$(INCDIR) -I/home/el/xenomai_rpi/xenomai_rpi_buildroot/buildroot-2014.02/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/xenomai/

LINKER   = $(CC) -o
# linking flags here
LFLAGS   = -L/home/el/xenomai_rpi/xenomai_rpi_buildroot/buildroot-2014.02/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib -lnative -lxenomai -lbcm2835 -lcJSON

# change these to set the proper directories where each files shoould be
SRCDIR   = ./sources
INCDIR   = ./includes
OBJDIR   = ./objects
BINDIR   = ./bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER)  $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONEY: shared_lib
shared_lib:
	$(CC) -shared -o libihome.a $(OBJECTS) #-lbcm2835
