/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:51:03 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 21:58:29 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::kickToken(std::string content, int i)
{
	std::string nickname;
	std::string channelName;
	std::string reason;
	std::string msg;

	nickname = content.substr(content.find(" ") + 1, content.find(" ", content.find(" ") + 1) - content.find(" ") - 1);
	channelName = content.substr(0, content.find(" "));
	reason = content.substr(content.find(":") + 1);
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
						sendError(_client[i], "442", "IRCserv:  KICK :You're not on this channel");
						return ;
					}
					if (_channel[k].isOperator(_client[i]) == 0)
					{
						msg = ":localhost 482 " + _client[i].getNickname() + " " + _channel[k].getChannelName() + " * KICK :You must be operator to kick someone in the channel\n";
						servSend(_fds[i].fd, msg);
						return ;
					}
					std::string msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost KICK " + _channel[k].getChannelName() + " " + nickname + " " + reason + "\n";
					// msg =  + " " + client.getNickname() + " :kicked\n";

					_channel[k].sendToAll(msg);
					_channel[k].removeClient(_client[j], "kicked");
					return ;
				}
			}
			sendError(_client[i], "401", "IRCserv:  KICK :No such channel");
			return ;
		}
	}
	sendError(_client[i], "403", "IRCserv:  KICK :No such nickname");
	return ;
}