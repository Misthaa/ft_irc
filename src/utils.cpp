/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:29:44 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/17 10:29:58 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string	ft_clearString(const std::string &str)
{
	std::string	clearLine = str;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == ' ')
			clearLine.erase(i, 1);
		else
			break;
	}
	return (clearLine);
}