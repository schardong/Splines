# BUILD SETTINGS ###########################################

TARGET := Splines

# FLAGS ####################################################

ifneq ($(MAKECMDGOALS), release)
    CONFIG := debug
    EXTRA_CXXFLAGS += -g3 -O0
else
    CONFIG := release
    EXTRA_CXXFLAGS += -g0 -O2 -DNDEBUG
endif

EXTRA_CXXFLAGS += -pedantic -Werror -Wall -Wextra -Wno-unused
ALL_CXXFLAGS += -std=c++0x -MMD -I./src -I include $(EXTRA_CXXFLAGS) $(CXXFLAGS)
ALL_LDFLAGS += -L lib $(LDFLAGS)
LDLIBS += -lglfw -lXrandr -lrt -lX11 -lGLU -lGL -pthread -lcoremath_$(CONFIG) -lm

############################################################

TARGET := bin/$(TARGET)
JUNK_DIR := bin/obj-$(CONFIG)

STRIP := strip

OBJS := $(shell find src -name *.cpp | sed "s/^src\///")
OBJS := $(foreach obj, $(OBJS:.cpp=.o), $(JUNK_DIR)$(obj))

# RULES ####################################################

.PHONY : all release clean

all : $(TARGET)

release : all
	@$(STRIP) $(TARGET)

clean :
	@rm -rf bin/*

ifneq ($(MAKECMDGOALS), clean)
    -include $(OBJS:.o=.d)
endif

$(TARGET) : $(OBJS)
	@$(CXX) -o $@ $(ALL_LDFLAGS) $^ $(LDLIBS)

$(JUNK_DIR)%.o : src/%.cpp
	@mkdir -p "$(dir $@)"
	@$(CXX) -c -o $@ $(ALL_CXXFLAGS) $<
