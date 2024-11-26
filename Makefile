UTILS_PATH  =		 ./utils
SERVER_PATH = 		 ./src_server
CLIENT_PATH = 		 ./src_client

UTILS_SRC_FILE  =	 $(UTILS_PATH)/ft_atoi_safe.c \
					 $(UTILS_PATH)/ft_strlen.c \
					 $(UTILS_PATH)/ft_memset.c \
					 $(UTILS_PATH)/ft_strlcpy.c \
					 $(UTILS_PATH)/exit_msg.c

SERVER_SRC_FILE =	 $(SERVER_PATH)/server.c

CLIENT_SRC_FILE =	 $(CLIENT_PATH)/client.c

OBJECT_FILE_UTILS  = $(UTILS_SRC_FILE:.c=.o)
OBJECT_FILE_SERVER = $(SERVER_SRC_FILE:.c=.o)
OBJECT_FILE_CLIENT = $(CLIENT_SRC_FILE:.c=.o)

CC = 				 cc

DEBUG  =			 -g3 #-fsanitize=address
CFLAGS = 			 -Wall -Wextra -Werror $(DEBUG)

SERVER_NAME =		 server
CLIENT_NAME =		 client

FT_PRINTF = 		 libftprintf.a

all: $(SERVER_NAME) $(CLIENT_NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(FT_PRINTF):
	make -C ft_printf all
	mv ft_printf/$(FT_PRINTF) ./$(FT_PRINTF)

$(SERVER_NAME): $(FT_PRINTF) $(OBJECT_FILE_SERVER) $(OBJECT_FILE_UTILS)
	$(CC) $(CFLAGS) -o $(SERVER_NAME) $(OBJECT_FILE_SERVER) $(OBJECT_FILE_UTILS) $(FT_PRINTF)

$(CLIENT_NAME): $(FT_PRINTF) $(OBJECT_FILE_CLIENT) $(OBJECT_FILE_UTILS)
	$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(OBJECT_FILE_CLIENT) $(OBJECT_FILE_UTILS) $(FT_PRINTF)

clean:
	make -C ft_printf clean
	rm -f $(OBJECT_FILE_SERVER) $(OBJECT_FILE_CLIENT) $(OBJECT_FILE_UTILS)

fclean: clean
	make -C ft_printf fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(FT_PRINTF)

re: fclean all

.PHONY: all re fclean clean