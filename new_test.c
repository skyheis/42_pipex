#include <stdio.h>

void	ft_sleep_kinda(size_t k)
{
	long unsigned i;

	if (!k)
		return ;
	i = 0;
	while (i < 82949672)
		i++;
	if (k)
		ft_sleep_kinda(k - 1);
}

int main(void)
{
	ft_sleep_kinda(1);
}
