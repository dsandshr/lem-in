#include "lem_in.h"

void restore_ferm(s_info *info, s_ferm **ferm)
{
	int branch;
	int rooms;

	rooms = 0;
	branch = 0;
	while (branch < info->c_rooms)
	{
		while (rooms < info->c_rooms)
		{
			if (ferm[branch][rooms].pass == -1)
				ferm[branch][rooms].pass = OPEN;
			rooms++;
		}
		rooms = 0;
		branch++;
	}
}

int recur_orient(s_info *info, s_ferm **ferm, int branch)
{
	int room;
	int go;

	room = 0;
	go = 0;
	if (ferm[branch][branch].type == END)
		return (OPEN);
	else if (ferm[branch][branch].type == START)
		return (CLOSE);
	while (room < info->c_rooms)
	{
		if(ferm[branch][room].pass == OPEN)
		{
			ferm[room][branch].pass = -1;
			ferm[branch][room].pass = -1;
			if(recur_orient(info, ferm, room) == OPEN)
				go++;
			else
				ferm[branch][room].pass = CLOSE;
		}
		room++;
	}
	if (go == 0)
		return (CLOSE);
	else
		return (OPEN);
}

void wide_walk(s_info *info, s_ferm **ferm, int branch)
{
	int room;
	s_set_path *stack;

	room = 0;
	stack = NULL;
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

void matrix_orient(s_info *info, s_ferm **ferm)
{
	int branch;
	int room;

	branch = 0;
	room = 0;
	while (ferm[branch][branch].type != END)
		branch++;
	room = 0;
	while (room < info->c_rooms)
	{
		ferm[branch][room].pass = CLOSE;
		room++;
	}
	branch = 0;
	room = 0;
	while (ferm[branch][branch].type != START)
		branch++;
	while (room < info->c_rooms)
	{
		if (ferm[branch][room].pass == OPEN)
		{
			//ft_putstr("SE\n");
			ferm[room][branch].pass = CLOSE;
			ferm[branch][room].pass = recur_orient(info, ferm, room);
			restore_ferm(info, ferm);
		}
		room++;
	}
	//wide_walk(info, ferm, branch);
	write_ferm(ferm, info, 0);
	exit (1);
}