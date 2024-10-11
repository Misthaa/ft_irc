# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 15:41:20 by madegryc          #+#    #+#              #
#    Updated: 2024/10/11 18:32:09 by madegryc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS        =	main.cpp\
				server.cpp\
				client.cpp\
				
NAME        =    ircserv

OBJS        =    ${SRCS:.cpp=.o}

CXX        =    g++

CXXFLAGS      =    -std=c++98 -Wall -Werror -Wextra

GREEN=\033[0;32m
YELLOW=\033[0;33m
NC=\033[0m

all : ${NAME}

${NAME} : ${OBJS}
	@${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}
	@echo "$(GREEN)Compilation de IRC...$(NC)"

clean :
	@rm -f ${OBJS}
	@echo "$(YELLOW)Nettoyage en cours...$(NC)"
	@echo "$(YELLOW)Nettoyage terminé.$(NC)"

fclean : clean
	@rm -f ${NAME}

re    : fclean all

.PHONY : re fclean all clean
