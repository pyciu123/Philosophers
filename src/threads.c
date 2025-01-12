#include "../include/philo.h"

int	run_philosophers(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philo)
	{
		if (pthread_create(&program->philos[i].thread, NULL, philo_routine, &program->philos[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d!\n", program->philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	run_monitor(t_program *program, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, life_monitor, program) != 0)
	{
		printf("Failed to create life monitor thread!");
		return (1);
	}
	return (0);
}
void philo_thread_join(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philo)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}