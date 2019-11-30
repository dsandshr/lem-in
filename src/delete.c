#include "lem_in.h"

char **delete_ar(char **ar, int size)
{
    // while (size != -1)
    // {
    //     free(ar[size]);
    //     ar[size] = NULL;
    //     size--;
    // }
	size = 9;
    free(ar);
    return (NULL);
}

void	delete_rooms(s_rooms **rooms)
{
	if (*rooms != NULL)
		delete_rooms(&(*rooms)->next);
	if (*rooms != NULL)
	{
		ft_strdel(&(*rooms)->name);
		(*rooms)->name = NULL;
		free(*rooms);
		*rooms = NULL;
	}
}

void	delete_links(s_links **links)
{
	if (*links != NULL)
		delete_links(&(*links)->next);
	if (*links != NULL)
	{
		ft_strdel(&(*links)->room1);
		ft_strdel(&(*links)->room2);
		free(*links);
		*links = NULL;
	}
}

void    delete_info(s_info **info)
{
	ft_strdel(&(*info)->input);
	delete_rooms(&(*info)->rooms);
	delete_links(&(*info)->links);
	free(*info);
	*info = NULL;
}

s_ferm	**delete_ferm(s_ferm **ferm, int room)
{
	room = room - 1;
	while (room != -1)
	{
		free(ferm[room]);
		ferm[room] = NULL;
		room--;
	}
	free(ferm);
	ferm = NULL;
	return (ferm);
}