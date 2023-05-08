# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:27:23 by Dugonzal          #+#    #+#              #
#    Updated: 2023/05/07 18:08:35 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make

function tester() {
	minishell=$(echo $@ | ./minishell >>logm)
	test=$(echo $@ | bash >>logb)
	if [ "$minishell" == "$test" ]; then
		echo "ok:"
	elif [ "$minishell" != "$test" ]; then
		echo "Error:$test"
	else
		echo "·----pmpmpm---"
	fi

	#	exit 1
}
tester "pwd"
tester "echo -n \"pasaje sin pasajero \"  "
tester "ls"
rm -r result.log
diff logm logb >result.log | bat result.log
tester "ls -l"
tester "ls -l -a"
tester "echo $HOME"
tester "echo $PWD"
tester "echo $PATH"
tester "ls .."
tester "exit"
