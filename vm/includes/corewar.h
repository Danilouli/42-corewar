#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <GLFW/glfw3.h>
# include <OpenCL/opencl.h>
# include <ncurses.h>
# define OPTION "adsvno"
# define NBOPT 6
# define STEALTH "--stealth"
# define LIFECODE 0xFFFFFFFF
# define LOG_BUFFSIZE 100000

typedef struct			s_champ
{
	char				num;
	char				*name;
	char				*comment;
	size_t				len_prog;
	char				*prog;
	intmax_t			lastlife;
}						t_champ;

typedef struct			s_map
{
	unsigned char		*map;
	unsigned char		*c_map;
	unsigned char		*p_map;
	intmax_t			t_cycles;
	int					cycles;
	intmax_t			cycle_todie;
	int					lives;
	int					checks;
	unsigned			round;
}						t_map;

typedef struct			s_process
{
	int					ptr;
	t_bool				active;
	int					life;
	unsigned char		op;
	unsigned			cycles;
	t_champ				*champ;
	char				carry;
	unsigned char		*reg;
}						t_process;

typedef struct			s_arg
{
	size_t				len;
	unsigned char		type;
	unsigned char		arg[4];
}						t_arg;

typedef struct		s_shader
{
	GLuint			id;
	GLchar			*src;
	GLuint			prog;
	GLenum			type;
	struct			s_info
	{
		GLint		success;
		GLint		msg_len; // Taille du message retourné par OpenGL après la compilation.
		GLchar		*log; // Message retourné.
		GLenum		type;
	}				info;
}					t_shader;

typedef struct			s_render
{
	GLFWwindow		*win;
	t_shader		*v_shader;
	t_shader		*f_shader;
	t_bool			pause;
	t_bool			ncurses;
	t_bool			npause;
	t_map			*map;
	short			skip;
	float			rotx;
	float			roty;
	float			scale;
}						t_render;

typedef struct			s_vertex
{
	float			x;
	float			y;
	float			z;
}						t_vertex;

typedef struct			s_tower
{
	t_vertex		pts[42];
	short			height;
	int				color;
	int				top_color;
}						t_ower;

/*
VM functions
*/
t_list					*option(int ac, char **av, char *opt, t_champ *champs);
void					setmap(t_map *map, t_champ *champs, t_list *allprocess);
int						usage(void);

/*
Arg functions
*/
unsigned char			*translate_OCP(unsigned char OCP);
int						OCPCheck(t_map *map, t_process *process);
t_arg					*get_arg(t_map *map, t_process *process, int nbarg, int *in);
unsigned				*tabarg(t_arg *arg, t_map *map, t_process *process);

/*
Process functions
*/
t_process				*createproc(t_champ *champ, char carry, char *reg);
void					delprocess(void *content, size_t content_size);
void					process_operations(t_render *r, t_map *map, t_champ *champs, t_list **allprocess);
t_list					*proc_filter(t_list *list, unsigned char *pmap);
t_process				*proccpy(t_process **process);
void					processit(t_map *map, t_list **allprocess, t_champ *champs, t_process *process);

/*
Champions functions
*/
size_t					champslen(t_champ *champs);
int						ischamp(char *path, t_champ *champ, unsigned char n_champ);
int						champ_isalive(t_map *map, t_list *list, t_champ *champs);
t_champ					*whowins(t_champ *champ);
void					freechampmap(t_champ *champs, t_map *map);

/*
Debug functions
*/
void					prt_map_hex(t_map map);

/*
Visualizer functions.
*/
int						init_context(t_render *r, t_map *map);
int						render(t_render *r, t_map *map);
t_shader				*build_shader(char *filename, GLenum type, GLuint prog_id, \
						t_bool prog);
void					event(GLFWwindow* window, int key, int scancode, int action, \
						int mods);
void					cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

/*
Ncurses functions.
*/

int						controls_ncurses(t_render *r);
void					print_nmap(t_list **allprocess, t_map *map);

/*
Operations functions
*/
int						add(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						sub(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						and(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						xor(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						or(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						live(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						zjmp(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						ldi(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						ld(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						sti(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						st(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						cfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						lcfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);
int						aff(t_map *map, t_champ *champ, t_process *process, t_list **allprocess);

/*
Memory functions
*/
void					bidir_memcpy(void *dst, void *src, int n, short where);
void					bidir_memset(void *dst, char champ_num, int n, short where);

#endif
