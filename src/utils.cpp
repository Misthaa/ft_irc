/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:29:44 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/22 16:27:01 by roguigna         ###   ########.fr       */
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

std::string normalizeSpaces(const std::string& input) {
	std::string result;
	bool inSpaces = false;

	for (std::string::const_iterator it = input.begin(); it != input.end(); ++it) {
		char ch = *it;

		if (ch == ' ') {
			if (!inSpaces) {
				result += ' ';
				inSpaces = true;
			}
		} else {
			result += ch;
			inSpaces = false;
		}
	}

	return result;
}


int countWord(const std::string &str)
{
	int count = 0;
	int c = 0;
	
	for (int i = 0; str[i]; i++)
	{
		if (!isspace(str[i]))
			c++;
		if (str[i] == ' ')
			count++;
	}
	if (c == 0)
		return (0);
	return (count + 1);
}