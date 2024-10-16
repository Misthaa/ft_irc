/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:51:03 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/15 19:46:44 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::kickToken(std::string content, int i)
{
	std::string nickname;
	std::string channelName;

	nickname = content.substr(0, content.find(" "));
	channelName = content.substr(content.find(" ") + 1);
	for (int j = 1; j < MAX_CLIENT; j++)
	{
		if (_client[j].getNickname() == nickname)
		{
			for (int k = 0; k < MAX_CHANNEL; k++)
			{
				if (_channel[k].getChannelName() == channelName)
				{
					if (_channel[k].isClientInChannel(_client[j]) == 0)
					{
						sendError(_client[i], "403", "* KICK :You're not on this channel");
						return ;
					}
					if (_channel[k].isOperator(_client[i]) == 0)
					{
						sendError(_client[i], "403", "* KICK :You're not operator of this channel");
						return ;
					}
					// _channel[k].removeClient(_client[j]);
					std::string msg = "You have been kicked from channel " + channelName;
					servSend(_fds[j].fd, msg);
					return ;
				}
			}
			sendError(_client[i], "403", "* KICK :No such channel");
			return ;
		}
	}
	sendError(_client[i], "403", "* KICK :No such nickname");
	return ;
}