SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

## Variable that points to SystemC installation path
SYSTEMC = /usr/local/systemc-2.3.0

SYSTEMC_LIB = $(SYSTEMC)/lib-$(TARGET_ARCH)

TARGET_ARCH = linux

MODULE = exemplo

CC = g++

CFLAGS = -Wno-deprecated -Wall -g

INCDIR = -I. -I.. -I$(SYSTEMC)/include
LIBDIR = -L. -L.. -L$(SYSTEMC_LIB) -Wl,-rpath=$(SYSTEMC_LIB)

LIBS   =  -lstdc++ -lsystemc

EXE    = $(MODULE).x

# Based on Eclipse generated Makefile
$(EXE): $(OBJS) $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CC) $(LIBDIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt
	@echo 'Finished building target: $@'
	@echo ' '

# Based on Eclipse generated Makefile
%.o : %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(INCDIR) -O0 -g3 -w -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean:
	rm -f $(wildcard *.o) $(wildcard *.d) $(EXE)
