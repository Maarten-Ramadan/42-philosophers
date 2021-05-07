/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 12:02:31 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:28:44 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

static long int	ft_conv(const char *str, int i,
unsigned long int out, int in)
{
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if ((out >= 922337203685477580 && (str[i] - '0') > 7) && in == 1)
			return (-1);
		else if ((out >= 922337203685477580 && (str[i] - '0') > 8) && in == -1)
			return (0);
		out = out * 10 + (str[i] - '0');
		i++;
	}
	return (out);
}

int	ft_atoi(const char *str)
{
	unsigned long int	out;
	int					in;
	int					i;

	out = 0;
	i = 0;
	in = 1;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		in = -1;
		i++;
	}
	out = ft_conv(str, i, out, in);
	return (in * out);
}

void	parse(int argc, char **argv)
{
	int	i;
	int	i2;

	i = 1;
	while (i < argc)
	{
		i2 = 0;
		while (argv[i][i2])
		{
			if (!ft_isdigit(argv[i][i2]))
			{
				printf("invalid input\n");
				exit(1);
			}
			i2++;
		}
		i++;
	}
}

int	sem_management(t_data *guys)
{
	int	i;

	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
	sem_unlink("eat");
	i = 0;
	while (i < guys->total)
	{
		guys[i].forks = sem_open("forks", O_CREAT, 0600, guys->total);
		guys[i].death = sem_open("death", O_CREAT, 0600, 0);
		guys[i].print = sem_open("print", O_CREAT, 0600, 1);
		guys[i].eat = sem_open("eat", O_CREAT, 0600, 1);
		if (guys[i].forks == SEM_FAILED || guys[i].death == SEM_FAILED
			|| guys[i].print == SEM_FAILED || guys[i].eat == SEM_FAILED)
			return (printf("sem_open failed\n"));
		i++;
	}
	return (0);
}

void	init(int argc, char **argv, t_data *guys)
{
	int	i;
	int	total;

	i = 0;
	total = ft_atoi(argv[1]);
	while (i < total)
	{
		guys[i].total = total;
		guys[i].time_to_die = ft_atoi(argv[2]);
		guys[i].time_to_eat = ft_atoi(argv[3]);
		guys[i].time_to_sleep = ft_atoi(argv[4]);
		guys[i].nb = i;
		guys[i].eat_count = 0;
		guys[i].limit = -1;
		if (argc == 6)
			guys[i].limit = ft_atoi(argv[5]);
		guys[i].start_time = get_time(NULL);
		guys[i].time_stamp = guys[i].start_time;
		i++;
	}
}
