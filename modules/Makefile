CMAKE:=cmake
GIT:=git
CMAKE_FLAGS:=
GENERATOR:="Unix Makefiles"
BUILDTOOL:=make
BUILDTOOL_MAKE:=true
BUILDTOOL_FLAGS:=

.PHONY: help all test_basic test_all install_submodules

all:
	@echo "No arguments passed..."
	@echo ""
	@make help

compile_prerequisites:
	@echo "[1/3] Generating GLFW"
	cd "../deps/glfw/"; \
	mkdir build; \
	cd build; \
	$(CMAKE) .. -G $(GENERATOR) $(CMAKE_FLAGS); \
	$(CMAKE) .. -G ""; \
	echo "[2/3] Compiling GLFW"; \
	$(BUILDTOOL) $(BUILDTOOL_FLAGS); \
	if [ $(BUILDTOOL_MAKE) == "true" ]; then \
		echo "[3/3] Installing GLFW" \
		$(BUILDTOOL) install \
	fi

install_submodules:
	git submodule init
	git submodule update

test_basic:
	@echo Not yet implemented

test_all:
	@echo Not yet implemented

help:
	@echo "Muzzle Set-up script version 1.0"
	@echo ""
	@echo "COMMANDS"
	@echo "    help - Show this screen"
	@echo "    compile_prerequisites - Compile all the prerequisites using CMake in the deps/ folder"
	@echo "    install_submodules - Install submodules"
	@echo "    test_basic - Test compiling the basic example"
	@echo "    test_all - Test compiling all examples"
	@echo ""
	@echo "DEFINITIONS"
	@echo "    CMAKE= - CMake executable"
	@echo "    CMAKE_FLAGS= - CMake flags"
	@echo "    GENERATOR=\"Unix Makefiles\" - CMake generator flag (cmake -h for more info)"
	@echo "    GIT=\"git\" - Git executable"
	@echo "    BUILDTOOL=\"make\" - Build tool executable"
	@echo "    BUILDTOOL_MAKE=true - Boolean [ \"true\" | \"false\"] if build tool is make"
	@echo "    BUILDTOOL_FLAGS= - Build tool flags"