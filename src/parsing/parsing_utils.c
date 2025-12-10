/* int	skip_spaces(char c) */
/* { */
/* 	return (c == 32 || (c >= 9 && c <= 13)); */
/* } */

/* #include <stdio.h> */

/* int	get_args(char *cmd) */
/* { */
/* 	int	i; */
/* 	int	j; */
/* 	int	args; */

/* 	i = 0; */
/* 	args = 0; */
/* 	while (cmd[i]) */
/* 	{ */
/* 		while (cmd[i] && cmd[i] == 32) */
/* 			i++; */
/* 		if (cmd[i] > 32 && cmd[i] < 127) */
/* 		{ */
/* //			args++; */
/* 			if (cmd[i] == 34 || cmd[i] == 39) */
/* 			{ */
/* 				j = i; */
/* 				j++; */
/* 				while (cmd[j] && (cmd[j] != 34 && cmd[j] != 39)) */
/* 				{ */
/* 					if (cmd[j + 1] == 34 || cmd[j + 1] == 39) */
/* 					{ */
/* 						i = j; */
/* 						break ; */
/* 					} */
/* 					else */
/* 						j++; */
/* 				} */
/* 			} */
/* //			else */
/* //				i++; */
/* //			args++; */
/* 		} */
/* 		i++; */
/* 		if (cmd[i] == 34 || cmd[i] == 39) */
/* 			i++; */
/* 		if (!cmd[i] || cmd[i] == 32) */
/* 			args++; */
/* 	} */
/* 	return (args); */
/* } */

/* int	main(void) */
/* { */
/* 	char	*str = "ola eu sou 'esmega coco' lol     lmao'   sakj"; */
/* //	char	*str = "ola eu sou 'esmega coco'lol     lmao'   sakj"; */
/* //	char	*str = "ola eu sou 'esmega coco' lol"; */
/* 	printf("%i\n", get_args(str)); */
/* } */
