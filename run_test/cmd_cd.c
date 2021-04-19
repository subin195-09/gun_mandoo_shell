
#include "minishell.h"

int		cmd_cd(t_nd *com, char **en, char *av)
{
	char	tmp[PATH_MAX];
	char	*tmp2;
	int		rt;

	getcwd(tmp, PATH_MAX);
	rt = ft_strncmp(com->args[1], "~", ft_strlen(com->args[1]));
	if (rt == 0 || !com->args[1])
		rt = chdir(getenv("HOME")); // HOME 환경변수가 없어졌을때도 동작하게 할 것인가
	// 예외 처리에 대해 더 연구하고 좀 더 정확하게 수정할 것
	else if (ft_strnstr(com->args[1], tmp, ft_strlen(tmp)))
	{
		rt = chdir(com->args[1]);
	}
	else
	{
		if (com->args[1][0] == '.' && com->args[1][1] == '/')
			rt = chdir(com->args[1]);
		else
		{
			tmp2 = ft_strjoin("./", com->args[1]);
			rt = chdir(tmp2);
			free(tmp2);
		}
	}

	if (rt < 0)
		printf("%s: %s: %s\n",com->args[0], com->args[1], strerror(errno));
	// else
	// {
	// 	// 환경변수에 추가해주는 함수 작업필요
	// 	ft_export(OLDPWD, tmp);
	// 	getcwd(tmp, 1024);
	// 	ft_export(PWD, tmp);
	// }
	return (EXIT_SUCCESS);
}
