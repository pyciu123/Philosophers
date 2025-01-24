#include "../include/philo.h"

void	think(t_philo *philo)
{
	msg("is thinking", philo, philo->id, 0);
}

void	f_sleep(t_philo *philo)
{
	msg("is sleeping", philo, philo->id, 0);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	msg("has taken left fork", philo, philo->id, 0);
	pthread_mutex_lock(philo->r_fork);
	msg("has taken right fork", philo, philo->id, 0);
	pthread_mutex_lock(philo->meal_lock);
	philo->is_eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	msg("is eating", philo, philo->id, 0);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->is_eating = 0;
	philo->meal_ate++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
