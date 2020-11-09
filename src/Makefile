PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = sup2srt.o
PGS_OBJS= pgsParser.o pgsSegment.o pgsSegmentHeader.o presentationCompositionSegment.o pgsUtil.o compositionObject.o windowDefinitionSegment.o windowSegment.o objectDefinitionSegment.o objectData.o paletteSegment.o paletteDefinitionSegment.o
PGS_PATH_OBJS = $(patsubst %.o,pgs/%.o,$(PGS_OBJS))
BMP_OBJS = bitmap.o bitmapFileHeader.o bitmapDIBHeaderV4.o bitmapDIBHeader.o bitmapColorTable.o
BMP_PATH_OBJS = $(patsubst %.o,bmp/%.o,$(BMP_OBJS))
SUB_DIRS = PGS BMP

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

#LDFLAGS := -I pgs -L pgs

all:	sup2srt

sup2srt:	$(SUB_DIRS) $(OBJS)
	$(CXX) $(LDFLAGS) sup2srt.o $(PGS_PATH_OBJS) $(BMP_PATH_OBJS) -o ../$@
	
%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

PGS:
	$(MAKE) -C pgs $(PGS_OBJS)

BMP:
	$(MAKE) -C bmp $(BMP_OBJS)
	
clean:
	$(MAKE) -C pgs clean
	$(MAKE) -C bmp clean
	rm -fr sup2srt $(OBJS)
