/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:00:02 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/21 19:35:39 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::joinToken(std::string content, int i)
{
	int countWord = 0;
	int existantChannel = 0;
	int channelIndex = 0;
	std::string msg;
	
	countWord = std::count(content.begin(), content.end(), ' ') + 1;
	std::string args = content.substr(content.find(" ") + 1);
	std::cout << "args: " << args << std::endl;
	content = content.substr(0, content.find(" "));
	if (countWord < 1)
	{
		sendError(_client[i], "461", "* JOIN :Not enough parameters");
		return;
	}
	if (_client[i].getNickname() == "" || _client[i].getUser() == "")
	{
		sendError(_client[i], "451", "* JOIN :You have not registered");
		return;
	}
	if (content.find_first_of("#") != 0)
	{
		sendError(_client[i], "461", "* JOIN :Not a channel");
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
				std::cout << "channel password: " << _channel[channelIndex].getChannelPassword() << std::endl;
				std::cout << "content: " << args.substr(0, args.find(" ")) << std::endl;
				std::cout << "on invite: " << _channel[channelIndex].getChannelOnInvite() << std::endl;
				std::cout << "is invited: " << _channel[channelIndex].isInvited(_client[i].getNickname()) << std::endl;
				if (_channel[channelIndex].getChannelPassword() != "" && _channel[channelIndex].getChannelPassword() != args.substr(0, args.find(" ") ))
				{
					sendError(_client[i], "475", "* JOIN :Wrong password");
					return;
				}
				if (_channel[channelIndex].getChannelOnInvite() == 1 && _channel[channelIndex].isInvited(_client[i].getNickname()) == false)
				{
					sendError(_client[i], "473", "* JOIN :You're not invited on this channel");
					return;
				}
				if ((int)_channel[channelIndex].getChannelClient().size() >= _channel[channelIndex].getUserLimit())
				{
					sendError(_client[i], "471", "* JOIN :Channel is full");
					return;
				}
			}
			_channel[channelIndex].addClient(_client[i]);
			msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost JOIN :" + content + "\n";
			_channel[channelIndex].sendToAll(msg);
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
				msg = ":localhsot MODE " + content + " +o " + _client[i].getNickname() + "\n";
				_channel[channelIndex].sendToAll(msg);
				break;
			}
			channelIndex++;
		}
	}
	msg = ":localhost 353 " + _client[i].getNickname() + " = " + content + " :";
	for (std::map<Client&, bool>::iterator it = _channel[channelIndex].getChannelClient().begin(); it != _channel[channelIndex].getChannelClient().end(); it++)
	{
		if (it->second == true)
			msg += "@";
		msg += it->first.getNickname() + " ";
	}
	msg += "\n";
	msg += ":localhost 366 " + _client[i].getNickname() + " " + _channel[channelIndex].getChannelName() + " :End of /NAMES list\n";
	msg += ":localhost 332 " + _client[i].getNickname() + " " + _channel[channelIndex].getChannelName() + " :" + _channel[channelIndex].getChannelTopic() + "\n";
	_channel[channelIndex].sendToAll(msg);
}