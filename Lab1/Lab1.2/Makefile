# Nome do executável final
TARGET = meu_programa

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Flags de linkagem (bibliotecas)
LDLIBS = -lGL -lGLU -lglut

# Coleta todos os arquivos .cpp da pasta
SRCS = $(wildcard *.cpp)

# Gera os arquivos .o correspondentes
OBJS = $(SRCS:.cpp=.o)

# Regra principal
all: $(TARGET)

# Como gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Como compilar cada .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)
