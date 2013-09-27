CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -Wall


#no debug
CFLAGS = $(OPT) $(OTHER) -Wno-deprecated

#uncomment this line for debug build
# CFLAGS = $(DEBUG) $(OTHER)


MODULE = run
# sources files separated by spaces
SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

# Set these variables according to your configuration
SYSTEMC = /usr/local/systemc-2.3.0
SYSTEMCAMS = /usr/local/systemc-ams-1.0

# Target architecture eg. linux or linux64
TARGET_ARCH = linux


INCDIR = -I. -I$(SYSTEMC)/include -I$(SYSTEMCAMS)/include
LIBDIR = -L$(SYSTEMC)/lib-$(TARGET_ARCH) -L$(SYSTEMCAMS)/lib-$(TARGET_ARCH)

LIBS   = -lpthread -lsystemc -lsystemc-ams  $(EXTRA_LIBS)


EXE    = $(MODULE).x

.SUFFIXES: .cpp .o .x


$(EXE): $(OBJS) $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a $(SYSTEMCAMS)/lib-$(TARGET_ARCH)/libsystemc-ams.a
	$(CC) $(CFLAGS) $(LIBDIR) -o $@ $(OBJS) $(LIBS)


all: $(EXE)	
	
.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $<

clean::
	rm -f $(OBJS) *~ $(EXE) *.vcd
