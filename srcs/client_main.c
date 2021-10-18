/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:09:04 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/18 10:09:05 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	ft_envoi_sigusr(int pid, char c)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (i < 8)
	{
		res = (c >> i++) & 1;
		if (res == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
	}
}

void	ft_boucle_envoie_message(int pid, char *str)
{
	int	x;

	x = -1;
	usleep(1000);
	while (str[++x])
		ft_envoi_sigusr(pid, str[x]);
	ft_envoi_sigusr(pid, '\0');
	exit (0);
}

int	ft_verif_pid(char *pid)
{
	int	x;

	x = 0;
	while (pid[x])
	{
		if (ft_isdigit(pid[x++]) == 0)
			return (-1);
	}
	return (1);
}

static void	ft_validation(int signo, siginfo_t *act, void *non)
{
	(void)act;
	(void)non;
	if (signo == SIGUSR2)
		exit (0);
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	act;

	pid = 0;
	if (ac != 3 || av[2] == NULL || av[1] == NULL)
		return (-1);
	if (ft_verif_pid(av[1]) == -1)
		return (-1);
	pid = ft_atoi(av[1]);
	act.sa_sigaction = ft_validation;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	ft_boucle_envoie_message(pid, av[2]);
	return (0);
}
