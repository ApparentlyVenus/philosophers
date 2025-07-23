/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:59:46 by odana             #+#    #+#             */
/*   Updated: 2025/07/22 17:32:10 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*death_monitor(void *arg)
{
	t_data	*data;
    
	data = (t_data *)arg;
	while (!data->simulation_end)
	{
		if (!check_last_meal(data))
			return (NULL);
		if (data->meals_required != -1)
		{
			if (!check_meal_count(data))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_last_meal(t_data *data)
{
    int i;
    long long current_last_meal;
    
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->meal);
        current_last_meal = get_timestamp() - data->philos[i].last_meal;
        pthread_mutex_unlock(&data->meal);
        if (current_last_meal > data->time_to_die)
        {
            pthread_mutex_lock(&data->death);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->death);
            safe_log(data, data->philos[i].id, "died");
            return (0);
        }
        i++;
    }
    return (1);
}

int check_meal_count(t_data *data)
{
    int i;
    int all_finished;

    i = 0;
    all_finished = 1;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->meal);
        if (data->philos[i].meals_eaten < data->meals_required)
            all_finished = 0;
        pthread_mutex_unlock(&data->meal);
        if (!all_finished)
            break ;
        i++;
    }
    if (all_finished)
    {
        pthread_mutex_lock(&data->death);
        data->simulation_end = 1;
        pthread_mutex_unlock(&data->death);
        return (0);
    }
    return (1);
}
