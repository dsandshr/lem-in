# include "lem_in.h"

void cord(t_ferm *ferm, t_info *info)
{
	int branch;

	branch = 0;
	while (branch < info->c_rooms)
	{
		ferm[branch].x = rand() % WIDTH;
		ferm[branch].y = rand() % HEIGHT;
		branch++;
	}
}

t_visual	*init_sdl(void)
{
	t_visual	*info;

	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) < 0)
		return (NULL);
	info = (t_visual *)malloc(sizeof(t_visual));
	info->window = SDL_CreateWindow("VisualFiller", \
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
	WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (info->window == NULL)
	{
		free(info);
		return (NULL);
	}
	info->render = SDL_CreateRenderer(info->window, -1, \
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	info->r_ants = SDL_CreateRenderer(info->window, -1, \
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	info->run = 1;
	return (info);
}

void		quit_visual(t_visual *info)
{
	SDL_DestroyWindow(info->window);
	SDL_DestroyRenderer(info->render);
	SDL_Quit();
}

int		visual(t_ferm *ferm, t_info *info, short flag)
{
	t_visual *visual;
	SDL_Event event;

	visual = init_sdl();
	if (visual == NULL)
		return (0);
	visual->size = flag;
	visual->radius = 5; //WIDTH / info->c_rooms > 0 ? WIDTH / (info->c_rooms * 10) : 2;
	if (visual->size == 1)
		cord(ferm, info);
	while (visual->run)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				visual->run = 0;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					ft_putstr("SPACE\n");
					exit (1);
				}
			}
		}
		SDL_SetRenderDrawColor(visual->render, 255, 255, 255, 1);
		SDL_RenderClear(visual->render);
		write_vis_ferm(ferm, visual, info);
		SDL_RenderPresent(visual->render);
		vis_march(ferm, info, visual, info->end_id);;
	}
	quit_visual(visual);
	return (0);
}
