PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = pgsParser.o sup2srt.o pgsSegment.o pgsSegmentHeader.o presentationCompositionSegment.o pgsUtil.o compositionObject.o windowDefinitionSegment.o windowSegment.o

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

CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

all:	sup2srt

sup2srt:	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ 

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr sup2srt $(OBJS) build
