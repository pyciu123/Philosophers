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
	usleep(milliseconds * 1000);
    return (0);
}

void *life_monitor(void *arg)
{
    t_program *program = (t_program *)arg;
    int i;

    while (program->all_alive)
    {
        i = 0;
        while (i < program->num_philo && program->all_alive)
        {
            pthread_mutex_lock(&program->state_lock);
            long current_time = get_current_time();
            long time_diff = current_time - program->philos[i].last_meal_time;

            if (time_diff > program->time_to_die)
            {
                program->all_alive = 0;
                pthread_mutex_unlock(&program->state_lock);

                pthread_mutex_lock(&program->print_locks);
                printf("Philosopher %d has died at %ld ms\n", program->philos[i].id, current_time);
                pthread_mutex_unlock(&program->print_locks);

                return NULL;
            }
            pthread_mutex_unlock(&program->state_lock);
            i++;
			ft_usleep(10)
        }
    }

    return NULL;
}
