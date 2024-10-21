/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:29:44 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/21 20:04:08 by roguigna         ###   ########.fr       */
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

int	ft_stoi(const std::string &str)
{
	int res = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int countWord(const std::string &str)
{
	int count = 0;

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			count++;
	}
	return (count + 1);
}