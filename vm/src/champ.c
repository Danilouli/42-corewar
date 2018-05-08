#include "corewar.h"

int			champregister(int fd, t_champ *champ, unsigned char n_champ)
{
	int		ret;
	char	buf[COMMENT_LENGTH + 1];

	champ->num = n_champ;
	champ->lastlife = 0;
	ft_printf("num : %i\n", champ->num);
	if ((ret = read(fd, buf, PROG_NAME_LENGTH)) <= 0 || ret != PROG_NAME_LENGTH)
		return (0);
	buf[ret] = '\0';
	champ->name = ft_strdup(buf);
	ft_printf("name : %s\n", champ->name);
	if ((ret = read(fd, buf, COMMENT_LENGTH)) <= 0 || ret != COMMENT_LENGTH)
		return (0);
	champ->comment = ft_strdup(&buf[8]);
	ft_printf("comment : %s\n", champ->comment);
	if (!(ret = read(fd, buf, CHAMP_MAX_SIZE + 1)) || ret > CHAMP_MAX_SIZE)
		return (0);
	buf[ret] = '\0';
	champ->len_prog = ret - 12;
	if (ft_memcmp(buf, "\0\0\0\0\0\0\0\0\0\0\0\0", 12))
		return (0);
	champ->prog = ft_memdup(&buf[12], (size_t)ret);
	// write(1, champ->prog, ret);
	return (1);
}

int			ischamp(char *path, t_champ *champ, unsigned char n_champ)
{
	int			fd;
	int			ret;
	unsigned	magic;
	unsigned	keep;
	size_t		i;

	if ((fd = open(path, O_RDONLY)) < 0 || (ret = read(fd, "", 0)) < 0)
	{
		ft_printf("Can't read source file %s\n", path);
		return (0);
	}
	i = 4;
	magic = 0;
	while (i--)
	{
		keep = 0;
		if (read(fd, &keep, 1) < 0)
			return (0);
		keep <<= i * 8;
		magic |= keep;
	}
	ft_printf("magic : %x | %x\n", magic, COREWAR_EXEC_MAGIC);
 	if (magic != COREWAR_EXEC_MAGIC)
		return (0);
	if (!champregister(fd, champ, n_champ) || close(fd) == -1)
		return (0);
	return (1);
}

size_t	champslen(t_champ *champs)
{
	size_t	i;

	i = 0;
	while(champs[i].num >= 0)
		i++;
	return (i);
}

int	champ_isalive(t_map *map, t_list *list, t_champ *champs)
{
	(void)champs;
	++map->cycles;
	++map->t_cycles;
	return (map->cycle_todie < 1 || !ft_lstlen(list) ? 0 : 1);
}
