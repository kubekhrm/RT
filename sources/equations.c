/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbinet <lbinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 19:30:09 by lbinet            #+#    #+#             */
/*   Updated: 2014/03/22 19:38:32 by lbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <ray.h>
#include <object.h>
#include <math.h>

static float	positive_smallest(float a, float b, t_ray *ray)
{
	if (a < 0)
	{
		if (b > 0)
		{
			ray->inside = 1;
			return (b);
		}
		ray->inside = 0;
		return (INFINITY);
	}
	if (b < 0)
	{
		if (a > 0)
		{
			ray->inside = 1;
			return (a);
		}
		ray->inside = 0;
		return (INFINITY);
	}
	ray->inside = 0;
	if (a < b)
		return (a);
	return (b);
}

static float	sphere_equation_det(t_object *s, t_ray *ray, float *a, float *b)
{
	t_vector	ray_direction;
	t_point		ray_origin;
	t_point		s_origin;
	float		radius;
	float		c;

	ray_direction = ray->direction;
	ray_origin = ray->origin;
	s_origin = s->origin;
	radius = s->radius;
	*a = ray_direction.x * ray_direction.x + ray_direction.y
		* ray_direction.y + ray_direction.z * ray_direction.z;
	*b = 2 * (ray_direction.x * (ray_origin.x - s_origin.x)
		+ ray_direction.y * (ray_origin.y - s_origin.y)
			+ ray_direction.z * (ray_origin.z - s_origin.z));
	c = (ray_origin.x - s_origin.x) * (ray_origin.x - s_origin.x)
		+ (ray_origin.y - s_origin.y)
		* (ray_origin.y - s_origin.y)
		+ (ray_origin.z - s_origin.z)
		* (ray_origin.z - s_origin.z) - radius * radius;
	return (c);
}

float			sphere_equation(t_object *sphere, t_ray *ray)
{
	float	res;
	float	a;
	float	b;
	float	c;
	float	det;

	c = sphere_equation_det(sphere, ray, &a, &b);
	det = b * b - 4 * a * c;
	if (det	>= 0)
	{
		det = sqrt(det);
		res = positive_smallest((-b + det) / (2 * a),
				(-b - det) / (2 * a), ray);
		return (res);
	}
	return (INFINITY);
}

float		plane_equation(t_object *plane, t_ray *ray)
{
	float	n;
	float	d;
	float	res;

	n = plane->normal.x * (plane->origin.x - ray->origin.x)
		+ plane->normal.y * (plane->origin.y - ray->origin.y)
		+ plane->normal.z * (plane->origin.z - ray->origin.z);
	d = plane->normal.x * ray->direction.x
		+ plane->normal.y * ray->direction.y
		+ plane->normal.z * ray->direction.z;
	if ((res = n / d) > 0)
		return (res);
	return (INFINITY);
}
