/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:13:08 by lmells            #+#    #+#             */
/*   Updated: 2023/08/25 10:29:56 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_CORE_H
# define PRINTF_CORE_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned int	t_uint;

enum e_flag_types
{
	PAD_ZEROS = 1
};

typedef struct s_flag
{
	uint8_t	type;
	size_t	pad_len;
}	t_flag;

typedef struct s_conversion
{
	uint8_t	ok;
	ssize_t	bs;
	char	**buffer;
	char	*fp;
	int		ret_len;
	va_list	args;
	t_flag	flag;
}	t_convert;

enum e_convert_status
{
	CONVERT_FAIL,
	CONVERT_SUCCESS
};

// Core.
void		printf_core(t_convert *c);

// Format flags.
char		*get_flag_info(char *fp, t_flag *info);

// Conversion.
// char		*convert_args(char *fp, t_convert *c);
int			convert_char(int ch, t_convert *c);
int			convert_str(const char *s, t_convert *c);
int			convert_dec(uint8_t sign, uint64_t n, t_convert *c);
int			convert_hex(uint64_t n, int alpha, t_convert *c);

// Output format conversion.
char		*outfmt_decimal(uint64_t n, size_t n_len, t_convert *c);
char		*outfmt_hexadecimal(uint64_t n, size_t n_len, int alpha,
				t_convert *c);

// Core utils.
size_t		get_unsigned_len_base(uint64_t n, size_t base);
void		*init_buffer(t_convert *c);
int			resize_buffer(t_convert *c);
int			conversion_failure(t_convert *c);

//	Libftall
# ifndef LIBFTALL_H

size_t		ft_strlen(const char *s);
int			ft_atoi(const char *s);
int			ft_resize_str(char **s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *b, size_t len);

# endif

#endif
