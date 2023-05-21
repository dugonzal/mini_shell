# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 07:25:54 by Dugonzal          #+#    #+#              #
#    Updated: 2023/05/21 07:31:38 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

test() {
	minishell=$(echo $@ | ./minishell)
	bash=$(echo $@ | bash)
	if [ "$test1" = "$test2" ]; then
		echo "[OK]"
		echo "minishell : $minishell"
		echo "bash : $bash"
	else
		echo "KO"
	fi
}

test "echo hello"
