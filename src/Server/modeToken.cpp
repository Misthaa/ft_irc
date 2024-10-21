/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:02:31 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/21 20:05:07 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int Server::execMode(std::string mode, std::string infos, int channelIndex, int clientIndex)
{
    // int arg = 0;
    std::string currArg;
    std::string msg;
    char sign = '+';
    
    std::cout << "\n\n\n" << std::endl;
    for (int i = 0; i < (int)mode.length(); i++)
    {
        if (mode[i] == '+' || mode[i] == '-')
        {
            sign = mode[i];
            i++;
        }
        std::cout << "sign:" << sign << std::endl;
        std::cout << "infos:" << infos << std::endl; 
        if (sign == '-')
        {
            if (mode[i] == 'k')
            {
                currArg = infos.substr(0, infos.find(" "));
                infos = infos.substr(infos.find(" ") + 1);
                if (_channel[channelIndex].getChannelPassword() == "")
                    continue;
                _channel[channelIndex].setChannelPassword("");
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -k " + currArg + "\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else if (mode[i] == 'l')
            {
                _channel[channelIndex].setUserLimit(MAX_CLIENT);
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -l " + currArg + "\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else if (mode[i] == 'o')
            {
                currArg = infos.substr(0, infos.find(" "));
                std::cout << "currArg: " << currArg << std::endl;
                infos = infos.substr(infos.find(" ") + 1);
                int clientTarget = isClientExist(currArg);
                if (clientTarget != 0)
                {
                    if ( _channel[channelIndex].isClientInChannel(_client[clientIndex]) == 1)
                    {
                        std::string msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -o " + currArg + "\n";
                        _channel[channelIndex].setOperator(_client[clientTarget], false);
                        _channel[channelIndex].sendToAll(msg);
                        continue;
                    }
                    msg = currArg + " 403 * MODE :User not on this channel";
                    servSend(_fds[clientIndex].fd, msg);
                    continue;
                }
                msg = currArg + " 403 * MODE :No such nickname";
                servSend(_fds[clientIndex].fd, msg);
                continue;
            }
            else if (mode[i] == 't')
            {
                _channel[channelIndex].setChangeTopic(false);
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -t\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else if (mode[i] == 'i')
            {
                _channel[channelIndex].setChannelOnInvite(false);
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " -i\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else
            {
                sendError(_client[clientIndex], "472", "* MODE :Unknown mode flag");
            }
        }
        else
        {
            if (mode[i] == 'k')
            {
                currArg = infos.substr(0, infos.find(" "));
                std::cout << "k: currArg: " << currArg << std::endl;
                _channel[channelIndex].setChannelPassword(currArg);
                infos = infos.substr(infos.find(" ") + 1);
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +k " + currArg + "\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else if (mode[i] == 'l')
            {
                currArg = infos.substr(0, infos.find(" "));
                std::cout << "l: currArg: " << currArg << std::endl;
                _channel[channelIndex].setUserLimit(ft_stoi(currArg));
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +l " + currArg + "\n";
                _channel[channelIndex].sendToAll(msg);
                infos = infos.substr(infos.find(" ") + 1);
            }
            else if (mode[i] == 'o')
            {
                currArg = infos.substr(0, infos.find(" "));
                infos = infos.substr(infos.find(" ") + 1);
                std::cout << "o: currArg: " << currArg << std::endl;
                int clientTarget = isClientExist(currArg);
                if (clientTarget != 0)
                {
                    if (_channel[channelIndex].isClientInChannel(_client[clientIndex]) == 1)
                    {
                        std::string msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +o " + currArg + "\n";
                        _channel[channelIndex].setOperator(_client[clientTarget], true);
                        _channel[channelIndex].sendToAll(msg);
                        continue;
                    }
                    msg = currArg + " 403 * MODE :User not on this channel";
                    servSend(_fds[clientIndex].fd, msg);
                    continue;
                }
                msg = currArg + " 403 * MODE :No such nickname";
                servSend(_fds[clientIndex].fd, msg);
                continue;
            }
            else if (mode[i] == 't')
            {
                _channel[channelIndex].setChangeTopic(true);
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +t\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else if (mode[i] == 'i')
            {
                _channel[channelIndex].setChannelOnInvite(true);
                msg = ":localhost MODE " + _channel[channelIndex].getChannelName() + " +i\n";
                _channel[channelIndex].sendToAll(msg);
            }
            else
            {
                sendError(_client[clientIndex], "472", "* MODE :Unknown mode flag");
            }
        } 
      std::cout << "\n\n\n" << std::endl;
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
    std::cout << "channelName: " << channelName << std::endl;
    std::cout << "mode: " << mode << std::endl;
    std::cout << "infos: " << infos << std::endl;
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