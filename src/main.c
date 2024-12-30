#include "../include/philo.h"

static int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(np * num));
}

static void	setup_properties(t_program *program, char **argv)
{
	program->num_philo = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
}



int main(int argc, char **argv)
{
	t_program	program;
	pthread_t	monitor;

	if (argc != 5)
	{
		printf("USAGE: ./philosophers [num of philo] [time to die] [time to eat] [time to sleep]\n");
		return (1);
	}
	init_program(&program);
	setup_properties(&program, argv);
	init_forks(&program, program.num_philo);
	init_philo(&program, program.num_philo);
	if (run_monitor(&program, &monitor) == 1)
		return (1);
	if (run_philosophers(&program) == 1)
		return (1);
	pthread_join(monitor, NULL);
	philo_thread_join(&program);
	return (0);
}