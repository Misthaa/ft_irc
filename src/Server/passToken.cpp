/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:30:14 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 18:04:47 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::passToken(std::string content, int i)
{
    if (_client[i].getCorrectPassword() == true)
    {
        sendError(_client[i], "462", "* PASS :You may not reregister");
        return ;
    }
    if (content == _password)
    {
        std::string msg = "Correct password " + _client[i].getNickname();
		_client[i].setCorrectPassword(true);
        servSend(_fds[i].fd, msg);
		if (_client[i].getNickname() != "" && _client[i].getUser() != "")
		{
			msg = ":localhost:" + _sPort + " 001 " + _client[i].getNickname() + " :Welcome to IRC " + _client[i].getNickname() + "!";
			servSend(_fds[i].fd, msg);
		}
    }
	else
	{
		sendError(_client[i], "464", "* PASS :Password incorrect");
		return ;
	}
    return ;
}