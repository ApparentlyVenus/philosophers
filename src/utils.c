/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:32:35 by odana             #+#    #+#             */
/*   Updated: 2025/07/23 14:01:00 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long get_timestamp(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long long get_elapsed_time(t_data *data)
{
    return get_timestamp() - data->start_time;
}

void precise_sleep(int duration_ms)
{
    long long start = get_timestamp();
    
    while (get_timestamp() - start < duration_ms)
    {
        usleep(100);
    }
}

void safe_log(t_data *data, int philo_id, char *message)
{
    pthread_mutex_lock(&data->log);
    if (!data->simulation_end) {
        printf("%lld %d %s\n", get_elapsed_time(data), philo_id, message);
    }
    pthread_mutex_unlock(&data->log);
}
