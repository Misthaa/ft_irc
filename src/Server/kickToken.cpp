/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:51:03 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 16:03:21 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::kickToken(std::string content, int i)
{
	std::string nickname;
	std::string channelName;
	std::string reason;

	nickname = content.substr(content.find(" ") + 1, content.find(" ", content.find(" ") + 1) - content.find(" ") - 1);
	channelName = content.substr(0, content.find(" "));
	reason = channelName.substr(channelName.find(" ") + 1);
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
					std::string msg = ":localhost KICK " + _channel[k].getChannelName() + " " + nickname + " " + reason + "\n";
					_channel[k].sendToAll(msg);
					_channel[k].removeClient(_client[j]);
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