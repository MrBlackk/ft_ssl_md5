/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

size_t g_sha512_const[80] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
	0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

void	set_initial_values_sha512(t_sh *sh)
{
	sh->a = 0x6a09e667f3bcc908;
	sh->b = 0xbb67ae8584caa73b;
	sh->c = 0x3c6ef372fe94f82b;
	sh->d = 0xa54ff53a5f1d36f1;
	sh->e = 0x510e527fade682d1;
	sh->f = 0x9b05688c2b3e6c1f;
	sh->g = 0x1f83d9abfb41bd6b;
	sh->h = 0x5be0cd19137e2179;
}

size_t	right_rotate64(size_t x, int n)
{
	return (x >> n) | (x << (64 - n));
}


size_t	schedule_rotates512(size_t num, int x, int y, int z)
{
	return right_rotate64(num, x) ^ right_rotate64(num, y) ^ (num >> z);
}


void	prepare_message_schedule512(size_t *mem, size_t *schedule)
{
	unsigned char	i;
	size_t	sc0;
	size_t	sc1;

	i = 0;
	while (i < 16)
	{
		schedule[i] = reverse_bytes(mem[i], 8);
		i++;
	}
	while (i < 80)
	{
		sc0 = schedule_rotates512(schedule[i - 15], 1, 8, 7);
		sc1 = schedule_rotates512(schedule[i - 2], 19, 61, 6);
		schedule[i] = sc1 + schedule[i - 7] + sc0 + schedule[i - 16];
		i++;
	}
}

void	save_start_values512(size_t start_values[8], t_sh *sh)
{
	start_values[0] = sh->a;
	start_values[1] = sh->b;
	start_values[2] = sh->c;
	start_values[3] = sh->d;
	start_values[4] = sh->e;
	start_values[5] = sh->f;
	start_values[6] = sh->g;
	start_values[7] = sh->h;
}

void	add_start_values512(size_t start_values[8], t_sh *sh)
{
	sh->a += start_values[0];
	sh->b += start_values[1];
	sh->c += start_values[2];
	sh->d += start_values[3];
	sh->e += start_values[4];
	sh->f += start_values[5];
	sh->g += start_values[6];
	sh->h += start_values[7];
}

size_t	sum512(size_t num, int x, int y, int z)
{
	return right_rotate64(num, x) ^ right_rotate64(num, y) ^ right_rotate64(num, z);
}

size_t	ch512(size_t x, size_t y, size_t z)
{
	return (x & y) ^ (~x & z);
}

size_t	maj512(size_t x, size_t y, size_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

void	debug_vars512(t_sh *sha)
{
	ft_printf("%llx ", sha->a);
	ft_printf("%llx ", sha->b);
	ft_printf("%llx ", sha->c);
	ft_printf("%llx ", sha->d);
	ft_printf("%llx ", sha->e);
	ft_printf("%llx ", sha->f);
	ft_printf("%llx ", sha->g);
	ft_printf("%llx\n", sha->h);
}

void	perm512(size_t *mem, t_sh *sh)
{
	unsigned char	i;
	size_t	start_values[8];
	size_t	schedule[80];
	size_t	temp1;
	size_t	temp2;

	i = 0;
	prepare_message_schedule512(mem, schedule);
	save_start_values512(start_values, sh);
	while (i < 80)
	{
		temp1 = sh->h + sum512(sh->e, 14, 18, 41) + ch512(sh->e, sh->f, sh->g) +
				+ g_sha512_const[i] + schedule[i];
		temp2 = sum512(sh->a, 28, 34, 39) + maj512(sh->a, sh->b, sh->c);
		sh->h = sh->g;
		sh->g = sh->f;
		sh->f = sh->e;
		sh->e = sh->d + temp1;
		sh->d = sh->c;
		sh->c = sh->b;
		sh->b = sh->a;
		sh->a = temp1 + temp2;
//		debug_vars512(sh);
		i++;
	}
	add_start_values512(start_values, sh);
}


void	sha512_permutations(char *init_mem, int fd, t_sh *sh)
{
	char	mem[SHA512_BLOCK];
	size_t	len;

	sh->len = get_next_block(&init_mem[0], mem, fd, SHA512_BLOCK);
	len = sh->len;
	while (len == SHA512_BLOCK)
	{
		perm512((size_t *) mem, sh);
		len = get_next_block(&init_mem[sh->len], mem, fd, SHA512_BLOCK);
		sh->len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= SHA512_MESSAGE)
	{
		perm512((size_t *) mem, sh);
		sh->len += get_next_block(&init_mem[sh->len], mem, fd, SHA512_BLOCK);
	}
	set_memory_length(&mem[SHA512_MESSAGE], sh->len, 8, 0);
	perm512((size_t *) mem, sh);
}


char *get_result_sha512(t_sh *sh)
{
	char	res[SHA512_LENGTH + 1];

	ft_bzero(&res, SHA512_LENGTH + 1);
	result(res, sh->a, 0, 0, 64);
	result(res, sh->b, 16, 0, 64);
	result(res, sh->c, 32, 0, 64);
	result(res, sh->d, 48, 0, 64);
	result(res, sh->e, 64, 0, 64);
	result(res, sh->f, 80, 0, 64);
	result(res, sh->g, 96, 0, 64);
	result(res, sh->h, 112, 0, 64);
	return ft_strdup(res);
}

char	*sha512(char *mem, int fd)
{
	t_sh	sh;

	set_initial_values_sha512(&sh);
	sha512_permutations(mem, fd, &sh);
	return get_result_sha512(&sh);
}
