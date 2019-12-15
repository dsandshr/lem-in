#include "lem_in.h"

t_set_path    *draw_traffic(t_ferm cord_1, t_ferm cord_2)
{
    int del_x;
    int del_y;
    int error;
    int sign_x;
    int sign_y;
    int error_2;
    t_set_path *path;

    path = NULL;
    del_x = abs(cord_2.x - cord_1.x);
    del_y = abs(cord_2.y - cord_1.y);
    sign_x = cord_1.x < cord_2.x ? 1 : -1;
    sign_y = cord_1.y < cord_2.y ? 1 : -1;
    error = del_x - del_y;
    while (cord_1.x != cord_2.x || cord_1.y != cord_2.y)
    {
        rev_push(&path, cord_1.y);
        rev_push(&path, cord_1.x);
        error_2 = error * 2;
        if (error_2 > -del_y)
        {
            error -= del_y;
            cord_1.x += sign_x;
        }
        if (error_2 < del_x)
        {
            error += del_x;
            cord_1.y += sign_y;
        }
    }
    return (path);
}