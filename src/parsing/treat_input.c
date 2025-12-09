char	**treat_input(char *str)
{
	int		i;
	char	**array;
	char	quote;

	i = 0;
	array = NULL;
	while (str[i] != ' ')
		i++;
	while (is_alpha(str[i]))
		i++;
	if (str[i] == '"' || str[i] == 39)
	{
		quote = str[i];
		while ()
	}
}
