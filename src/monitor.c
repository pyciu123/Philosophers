#include "../include/philo.h"

long get_current_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return time;
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void *life_monitor(void *arg)
{
    t_program *program = (t_program *)arg;
    int i;
    long meal_time;
	long current_time;
    int	is_eating;

    while (program->all_alive)
    {
        i = 0;
        while (i < program->num_philo && program->all_alive)
        {
            pthread_mutex_lock(&program->meal_lock);
            meal_time = program->philos[i].last_meal_time;
			current_time = get_current_time();
			is_eating = program->philos[i].is_eating;
            pthread_mutex_unlock(&program->meal_lock);
			pthread_mutex_lock(&program->dead_lock);
            if (current_time - meal_time > program->time_to_die && is_eating != 1)
            {
                program->all_alive = 0;
                pthread_mutex_unlock(&program->dead_lock);
                pthread_mutex_lock(&program->print_locks);
                printf("Philosopher %d has died at %ld ms\n", program->philos[i].id, current_time);
                pthread_mutex_unlock(&program->print_locks);
                return NULL;
            }
            pthread_mutex_unlock(&program->dead_lock);
            i++;
        }
		usleep(50);
    }
    return NULL;
}
