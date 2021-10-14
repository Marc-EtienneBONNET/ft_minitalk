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
		usleep(1000);
	}
}

void	ft_boucle_envoie_message(int pid, char *str)
{
	int	x;

	x = -1;
	while (str[++x])
		ft_envoi_sigusr(pid, str[x]);
	ft_envoi_sigusr(pid, '\0');
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

int	main(int ac, char **av)
{
	int	pid;

	pid = 0;
	if (ac != 3 || av[2] == NULL || av[1] == NULL)
		return (-1);
	if (ft_verif_pid(av[1]) == -1)
		return (-1);
	pid = ft_atoi(av[1]);
	ft_boucle_envoie_message(pid, av[2]);
	return (0);
}
