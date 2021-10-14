/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:58:59 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/14 10:39:02 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

void	ft_traduction(int signo)
{
	static char	buf[100];
	static int	i;
	static int	bit;

	if (bit == 8)
		bit = 0;
	if (signo == SIGUSR2)
		buf[i] |= (1 << bit);
	else
		buf[i] &= ~(1 << bit);
	if (++bit == 8)
	{
		if (i == 98)
		{
			buf[++i] = '\0';
			ft_printf("%s", buf);
			i = 0;
		}
		else if (buf[i] == '\0')
			ft_printf("%s\n", buf);
		else
			i++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	(void)av;
	if (ac != 1)
		return (-1);
	else
	{
		pid = getpid();
		ft_printf("%d\n", pid);
		while (1)
		{
			signal(SIGUSR1, ft_traduction);
			signal(SIGUSR2, ft_traduction);
		}
	}
}
