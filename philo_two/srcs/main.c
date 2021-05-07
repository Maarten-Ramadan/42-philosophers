/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 12:04:03 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:36:14 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	eat_or_die(t_data *guy, int nb)
{
	int	ret;

	if (sem_wait(guy->eat) == -1)
		return (1);
	if (nb == 1)
	{
		guy->time_stamp = get_time(NULL);
		guy->limit--;
		if (sem_post(guy->eat) == -1)
			return (1);
	}
	else
	{
		ret = check_deaths(guy);
		if (sem_post(guy->eat) == -1)
			return (1);
		return (ret);
	}
	return (0);
}

void	*philo_go(void *void_guy)
{
	t_data	*guy;

	guy = void_guy;
	while (!*guy->death)
	{
		if (*guy->death || eat(guy))
			return (NULL);
		if (*guy->death || go_sleep(guy))
			return (NULL);
		if (*guy->death || message(6, guy))
			return (NULL);
		if (!guy->limit)
			return (NULL);
	}
	return (NULL);
}

void	*check_pulse(void *void_guys)
{
	t_data	*guys;
	int		i;

	i = 0;
	guys = void_guys;
	while (1)
	{
		if (i == guys->total)
			i = 0;
		if (eat_or_die(&guys[i], 0) && guys[i].limit != 0)
		{
			message(5, &guys[i]);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	threading_action(t_data *guys, pthread_t *newthread)
{
	int	i;

	i = 0;
	while (i < guys->total)
	{
		if (pthread_create(&newthread[i], NULL, philo_go, &guys[i]))
			return ;
		sleeeep(1);
		i++;
	}
	sleeeep(1);
	if (pthread_create(&newthread[i], NULL, check_pulse, guys))
		return ;
	while (i > 0)
	{
		i--;
		if (pthread_join(newthread[i], NULL))
			return ;
	}
}

int	main(int argc, char **argv)
{
	pthread_t	*newthread;
	t_data		*guys;

	if (argc == 5 || argc == 6)
	{
		if (parse(argc, argv))
			return (0);
		guys = malloc(sizeof(t_data) * ft_atoi(argv[1]));
		newthread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]) + 1);
		if (!guys)
			return (0);
		if (init(argc, argv, guys, 0))
			return (0);
		if (sem_management(guys))
			return (0);
		threading_action(guys, newthread);
		destroy(guys, newthread);
	}
	else
		printf("Error args\n");
	return (0);
}
