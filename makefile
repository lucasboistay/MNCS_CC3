CPPC = g++
CFLAGS = -W -Wall -Wshadow -pedantic -std=c++17
INCLUDES = -I./include -I./lib/eigen-3.4.0
SRC= $(wildcard src/*.cpp)
OBJ= $(SRC:.cpp=.o)
RM = rm -f
ZIPNAME = CC3.zip
TARNAME = CC3.tgz
ZIPFILES = src/ include/ lib/ data/ makefile README.md .gitignore plot-laplace-sym.py requirements.txt enonce.pdf

# -----------------------------------
# To change the name of the data file
DATANAME = banane  # <----------- HERE
# -----------------------------------

# Règle de compilation
all: $(OBJ)
	$(CPPC) $(CFLAGS) $(INCLUDES) $(OBJ) -o a.out

# Règle de compilation des fichiers sources
%.o: %.cpp
	$(CPPC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Exemples de règles pour le ménage
.PHONY: clean super_clean

clean :
	$(RM) $(OBJ)

super_clean :
	$(RM) $(OBJ) a.out

clean_data :
	$(RM) data/*.txt data/*.pdf data/*.dat

tar :
	tar -cvzf $(TARNAME) $(ZIPFILES)

zip :
	zip -r $(ZIPNAME) $(ZIPFILES)

plot :
	python3 plot-laplace.py
