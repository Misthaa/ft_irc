/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:22:02 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/23 17:12:26 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static std::string nextArg(std::string infos)
{
	if (infos.find(" ") == std::string::npos)
		return "";
	infos = infos.substr(infos.find(" ") + 1);
	return infos;
}

static std::string modeArgError(char mode, std::string nickname, std::string channelName)
{
	std::string msg = "";
	
	if (mode == 'k')
		msg = ":localhost 696 " + nickname + " " + channelName + " k * :You must specify a parameter for the key mode. Syntax: <key>.\n";
	if (mode == 'o')
		msg = ":localhost 696 " + nickname + " " + channelName + " o * :You must specify a parameter for the operator mode. Syntax: <nickname>.\n";
	if (mode == 'l')
		msg = ":localhost 696 " + nickname + " " + channelName + " l * :You must specify a parameter for the limit mode. Syntax: <limit>.\n";
	return msg ;
}

std::string Server::positiveMode(char mode, std::string infos, int channelIndex, int clientIndex)
{
	std::string currArg;
	std::string msg;

	currArg = infos.substr(0, infos.find(" "));
	if (currArg == "" && (mode == 'k' || mode == 'o' || mode == 'l'))
	{
		msg = modeArgError(mode, _client[clientIndex].getNickname(), _channel[channelIndex].getChannelName());
		_channel[channelIndex].sendToAll(msg);
		return (infos);
	}
	if (mode == 'k')
	{
		_channel[channelIndex].setChannelPassword(currArg);
		infos = nextArg(infos);
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +k " + currArg + "\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else if (mode == 'l')
	{
		_channel[channelIndex].setUserLimit(ft_stoi(currArg));
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +l " + currArg + "\n";
		_channel[channelIndex].sendToAll(msg);
		infos = nextArg(infos);

	}
	else if (mode == 'o')
	{
		infos = nextArg(infos);
		int clientTarget = isClientExist(currArg);
		if (clientTarget != 0)
		{
			if (_channel[channelIndex].isClientInChannel(_client[clientIndex]) == 1)
			{
				std::string msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +o " + currArg + "\n";
				_channel[channelIndex].setOperator(_client[clientTarget], true);
				_channel[channelIndex].sendToAll(msg);
				return infos;
			}
			msg = currArg + " 403 * MODE :User not on this channel";
			servSend(_fds[clientIndex].fd, msg);
			return infos;
		}
		msg = currArg + " 403 * MODE :No such nickname";
		servSend(_fds[clientIndex].fd, msg);
		return infos;
	}
	else if (mode == 't')
	{
		_channel[channelIndex].setChangeTopic(true);
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +t\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else if (mode == 'i')
	{
		_channel[channelIndex].setChannelOnInvite(true);
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +i\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else
		sendError(_client[clientIndex], "472", "* MODE :Unknown mode flag");
	return infos;
}

std::string Server::negativeMode(char mode, std::string infos, int channelIndex, int clientIndex)
{
	std::string currArg;
	std::string msg;

	currArg = infos.substr(0, infos.find(" "));
	if (currArg == "" && (mode == 'k' || mode == 'o'))
	{
		msg = modeArgError(mode, _client[clientIndex].getNickname(), _channel[channelIndex].getChannelName());
		_channel[channelIndex].sendToAll(msg);
		return (infos);
	}
	if (mode == 'k')
	{
		infos = nextArg(infos);
		if (_channel[channelIndex].getChannelPassword() == "")
			return infos;
		_channel[channelIndex].setChannelPassword("");
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -k " + currArg + "\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else if (mode == 'l')
	{
		_channel[channelIndex].setUserLimit(MAX_CLIENT);
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -l " + currArg + "\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else if (mode == 'o')
	{
		infos = nextArg(infos);
		int clientTarget = isClientExist(currArg);
		if (clientTarget != 0)
		{
			if ( _channel[channelIndex].isClientInChannel(_client[clientIndex]) == 1)
			{
				std::string msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -o " + currArg + "\n";
				_channel[channelIndex].setOperator(_client[clientTarget], false);
				_channel[channelIndex].sendToAll(msg);
				return infos;
			}
			msg = currArg + " 403 * MODE :User not on this channel";
			servSend(_fds[clientIndex].fd, msg);
			return infos;
		}
		msg = currArg + " 403 * MODE :No such nickname";
		servSend(_fds[clientIndex].fd, msg);
		return infos;
	}
	else if (mode == 't')
	{
		_channel[channelIndex].setChangeTopic(false);
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -t\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else if (mode == 'i')
	{
		_channel[channelIndex].setChannelOnInvite(false);
		msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -i\n";
		_channel[channelIndex].sendToAll(msg);
	}
	else
		sendError(_client[clientIndex], "472", "* MODE :Unknown mode flag");
	return infos;
}

int Server::execMode(std::string mode, std::string infos, int channelIndex, int clientIndex)
{
	std::string currArg;
	std::string msg;
	char sign = '+';

	for (int i = 0; i < (int)mode.length(); i++)
	{
		if (mode[i] == '+' || mode[i] == '-')
		{
			sign = mode[i];
			i++;
		}
		if (sign == '-')
			infos = negativeMode(mode[i], infos, channelIndex, clientIndex);
		else
			infos = positiveMode(mode[i], infos, channelIndex, clientIndex);
	}
	return 1;
}
void Server::modeToken(std::string content, int i)
{
	std::string channelName;
	std::string mode;
	std::string infos;

	if (countWord(content) < 2)
		return;
	channelName = content.substr(0, content.find(" "));
	content = nextArg(content);
	mode = content.substr(0, content.find(" "));
	content = nextArg(content);
	infos = content;
	for (int j = 0; j < MAX_CHANNEL; j++)
	{
		if (channelName == _channel[j].getChannelName())
		{
			if (_channel[j].isOperator(_client[i]) == 0)
			{
				sendError(_client[i], "482", "* MODE :You're not operator of this channel");
				return ;
			}
			else if (execMode(mode, infos, j, i) == 0)
				return ;
			return ;
		}
	}
	sendError(_client[i], "403", "* MODE :No such channel");
	return ;
}