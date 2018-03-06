CXX := g++
CXXFLAGS := -std=gnu++11

ifneq ($(D),)
CXXFLAGS += -g -DDEBUG
endif

all: cache_simulator

objs := \
	cache.o \
	direct_mapped.o \
	main.o \
	memory.o \
	non_blocking.o \
	processor.o \
	set_assoc.o \
	sram_array.o \
	tag_array.o \
	ticked_object.o

DEPFLAGS = -MMD -MF $(@:.o=.d)
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

cache_simulator: $(objs)
	@echo "CXX	$@"
	@$(CXX) $^ -o $@

%.o: %.cc
	@echo "CXX	$@"
	@$(CXX) $(CXXFLAGS) -o $@ -c $< $(DEPFLAGS)

clean:
	@echo "CLEAN	$(shell pwd)"
	@rm -f $(objs) $(deps)

.PHONY: all clean
