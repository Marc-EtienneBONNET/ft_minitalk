/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:58:59 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/14 18:17:48 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	ft_print_msg(int signo, siginfo_t *sig)
{
	static int		bit = 0;
	static char		tmp = 0;
	static pid_t	client_pid = 0;

	if (client_pid == 0)
		client_pid = sig->si_pid;
	tmp |= (signo << bit);
	if (++bit == 8)
	{
		if (tmp == '\0')
		{
			write(1, "\n", 2);
			kill(client_pid, SIGUSR2);
			client_pid = 0;
		}
		else
			write(1, &tmp, 1);
		bit = 0;
		tmp = 0;
	}
	else
		kill(client_pid, SIGUSR1);
}

static void	ft_handler(int signo, siginfo_t *sig, void *non)
{
	(void)non;
	ft_print_msg(signo == SIGUSR2, sig);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	act;

	(void)av;
	if (ac != 1)
		return (-1);
	else
	{
		act.sa_sigaction = ft_handler;
		act.sa_flags = SA_SIGINFO;
		pid = getpid();
		ft_printf("%d\n", pid);
		sigaction(SIGUSR1, &act, 0);
		sigaction(SIGUSR2, &act, 0);
		while (1)
			pause();
	}
}
