# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:27:23 by Dugonzal          #+#    #+#              #
#    Updated: 2023/05/08 17:42:48 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make

function tester() {
	minishell=$(echo $@ | ./minishell)
	test=$(echo $@ | bash)
	#echo $@ >>logm
	#echo $@ >>logb
	if [ "$minishell" == "$test" ]; then
		echo "ok: $test $minishell"
	elif [ "$minishell" != "$test" ]; then
		echo "Error:  resultTest ->  $test "
		echo "resultMiniShell -> $minishell"
	else
		echo "·----pmpmpm---"
	fi

	#	exit 1
}
tester "pwd; ls "
tester "echo -n \"pasaje sin pasajero \"  "
tester "ls"
tester "ls -l"
tester "ls -l -a"
tester "echo $HOME"
tester "echo $PWD"
tester "echo $PATH"
tester "ls .."
tester "exit"

exec ./minishell <command
