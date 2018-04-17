#include "corewar.h"

t_process	*createproc(t_champ *champ, char carry, char *reg)
{
	t_process	*proc;
	unsigned	*cast;

	if (!(proc = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	proc->ptr = 0;
	proc->life = CYCLE_TO_DIE;
	proc->champ = champ;
	proc->op = -1;
	proc->cycles = 0;
	proc->carry = carry;
	proc->params = NULL;
	proc->active = 0;
	if (reg)
		proc->reg = ft_memdup(reg, REG_NUMBER * REG_SIZE);
	else
	{
		proc->reg = ft_strnew(REG_NUMBER * REG_SIZE);
		cast = (unsigned *)proc->reg;
		*cast = LIFECODE - champ->num;
	}
	return (proc);
}

void	delprocess(void *content, size_t content_size)
{
	t_process	*process;

	(void)content_size;
	process = (t_process *)content;
	if (process->params)
		free(process->params);
	if (process->reg)
		free(process->reg);
}

int	proc_isalive(t_list *list, void *ref)
{
	t_process	*process;

	(void)ref;
	process = (t_process *)list->content;
	return (process->life > 0 ? 1 : 0);
}
