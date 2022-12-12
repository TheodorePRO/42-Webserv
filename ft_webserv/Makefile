NAME = webserv

# --   Directory   -- #
OBJ_DIR = objs
INC_DIR = incs
LIB_DIR = lib

# --  Search All files in SRCS  -- #
SRC_DIR = $(shell find srcs -type d)
vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)
SRCS = $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.cpp), $(notdir $(file))))

# -- Dependencies
INC_DIR = $(shell find incs -type d)
vpath %.hpp $(foreach dir, $(INC_DIR), $(dir):)
INCS = $(foreach dir, $(INC_DIR), $(foreach file, $(wildcard $(dir)/*.hpp), $(notdir $(file))))

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.opp))

# --   Compilation flags  -- #
CC		=	c++
FLAGS	=	-Wshadow -g3 -std=c++98 -Wall -Wextra -Werror 
LIBS	=	-lm

all:
	mkdir -p $(OBJ_DIR)
	make $(NAME)

$(NAME): $(OBJS)
	echo "$(OBJS)"
	@echo "\033[93m>> Compilation\033[0m"
	$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.opp: %.cpp $(INCS)
	@echo "\033[93m>> Obj $@\033[0m"
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@echo "\033[93m>> Cleaning objects \033[0m"
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:	fclean all

bonus: $(NAME)

.PHONY: all, clean, fclean, re, bonus
# -- https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
