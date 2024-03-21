#include <unistd.h>
#include <stdlib.h>

int	adress_size(unsigned long n, int base)
{
	int				size;

	size = 1;
	while (n >= (unsigned long long)base)
	{
		n /= base;
		size++;
	}
	size++;
	return (size);
}

void	print_0x(unsigned long nbr, int base, char *result, char *str)
{
	int	aux;

	aux = 0;
	while (nbr >= (unsigned long long)base)
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

void	adress_convert(char *str, unsigned long n, int size, int base)
{
	char				*result;

	result = malloc(size * sizeof(char));
	if (result)
	{
		print_0x(n, base, result, str);
		free (result);
	}
}

void	ft_put0x(unsigned long n, char x)
{
	int	base;
	int	size;

	write(1, "0", 1);
	write(1, &x, 1);
	base = 16;
	size = adress_size(n, base);
	if (x == 'x')
		adress_convert("0123456789abcdef", n, size, base);
	else if (x == 'X')
		adress_convert("0123456789ABCDEF", n, size, base);
}
