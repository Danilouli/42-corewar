#include "corewar.h"

t_process	*createproc(int life)
{
	t_process	*proc;

	if (!(proc = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	proc->ptr = NULL;
	proc->life = life;
	return (proc);
}

int	ischamp(char *path, t_champ *champ)
{
	int				fd;
	int				ret;
	unsigned		magic;
	unsigned		keep;
	size_t			i;
	char			buf[COMMENT_LENGTH + 1];

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
 	if (!(magic == COREWAR_EXEC_MAGIC))
		return (0);
	ret = read(fd, buf, PROG_NAME_LENGTH);
	buf[ret] = '\0';
	champ->name = ft_strdup(buf);
	ft_printf("name : %s\n", champ->name);
	ret = read(fd, buf, COMMENT_LENGTH);
	champ->comment = ft_strdup(&buf[8]);
	ft_printf("comment : %s\n", champ->comment);
	ret = read(fd, buf, CHAMP_MAX_SIZE);
	buf[ret] = '\0';
	champ->len_prog = ret;
	champ->prog = ft_memdup(buf, (size_t)ret);
	write(1, champ->prog, ret);
	champ->processus = ft_lstlink(createproc(-1), sizeof(t_process));
	if ((close(fd) == -1))
		return (0);
	return (1);
}

size_t	champslen(t_champ *champs)
{
	size_t	i;

	i = 0;
	while(champs[i].name)
		i++;
	return (i);
}
