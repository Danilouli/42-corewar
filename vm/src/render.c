/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:39:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/29 18:46:42 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				initmap(t_map *map)
{
	float	vertices[3969 * 36];
	GLuint	vbo;
	GLuint	vao;

	map->ctrl_pts = getintvertices(map->int_vert, map);
	getmap(&vertices[0], map);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3969 * 36 * sizeof(float), \
	vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * 4, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * 4, (void*)(3 * 4));
	glEnableVertexAttribArray(1);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	return (vao);
}

int				render(t_render *r, t_map *map)
{
	GLuint vao;

	vao = initmap(map);
	map->style = r->style;
	glUniform1f(glGetUniformLocation(r->v_shader->prog, "rotx"), r->rotx);
	glUniform1f(glGetUniformLocation(r->v_shader->prog, "roty"), r->roty);
	glUniform1f(glGetUniformLocation(r->v_shader->prog, "s"), r->scale);
	glfwSetKeyCallback(r->win, event);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 4096 * 6);
	glDrawArrays(GL_POINTS, 0, 4096 * 6);
	glfwPollEvents();
	glfwSwapBuffers(r->win);
	return (0);
}

void			p_color(t_map *map, int i, WINDOW *win)
{
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	map->p_map[i] ? wattron(win, COLOR_PAIR(6))
	: wattron(win, COLOR_PAIR(map->c_map[i]));
	mvwprintw(win, i / 64 + 2, (i % 64) * 3 + 4, "%02x", map->map[i]);
	map->p_map[i] ? wattroff(win, COLOR_PAIR(6))
	: wattroff(win, COLOR_PAIR(map->c_map[i]));
	mvwprintw(win, i / 64 + 2, (i % 64) * 3 + 6, " ", map->map[i]);
}

void			print_champs(t_champ *c, WINDOW *rwin)
{
	mvwprintw(rwin, 14, 4, "Terrible player one : %s", c[0].name);
	mvwprintw(rwin, 15, 6, "Last live : %li", c[0].lastlife);
	c[1].name ? mvwprintw(rwin, 18, 4, "Another terrible player : %s", \
	c[1].name) : (void)c[1].name;
	c[1].name ? mvwprintw(rwin, 19, 6, "Last live : %li", c[1].lastlife)
	: (void)c[1].name;
	c[2].name ? mvwprintw(rwin, 22, 4, "Yet another one : %s", c[2].name)
	: (void)c[2].name;
	c[2].name ? mvwprintw(rwin, 23, 6, "Last live : %li", c[2].lastlife)
	: (void)c[2].name;
	c[3].name ? mvwprintw(rwin, 26, 4, "OMG!!! THIS IS THE BEST PLA... Ah, \
	nope : %.10s", c[3].name) : (void)c[3].name;
	c[3].name ? mvwprintw(rwin, 27, 6, "Last live : %li", c[3].lastlife)
	: (void)c[3].name;
}

int				print_nmap(t_list **allp, t_map *map, t_render *r, t_champ *c)
{
	int		i;
	WINDOW	*lwin;
	WINDOW	*rwin;

	lwin = subwin(stdscr, LINES / 1.2, COLS / 1.8, 0, 0);
	rwin = subwin(stdscr, LINES / 1.2, COLS / 5, 0, COLS / 1.8 - 1);
	box(lwin, ACS_VLINE, ACS_HLINE);
	box(rwin, ACS_VLINE, ACS_HLINE);
	i = 0;
	while (i < MEM_SIZE)
		p_color(map, i++, lwin);
	r->npause ? mvwprintw(rwin, 3, 4, "** Paused **   ")
	: mvwprintw(rwin, 3, 4, "** Running ** ");
	mvwprintw(rwin, 7, 4, "Cycles : %i", map->t_cycles);
	mvwprintw(rwin, 8, 4, "Processes : %li", ft_lstlen(*allp));
	mvwprintw(rwin, 9, 4, "Speed : %i", r->skip);
	print_champs(c, rwin);
	wrefresh(lwin);
	wrefresh(rwin);
	return (1);
}
