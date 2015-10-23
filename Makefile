##
## Makefile for zappy in /home/charla_n//zappy/server
## 
## Made by nicolas charlas
## Login   <charla_n@epitech.net>
## 
## Started on  Sat Jul 13 11:51:45 2013 nicolas charlas
## Last update Sat Jul 13 12:13:38 2013 nicolas charlas
##

NAME_SERVER=	server

DIR_SERVER=	src

SRC_SERVER=	$(DIR_SERVER)/main.c \
		$(DIR_SERVER)/parse_option.c \
		$(DIR_SERVER)/processing.c \
		$(DIR_SERVER)/write_error.c \
		$(DIR_SERVER)/connect_to.c \
		$(DIR_SERVER)/new_client.c \
		$(DIR_SERVER)/client_op.c \
		$(DIR_SERVER)/circ_func.c \
		$(DIR_SERVER)/std_clients.c \
		$(DIR_SERVER)/is_in_life.c \
		$(DIR_SERVER)/parser.c \
		$(DIR_SERVER)/generate_elements.c \
		$(DIR_SERVER)/circ_func_others.c \
		$(DIR_SERVER)/graphic_clients_cmd.c \
		$(DIR_SERVER)/engage_conversation.c \
		$(DIR_SERVER)/manage_task.c \
		$(DIR_SERVER)/call_parsing.c \
		$(DIR_SERVER)/init_time_task.c \
		$(DIR_SERVER)/clients_still_alive.c \
		$(DIR_SERVER)/events_graphic_connection.c \
		$(DIR_SERVER)/free_all.c \
		$(DIR_SERVER)/event_player_connection.c \
		$(DIR_SERVER)/event_expulse.c \
		$(DIR_SERVER)/event_egg.c \
		$(DIR_SERVER)/end_game.c \
		$(DIR_SERVER)/processing_flags.c \
		$(DIR_SERVER)/delete_egg.c \
		$(DIR_SERVER)/epoll_loop.c \
		$(DIR_SERVER)/event_end_incantation.c \
		$(DIR_SERVER)/cmd/get_begin_orientation.c \
		$(DIR_SERVER)/cmd/forward.c \
		$(DIR_SERVER)/cmd/right.c \
		$(DIR_SERVER)/cmd/left.c \
		$(DIR_SERVER)/cmd/view.c \
		$(DIR_SERVER)/cmd/view_client.c \
		$(DIR_SERVER)/cmd/view_object_at.c \
		$(DIR_SERVER)/cmd/view_get_line.c \
		$(DIR_SERVER)/cmd/inventory.c \
		$(DIR_SERVER)/cmd/take_object.c \
		$(DIR_SERVER)/cmd/drop_object.c \
		$(DIR_SERVER)/cmd/expulse.c \
		$(DIR_SERVER)/cmd/expulse_client_to.c \
		$(DIR_SERVER)/cmd/expulse_direction.c \
		$(DIR_SERVER)/cmd/broadcast.c \
		$(DIR_SERVER)/cmd/broadcast_other.c \
		$(DIR_SERVER)/cmd/broadcast_mapmanip.c \
		$(DIR_SERVER)/cmd/broadcast_vectormanip.c \
		$(DIR_SERVER)/cmd/incantation.c \
		$(DIR_SERVER)/cmd/incantation_send_msg.c \
		$(DIR_SERVER)/cmd/fork_player.c \
		$(DIR_SERVER)/cmd/connect_nbr.c \
		$(DIR_SERVER)/cmd/move_a_client.c \
		$(DIR_SERVER)/cmd/msz.c \
		$(DIR_SERVER)/cmd/bct.c \
		$(DIR_SERVER)/cmd/mct.c \
		$(DIR_SERVER)/cmd/tna.c \
		$(DIR_SERVER)/cmd/ppo.c \
		$(DIR_SERVER)/cmd/plv.c \
		$(DIR_SERVER)/cmd/pnw.c \
		$(DIR_SERVER)/cmd/pin.c \
		$(DIR_SERVER)/cmd/pex.c \
		$(DIR_SERVER)/cmd/pbc.c \
		$(DIR_SERVER)/cmd/pic.c \
		$(DIR_SERVER)/cmd/pfk.c \
		$(DIR_SERVER)/cmd/sgt.c \
		$(DIR_SERVER)/cmd/pie.c \
		$(DIR_SERVER)/cmd/pdr.c \
		$(DIR_SERVER)/cmd/pgt.c \
		$(DIR_SERVER)/cmd/pdi.c \
		$(DIR_SERVER)/cmd/suc.c \
		$(DIR_SERVER)/cmd/sbp.c \
		$(DIR_SERVER)/cmd/smg.c \
		$(DIR_SERVER)/cmd/seg.c \
		$(DIR_SERVER)/cmd/sst.c \
		$(DIR_SERVER)/cmd/edi.c \
		$(DIR_SERVER)/cmd/ebo.c \
		$(DIR_SERVER)/cmd/eht.c \
		$(DIR_SERVER)/cmd/enw.c

OBJ_SERVER=	$(SRC_SERVER:.c=.o)

EPOLL=		no

LDFLAGS = -lm

CFLAGS = 	-W -Wall -Wextra -pedantic -ansi -I include/

ifeq ($(EPOLL),yes)
	CFLAGS +=	 -DEPOLL
endif

RM=		rm -f

all:
		make $(NAME_SERVER)

$(NAME_SERVER):	$(OBJ_SERVER) $(SHARED_OBJ)
		cc $(OBJ_SERVER) $(SHARED_OBJ) -o $(NAME_SERVER) $(LDFLAGS)

clean:
		$(RM) *~
		$(RM) $(OBJ_SERVER)

fclean:		clean
		$(RM) $(NAME_SERVER)

re:		fclean all
