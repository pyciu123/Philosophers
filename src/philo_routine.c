#include "../include/philo.h"

static void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->print_locks);
	printf("Philosopher %d is thinking...\n", philo->id);
	pthread_mutex_unlock(&philo->program->print_locks);
}

static void eat(t_philo *philo)
{
    // Zajmowanie prawych i lewych widelców
    pthread_mutex_lock(&philo->r_fork->mutex);
    pthread_mutex_lock(&philo->l_fork->mutex);

    // Aktualizacja czasu ostatniego posiłku przed rozpoczęciem jedzenia
    pthread_mutex_lock(&philo->program->state_lock);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->program->state_lock);

    // Informowanie o rozpoczęciu jedzenia
    pthread_mutex_lock(&philo->program->print_locks);
    printf("Philosopher %d is eating\n", philo->id);
    pthread_mutex_unlock(&philo->program->print_locks);

    // Symulacja jedzenia
    ft_usleep(philo->program->time_to_eat);

    // Zwolnienie widelców po jedzeniu
    pthread_mutex_unlock(&philo->l_fork->mutex);
    pthread_mutex_unlock(&philo->r_fork->mutex);
}

static void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->print_locks);
	printf("Philosopher %d is sleeping\n", philo->id);
	ft_usleep(philo->program->time_to_sleep);
	pthread_mutex_unlock(&philo->program->print_locks);
}

static int	check_if_alive(t_program *program)
{
	pthread_mutex_lock(&program->state_lock);
	if (program->all_alive == 0)
	{
		pthread_mutex_unlock(&program->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&program->state_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (check_if_alive(program) == 1)
			return (NULL);
		eat(philo);
		if (check_if_alive(program) == 1)
			return (NULL);
		do_sleep(philo);
		if (check_if_alive(program) == 1)
			return (NULL);
		think(philo);
	}
	pthread_mutex_lock(&program->print_locks);
	printf("Philosopher %d stops working...\n", philo->id);
	pthread_mutex_unlock(&program->print_locks);
	return (NULL);
}
