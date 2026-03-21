#compiler
CXX = g++
WARS = -Wall
INCS = -I .. -I /usr/include/freetype2
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
out_lib = dist/$(mode)/libcanvas.so
out_exe = Test/dist/$(mode)/test.out

#sources
src_lib := $(shell find -path './src/*.cpp')
src_exe := $(shell find -path './Test/src/*.cpp')

#objects
obj_lib = $(subst ./src/,build/$(mode)/,$(subst .cpp,.o,$(src_lib)))
obj_exe = $(subst ./Test/src/,Test/build/$(mode)/,$(subst .cpp,.o,$(src_exe)))

#dependencies
dep_lib = $(subst .o,.d,$(obj_lib))
dep_exe = $(subst .o,.d,$(obj_exe))

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
	@g++ -fopenmp -o $(out_exe) $(obj_exe) dist/$(mode)/libcanvas.so -l GL -l X11 -l glfw -l freetype
	@echo 'executable - $(mode): $@'

Test/build/$(mode)/%.o : Test/src/%.cpp Test/build/$(mode)/%.d
	@mkdir -p $(dir $@)
	@echo 'compiling - $(mode): $<'
	@$(CXX) $(CXXFLAGS) -c $< -o $@

build/$(mode)/%.o : src/%.cpp build/$(mode)/%.d
	@mkdir -p $(dir $@)
	@echo 'compiling - $(mode): $<'
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(dep_lib) : ;

$(dep_exe) : ;

-include $(dep_lib)

-include $(dep_exe)

clean :
	@rm -rf dist/$(mode)
	@rm -rf build/$(mode)
	@rm -rf Test/dist/$(mode)
	@rm -rf Test/build/$(mode)
	@echo 'clean - $(mode): complete!'

print-% :
	@echo $* = $($*)

.PHONY : all clean print-%