/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 12:05:35 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:28:21 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	join_and_wait(t_data *guys, int i)
{
	while (i < guys->total)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	message(int message, t_data *guy)
{
	if (sem_wait(guy->print) == -1)
		return (printf("sem_wait fail"));
	if (message == 1)
		return (printf("sem_wait fail"));
	else if (message == 2)
		return (printf("sem_post fail\n"));
	else if (message == 3)
		printf("%lu - philo %d: has taken a fork\n", get_time(guy), guy->nb);
	else if (message == 4)
		printf("%lu - philo %d: eats\n", get_time(guy), guy->nb);
	else if (message == 5)
		return (printf("%lu - philo %d: died\n", get_time(guy), guy->nb));
	else if (message == 6)
		printf("%lu - philo %d: thinks\n", get_time(guy), guy->nb);
	else if (message == 7)
		printf("%lu - philo %d: sleeps\n", get_time(guy), guy->nb);
	if (sem_post(guy->print) == -1)
		return (printf("sem_post fail"));
	return (0);
}

unsigned long int	get_time(t_data *guy)
{
	struct timeval		current_time;
	unsigned long int	now;

	gettimeofday(&current_time, NULL);
	now = current_time.tv_sec * 1000;
	now += current_time.tv_usec / 1000;
	if (!guy)
		return (now);
	else
		return (now - guy->start_time);
}

int	destroy(t_data *guys, pthread_t *newthread)
{
	if (sem_unlink("forks") || sem_unlink("death")
		|| sem_unlink("print") || sem_unlink("eat"))
		printf("sem_unlink failed\n");
	if (sem_close(guys->print) || sem_close(guys->forks)
		|| sem_close(guys->eat) || sem_close(guys->death))
		printf("sem_close failed\n");
	free(newthread);
	free(guys);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
