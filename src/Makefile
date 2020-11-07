PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = sup2srt.o 
PGSOBJS = $(patsubst %.o,pgs/%.o,pgsParser.o pgsSegment.o pgsSegmentHeader.o presentationCompositionSegment.o pgsUtil.o compositionObject.o windowDefinitionSegment.o windowSegment.o objectDefinitionSegment.o objectData.o paletteSegment.o paletteDefinitionSegment.o)
BMPOBJS = $(patsubst %.o,bmp/%.o,bitmap.o)
SHARED_OBJS = pgs/libpgs.so bmp/libbmp.so

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

sup2srt:	$(SHARED_OBJS) $(OBJS)
	$(CXX) $(LDFLAGS) sup2srt.o $(PGSOBJS) $(BMPOBJS) -o ../$@
	
%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

pgs/libpgs.so:
	$(MAKE) -C pgs

bmp/libbmp.so:
	$(MAKE) -C bmp
	
clean:
	$(MAKE) -C pgs clean
	rm -fr sup2srt $(OBJS)
