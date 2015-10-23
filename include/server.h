/*
** server.h for server in /home/charla_n/projects/zappy/server
**
** Made by nicolas charlas
** Login   <charla_n@epitech.net>
**
** Started on  Thu May  9 15:09:42 2013 nicolas charlas
** Last update Sat Jul 13 12:21:13 2013 nicolas charlas
*/

#ifndef SERVER_H_
# define SERVER_H_

# define	SUCCESS		0
# define	FAILURE		-1
# define	DISCONNECTION	-2
# define	FULL_CLIENT	-3

# define	DEFAULT_PORT	1337
# define	DEFAULT_MAPX	42
# define	DEFAULT_MAPY	42
# define	DEFAULT_CSTA	6
# define	DEFAULT_WAIT	100
# define	DEFAULT_LIFE	10
# define	DEFAULT_LVL	1

# define	AV_CLIENT	256
# define	QUEUE		64
# define	MAX_EVENTS	1024

# define	MAX_FD		21000
# define	FD_FREE		0
# define	FD_CLIENT	1
# define	FD_SERVER	2
# define	FD_GRAPHIC	3
# define	FD_EGG		4

# define	BUFFER_SIZE	1024
# define	DELIM		"\n"
# define	TYPE_OBJ_STOCK	7
# define	MAX_MAP_SIZE	200
# define	MIN_MAP_SIZE	10
# define	TIME_GENERATE	20
# define	TRY_GENERATE	20
# define	MAX_REQUEST	10
# define	MAX_OBJ_CASE	10
# define	MAX_CIRC_SIZE	1000000
# define	STEP_REALLOC	21000
# define	MAX_TM_SIZE	256

# define	MESSAGE_1	"BIENVENUE"
# define	MESSAGE_GRAPH	"GRAPHIC"
# define	MESSAGE_DIE	"mort"

# include			<sys/time.h>

# ifdef		EPOLL
# include			<sys/epoll.h>
# else
# include			<sys/select.h>
# endif

typedef unsigned short		us;
typedef unsigned int		ui;
typedef struct s_srv		t_srv;
typedef struct s_listadvvector	t_listadvvector;

typedef enum			e_type
  {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    EGG,
    LAST
  }				t_type;

typedef enum			e_direction
  {
    NORTH,
    EAST,
    SOUTH,
    WEST
  }				t_direction;

typedef struct			s_vector
{
  t_direction			direction;
  double			norme;
  double			angle;
  int				x;
  int				y;
}				t_vector;

typedef struct			s_tmpview
{
  int				i;
  char				**answer;
  t_vector			*begin;
}				t_tmpview;

typedef struct			s_advvector
{
  t_vector			ab;
  int				ax;
  int				ay;
  int				bx;
  int				by;
}				t_advvector;

struct				s_listadvvector
{
  t_advvector			vect;
  t_listadvvector		*next;
};

	/* buffer circular */

typedef struct			s_circ
{
  int				size;
  int				start;
  int				end;
  char				*tab;
}				t_circ;

	/* representation of an object */

typedef struct			s_object
{
  t_vector			position;
  t_type			type;
  char				*type_str;
  struct s_object		*next;
}				t_object;

	/* time representation */

typedef struct			s_action
{
  int				has_task;
  struct timeval		time_task;
  int				sec_task;
  int				must_write;
  int				duration;
}				t_action;

typedef struct			s_team
{
  char				*name;
  ui				nb_client;
  struct s_team			*next;
}				t_team;

	/* client representation */

typedef struct			s_client
{
  t_team			*team;
  int				id;
  int				fd;
  int				by;
  int				type;
  int				(*read_func)(t_srv *, struct s_client *);
  int				(*write_func)(t_srv *, struct s_client *);
  t_vector			position;
  struct timeval		ttl;
  ui				level;
  t_action			action;
  t_circ			buff_circ_r;
  t_circ			buff_circ_w;
  int				inventory[LAST];
  int				step_engage;
  int				cmd_waiting;
  struct s_client		**incant;
  int				result;
  int				objects_position;
  struct s_client		*next;
}				t_client;

typedef struct			s_parse
{
  char				*name;
  int				(*exec)(t_srv *, void *, char *, char *);
}				t_parse;

typedef struct			s_corresp_obj
{
  t_type			type;
  char				*name;
}				t_corresp_obj;

typedef struct			s_luck_generate
{
  t_type			type;
  ui				luck;
}				t_luck_generate;

typedef struct			s_args
{
  us				port;
  ui				map_x;
  ui				map_y;
  t_team			*team;
  ui				nb_client_start;
  ui				wait_time;
}				t_args;

typedef struct			s_incantation
{
  int				lvl;
  int				need_player;
  int				nb_needed[LAST];
}				t_incantation;

typedef struct			s_graphic
{
  t_client			*graphic;
  int				length_graphic;
  void				*players;
  int				length_players;
}				t_graphic;

struct				s_srv
{
  t_args			args;
# ifdef				EPOLL
  int				epollfd;
  struct epoll_event		event;
# else
  fd_set			read;
  fd_set			write;
# endif
  int				fd_srv;
  int				id_egg;
  t_client			*clients;
  t_client			*views;
  t_client			*eggs;
  t_object			**begin;
};

int		parse_option(int ac, char * const av[], t_srv *srv);
int		processing(t_srv *srv);
int		write_error(char *str, int fd);
int		connect_to(t_srv *srv);
t_client	*put_in_list_client(int fd, int type, t_client **client,
				   int (*fct[2])(t_srv *srv, t_client *));
