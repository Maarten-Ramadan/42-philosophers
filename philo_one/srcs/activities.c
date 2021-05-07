/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:24:04 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 09:55:41 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

bool	check_deaths(t_data *guy)
{
	if (get_time(NULL) >= (guy->time_stamp + guy->time_to_die))
		return (true);
	else
		return (false);
}

void	sleeeep(int time_to_sleep)
{
	unsigned long		start;

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
	if (pthread_mutex_lock(guy->r_fork) == -1)
		return (message(1, NULL));
	if (*guy->death)
	{
		pthread_mutex_unlock(guy->r_fork);
		return (1);
	}
	if (message(3, guy))
		return (1);
	if (pthread_mutex_lock(guy->l_fork) == -1)
		return (message(1, NULL));
	if (message(3, guy))
		return (1);
	if (*guy->death || eat_or_die(guy, 1))
	{
		pthread_mutex_unlock(guy->r_fork);
		pthread_mutex_unlock(guy->l_fork);
		return (1);
	}
	if (message(4, guy))
		return (1);
	sleeeep(guy->time_to_eat);
	if (pthread_mutex_unlock(guy->r_fork) || pthread_mutex_unlock(guy->l_fork))
		return (message(2, NULL));
	return (0);
}
