#include "lem_in.h"

void	delete(s_set_path **stack)
{
	s_set_path *tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	tmp = NULL;
}

void	push(s_set_path **stack, int id)
{
	s_set_path *tmp;

	tmp = *stack;
	if (*stack == NULL)
	{
		*stack = (s_set_path *)malloc(sizeof(s_set_path));
		(*stack)->var = id;
		(*stack)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (s_set_path *)malloc(sizeof(s_set_path));
	tmp->next->var = id;
	tmp->next->next = NULL;
}

void	matrix_orient(s_ferm **ferm, s_info *info)
{
	int branch;
	int room;
	s_set_path *stack;

	branch = 0;
	room = 0;
	stack = NULL;
	while (ferm[branch][branch].type != START)
		branch++;
	push(&stack, branch);
	while (stack)
	{
		branch = stack->var;
		while (room < info->c_rooms && ferm[branch][branch].type != END)
		{
			if (ferm[branch][room].pass == OPEN)
			{
				ferm[room][branch].pass = CLOSE;
				push(&stack, room);
			}
			room++;
		}
		room = 0;
		delete(&stack);
	}
}