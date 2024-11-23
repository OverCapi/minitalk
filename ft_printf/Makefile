SRCS_FILE =  ft_printf.c \
			 converter.c \
			 converter_utils.c \
			 utils.c

OBJECT_FILE = $(SRCS_FILE:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

NAME = libftprintf.a

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECT_FILE)
		$(AR) $(NAME) $(OBJECT_FILE)

clean:
	rm -f $(OBJECT_FILE)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all re fclean clean
