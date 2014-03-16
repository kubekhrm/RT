/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 15:50:12 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/03/16 17:27:13 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ft_memory.h>

#include <stdio.h>

void		init_pressed_keys(t_pressedkeys *keys)
{
	ft_bzero(keys, sizeof(*keys));
}

int			keypress_hook(int keycode, t_env *env)
{
	/*
	**	Use allocated table here with Callbacks, Better Performance, Less lines
	*/

	// printf("KPH : pk adress : %p\n", &env->pressed_keys);

	printf("Press %d\n", keycode);

	if (keycode == 65307)
		exit(0);
	else if (keycode == 65363)
		env->pressed_keys.right = 1;
	else if (keycode == 65361)
		env->pressed_keys.left = 1;
	else if (keycode == 65362)
		env->pressed_keys.up = 1;
	else if (keycode == 65364)
		env->pressed_keys.down = 1;
	else if (keycode == 65366)
		env->pressed_keys.p_down = 1;
	else if (keycode == 65451)
		env->pressed_keys.num_plus = 1;
	else if (keycode == 65453)
		env->pressed_keys.num_minus = 1;
	else if (keycode == 119)
		env->pressed_keys.w = 1;
	else if (keycode == 97)
		env->pressed_keys.a = 1;
	else if (keycode == 115)
		env->pressed_keys.s = 1;
	else if (keycode == 100)
		env->pressed_keys.d = 1;
	else if (keycode == 65535)
		env->pressed_keys.del = 1;
	else if (keycode == 65505)
		env->pressed_keys.shift = 1;
	else if (keycode == 65507)
		env->pressed_keys.ctrl = 1;
	else if (keycode == 61)
		env->scene->diaphragm *= 1.05;
	else if (keycode == 45)
		env->scene->diaphragm /= 1.05;
	return (0);
}

int				is_one_key_pressed(t_pressedkeys *keys)
{
	int			i;
	int			*key;
	/*
	**	Maybe would be better with a mask ?
	*/
	i = 0;
	key = (int*)keys;
	while ((size_t)key - (size_t)(keys) < sizeof(*keys))
	{
		if (*key)
			return (1);
		key++;
	}
	return (0);
}

void				check_pressed_keys(t_env *env, t_pressedkeys *keys)
{
	/*
	**	Use dedicated Key Structure with Callback ?
	**	(Better Perfomance, Less Lines)
	**	Maybe do this in is_one_key_pressed function
	*/

	if (keys->up)
		cam_rot_y(&env->scene->camera, -KEYBOARD_ROT_PLOT);
	if (keys->down)
		cam_rot_y(&env->scene->camera, KEYBOARD_ROT_PLOT);
	if (keys->left)
		cam_rot_z(&env->scene->camera, KEYBOARD_ROT_PLOT);
	if (keys->right)
		cam_rot_z(&env->scene->camera, -KEYBOARD_ROT_PLOT);
	if (keys->p_up)
		cam_rot_x(&env->scene->camera, -KEYBOARD_ROT_PLOT);
	if (keys->p_down)
		cam_rot_x(&env->scene->camera, KEYBOARD_ROT_PLOT);
	if (keys->num_plus)
		cam_translate(&env->scene->camera, 0, 0, KEYBOARD_MOV_PLOT);
	if (keys->num_minus)
		cam_translate(&env->scene->camera, 0, 0, -KEYBOARD_MOV_PLOT);
	if (keys->w)
	{
		if (env->selected_object)
			vector_add((t_vector*)&(env->selected_object->origin), &env->scene->camera.x_axis, KEYBOARD_MOV_PLOT);
		cam_translate_vector(&env->scene->camera, &env->scene->camera.x_axis, KEYBOARD_MOV_PLOT);
	}
	if (keys->a)
	{
		if (env->selected_object)
			vector_add((t_vector*)&(env->selected_object->origin), &env->scene->camera.y_axis, KEYBOARD_MOV_PLOT);
		cam_translate_vector(&env->scene->camera, &env->scene->camera.y_axis, KEYBOARD_MOV_PLOT);
	}
	if (keys->s)
	{
		if (env->selected_object)
			vector_add((t_vector*)&(env->selected_object->origin), &env->scene->camera.x_axis, -KEYBOARD_MOV_PLOT);
		cam_translate_vector(&env->scene->camera, &env->scene->camera.x_axis, -KEYBOARD_MOV_PLOT);
	}
	if (keys->d)
	{
		if (env->selected_object)
			vector_add((t_vector*)&(env->selected_object->origin), &env->scene->camera.y_axis, -KEYBOARD_MOV_PLOT);
		cam_translate_vector(&env->scene->camera, &env->scene->camera.y_axis, -KEYBOARD_MOV_PLOT);
	}
	env->refresh_image = 1;
}

int			keyrelease_hook(int keycode, t_env *env)
{
	/*
	**	Use allocated table here with Callbacks, Better Performance, Less lines
	*/
	if (keycode == 65363)
		env->pressed_keys.right = 0;
	else if (keycode == 65361)
		env->pressed_keys.left = 0;
	else if (keycode == 65362)
		env->pressed_keys.up = 0;
	else if (keycode == 65364)
		env->pressed_keys.down = 0;
	else if (keycode == 65366)
		env->pressed_keys.p_down = 0;
	else if (keycode == 65451)
		env->pressed_keys.num_plus = 0;
	else if (keycode == 65453)
		env->pressed_keys.num_minus = 0;
	else if (keycode == 119)
		env->pressed_keys.w = 0;
	else if (keycode == 97)
		env->pressed_keys.a = 0;
	else if (keycode == 115)
		env->pressed_keys.s = 0;
	else if (keycode == 100)
		env->pressed_keys.d = 0;
	else if (keycode == 65535)
		env->pressed_keys.del = 0;
	else if (keycode == 65505)
		env->pressed_keys.shift = 0;
	else if (keycode == 65507)
		env->pressed_keys.ctrl = 0;
	return (0);
}
