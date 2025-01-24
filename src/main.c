#include "../include/philo.h"

void	ft_usleep(int time)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time)
		usleep(100);
}

void	msg(char *str, t_philo *philo, int id, int mon_check)
{
	long	offset_time;

	pthread_mutex_lock(philo->dead_lock);
	if ((*philo->dead == 1 && mon_check == 0) || *philo->is_limit_reached == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->write_lock);
	offset_time = get_current_time() - philo->start_time;
	printf("%ld %d %s\n", offset_time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	ft_atoi(const char *str)
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

static int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[300];
	pthread_mutex_t	forks[300];

	if (argc != 5 && argc != 6)
	{
		printf("USAGE: ./philosophers [num of philo] [time to die]"
			"[time to eat] [time to sleep]"
			"[number_of_times_each_philosopher_must_eat (optional)]\n"
			);
		return (1);
	}
	if (check_args(argv) == 1)
	{
		printf("arguments need to be intinger\n");
		return (1);
	}
	init_program(&program, philos, argv);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(&program, philos, forks, argv);
	init_threads(&program, forks);
	return (0);
}
