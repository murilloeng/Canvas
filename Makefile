#compiler
CXX = g++
WARS = -Wall
INCS = -I .. -I ../external/cpp/inc
CXXFLAGS = -std=c++20 -fPIC -pipe -fopenmp -MT $@ -MMD -MP -MF $(subst .o,.d, $@) $(DEFS) $(INCS) $(WARS)

#mode
ifneq ($(m), r)
	mode = debug
	CXXFLAGS += -ggdb3
else
	mode = release
	CXXFLAGS += -Ofast
endif

#ouput
out_exe = Test/dist/$(mode)/test.out
out_lib = Canvas/dist/$(mode)/libcanvas.so

#sources
src_exe := $(sort $(shell find -path './Test/src/*.cpp'))
src_lib := $(sort $(shell find -path './Canvas/src/*.cpp'))

#objects
obj_exe = $(sort $(subst ./Test/src/, Test/build/$(mode)/, $(addsuffix .o, $(basename $(src_exe)))))
obj_lib = $(sort $(subst ./Canvas/src/, Canvas/build/$(mode)/, $(addsuffix .o, $(basename $(src_lib)))))

#dependencies
dep_exe = $(subst .o,.d, $(obj_exe))
dep_lib = $(subst .o,.d, $(obj_lib))

#rules
all : exe

run : exe
	./$(out_exe)

debug : exe
	gdb ./$(out_exe)

lib : $(out_lib)
	@echo 'library build - $(mode): complete!'

exe : lib $(out_exe)
	@echo 'executable build - $(mode): complete!'

$(out_lib) : $(obj_lib)
	@mkdir -p $(dir $@)
	@g++ -shared -o $(out_lib) $(obj_lib)
	@echo 'library - $(mode): $@'

$(out_exe) : $(obj_exe)
	@mkdir -p $(dir $@)
	@g++ -fopenmp -o $(out_exe) $(obj_exe) Canvas/dist/$(mode)/libcanvas.so -l GL -l X11 -l glfw -l freetype
	@echo 'executable - $(mode): $@'

Test/build/$(mode)/%.o : Test/src/%.cpp Test/build/$(mode)/%.d
	@echo 'compiling - $(mode): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

Canvas/build/$(mode)/%.o : Canvas/src/%.cpp Canvas/build/$(mode)/%.d
	@echo 'compiling - $(mode): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(dep_exe) : ;

$(dep_lib) : ;

-include $(dep_exe)

-include $(dep_lib)

clean :
	@rm -rf Test/dist/$(mode)
	@rm -rf Test/build/$(mode)
	@rm -rf Canvas/dist/$(mode)
	@rm -rf Canvas/build/$(mode)
	@echo 'clean - $(mode): complete!'

print-% :
	@echo $* = $($*)

.PHONY : all clean print-%