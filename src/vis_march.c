#include "lem_in.h"

t_paths		*vis_step(t_ferm *ferm, t_set_path **stack, int path, int room)
{
	t_paths *s_paths;

	s_paths = NULL;
	if (ferm[path].matrix[room].pass == TMP_OPEN)
	{
		push(stack, room);
		if (ferm[room].matrix[room].ants != 0)
		{
			s_paths = (t_paths *)malloc(sizeof(t_paths));
			ferm[path].matrix[path].split--;
			ferm[room].matrix[room].ants--;
			ferm[path].matrix[path].ants++;
			ferm[path].matrix[path].visit = ferm[room].matrix[room].visit;
			s_paths->s_set = draw_traffic(ferm[path], ferm[room]);
			s_paths->set = s_paths->s_set;
			if (ferm[room].matrix[room].type == START)
				ferm[room].matrix[room].visit++;
		}
	}
    return (s_paths);
}

void            run_ants(t_paths *paths, t_visual *vis, t_ferm *ferm, t_info *info)
{
    t_paths *tmp;
	t_ferm cord_1;
	SDL_Event event;
	int go;

	go = 1;
    tmp = paths;
	while (go)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit (1);
		}
		go = 0;
		tmp = paths;
		SDL_SetRenderDrawColor(vis->render, 255, 192, 203, 1);
		SDL_RenderClear(vis->render);
		write_vis_ferm(ferm, vis, info);
		while (tmp)
		{
			if (tmp->set != NULL)
			{
				cord_1.matrix = NULL;
				cord_1.links = NULL;
				cord_1.x = tmp->set->var;
				cord_1.y = tmp->set->next->var;
				tmp->set = tmp->set->next->next;
				go++;
			}
			SDL_SetRenderDrawColor(vis->render, 210, 105, 30, 1);
			drawing_circle(cord_1, vis->radius, vis);
			tmp = tmp->next;
		}
		SDL_RenderPresent(vis->render);
	}
}

void			vis_march(t_ferm *ferm, t_info *info, t_visual *vis, int end)
{
	int			room;
	int			p;
	t_set_path	*stack;
	t_set_path	*links;
	t_paths		*paths;
	t_paths		*tmp_paths;

	stack = NULL;
	tmp_paths = NULL;
	paths = NULL;
	p = 0;
	room = 0;
	while (ferm[end].matrix[end].ants < info->c_ants)
	{
		push(&stack, end);
		while (stack)
		{
			p = stack->var;
			links = ferm[p].links;
			delete(&stack);
			while (links)
			{
				room = links->var;
				if ((ferm[p].matrix[p].split > 0 || ferm[p].matrix[p].type == END))
				{
					if (paths == NULL)
                    {
					    paths = vis_step(ferm, &stack, p, room);
						if (paths)
                        	paths->next = NULL;
                    }
                    else
                    {
                        tmp_paths = paths;
                        while (tmp_paths->next != NULL)
                            tmp_paths = tmp_paths->next;
                    	tmp_paths->next = vis_step(ferm, &stack, p, room);
                        if(tmp_paths->next != NULL)
							tmp_paths->next->next = NULL;
                    }
				}
				links = links->next;
			}
		}
		if (paths)
		{
			run_ants(paths, vis, ferm, info);
			paths = delete_paths(&paths);
		}
	}
}