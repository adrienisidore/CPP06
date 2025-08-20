# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 14:09:31 by aisidore          #+#    #+#              #
#    Updated: 2025/08/20 18:22:50 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = base

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = src/main.cpp src/Base.cpp

OBJ = objets/main.o objets/Base.o

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME)

objets/%.o: src/%.cpp
	mkdir -p objets
	c++ $(FLAGS) -c $< -o $@

clean:
	rm -f objets/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re