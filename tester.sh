# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:27:23 by Dugonzal          #+#    #+#              #
#    Updated: 2023/05/10 17:44:51 by sizquier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make

rm -rf logm.log logb.log diff.bm
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
