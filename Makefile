# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 15:41:20 by madegryc          #+#    #+#              #
#    Updated: 2024/10/21 15:06:57 by roguigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources
SRCS        =	main.cpp\
				src/Client/client.cpp\
				src/Server/server.cpp\
				src/Server/nickToken.cpp\
				src/Server/userToken.cpp \
				src/Server/channel.cpp\
				src/Server/joinToken.cpp\
				src/Server/prvMsgToken.cpp\
				src/Server/inviteToken.cpp\
				src/Server/topicToken.cpp\
				src/Server/kickToken.cpp\
				src/Server/quitToken.cpp\
				src/Server/partToken.cpp\
				src/Server/modeToken.cpp\
				src/utils.cpp\

# Nom de l'exécutable
NAME        =    ircserv

# Répertoire pour les fichiers objets
OBJ_DIR     =    obj

# Objets (les .o seront créés dans le répertoire obj/)
OBJS        =    $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

# Compilateur et options
CXX         =    c++
CXXFLAGS    =    -std=c++98 -Wall  -Wextra -Iincludes -Werror

# Couleurs
GREEN       =    \033[0;32m
YELLOW      =    \033[0;33m
NC          =    \033[0m

# Règle par défaut
all : $(NAME)

# Création de l'exécutable
$(NAME) : $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)Compilation de IRC...$(NC)"

# Compilation des fichiers .cpp en .o dans obj/
$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Création du répertoire obj si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets
clean :
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Nettoyage en cours...$(NC)"
	@echo "$(YELLOW)Nettoyage terminé.$(NC)"

# Nettoyage complet (objets et exécutable)
fclean : clean
	@rm -f $(NAME)

# Recompiler tout
re    : fclean all

.PHONY : re fclean all clean

