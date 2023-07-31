#! /bin/bash

# set -xe

libmlx=$(find . -type f -name "libmlx.a")
mlx_h=$(find . -type f -name "mlx.h")
if [[ -z ${libmlx} || -z ${mlx_h} ]]; then
	if [[ -z ${libmlx} ]]; then
		mlxcopy=$(find ../lib/mlx -type f -name "libmlx.a")
		if [[ -z ${mlxcopy} ]]; then
			make -C ../lib/mlx
		fi
		printf "Copying '$mlxcopy' to '$PWD'\n"
		cp $mlxcopy .
	fi
	if [[ -z ${mlx_h} ]]; then
		printf "Copying '../lib/mlx/mlx.h' to '$PWD'\n"
		cp ../lib/mlx/mlx.h .
	fi
fi

chong_sketch="libcsketch.a"
chong_sketch_source=$(find chong_sketch -type f -name chong_sketch*.c)
chong_sketch_objects=$(find chong_sketch -type f -name chong_sketch*.o)

cflags="-g -Wall -Werror -Wextra"
includes="-I. -Ichong_sketch"
link="-Lchong_sketch -lcsketch -L. -lmlx -framework OpenGL -framework AppKit"

if [[ -n $(find . -type f -name "libmlx.a") && -n $(find . -type f -name "mlx.h") ]]; then
	for file in $chong_sketch_source; do
		cc $cflags $includes -o ${file:0:$(expr ${#file} - 2)}.o -c $file
	done
	chong_sketch_objects=$(find chong_sketch -type f -name chong_sketch*.o)
	ar vrcs $chong_sketch $chong_sketch_objects
	cc $cflags $includes $link -o bench main.c && ./bench
else
	echo Something fucked has happened... Check the directories maybe idk.
fi
