#include "sh.h"

int			cnt_words(char const *s, char c)
{
	int		i;
	int		in_word;

	i = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c && in_word == 1)
		{
			in_word = 0;
			continue ;
		}
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			i++;
		}
		s++;
	}
	return (i);
}

