/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:39:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/04/06 22:40:33 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define TOWER_OBJ "rsc/tower.obj"

static GLuint createVAO(void)
{
	GLuint vao;

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return (vao);
}

void	initTower(int fd, t_ower *towers)
{
	char		*line;
	int			v;
	short		f;
	t_vertex 	vertices[10];
	t_ower		model;

	f = 0;
	v = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 'v')
		{
			vertices[v].x = (float)ft_atoi(ft_strchr(line, ' ') + 1) / 10;
			vertices[v].z = (float)ft_atoi(ft_strchr(line, ',') + 1) / 10;
			vertices[v++].y = (float)ft_atoi(ft_strrchr(line, ',') + 1) / 10;
		}
		if (*line == 'f')
		{
			ft_memcpy(&towers[0].pts[f++], &vertices[ft_atoi(ft_strchr(line, ' ') + 1)], sizeof(t_vertex));
			ft_memcpy(&towers[0].pts[f++], &vertices[ft_atoi(ft_strchr(line, ',') + 1)], sizeof(t_vertex));
			ft_memcpy(&towers[0].pts[f++], &vertices[ft_atoi(ft_strrchr(line, ',') + 1)], sizeof(t_vertex));
		}
	}
	model = towers[0];
	int t = 1;
	f = 0;
	float incy = 0.2;
	while (f < 64)
	{
		v = !f ? 1 : 0;
		for (size_t i = 0; i < 42; i++) {
			model.pts[i].x = towers[0].pts[i].x;
		}
		float incx = 0.2;
		while (v < 64)
		{
			for (size_t i = 0; i < 42; i++) {
				model.pts[i].x += incx;
			}
			ft_memcpy(&towers[t++], &model, sizeof(t_ower));
			v++;
		}
		for (size_t i = 0; i < 42; i++) {
			model.pts[i].y += incy;
		}
		f++;
	}
}

int buildTower(t_ower tower)
{
	GLuint vao;

	vao = createVAO();
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 42 * 3 * sizeof(float), tower.pts, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	return (vao);
}

int	render(t_render *r, t_map *map)
{
	GLuint	vao;
	t_ower	towers[4096];
	int		fd;
	static int f = 0;

	fd = open(TOWER_OBJ, O_RDONLY);
	(void)map;
	initTower(fd, &towers[0]);
	vao = buildTower(towers[0]);
	glUseProgram(r->v_shader->prog);
	glfwSetKeyCallback(r->win, event);
	glfwSetCursorPosCallback(r->win, cursor_position_callback);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 4096);
	glfwPollEvents();
	glfwSwapBuffers(r->win);
	return (0);
}

void	print_nmap(t_map *map)
{
	int		i;

	i = 0;
	init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);

	while(i < MEM_SIZE)
	{
		if (map->p_map[i] == 1)
		{
			attron(COLOR_PAIR(1));
			printw("%02x", map->map[i]);
			attroff(COLOR_PAIR(1));
		}
		else if (map->c_map[i] == 1)
		{
			attron(COLOR_PAIR(2));
			printw("%02x", map->map[i]);
			attroff(COLOR_PAIR(2));
		}
		else if (map->c_map[i] == 2)
		{
			attron(COLOR_PAIR(3));
			printw("%02x", map->map[i]);
			attroff(COLOR_PAIR(3));
		}
		else if (map->c_map[i] == 3)
		{
			attron(COLOR_PAIR(4));
			printw("%02x", map->map[i]);
			attroff(COLOR_PAIR(4));
		}
		else if (map->c_map[i] == 4)
		{
			attron(COLOR_PAIR(5));
			printw("%02x", map->map[i]);
			attroff(COLOR_PAIR(5));
		}
		else if (map->c_map[i] == 0)
		{
			attron(COLOR_PAIR(6));
			printw("%02x", map->map[i]);
			attroff(COLOR_PAIR(6));
		}
		i++;
		if (i % 64 == 0)
			printw("\n");
		else
			printw(" ");
	}
	printw("Cycles at: %li\n", map->t_cycles);
	move(0, 0);
}
