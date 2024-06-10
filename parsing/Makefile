RM				=	rm -f

NAME			=	so_long
NAME_BONUS		=	so_long_bonus

all:			$(NAME)

$(NAME):
				@make -C ./mandatory/

clean:
				@make clean -C ./mandatory/

fclean:			clean
				@make fclean -C ./mandatory/
				@$(RM) $(NAME)
				@$(RM) $(NAME_BONUS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re $(NAME_BONUS)
