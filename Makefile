CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -MP

TARGET := prog
SOURCES := main.cpp Cadastro.cpp Login.cpp Sessao.cpp UserManager.cpp ProdutcsManager.cpp
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDS := $(OBJECTS:.o=.d)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPENDS)

rebuild: clean all

-include $(DEPENDS)