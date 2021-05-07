/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 12:02:31 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:14:57 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	parse(int argc, char **argv)
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
				return (printf("invalid input\n"));
			i2++;
		}
		i++;
	}
	return (0);
}

int	sem_management(t_data *guys)
{
	int	i;

	i = 0;
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("eat");
	while (i < guys->total)
	{
		guys[i].forks = sem_open("forks", O_CREAT, 0600, guys->total);
		guys[i].print = sem_open("print", O_CREAT, 0600, 1);
		guys[i].eat = sem_open("eat", O_CREAT, 0600, 1);
		if (guys[i].forks == SEM_FAILED || guys[i].print == SEM_FAILED
			|| guys[i].eat == SEM_FAILED)
			return (printf("sem_open failed\n"));
		i++;
	}
	return (0);
}

int	init(int argc, char **argv, t_data *guys, int i)
{
	int	total;
	int	*death;

	death = malloc(sizeof(int));
	if (!death)
		return (printf("malloc fail\n"));
	*death = 0;
	total = ft_atoi(argv[1]);
	while (i < total)
	{
		guys[i].death = death;
		guys[i].total = total;
		guys[i].time_to_die = ft_atoi(argv[2]);
		guys[i].time_to_eat = ft_atoi(argv[3]);
		guys[i].time_to_sleep = ft_atoi(argv[4]);
		guys[i].nb = i;
		guys[i].eat_count = 0;
		guys[i].time_stamp = get_time(NULL);
		guys[i].start_time = guys[i].time_stamp;
		guys[i].limit = -1;
		if (argc == 6)
			guys[i].limit = ft_atoi(argv[5]);
		i++;
	}
	return (0);
}
