/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:58:59 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/18 10:08:10 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	ft_print_msg(int signo, siginfo_t *sig)
{
	static int		bit = 0;
	static int		tmp = 0;

	tmp |= (signo << bit);
	if (tmp < 0 || tmp > 255)
	{
		tmp = 0;
		bit = 0;
		ft_printf("\nCaractère corrompus\n");
		usleep(500);
		kill(sig->si_pid, SIGUSR2);
	}
	else if (++bit == 8)
	{
		if (tmp == '\0')
			write(1, "\n", 2);
		else
			write(1, &tmp, 1);
		bit = 0;
		tmp = 0;
	}
	usleep(500);
	kill(sig->si_pid, SIGUSR1);
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
		act.sa_flags = SA_SIGINFO | SA_RESTART;
		pid = getpid();
		ft_printf("%d\n", pid);
		sigaction(SIGUSR1, &act, 0);
		sigaction(SIGUSR2, &act, 0);
		while (1)
			pause();
	}
}
