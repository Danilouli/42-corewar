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
#define SVERT "rsc/shaders/test.vert"
#define FRAG_G "rsc/shaders/green.frag"

static GLuint createVAO(void)
{
	GLuint vao;

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return (vao);
}

GLuint createBuffer(float pts[][6])
{
	GLuint vao;

	vao = createVAO();
	int i;

	i = -1;
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4096 * 6 * sizeof(float), pts, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	return (vao);
}


void	getPts(float pts[][6], t_map *map) {
	int i;
	int j;
	int c;

	c = 0;
	i = -1;
	while (++i < 64) {
		j = -1;
		while (++j < 64) {
			pts[c][0] = (float)i / 34 - 0.93;
			pts[c][1] = (float)j / 34 - 0.93;
			pts[c][2] = (float)map->p_map[c] / 100;
			if (map->c_map[c] == 1) {
				pts[c][3] = 255;
				pts[c][4] = 0;
				pts[c++][5] = 0;
			}
			else if (map->c_map[c] == 2)
			{
				pts[c][3] = 0;
				pts[c][4] = 255;
				pts[c++][5] = 0;
			}
			else if (map->c_map[c] == 3)
			{
				pts[c][3] = 0;
				pts[c][4] = 0;
				pts[c++][5] = 255;
			}
			else if (map->c_map[c] == 4)
			{
				pts[c][3] = 255;
				pts[c][4] = 255;
				pts[c++][5] = 0;
			}
			else if (map->c_map[c] == 0) {
				pts[c][3] = 100;
				pts[c][4] = 100;
				pts[c++][5] = 100;
			}
		}
	}
}

int	render(t_render *r, t_map *map)
{
	GLuint	vao;
	float	pts[4096][6];

	getPts(pts, map);
	vao = createBuffer(pts);
	glfwSetWindowUserPointer(r->win, map);
	glUseProgram(r->v_shader->prog);
	glfwSetKeyCallback(r->win, event);
	glfwSetCursorPosCallback(r->win, cursor_position_callback);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 4096);
	glfwPollEvents();
	glfwSwapBuffers(r->win);
	return (0);
}
