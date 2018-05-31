/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codecon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:06:07 by acouturi          #+#    #+#             */
/*   Updated: 2018/05/31 17:22:46 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		main()
{
	int		fd;
	int		fdn;
	char	*data;
	char	*name;
	char	*tmp;
	int		i;

	if (0 >= (fd = open("line.test", O_RDONLY)))
		return (1);
	i = 0;
	while (get_next_line(fd, &data) == 1)
	{
		ft_printf("%s\n", data);
		name = ft_itoa(i);
		tmp = ft_strjoin("champ_debile/___test", name);
		free(name);
		name = ft_strjoin(tmp, ".s");
		free(tmp);
		if (data && 0 < (fdn = open(name, O_WRONLY | O_CREAT | O_TRUNC, 420)))
		{
			ft_dprintf(fdn, ".name \"lol\"\n.comment\"lol\"\n\n%s\n", data);
			close(fdn);
		}
		free(name);
		free(data);
		i++;
	}
	close(fd);
	return (0);
}