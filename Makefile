JavaDir := ./java
JavaDeps := $(JavaDir)/MyExpt.class

#?
JDK_DIR := /usr/lib/jvm/java-11-openjdk-amd64
CXX := clang++-8
CXXFLAGS := -std=c++17 -O3 -I"$(JDK_DIR)/include" -I"$(JDK_DIR)/include/linux"
LDFLAGS := -L"$(JDK_DIR)/lib" -L"$(JDK_DIR)/lib/server"
LDLIBS := -ljvm
# -ljava?
# jvm static link or runtime?


main: main.o $(JavaDeps)
	# TODO pass javadir
	$(CXX) main.o $(LDFLAGS) $(LDLIBS) -Wl,-R"$(JDK_DIR)/lib/server" -o main


# -h where to put headers
# -d dist build dir
$(JavaDeps): %.class : %.java
	javac $<

# TODO pass class path
main.o : main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c main.cpp -o main.o

