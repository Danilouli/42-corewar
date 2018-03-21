/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:18:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/03/21 18:18:43 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int	usage(void)
{
	ft_putendl("Usage: ./corewar [-d -s | -b --stealth | -n --stealth] [-a] \
	<champion1.cor> <champion2.cor>");
	ft_putendl("	-a	: Prints the output from the \"aff\" instruction");
	ft_putendl("########################################## TEXT OUTPUT MODE");
	return (1);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac < 2)
		return (usage());
}
