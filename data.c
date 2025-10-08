#include "minishellM.h"

t_msh	*msh(void)
{
	static t_msh	data;
	return (&data);
}