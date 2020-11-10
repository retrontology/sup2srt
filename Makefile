PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
#else
#    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

MAKEFLAGS += --jobs=8
CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

all:	sup2srt

sup2srt:
	$(MAKE) -C src
	mv src/sup2srt .
	
clean:
	$(MAKE) -C src clean
	rm -fr sup2srt img
