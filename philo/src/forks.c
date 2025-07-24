/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odana <odana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:06 by odana             #+#    #+#             */
/*   Updated: 2025/07/24 13:56:30 by odana            ###   ########.fr       */
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

// void determine_fork_order(t_philo *philo, pthread_mutex_t **first, 
//     pthread_mutex_t **second)
// {
//     if (philo->data->num_philos == 2 && philo->id == philo->data->num_philos)
//     {
//         *first = philo->right_fork;
//         *second = philo->left_fork;
//     }
//     else if (philo->left_fork < philo->right_fork)
//     {
//         *first = philo->left_fork;
//         *second = philo->right_fork;
//     }
//     else
//     {
//         *first = philo->right_fork;
//         *second = philo->left_fork;
//     }
// }

int take_forks(t_philo *philo)
{
    if (philo->data->num_philos == 1)
        return (handle_single_philosopher(philo));
    if (philo->id % 2 == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_log(philo->data, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        safe_log(philo->data, philo->id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        safe_log(philo->data, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        safe_log(philo->data, philo->id, "has taken a fork");
    }
    return (1);
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}