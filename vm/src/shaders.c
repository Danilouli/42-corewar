/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:37:32 by fsabatie          #+#    #+#             */
/*   Updated: 2018/03/26 14:37:33 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static GLchar	*getFileSource(char *filename)
{
	char	*line;
	char	*src;
	int		fd;

	if (!(fd = open(filename, O_RDONLY))
		|| !(src = (char*)malloc(1)))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoinfree(line, "\n");
		src = ft_strjoinfree(src, line);
		free(line);
	}
	return ((GLchar*)src);
}

// static int		errShaderCompilation(t_shader *s, char *filename)
// {
// 	if (s->info.success != GL_TRUE)
// 	{
// 		glGetShaderiv(s->id, GL_INFO_LOG_LENGTH, &(s->info.msg_len));
// 		glGetShaderInfoLog(s->id, LOG_BUFFSIZE, &(s->info.msg_len), s->info.log);
// 		s->info.log[s->info.msg_len] = '\0';
// 		ft_printf("Erreur de compilation pour \"%s\"\n%s", filename, s->info.log);
// 		return (1);
// 	}
// 	return (0);
// }

t_shader		*build_shader(char *filename, GLenum type, GLuint prog_id, \
				t_bool prog)
{
	t_shader *s;

	if (!(s = (t_shader*)malloc(sizeof(t_shader)))
		|| !(s->info.log = (GLchar*)malloc(sizeof(LOG_BUFFSIZE))))
		return (0);
	if (!(s->id = glCreateShader(type))
		|| !(s->src = getFileSource(filename)))
		return (0);
	glShaderSource(s->id, 1, (const char *const *)&(s->src), 0);
	glCompileShader(s->id);
	glGetShaderiv(s->id, GL_COMPILE_STATUS, &(s->info.success));
	// if (errShaderCompilation(s, filename))
	// 	return (NULL);
	s->prog = (prog == TRUE) ? prog_id : glCreateProgram();
	glAttachShader(s->prog, s->id);
	glLinkProgram(s->prog);
	return (s);
}
