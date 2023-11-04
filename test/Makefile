#compiler
CXX = g++
WARS += -Wall -Werror
INCS += -I . -I ../lib/
LIBS += -l GLEW -l GL -l glut -l freetype
WARS += -Wno-format-security -Wno-return-type -Wno-unused-function -Wformat-overflow=0
CXXFLAGS += -std=c++20 -fPIC -pipe -fopenmp -MT $@ -MMD -MP -MF $(subst .o,.d, $@) $(DEFS) $(INCS) $(WARS)

#mode
ifneq ($(m), r)
	mode = debug
	CXXFLAGS += -ggdb3
else
	mode = release
	CXXFLAGS += -Ofast
endif

#ouput
out = dist/$(mode)/test.out

#sources
src := $(sort $(shell find -path './src/*.cpp'))

#objects
obj := $(sort $(subst ./src/, build/$(mode)/, $(addsuffix .o, $(basename $(src)))))

#dependencies
dep := $(subst .o,.d, $(obj))

#rules
all : lib $(out)
	@echo 'build($(mode)): complete!'

run : lib $(out)
	@./$(out)

debug : 
	@gdb $(out) -x gdb.txt

$(out) : $(obj)
	@echo 'executable($(mode)): $@'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) -fopenmp -o $(out) $(obj) ../lib/dist/$(mode)/libcanvas.so $(LIBS)

lib :
	@cd ../lib && make -f Makefile m=$m

build/$(mode)/%.o : src/%.cpp build/$(mode)/%.d
	@echo 'compiling($(mode)): $<'
	@mkdir -p $(dir $@) && rm -rf $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(dep) : ;

-include $(dep)

clean :
	@rm -rf dist/$(mode)
	@rm -rf build/$(mode)
	@echo 'clean($(mode)): complete!'

cleanlib :
	@cd ../lib && make -f Makefile m=$m cleanall

cleanall : cleanlib clean

print-% :
	@echo $* = $($*)

.PHONY : all run lib clean cleanlib cleanall print-%