/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:00:02 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/29 21:58:24 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::joinToken(std::string content, int i)
{
	int nbWord = 0;
	int existantChannel = 0;
	int channelIndex = 0;
	std::string msg;
	
	nbWord = countWord(content);
	std::string args = content.substr(content.find(" ") + 1);
	content = content.substr(0, content.find(" "));
	if (nbWord < 1)
	{
		sendError(_client[i], "461", "IRCserv: JOIN :Not enough parameters");
		return;
	}
	if (_client[i].getNickname() == "" || _client[i].getUser() == "")
	{
		sendError(_client[i], "451", "IRCserv: JOIN :You have not registered");
		return;
	}
	if (content.find_first_of("#") != 0)
	{
		sendError(_client[i], "403", "IRCserv: JOIN :No such channel");
		return;
	}
	while (channelIndex < MAX_CHANNEL)
	{
		if (_channel[channelIndex].getChannelName() == content)
		{
			if ((_channel[channelIndex].getChannelOnInvite() == 1 && _channel[channelIndex].isInvited(_client[i].getNickname()) == true) ||  _channel[channelIndex].isInvited(_client[i].getNickname()) == true)
				;
			else
			{
				if (_channel[channelIndex].getChannelPassword() != "" && _channel[channelIndex].getChannelPassword() != args.substr(0, args.find(" ") ))
				{
					msg = _channel[channelIndex].getChannelName() + " JOIN :Wrong password";
					sendError(_client[i], "475", msg);
					return;
				}
				if (_channel[channelIndex].getChannelOnInvite() == 1 && _channel[channelIndex].isInvited(_client[i].getNickname()) == false)
				{
					msg = _channel[channelIndex].getChannelName() + " JOIN :You're not invited on this channel";
					sendError(_client[i], "473", msg);
					return;
				}
				if ((int)_channel[channelIndex].getChannelClient().size() >= _channel[channelIndex].getUserLimit())
				{
					msg = _channel[channelIndex].getChannelName() + " JOIN :Channel is full";
					sendError(_client[i], "471", msg);
					return;
				}
			}
			_channel[channelIndex].addClient(_client[i]);
			msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost JOIN :" + content + "\n";
			_channel[channelIndex].sendToAll(msg);
			_channel[channelIndex].deleteInviteList(_client[i].getNickname());
			existantChannel = 1;
			break ; 
		}
		channelIndex++;
	}
	if (existantChannel == 0)
	{
		channelIndex = 0;
		while (channelIndex < MAX_CHANNEL)
		{
			if (_channel[channelIndex].getChannelName() == "")
			{
				_channel[channelIndex].start(content, "", _client[i]);
				msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost JOIN :" + content + "\n";
				_channel[channelIndex].sendToAll(msg);
				msg = ":localhost MODE " + content + " +o " + _client[i].getNickname() + "\n";
				_channel[channelIndex].sendToAll(msg);
				break;
			}
			channelIndex++;
		}
	}
	msg = ":localhost 353 " + _client[i].getNickname() + " = " + content + " :";
	msg += _channel[channelIndex].listChannelClient();
	msg += ":localhost 366 " + _client[i].getNickname() + " " + _channel[channelIndex].getChannelName() + " :End of /NAMES list\n";
	_channel[channelIndex].sendToAll(msg);
	msg = ":localhost 332 " + _client[i].getNickname() + " " + _channel[channelIndex].getChannelName() + " " + _channel[channelIndex].getChannelTopic();
	servSend(_fds[i].fd, msg);
}