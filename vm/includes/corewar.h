#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <GLFW/glfw3.h>
# include <OpenCL/opencl.h>
# define OPTION "adsvbn"
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
	uintmax_t			cycles;
	unsigned			round;
}						t_map;

typedef struct			s_process
{
	int					ptr;
	t_bool				active;
	int					life;
	unsigned char		op;
	unsigned char		*params;
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
	GLFWwindow	*win;
	t_shader	*v_shader;
	t_shader	*f_shader;
	t_bool		pause;
	t_map		*map;
}						t_render;

t_list					*option(int ac, char **av, char *opt, t_champ *champs);
void					setmap(t_map *map, t_champ *champs, t_list *allprocess);
int						usage(void);
/*
Process functions
*/
t_process				*createproc(t_champ *champ, char carry, char *reg);
void					delprocess(void *content, size_t content_size);
void					process_operations(t_render *r, t_map *map, t_champ *champs, t_list **allprocess);
int						proc_isalive(t_list *list, void *ref);
t_process				*proccpy(t_process **process);

/*
Champions functions
*/
size_t					champslen(t_champ *champs);
int						ischamp(char *path, t_champ *champ, unsigned char n_champ);
int						champ_isalive(t_map *map, t_list *list, t_champ *champs);

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

#endif
