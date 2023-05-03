# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:27:23 by Dugonzal          #+#    #+#              #
#    Updated: 2023/05/03 17:50:32 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

make

function tester() {
	test=$(echo $@"; exit" | ./minishell 2>&1)
	test2=$(echo $@"; exit" | bash 2>&1)
	if [ test != test2 ]; then
		echo "Error: $1"
		echo "Expected: $test2"
		echo "Got: $test"
		exit 1
	else
		echo "OK:"
	fi
}

tester "echo hello world"
