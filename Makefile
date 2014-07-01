#
#  Makefile 
#     make tmpdir (creation of temporary directory)
#     make all    (compilation and link)
#     make clean  (delete compilation files and exe)
#
################################################################################
# i would to thanks vawjr and laurent for their help in the write of this makefile
###############################################################################

EXE = snice
DISTDIR = dist
SRCDIR = src
OBJDIR = build

CPP = g++
#OS = Linux
OS = Win
#DEBUG = no
DEBUG = yes

# Every subdirectory with source files must be described here
SUBDIRS := xml widget nodes dialog .


ifeq ($(DEBUG),yes)
	CFLAGS=-I. -Isrc -Ixml -O0 -g -fno-inline -c -fmessage-length=0
else
	CFLAGS=-Isrc -Ixml -O0 -c -fmessage-length=0
endif

RM := rm -rf

# All Target
all: outbin

# All of the sources participating in the build are defined here
-include $(SUBDIRS:%=$(SRCDIR)/%/subdir.mk)

# list of all the cpp source file in the directories
CPP_SRCS =
CPP_SRCS += $(wildcard $(SUBDIRS:%=$(SRCDIR)/%/*.cpp))

# OS specific
ifeq ($(OS),Win)
	LIBS = -lglfw -lopengl32 -ltinyxmld
	LIBS_DIRS = -Llib/
	CPP_SRCS := $(CPP_SRCS:$(SRCDIR)/./file_system_posix.cpp=)
endif

ifeq ($(OS),Linux)
	LIBS =-lGL -lglfw
	LIBS_DIRS = -L/usr/lib/ -Llib/
	CPP_SRCS := $(CPP_SRCS:$(SRCDIR)/./file_system_win.cpp=)
endif


# add the prefix to create files at the rigth place
OBJS = $(addprefix $(OBJDIR), $(addprefix /, $(notdir $(CPP_SRCS:.cpp=.o))))


ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif


# Tool invocations
$(EXE): $(OBJS)
	@echo 'Building target: $@ for $(OS)'
	@echo 'Invoking: GCC C++ Linker'
	@echo '$(CPP) $(LIBS_DIRS) -o$(addprefix $(DISTDIR), $(addprefix /, $(EXE))) $(OBJS) $(LIBS)'
	@$(CPP) $(LIBS_DIRS) -o$(addprefix $(DISTDIR), $(addprefix /, $(EXE))) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

outbin: $(EXE)
	@echo 'copy extra files'
	@cp $(SRCDIR)/Data/* $(DISTDIR)/Data/
	

# Other Targets
clean:
	$(RM) $(OBJS) $(DEPS)
	@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include $(ROOT)/makefile.targets
