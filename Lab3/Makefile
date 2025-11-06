# Define o compilador C++ que será usado
CXX = g++

# Define flags de compilação (opcional, mas boa prática)
# -Wall (ativa todos os avisos)
# -std=c++11 (define o padrão do C++)
CXXFLAGS = -Wall -std=c++11

# Define o nome do arquivo executável final 
TARGET = test

# Define as bibliotecas necessárias para a linkagem (OpenGL, GLU, GLUT) [cite: 20]
# O PDF menciona -IGL, -IGLU, -Iglut[cite: 19, 20], que são prováveis erros de digitação.
# O correto para linkar bibliotecas no Linux é -l (L minúsculo).
LIBS = -lGL -lGLU -lglut

# Pega todos os arquivos .cpp na pasta, como o "*.cpp" do comando 
SRCS = $(wildcard *.cpp)

# A regra padrão (o que acontece quando você digita "make")
# Ela depende da regra "all"
.PHONY: all
all: $(TARGET)

# Regra para criar o executável
# Ela diz ao "make" como construir o $(TARGET)
$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Regra "clean" (opcional, mas muito útil)
# Permite que você digite "make clean" para apagar o executável
.PHONY: clean
clean:
	rm -f $(TARGET)