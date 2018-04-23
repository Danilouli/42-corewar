/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:38:59 by fsabatie          #+#    #+#             */
/*   Updated: 2018/03/26 14:39:00 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define VERTEX_SHADER "rsc/s.vert"
#define FRAG_SHADER "rsc/s.frag"

void	event(GLFWwindow* window, int key, int scancode, int action, \
		int mods)
{
	t_map *map = glfwGetWindowUserPointer(window);
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_P && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		prt_map_hex(*map);
	}
}

int	init_context(t_render *r)
{
	if (!glfwInit())
		return (0);
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	if (!(r->win = glfwCreateWindow(800, 800, "Hello World", NULL, NULL)))
	{
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(r->win);
	if (!(r->v_shader = build_shader(VERTEX_SHADER, GL_VERTEX_SHADER, 0, FALSE)))
		return (0);
	if (!(r->f_shader = build_shader(FRAG_SHADER, GL_FRAGMENT_SHADER, r->v_shader->prog, TRUE)))
		return (0);
	return (1);
}
