.PHONY:     			all $(NAME) clear mkbuild lib clear clean fclean re sanitize

NAME					= philo

BUILD_DIR				= build/

HEADER_DIR				= header/

HEADER_FILE				= minishell.h pipex.h

DIR						= src/

SRC			 			= main.c	parsing.c	utils.c	check_end_of_loop.c
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)
	
CC						= cc
CFLAGS					= -Wall -Wextra -Werror
SANITIZE				= $(CFLAGS) -fsanitize=thread

RM 						= rm -rf
CLEAR					= clear

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)*  Makefile 
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

all: 					clear lib mkbuild  $(HEADER_DIR) $(NAME)
	
mkbuild:	
						@mkdir -p ${BUILD_DIR}

clear:
						$(CLEAR)
						
$(NAME): 				$(OBJECTS) 
						$(CC) $(OBJECTS) -o $(NAME) -pthread

sanitize :				$(OBJECTS) 
						$(CC) $(SANITIZE) $(OBJECTS) -o $(NAME) 
clean:					
						@${RM} $(OBJECTS)
						@${RM} $(BUILD_DIR)

fclean:					clean
						@${RM} ${NAME}

re:						fclean all
						$(MAKE) all