/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 12:05:35 by Marty         #+#    #+#                 */
/*   Updated: 2021/02/22 10:14:04 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
		printf("%lu - philo %d: died\n", get_time(guy), guy->nb);
	else if (message == 6)
		printf("%lu - philo %d: thinks\n", get_time(guy), guy->nb);
	else if (message == 7)
		printf("%lu - philo %d: sleeps\n", get_time(guy), guy->nb);
	if (sem_post(guy->print) == -1)
		return (printf("sem_post fail"));
	return (0);
}

void	destroy(t_data *guys, pthread_t *newthread)
{
	sem_close(guys->forks);
	sem_close(guys->eat);
	sem_close(guys->print);
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("print");
	free(newthread);
	free(guys->death);
	free(guys);
}

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
