# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 15:41:20 by madegryc          #+#    #+#              #
#    Updated: 2024/10/23 19:53:47 by roguigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources
SRCS        =	main.cpp\
				src/Client/client.cpp\
				src/Server/server.cpp\
				src/Server/nickToken.cpp\
				src/Server/userToken.cpp \
				src/Server/passToken.cpp\
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

SRCS_BONUS	=	src_bonus/main.cpp\
				src_bonus/bot.cpp\

# Nom de l'exécutable
NAME        =    ircserv

NAME_BONUS	=	bot

# Répertoire pour les fichiers objets
OBJ_DIR     =    obj

OBJ_DIR_BONUS = obj_bonus

# Objets (les .o seront créés dans le répertoire obj/)
OBJS        =    $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

OBJS_BONUS	=	$(addprefix $(OBJ_DIR_BONUS)/, $(SRCS_BONUS:.cpp=.o))

# Compilateur et options
CXX         =    c++
CXXFLAGS    =    -std=c++98 -Wall  -Wextra -Iincludes -Werror -g3

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

bonus : $(NAME_BONUS) 
	@$(CXX) $(CXXFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)
	@echo "$(GREEN)Compilation de bot...$(NC)"

$(NAME_BONUS) : $(OBJS_BONUS)
	@$(CXX) $(CXXFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

# Compilation des fichiers .cpp en .o dans obj/
$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o : %.cpp | $(OBJ_DIR_BONUS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Création du répertoire obj si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

# Nettoyage des fichiers objets
clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "$(YELLOW)Nettoyage en cours...$(NC)"
	@echo "$(YELLOW)Nettoyage terminé.$(NC)"

# Nettoyage complet (objets et exécutable)
fclean : clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

# Recompiler tout
re    : fclean all

.PHONY : re fclean all clean

