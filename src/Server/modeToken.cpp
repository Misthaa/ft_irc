/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:22:02 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 17:11:12 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string Server::positiveMode(char mode, std::string infos, int channelIndex, int clientIndex)
{
    std::string currArg;
    std::string msg;

    if (mode == 'k')
    {
        currArg = infos.substr(0, infos.find(" "));
        _channel[channelIndex].setChannelPassword(currArg);
        infos = infos.substr(infos.find(" ") + 1);
        msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +k " + currArg + "\n";
        _channel[channelIndex].sendToAll(msg);
    }
    else if (mode == 'l')
    {
        currArg = infos.substr(0, infos.find(" "));
        _channel[channelIndex].setUserLimit(ft_stoi(currArg));
        msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +l " + currArg + "\n";
        _channel[channelIndex].sendToAll(msg);
        infos = infos.substr(infos.find(" ") + 1);
    }
    else if (mode == 'o')
    {
        currArg = infos.substr(0, infos.find(" "));
        infos = infos.substr(infos.find(" ") + 1);
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

    if (mode == 'k')
    {
        currArg = infos.substr(0, infos.find(" "));
        infos = infos.substr(infos.find(" ") + 1);
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
        currArg = infos.substr(0, infos.find(" "));
        infos = infos.substr(infos.find(" ") + 1);
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
            negativeMode(mode[i], infos, channelIndex, clientIndex);
        else
            positiveMode(mode[i], infos, channelIndex, clientIndex);
    }
    return 1;
}
void Server::modeToken(std::string content, int i)
{
    std::string channelName;
    std::string mode;
    std::string infos;

    channelName = content.substr(0, content.find(" "));
    mode = content.substr(content.find(" ") + 1, content.find(" ", content.find(" ") + 1) - content.find(" ") - 1);
    infos = content.substr(content.find(" ", content.find(" ") + 1) + 1);
    if (countWord(content) < 2)
        return;
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