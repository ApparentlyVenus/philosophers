/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:32:35 by odana             #+#    #+#             */
/*   Updated: 2025/07/24 14:39:44 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(int duration_ms, t_data *data)
{
	long long	start;

	start = get_time();
	while (get_time() - start < duration_ms)
	{
		pthread_mutex_lock(&data->death);
		if (data->simulation_end)
		{
			pthread_mutex_unlock(&data->death);
			break ;
		}
		pthread_mutex_unlock(&data->death);
		usleep(100);
	}
}

void	safe_log(t_data *data, int philo_id, char *message)
{
	pthread_mutex_lock(&data->death);
	pthread_mutex_lock(&data->log);
	if (!data->simulation_end || (message && strcmp(message, "died") == 0))
		printf("%lld %d %s\n", get_time() - data->start_time,
			philo_id, message);
	pthread_mutex_unlock(&data->log);
	pthread_mutex_unlock(&data->death);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}
