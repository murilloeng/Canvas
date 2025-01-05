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
out_man = Managers/dist/$(mode)/libmanagers.so

#sources
src_exe := $(sort $(shell find -path './Test/src/*.cpp'))
src_lib := $(sort $(shell find -path './Canvas/src/*.cpp'))
src_man := $(sort $(shell find -path './Managers/src/*.cpp'))

#objects
obj_exe = $(sort $(subst ./Test/src/, Test/build/$(mode)/, $(addsuffix .o, $(basename $(src_exe)))))
obj_lib = $(sort $(subst ./Canvas/src/, Canvas/build/$(mode)/, $(addsuffix .o, $(basename $(src_lib)))))
obj_man = $(sort $(subst ./Managers/src/, Managers/build/$(mode)/, $(addsuffix .o, $(basename $(src_man)))))

#dependencies
dep_exe = $(subst .o,.d, $(obj_exe))
dep_lib = $(subst .o,.d, $(obj_lib))
dep_man = $(subst .o,.d, $(obj_man))

#rules
all : exe

run : exe
	./$(out_exe)

debug : exe
	gdb ./$(out_exe)

lib : $(out_lib)
	@echo 'library build - $(mode): complete!'

man : $(out_man)
	@echo 'managers build - $(mode): complete!'

exe : lib man $(out_exe)
	@echo 'executable build - $(mode): complete!'

$(out_lib) : $(obj_lib)
	@mkdir -p $(dir $@)
	@g++ -shared -o $(out_lib) $(obj_lib)
	@echo 'library - $(mode): $@'

$(out_man) : $(obj_man)
	@mkdir -p $(dir $@)
	@g++ -shared -o $(out_man) $(obj_man)
	@echo 'managers - $(mode): $@'

$(out_exe) : $(obj_exe)
	@mkdir -p $(dir $@)
	@g++ -fopenmp -o $(out_exe) $(obj_exe) Canvas/dist/$(mode)/libcanvas.so Managers/dist/$(mode)/libmanagers.so -l GLEW -l glut -l glfw -l freetype
	@echo 'executable - $(mode): $@'

Test/build/$(mode)/%.o : Test/src/%.cpp Test/build/$(mode)/%.d
	@echo 'compiling - $(mode): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

Canvas/build/$(mode)/%.o : Canvas/src/%.cpp Canvas/build/$(mode)/%.d
	@echo 'compiling - $(mode): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

Managers/build/$(mode)/%.o : Managers/src/%.cpp Managers/build/$(mode)/%.d
	@echo 'compiling - $(mode): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(dep_exe) : ;

$(dep_lib) : ;

$(dep_man) : ;

-include $(dep_exe)

-include $(dep_lib)

-include $(dep_man)

clean :
	@rm -rf Test/dist/$(mode)
	@rm -rf Test/build/$(mode)
	@rm -rf Canvas/dist/$(mode)
	@rm -rf Canvas/build/$(mode)
	@rm -rf Managers/dist/$(mode)
	@rm -rf Managers/build/$(mode)
	@echo 'clean - $(mode): complete!'

print-% :
	@echo $* = $($*)

.PHONY : all clean print-%