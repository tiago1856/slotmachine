EXE = game

CC=g++

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CFLAGS += -Wall -fexceptions -std=c++11
LDFLAGS += -Llib
LDLIBS += -lm


.PHONY:  all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)


