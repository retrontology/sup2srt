PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = sup2srt.o srtUtil.o mkvUtil.o
PGS_OBJS= pgsParser.o pgsSegment.o pgsSegmentHeader.o presentationCompositionSegment.o pgsUtil.o compositionObject.o windowDefinitionSegment.o windowSegment.o objectDefinitionSegment.o paletteSegment.o paletteDefinitionSegment.o displaySegment.o
PGS_PATH_OBJS = $(patsubst %.o,pgs/%.o,$(PGS_OBJS))
SUB_DIRS = PGS
DISK = sup2disk.o mkvUtil.o 

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

#LDFLAGS := -I /usr/include
#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
LIBFLAGS := -ltiff -ltiffxx -llept -ltesseract -lavcodec -lavformat -lavutil

all:	sup2srt sup2disk

sup2srt:	$(SUB_DIRS) $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(PGS_PATH_OBJS) -o $@ ${LIBFLAGS}

sup2disk:	$(SUB_DIRS) $(DISK)
	$(CXX) $(LDFLAGS) ${DISK} $(PGS_PATH_OBJS) -o $@ ${LIBFLAGS}
	
%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $< ${LIBFLAGS}

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

PGS:
	$(MAKE) -C pgs $(PGS_OBJS)
	
clean:
	$(MAKE) -C pgs clean
	rm -fr sup2srt sup2disk $(OBJS) $(DISK)
