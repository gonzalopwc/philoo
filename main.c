/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/10/09 20:30:52 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valabs(int num)
{
	if (num < 0)
		num = -num;
	return (num);
}

static int	condig(int num)
{
	int	i;

	i = 0;
	if (num < 0)
		i++;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*src;

	i = condig(n);
	src = malloc(i + 1);
	if (!src)
		return (NULL);
	src[0] = '0';
	src[condig(n)] = '\0';
	if (n < 0)
		src[0] = '-';
	while (n != 0)
	{
		src[i - 1] = valabs(n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (src);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		num;

	i = 0;
	if (!n)
		return (0);
	num = (unsigned char)s1[i] - (unsigned char)s2[i];
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
		{
			num = (unsigned char)s1[i] - (unsigned char)s2[i];
			break ;
		}
		i++;
	}
	return (num);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*scr;
	int		j;

	i = ft_strlen(s1) + ft_strlen(s2);
	scr = malloc(i + 1);
	if (scr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		scr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		scr[i] = s2[j];
		i++;
		j++;
	}
	scr[i] = '\0';
	return (scr);
}


void	ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*src;

	if (nmemb * size >= SIZE_MAX)
		return (NULL);
	src = malloc(nmemb * size);
	if (src == NULL)
		return (NULL);
	ft_bzero(src, nmemb * size);
	return (src);
}

/*#################################################################*/

char	**ft_free(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i] = NULL;
		i++;
	}
	free(mat);
	mat = NULL;
	return (NULL);
}

void	ft_error(char *str, char *file)
{
	char	*msg;

	if (file)
	{
		msg = ft_strjoin(str, file);
		if (!msg)
			return (perror("Error\n"));
		ft_putstr_fd(msg, 2);
	}
	else
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	null_check(int argn, char **argv)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < argn)
	{
		if (ft_strncmp(argv[i], "", 1) == 0)
			ft_error("Error null argument", NULL);
		j = 0;
		while (argv[i][j] == ' ')
			j++;
		if (j == ft_strlen(argv[i]))
			ft_error("Error spaces argument", NULL);
		i++;
	}
}

int	philo_atoi(const char *nscr)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (nscr[i] == ' ' || nscr[i] == '\n' || nscr[i] == '\r'
		|| nscr[i] == '\t' || nscr[i] == '\v' || nscr[i] == '\f')
		i++;
	if (nscr[i] == '-' || nscr[i] == '+')
		ft_error(SYMBOL, NULL);
	while (nscr[i] != '\0')
	{
		if ('0' <= nscr[i] && nscr[i] <= '9')
			num = num * 10 + (nscr[i] - '0');
		else
			ft_error(NUMBERS, NULL);
		i++;
	}
	return (num);
}

void	arg_checker(int argn, char **argv)
{
	int		i;
	int		num;
	char	*test;

	if (argn > 6 || argn < 5)
		ft_error(ARGUMENTS, NULL);
	null_check(argn, argv);
	i = 0;
	while (argv[++i])
	{
		num = philo_atoi(argv[i]);
		test = ft_itoa(num);
		if (ft_strncmp(test, argv[i], ft_strlen(argv[i])) != 0)
		{
			free(test);
			ft_error(BIG_NUM, NULL);
		}
		free(test);
	}
}

/*###############################################################*/

t_ini_vals	*philo_values(int argn, char **argv)
{
	t_ini_vals		*philo_vals;

	philo_vals = ft_calloc(1, sizeof(t_ini_vals));
	if (!philo_vals)
		ft_error(MALLOC, NULL);
	philo_vals->num_philo = philo_atoi(argv[1]);
	philo_vals->time_die = philo_atoi(argv[2]);
	philo_vals->time_eat = philo_atoi(argv[3]);
	philo_vals->time_sleep = philo_atoi(argv[4]);
	if (argn == 6)
		philo_vals->num_times = philo_atoi(argv[5]);
	else
		philo_vals->num_times = -1;
	gettimeofday(&philo_vals->ini_time, NULL);
	return (philo_vals);
}

void	print_philo_info(t_ini_vals *ini_vals)
{
	printf("Número de filósofo: %d\n", ini_vals->num_philo);
	printf("Tiempo para morir: %d ms\n", ini_vals->time_die);
	printf("Tiempo para comer: %d ms\n", ini_vals->time_eat);
	printf("Tiempo para dormir: %d ms\n", ini_vals->time_sleep);
	printf("Número de veces que come: %d\n", ini_vals->num_times);
	printf("El tiempo inicial en seg: %ld\n", ini_vals->ini_time.tv_sec);
}

t_table	*create_table(void)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	table->head = NULL;
	return (table);
}

void	philo_append(t_table *list, int id)
{
	t_philo	*new_philo;
	t_philo	*last_philo;

	new_philo = ft_calloc(1, sizeof(t_philo));
	if (!new_philo)
		ft_error(MALLOC, NULL);
	new_philo->id = id;
	new_philo->next = new_philo;
	new_philo->prev = new_philo;
	if (list->head == NULL)
		list->head = new_philo;
	else
	{
		last_philo = list->head->prev;
		last_philo->next = new_philo;
		new_philo->prev = last_philo;
	}
	new_philo->next = list->head;
	list->head->prev = new_philo;
}

void	free_table(t_table *table)
{
	t_philo	*current;
	t_philo	*next;

	current = table->head;
	while (current != NULL)
	{
		next = current->next;
		if (next == table->head)
			next = NULL;
		free(current);
		current = NULL;
		current = next;
	}
	free(table);
}

struct timeval dif_time(struct timeval	ini, struct timeval	fin)
{
	long			seconds;
	long			microseconds;
	struct timeval	time;

	seconds = fin.tv_sec - ini.tv_sec;
	microseconds = fin.tv_usec - ini.tv_usec;
	if (microseconds < 0)
	{
		seconds--;
		microseconds = microseconds + 1000000;
	}
	time.tv_sec = seconds;
	time.tv_usec = microseconds;
	return (time);
}

void    *voiffun(void *arg)
{
    printf("Hola mundo\n");
    return (0);
}

int	main(int argn, char **argv)
{
	t_ini_vals		*philo_vals;
	t_table			*table;
	pthread_t		*philo_thread;
	int				i;
	struct timeval	tv;
	struct timeval	final;
    t_args_thread   *args_thread;

	arg_checker(argn, argv);
	philo_vals = philo_values(argn, argv);
	philo_thread = ft_calloc(philo_vals->num_philo, sizeof(pthread_t));
    if (!philo_thread)
        ft_error(MALLOC, NULL);
    args_thread = ft_calloc(1, sizeof(args_thread));
    if (!args_thread)
        ft_error(MALLOC, NULL);
	table = create_table();
	i = -1;
	while (++i < philo_vals->num_philo)
		philo_append(table, i);
    args_thread->ini_vals = philo_vals;
    args_thread->table = table;
	i = -1;
	while (++i < philo_vals->num_philo)
    {
	    if (pthread_create(&philo_thread[i], NULL, &voiffun, args_thread) != 0)
	 	    ft_error(PTHREAD, NULL);
    }	
	i = -1;
	while (++i < 8)
	{
		printf("El id es: %i\n", table->head->id);
		table->head = table->head->next;
	}
	usleep(3000000);
	gettimeofday(&tv, NULL);
	final = dif_time(philo_vals->ini_time, tv);
    printf("Han pasado: %ld segundos y %ld microsegundos\n", final.tv_sec, final.tv_usec);
    free(args_thread);
	free(philo_vals);
	free_table(table);
}
