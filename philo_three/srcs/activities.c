/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:24:04 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:26:05 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	sleeeep(int time_to_sleep)
{
	unsigned long	start;

	start = get_time(NULL);
	while (get_time(NULL) < start + time_to_sleep)
		usleep(100);
}

int	go_sleep(t_data *guy)
{
	if (message(7, guy))
		return (1);
	sleeeep(guy->time_to_sleep);
	return (0);
}

int	eat(t_data *guy)
{
	if (sem_wait(guy->forks) == -1)
		return (message(1, NULL));
	if (message(3, guy))
		return (1);
	if (sem_wait(guy->forks) == -1)
		return (message(1, NULL));
	if (message(3, guy))
		return (1);
	if (eat_or_die(guy, 1))
		return (1);
	if (message(4, guy))
		return (1);
	sleeeep(guy->time_to_eat);
	if (sem_post(guy->forks) == -1)
		return (message(2, NULL));
	if (sem_post(guy->forks) == -1)
		return (message(2, NULL));
	return (0);
}

bool	check_deaths(t_data *guy)
{
	if (get_time(NULL) >= (guy->time_stamp + guy->time_to_die))
	{
		message(5, guy);
		if (sem_post(guy->death) == -1)
			exit(1);
		return (true);
	}
	else
		return (false);
}

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
		if (!ret && sem_post(guy->eat) == -1)
			return (1);
		return (ret);
	}
	return (0);
}
