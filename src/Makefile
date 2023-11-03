#
# * rtpengine_connector Makefile *
#
#   Created by Dimitar Kokov ,dkokov75 at gmail dot com  (2023-11-02)
#
#   History:
#	2023-11-02, first version (init)
# 
#

SHELL = /bin/sh
CC    = gcc

FLAGS   = -Wall
CFLAGS  = -fPIC -Ofast
LDFLAGS = -shared
#LDLIBS  = -lpq

# uname -p , print the processor type (non-portable)
# uname -s , print the kernel name
# uname -i , print the hardware platform (non-portable) 
# uname -m , print the machine hardware name

OS = $(shell uname -s)
ifeq ($(OS),Linux)
	OS_PREFIX = /usr/local/RateEngine/
	HOST_ARCH = $(shell uname -m)
#	LDLIBS += -lpthread
endif

# GCC version
GCC_VERSION = $(shell gcc -dumpversion)
ifeq ($(GCC_VERSION),12)
	#echo "ERROR..."
	#exit
endif

# CPU ARCH
ifeq ($(HOST_ARCH),x86_64)
	CFLAGS += -m64 -march=nocona -mtune=generic -mfpmath=sse -flto -funroll-loops
#	CFLAGS += -m64 -mfpmath=sse -flto -march=native -funroll-loops
# 2019-10-16,
#	CFLAGS += -m64 -mtune=generic -flto -funroll-loops -mavx2
else
ifeq ($(HOST_ARCH),i386)
	CFLAGS += -m32
endif
endif

DEBUG ?= 0
ifeq ($(DEBUG),1)
    FLAGS     += -g
#    CFLAGS    += $(FLAGS) -DDEBUG_MEM
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
	-@echo " Help for RateEngine make commands:"
	-@echo "  make                             - compiletion with gcc standart flags"
	-@echo "  make DEBUG=1                     - compiletion with gcc debug flags"
	-@echo "  make clean                       - remove all object,share libs and exe files from the src dir"
	-@echo "  make install                     - instalation with default PREFIX=/usr/local/RateEngine/"
	-@echo "  make install PREFIX=/usr/local   - instalation in define path in PREFIX="
	-@echo "  make uninstall                   - uninstalation from default path,PREFIX=/usr/local/RateEngine/"
	-@echo "  make uninstall PREFIX=/usr/local - uninstalation from define path in PREFIX="
	-@echo ""

PREFIX ?= $(OS_PREFIX)

LIBS_CFG = /etc/ld.so.conf.d/RateEngine.conf

BIN  = $(PREFIX)bin/
LIBS = $(PREFIX)libs/
CFG  = $(PREFIX)config/
SMP  = $(CORE_DIR)config/samples/*
_SMP  = $(CORE_DIR)config/samples/
LOG  = $(PREFIX)logs/
SS   = $(PREFIX)scripts/

.PHONY: install
install: RateEngine
	@if [ ! -d $(BIN) ]; then \
	    mkdir -p $(BIN); \
	fi
	@if [ -f $(MAIN_TARGET) ]; then \
	    cp -fv $(MAIN_TARGET) $(BIN); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(MAIN_TARGET)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi
	@if [ ! -d $(LIBS) ]; then \
	    mkdir -p $(LIBS); \
	fi
	@if [ -f $(RATING_LIB) ]; then \
	    cp -fv $(RATING_LIB) $(LIBS); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(RATING_LIB)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi
	@if [ -f $(CORE_LIB) ]; then \
	    cp -fv $(CORE_LIB) $(LIBS); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(CORE_LIB)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi
	@if [ -f $(CC_LIB) ]; then \
	    cp -fv $(CC_LIB) $(LIBS); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(CC_LIB)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi
	@if [ -f $(CDRM_LIB) ]; then \
	    cp -fv $(CDRM_LIB) $(LIBS); \
	else \
	    echo ""; \
	    echo "Installation ERROR! The file "$(CDRM_LIB)" is not found!"; \
	    echo ""; \
	    exit 1; \
	fi
	@if [ ! -f $(LIBS_CFG) ]; then \
	    echo $(LIBS) > $(LIBS_CFG); \
	    ldconfig; \
	fi
	@if [ ! -d $(CFG) ]; then \
	    mkdir -p $(CFG); \
	    cp -vR $(SMP) $(CFG);\
	else \
	    cp -vfR $(_SMP) $(CFG);\
	fi
	@if [ ! -d $(LOG) ]; then \
	    mkdir -p $(LOG); \
	fi
	@if [ ! -d $(SS) ]; then \
	    mkdir -p $(SS); \
	    cp -vR $(CORE_DIR)scripts/* $(SS); \
	fi


.PHONY: uninstall
uninstall:
	@if [ -d $(PREFIX) ]; then \
	    rm -fvR $(PREFIX); \
	fi
	@if [ -f $(LIBS_CFG) ]; then \
	    rm -fv $(LIBS_CFG); \
	fi


