#include "minishell.h"

void	p_handler(int sig)
{
	if (sig != SIGINT)
	{
		return ;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	error_status = 1;
}
/**
 * ls 등 명령어 실행 후 프롬프트에서 SIGINT 시그널 보낼 시 rl_redisplay 고장남
 * redisplay()의 문제 -> cat 입력 대기 중 SIGINT시 프롬프트 한 줄에 두 번 출력
*/

void	c_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
	else if (sig == SIGTERM)
		exit(0);
}