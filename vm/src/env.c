/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:38:59 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/08 15:24:28 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <math.h>
#define VERTEX_SHADER "rsc/s.vert"
#define FRAG_SHADER "rsc/s.frag"

void	event(GLFWwindow* window, int key, int scancode, int action, \
		int mods)
{
	t_render *r;

	r = glfwGetWindowUserPointer(window);
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_P && (action == GLFW_PRESS || action == GLFW_REPEAT))
		prt_map_hex(*(r->map));
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		r->pause = r->pause ? 0 : 1;
	if (key == GLFW_KEY_R  && action == GLFW_PRESS)
		r->skip += r->skip < 1000 ? 10 : 0;
	if (key == GLFW_KEY_S  && action == GLFW_PRESS)
		r->skip -= r->skip <= 1 ? 0 : 10;
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		r->rotx -= 0.01;
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		r->rotx += 0.01;
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		r->roty += 0.01;
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		r->roty -= 0.01;
	if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT))
		r->scale -= 0.01;
	if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT))
		r->scale += 0.01;
}

int	init_context(t_render *r, t_map *map)
{
	if (!glfwInit())
		return (0);
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	if (!(r->win = glfwCreateWindow(1200, 1200, "CoreWar", NULL, NULL)))
	{
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(r->win);
	if (!(r->v_shader = build_shader(VERTEX_SHADER, GL_VERTEX_SHADER, 0, FALSE)))
		return (0);
	if (!(r->f_shader = build_shader(FRAG_SHADER, GL_FRAGMENT_SHADER, r->v_shader->prog, TRUE)))
		return (0);
	r->map = map;
	r->rotx = 1;
	r->roty = 1;
	r->scale = 1;
	glUseProgram(r->v_shader->prog);
	return (1);
}

int controls_ncurses(t_render *r, t_list **allprocess, t_map *map, t_champ *champs)
{
	int ch;

	ch = getch();
	if (ch == ' ')
	{
		r->npause = r->npause ? 0 : 1;
		print_nmap(allprocess, map, r, champs);
	}
	if (ch == 's')
		r->skip += r->skip < 10 ? 1 : 0;
	if (ch == 'r')
		r->skip -= r->skip > 1 ? 1 : 0;
	for (double i = 0; i < pow(10, r->skip) ; i++) // Slows the
		(void)r;
	return (0);
}
