# Colors
DEF_COLOR   = "\033[0;39m"
GRAY        = "\033[0;90m"
YELLOW      = "\033[0;93m"
GREEN       = "\033[0;92m"
RED         = "\033[0;91m"
BLUE        = "\033[0;94m"
MAGENTA     = "\033[0;95m"
CYAN        = "\033[0;96m"
WHITE       = "\033[0;97m"
ORANGE      = "\033[38;5;222m"
GREEN_BR    = "\033[38;5;118m"
YELLOW_BR   = "\033[38;5;227m"
PINK_BR     = "\033[38;5;206m"
BLUE_BR     = "\033[38;5;051m"
PINK_BRR    = "\033[38;5;219m"

# Text styles
BOLD        = "\033[1m"
UNDERLINE   = "\033[4m"
BLINK       = "\033[5m"

NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I.

SRCS = ircserv.cpp Server.cpp Channel.cpp Client.cpp CommandHandler.cpp Config.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
	@printf $(DEF_COLOR)
	@printf $(BOLD)$(YELLOW)"\nircserv compiled!\n\n"
	@printf $(BOLD)$(GREEN_BR)
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣴⣶⡿⠿⠿⠿⠿⠿⠿⠿⢷\n"
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⡿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠀⢀⣾⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⣰⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⢠⣾⣿⠿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⣴⣿⠿⠋⠀⠀⠀"$(BLUE)"Use ./ircserv 6667 jopa\n"
	@printf "⠀⠈⠉    "$(BLUE)"Use nc -C 127.0.0.1 6667\n\n"
	@printf $(BOLD)$(YELLOW)"PASS :jopa\n"
	@printf $(BOLD)$(YELLOW)"NICK Alice\n"
	@printf $(BOLD)$(YELLOW)"USER alice 0 * :\n"
	@printf $(BOLD)$(CYAN)"irssi\n"
	@printf $(YELLOW)"/set autolog off\n"
	@printf $(YELLOW)"/connect localhost 6667\n"
	@printf $(YELLOW)"/quote PASS :jopa\n"
	@printf $(YELLOW)"/quote NICK Bob\n"
	@printf $(YELLOW)"/quote USER bob 0 * :\n"
	@printf $(YELLOW)"/join #test\n"
	@printf $(YELLOW)"/window close (list,1,2 ...)\n"
	@printf $(YELLOW)"/msg Alice Привет, это личное!\n"

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

go:
	./ircserv 1111 jopa

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
