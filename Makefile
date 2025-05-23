# Nom de l'exécutable
EXEC = operation_flocon

# Fichiers source
SRCS = main.c fonctions.c interface_utilisateur.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Le compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11

# Options de liaison
LDFLAGS = -lm

all: $(EXEC)

$(EXEC): $(OBJS) biblio.h
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Force la recompilation complète
rebuild: clean all