int		new_client(t_srv *srv, t_client *client);
int		client_read(t_srv *srv, t_client *);
int		client_write(t_srv *srv, t_client *);
int		is_valid_position(t_client *client, t_client *begin);
int		initialize_circ(t_circ *circ);
char		*read_circ(t_circ *circ, int speed);
int		write_circ(t_circ *circ, char *str);
char		circ_full(t_circ *circ);
char		circ_end_mess(t_circ *circ);
int		is_in_life(t_client **client, t_srv *srv);
int		nb_request(t_circ *circ);
int		parser(t_srv *srv, t_client *client, char *cmd);
time_t		generate_elements(t_srv *srv, int *res);
int		is_empty_place(int x, int y, t_client *begin);
int		push_object(t_srv *srv, t_type type, int x, int y);
int		engage_conversation(t_srv *srv, t_client *nc, char *ask);
int		count_object(t_srv *srv, int x, int y);
int		manage_task(t_srv *srv, t_client *);
int		call_parsing(t_srv *srv, t_client *client);
void		init_time_task(t_srv *srv, t_client *client, int time_task);
int		clients_still_alive(t_client *clients, t_srv *srv);
int		send_lvl(t_srv *srv, t_client *client);
void		delete_graphic(t_srv *srv);
void		delete_client(t_client **clients, t_client **todelete);
t_client	*init_client(t_client *client, t_srv *srv);
void		move_client_to_north(t_client *client, t_srv *server);
void		move_client_to_south(t_client *client, t_srv *server);
void		move_client_to_east(t_client *client, t_srv *server);
void		move_client_to_west(t_client *client, t_srv *server);
int		exp_client_ahead(t_client *tmpclient);
int		exp_client_his_left(t_client *tmpclient);
int		exp_client_behind(t_client *tmpclient);
int		exp_client_his_right(t_client *tmpclient);
int		search_bro_direction(t_client *clientondemand,
				     t_client *tmpclient,
				     t_srv *server);
int		events_graphic_connection(t_srv *srv, t_client *client);
void		free_broadcast_map(char **map);
char		**make_broadcast_map(t_srv *server);
void		free_broadcast_vectorlist(t_listadvvector *vect);
t_listadvvector	*add_in_vectorlist(t_listadvvector *listvector,
				   t_advvector *vect);
t_listadvvector	*save_vectors(t_listadvvector *listvector, t_srv *server,
			      t_client *clientondemand,
			      t_client *tmpclient, char **map);
t_advvector	*calcul_smallest_vector(t_listadvvector *vectors);
void		print_broadcast_vectorlist(t_listadvvector *vect);
void		print_broadcast_map(char **map, t_srv *server);
int		graphic_clients_cmd(t_srv *srv, char *command,
				    t_graphic *graph);
int		forward(t_srv *, void *, char *, char *);
int		right(t_srv *, void *, char *, char *);
int		left(t_srv *, void *, char *, char *);
int		view(t_srv *, void *, char *, char *);
int		object_at(int x, int y, char **answer, t_srv *srv);
int		view_get_line(t_client *client, char **answer, int range,
			      t_srv *srv);
int		inventory(t_srv *, void *, char *, char *);
int		take_object(t_srv *, void *, char *, char *);
int		drop_object(t_srv *, void *, char *, char *);
int		expulse(t_srv *, void *, char *, char *);
int		exp_client_to_north(t_client *tmpclient);
int		exp_client_to_east(t_client *tmpclient);
int		exp_client_to_south(t_client *tmpclient);
int		exp_client_to_west(t_client *tmpclient);

int		broadcast(t_srv *, void *, char *, char *);
int		incantation(t_srv *, void *, char *, char *);
int		incantation_send_msg(t_srv *srv, t_client *client,
				     t_object **o_oth, t_client **oth);
int		fork_player(t_srv *, void *, char *, char *);
int		connect_nbr(t_srv *, void *, char *, char *);
void		delete_object(t_object **objs, t_object **todelete);
void		free_all(t_srv *srv);
int		event_player_connection(t_srv *srv, t_client *client);
int		event_expulse(t_srv *srv, t_client *client);
int		event_players_expulsed(t_srv *srv, t_client *client);
int		end_game(t_srv *srv);
int		event_egg(t_srv *srv, t_client *egg);
int		event_egg_opened(t_srv *srv, t_client *egg);
int		event_egg_died(t_srv *srv, t_client *egg);
int		client_graphic_write(t_srv *srv, t_client *client);
t_vector	get_begin_north(int range, t_client *client, t_srv *srv);
t_vector	get_begin_south(int range, t_client *client, t_srv *srv);
t_vector	get_begin_west(int range, t_client *client, t_srv *srv);
t_vector	get_begin_east(int range, t_client *client, t_srv *srv);
int		is_flaged(t_srv *srv, t_client *current);
void		initialize(t_srv *srv, int *max, int *has_data_write,
			   t_client *current);
int		event_player_die(t_srv *srv, t_client *client);
int		delete_egg(t_object **object);
int		view_client(t_srv *srv, int x, int y, char **answer);
# ifdef		EPOLL
int		loop(t_srv *srv);
# endif
void		get_time(struct timeval *t, t_srv *srv);
int		do_manage(t_srv *srv);
int		event_end_incantation(t_srv *srv, t_client *client);
int		usage();
int		msz(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		bct(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		mct(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		tna(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		plv(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		ppo(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pin(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pnw(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pex(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pbc(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pic(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pfk(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		sgt(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pie(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pdr(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pgt(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		pdi(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		smg(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		seg(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		sst(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		edi(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		ebo(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		eht(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		enw(t_srv *srv, void *ptr, char *cmd1, char *cmd2);
int		suc(t_client *c);
int		sbp(t_client *c);

#endif /* !SERVER_H_ */
