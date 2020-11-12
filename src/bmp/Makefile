PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = bitmap.o bitmapFileHeader.o bitmapDIBHeaderV4.o bitmapDIBHeader.o bitmapColorTable.o bitmapUtil.o colorSpaceEndpoints.o

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

#CFLAGS := -fPIC
#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

all:	$(OBJS)

libbmp.so:	$(OBJS)
	$(CXX) -shared -o $@ $(OBJS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr $(OBJS) libbitmap.so
