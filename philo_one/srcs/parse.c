/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 12:02:31 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:05:01 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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

int	mutex_management(t_data *guys, int i)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*eat;

	guys->forks = malloc(sizeof(pthread_mutex_t) * guys->total);
	print = malloc(sizeof(pthread_mutex_t));
	eat = malloc(sizeof(pthread_mutex_t));
	if (!guys->forks || !print || !eat)
		return (printf("malloc fail\n"));
	if (pthread_mutex_init(eat, NULL) == -1
		|| pthread_mutex_init(print, NULL) == -1)
		return (printf("mutex init error\n"));
	while (i < guys->total)
	{
		guys[i].print = print;
		guys[i].eat = eat;
		if (pthread_mutex_init(&guys->forks[i], NULL) == -1)
			return (printf("mutex init error\n"));
		guys[i].l_fork = &guys->forks[i];
		if (i > 0)
			guys[i].r_fork = &guys->forks[i - 1];
		i++;
	}
	guys[0].r_fork = &guys->forks[i - 1];
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
