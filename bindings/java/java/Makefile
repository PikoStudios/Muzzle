JAVAC := javac
JAVAC_FLAGS := -parameters
JAR := jar
JAR_NAME := muzzlejava.jar
SRC := dev/pikostudios/muzzle/bridge
OUTPUT_DIR := out
JNI_OUTPUR_DIR := include

all: jar-clean-classes

build:
	$(JAVAC) $(JAVAC_FLAGS) $(SRC)/*.java

jni-no-clean:
	$(JAVAC) -h $(JNI_OUTPUR_DIR) $(SRC)/*.java

jni: jni-no-clean clean-classes

jar: build
	$(JAR) cf $(OUTPUT_DIR)/$(JAR_NAME) $(SRC)/*.class

jar-clean-classes: jar clean-classes

clean-classes:
	-rm $(SRC)/*.class

clean: clean-classes
	-rm -rf $(OUTPUT_DIR)

help:
	@echo "Available targets:"
	@echo "	make			- Build bindings, create jar, and remove compiled java classes"
	@echo "	make build		- Build bindings"
	@echo "	make jar		- Create jar"
	@echo "	make jar-clean-classes	- Create jar, and remove compiled java classes"
	@echo "	make jni-no-clean	- Generate JNI headers"
	@echo "	make jni		- Generate JNI headers and remove compiled java classes"
	@echo "	make clean-classes	- Remove compiled java classes"
	@echo "	make clean		- Remove jar, and compiled java classes"
	@echo "	make help		- Show this message"

.PHONY: build jar help clean clean-classes jar-clean-classes jni-no-clean jni
