/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/10/22 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"

# define BYTE 8
# define FIRST_BITE 128
# define BLOCK_SIZE 64
# define MESSAGE_SIZE 56
# define MD5_LENGTH 32

# define A 0x67452301
# define B 0xefcdab89
# define C 0x98badcfe
# define D 0x10325476

typedef unsigned int t_round(unsigned int x, unsigned int y, unsigned int z);
typedef struct s_md	t_md;

struct	s_md
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	a0;
	unsigned int	b0;
	unsigned int	c0;
	unsigned int	d0;
	size_t			len;
};

#endif
