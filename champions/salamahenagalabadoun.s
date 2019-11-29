# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    salamahenagalabadoun.s                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjestin <gjestin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/21 22:08:42 by gjestin           #+#    #+#              #
#    Updated: 2019/11/28 16:56:28 by jjaegle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.name "salamahenagalabadoun"
.comment "sussKBO hin hin"

ld		32, r3
ld		4, r4
ld		190, r5
st		r1, 6
loop:
live	%666
sti		r5, r5, r3
add		r3, r4, r5
ld		%0, r16
zjmp	%:loop
