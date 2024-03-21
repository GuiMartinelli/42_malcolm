#include <unistd.h>
#include <stdlib.h>

int	nb_size(unsigned int n, int base)
{
	int	size;

	size = 1;
	while (n >= (unsigned int)base)
	{
		n /= base;
		size++;
	}
	size++;
	return (size);
}

void	nb_print(unsigned int nbr, int base, char *result, char *str)
{
	int	aux;

	aux = 0;
	while (nbr >= (unsigned int)base)
	{
		*(result + aux) = *(str + (nbr % base));
		nbr /= base;
		aux++;
	}
	*(result + aux) = *(str + nbr);
	while ((result + aux) >= result)
	{
		write (1, &*(result + aux), 1);
		aux--;
	}
}

void	nb_convert(char *str, unsigned int n, int size, int base)
{
	char	*result;

	result = malloc(size * sizeof(char));
	if (result)
	{
		nb_print(n, base, result, str);
		free (result);
	}
}

void	ft_putnbrX(unsigned int n, char x)
{
	int	base;
	int	size;

	base = 16;
	size = nb_size(n, base);
	if (x == 'x')
		nb_convert("0123456789abcdef", n, size, base);
	else if (x == 'X')
		nb_convert("0123456789ABCDEF", n, size, base);
}
