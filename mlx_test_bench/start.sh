#! /bin/bash

# set -xe

libmlx=$(find . -type f -name "libmlx.a")
mlx_h=$(find . -type f -name "mlx.h")
if [[ -z ${libmlx} || -z ${mlx_h} ]]; then
	if [[ -z ${libmlx} ]]; then
		if [[ -z $(find ../lib/mlx -type f -name "libmlx.a") ]]; then
			make -C ../lib/mlx
		fi
		mlxcopy=$(find ../lib/mlx -type f -name "libmlx.a")
		printf "Copying '${mlxcopy}' to '$PWD'\n"
		cp ${mlxcopy} ${PWD}
	fi
	if [[ -z ${mlx_h} ]]; then
		mlx_h=$(find ../lib/mlx -type f -name "mlx.h")
		printf "Copying '${mlx_h}' to '${PWD}'\n"
		cp ${mlx_h} ${PWD}
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
