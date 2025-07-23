/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:06 by odana             #+#    #+#             */
/*   Updated: 2025/07/23 14:20:16 by odana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int handle_single_philosopher(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    safe_log(philo->data, philo->id, "has taken a fork");
    pthread_mutex_unlock(philo->left_fork);
    return (0);
}

void determine_fork_order(t_philo *philo, pthread_mutex_t **first, 
    pthread_mutex_t **second)
{
    if (philo->left_fork < philo->right_fork)
    {
        *first = philo->left_fork;
        *second = philo->right_fork;
    }
    else
    {
        *first = philo->right_fork;
        *second = philo->left_fork;
    }
}

int take_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    
    if (philo->data->num_philos == 1)
        return (handle_single_philosopher(philo));
    determine_fork_order(philo, &first_fork, &second_fork);
    pthread_mutex_lock(first_fork);
    if (philo->data->simulation_end)
    {
        pthread_mutex_unlock(first_fork);
        return (0);
    }
    safe_log(philo->data, philo->id, "has taken a fork");
    pthread_mutex_lock(second_fork);
    if (philo->data->simulation_end)
    {
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        return (0);
    }
    safe_log(philo->data, philo->id, "has taken a fork");
    return (1);
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}