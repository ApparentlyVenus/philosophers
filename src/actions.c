/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:48:08 by odana             #+#    #+#             */
/*   Updated: 2025/07/23 13:59:42 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int philo_eat(t_philo *philo)
{
    if (!take_forks(philo))
        return (0);
    pthread_mutex_lock(&philo->data->meal);
    philo->last_meal = get_timestamp();
    safe_log(philo->data, philo->id, "is eating");
    pthread_mutex_unlock(&philo->data->meal);
    precise_sleep(philo->data->time_to_eat);
    pthread_mutex_lock(&philo->data->meal);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal);
    release_forks(philo);
    return (1);
}

void philo_sleep(t_philo *philo)
{
    safe_log(philo->data, philo->id, "is sleeping");
    precise_sleep(philo->data->time_to_sleep);
}

void philo_think(t_philo *philo)
{
    safe_log(philo->data, philo->id, "is thinking");
    usleep(1000);
}