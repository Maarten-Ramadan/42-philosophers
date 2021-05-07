/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 12:04:03 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:26:32 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*philo_go(void *void_guy)
{
	t_data	*guy;

	guy = void_guy;
	while (1)
	{
		if (eat(guy))
			return (NULL);
		if (go_sleep(guy))
			return (NULL);
		if (message(6, guy))
			return (NULL);
		if (!guy->limit)
		{
			sem_post(guy->death);
			exit(0);
		}
	}
	return (NULL);
}

void	*check_pulse(void *void_guy)
{
	t_data	*guy;

	guy = void_guy;
	while (1)
		eat_or_die(guy, 2);
	return (NULL);
}

void	*kill_thread(void *void_guys)
{
	t_data	*guys;
	int		i;

	i = 0;
	guys = void_guys;
	if (sem_wait(guys->death) == -1)
	{
		printf("sem_wait failed");
		return (NULL);
	}
	while (i < guys->total)
	{
		kill(guys[i].pid, SIGTERM);
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
		guys[i].pid = fork();
		sleeeep(1);
		if (!guys[i].pid)
		{
			if (pthread_create(&newthread[i], NULL, check_pulse, &guys[i]))
				return ;
			philo_go(&guys[i]);
		}
		i++;
	}
	if (pthread_create(&newthread[i], NULL, kill_thread, guys))
		return ;
	while (i >= 0)
	{
		if (pthread_join(newthread[i], NULL))
			return ;
		i--;
	}
	join_and_wait(guys, i);
}

int	main(int argc, char **argv)
{
	t_data		*guys;
	pthread_t	*newthread;

	if (argc == 5 || argc == 6)
	{
		parse(argc, argv);
		guys = malloc(sizeof(t_data) * ft_atoi(argv[1]));
		newthread = malloc(sizeof(pthread_t) * (ft_atoi(argv[1]) + 1));
		init(argc, argv, guys);
		if (sem_management(guys))
			return (0);
		threading_action(guys, newthread);
		destroy(guys, newthread);
	}
	else
		printf("Error args\n");
	return (0);
}
