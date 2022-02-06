TOP      = $(shell pwd)

# OS Name (Linux or Darwin)
OSUPPER = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
OSLOWER = $(shell uname -s 2>/dev/null | tr [:upper:] [:lower:])

# Flags to detect 32-bit or 64-bit OS platform
OS_SIZE = $(shell uname -m | sed -e "s/i.86/32/" -e "s/x86_64/64/")
OS_ARCH = $(shell uname -m | sed -e "s/i386/i686/")

# Flags to detect either a Linux system (linux) or Mac OSX (darwin)
DARWIN = $(strip $(findstring DARWIN, $(OSUPPER)))

# OS-specific build flags
ifneq ($(DARWIN),)
    CXXFLAGS   := -arch $(OS_ARCH)
else
  ifeq ($(OS_SIZE),32)
    CXXFLAGS   := -m32
  else
    CXXFLAGS   := -m64
  endif
endif

MYMAKEFLAGS := 

# COMPILERS OPTIONS
ifneq ($(DARWIN),)
  CXX          := g++-mp-6
else
  CXX          := c++
endif

CXXFLAGS       += -std=c++11 -fPIC -Wall -pedantic
OPTIMFLAGS      = -O2 -funroll-loops -falign-loops=8 #-ffast-math

ARCHIVE      := ar
ARCHFLAG     := -rc

# Debug build flags
DEBUGVERSION := 0
ifeq ($(DEBUGVERSION),1)
  CXXFLAGS     += -DDEBUG=1 -ggdb -W -Wno-long-long
  MYMAKEFLAGS += DEBUGVERSION=1
else
   ifeq ($(PROFILEVERSION),1)
      CXXFLAGS     += -DDEBUG=1 -g -pg -Wall -pedantic $(OPTIMFLAGS)
      MYMAKEFLAGS += PROFILEVERSION=1
   else
      CXXFLAGS     += -DDEBUG=0 -Wall -pedantic $(OPTIMFLAGS)
   endif
endif

INCDEFS        :=  -include localdefs.h

# FILES
CPPOBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
CCOBJS=$(patsubst %.cc,%.o,$(wildcard *.cc))
OBJS= $(CPPOBJS) $(CCOBJS)
HEADERS=$(wildcard *.h)
SOURCES=$(wildcard *.cpp *.cc)
LIBOBJS=$(shell echo $(OBJS))
COMMONSTATICLIBNAME=$(shell cd ../..; pwd | sed -e 's;\(.*\)/\(.*\);\2;')
TESTEXECS=$(patsubst %.cc,%.x,$(wildcard *.cc))

# -L: FOLDER LIBRARY
LFLAGS+=#-L.

# -l: LIBRARY
lLIBS+= 

# -I: INCLUDES
IFLAGS+=-I. $(INCDEFS)

TARGET=target

$(TARGET): localdefs.h $(OBJS) $(TESTEXECS)

$(CPPOBJS): %.o: %.cpp %.h
	@echo "\033[32m   Compiling $@\\033[m"
	$(CXX) $(CXXFLAGS) -c $< -o $@  $(IFLAGS) 

$(CCOBJS): %.o: %.cc $(HEADERS)
	@echo "\033[32m   Compiling $@\\033[m"
	$(CXX) $(CXXFLAGS) -c $<  -o $@  $(IFLAGS) 

$(TESTEXECS): %.x: %.o $(CCOBJS) $(CPPOBJS) $(SOURCES) $(HEADERS)
	@echo "\033[32m   Linking $@\\033[m"
	$(CXX) $(LFLAGS) $(OPTIMFLAGS) $< $(CPPOBJS) -o $@

localdefs.h: 
	@echo "//Here you can define the macros that are used WITHIN"  > localdefs.h
	@echo "//this directory. Notice that the macros defined here" >> localdefs.h
	@echo "//affect ALL and every single *cc and *cpp source." >> localdefs.h
	@echo "#ifndef _LOCALDEFS_H_" >> localdefs.h
	@echo "#define _LOCALDEFS_H_" >> localdefs.h
	@echo "" >> localdefs.h
	@echo "#endif /* _LOCALDEFS_H_ */" >> localdefs.h

.PHONY: clean
clean:
	$(info CLEANING ALL)
	@$(RM) -f $(TARGET) $(OBJS) $(TESTEXECS) 2>/dev/null || true

.PHONY: fullclean
fullclean: clean

.PHONY: help
help: ## Shows this help
	@echo '=================================================================================='
	@echo 'usage: make [target] ...'
	@echo '=================================================================================='
	@echo ''
	@echo 'targets:'
	@egrep -e '^(.+)\:\ .*##\ (.+)' ${MAKEFILE_LIST} | sed 's/:.*##/#/' | column -t -c 2 -s '#'
	@echo ''
	@echo '=================================================================================='

list:
	@echo $(OBJS)
	@echo $(HEADERS)

listobjs:
	@echo $(LIBOBJS)

