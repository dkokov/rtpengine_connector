#
# * rtpengine_connector Makefile *
#
#   Created by Dimitar Kokov ,dkokov75 at gmail dot com  (2023-11-02)
#
#   History:
#	2023-11-02, first version (init)
#   2023-11-03, edit install,unistall options
#

SHELL = /bin/sh
CC    = gcc

FLAGS   = -Wall
CFLAGS  = -fPIC -Ofast
LDFLAGS = -shared

OS = $(shell uname -s)
ifeq ($(OS),Linux)
	OS_BIN = /usr/local/sbin/
	OS_LIB = /lib/
	HOST_ARCH = $(shell uname -m)
#	LDLIBS += -lpthread
endif

# GCC version
GCC_VERSION = $(shell gcc -dumpversion)

ifneq ($(GCC_VERSION),12)
    $(error GCC version is not 12. Please use GCC version 12.)
endif

# CPU ARCH
ifeq ($(HOST_ARCH),x86_64)
	CFLAGS += -m64 -march=nocona -mtune=generic -mfpmath=sse -flto -funroll-loops
#	CFLAGS += -m64 -mfpmath=sse -flto -march=native -funroll-loops
#	CFLAGS += -m64 -mtune=generic -flto -funroll-loops -mavx2
else
ifeq ($(HOST_ARCH),i386)
	CFLAGS += -m32
endif
endif

DEBUG ?= 0
ifeq ($(DEBUG),1)
    FLAGS     += -g
    CFLAGS    += $(FLAGS) -DDEBUG_MEM
    LDFLAGS   += $(FLAGS)
endif

all:lib cli

CORE_DIR = ./

# rtpengine-connector lib
RTPENGINE_CONNECTOR_LIB  = $(CORE_DIR)librtpengc.so
RTP_SRC = $(shell echo $(CORE_DIR)*.c)
RTP_OBJS = $(RTP_SRC:.c=.o)
depends = $(RTP_SRC:.c=.d)

lib: $(RTP_OBJS) 
	$(CC) $(LDFLAGS) -o $(RTPENGINE_CONNECTOR_LIB) $(RTP_OBJS)

# rtpengine_connector_cli, main()
CLI_DIR = cli/
CLI_SRC = $(shell echo $(CLI_DIR)*.c)
CLI_OBJ = $(CLI_SRC:.c=.o)
CLI_TARGET = rtpengine_connector_cli

cli: $(CLI_OBJ)
	$(CC) $(FLAGS) -o $(CLI_TARGET) $(CLI_OBJ) $(LDLIBS) -L. -lrtpengc


.PHONY: clean
clean:
	@rm -fv $(RTPENGINE_CONNECTOR_LIB) $(RTP_OBJS) $(CLI_OBJ) $(CLI_TARGET)

.PHONY: help
help:
	-@echo ""
	-@echo " Help for rtpengine-connector make commands:"
	-@echo "  make                             - compiletion with gcc standart flags"
	-@echo "  make DEBUG=1                     - compiletion with gcc debug flags"
	-@echo "  make clean                       - remove all object,share libs and exe files from the src dir"
	-@echo "  make install                     - instalation "
	-@echo "  make uninstall                   - uninstalation"
	-@echo ""


.PHONY: install
install: lib cli
	@if [ -f $(CLI_TARGET) ]; then \
	    cp -fv $(CLI_TARGET) $(OS_BIN); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(CLI_TARGET)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi
	@if [ -f  $(RTPENGINE_CONNECTOR_LIB)]; then \
	    cp -fv $(RTPENGINE_CONNECTOR_LIB) $(OS_LIB); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(RTPENGINE_CONNECTOR_LIB)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi


.PHONY: uninstall
uninstall: clean
	@if [ -f $(OS_BIN)$(CLI_TARGET) ]; then \
	    rm -fv  $(OS_BIN)$(CLI_TARGET); \
	fi
	@if [ -f $(OS_BIN)$(RTPENGINE_CONNECTOR_LIB) ]; then \
	    rm -fv $(OS_BIN)$(RTPENGINE_CONNECTOR_LIB); \
	fi
