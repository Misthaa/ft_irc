/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topicToken.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:54:28 by madegryc          #+#    #+#             */
/*   Updated: 2024/11/04 14:15:41 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::topicToken(std::string content, int i)
{
    std::string channelName;
    std::string topic;
    std::string msg;

    channelName = content.substr(0, content.find(" "));
    if (content.find(" ") == std::string::npos)
        topic = "";
    else
        topic = content.substr(content.find(" ") + 1);
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (channelName == _channel[j].getChannelName())
        {
            if (_channel[j].isClientInChannel(_client[i]) == false)
            {
                sendError(_client[i], "403", "IRCserv: TOPIC :You're not on this channel");
                return ;
            }
            if (topic == "" && _channel[j].getChannelTopic() == "(no topic)")
            {
                msg = ":localhost 331 " + _client[i].getNickname() + " " + _channel[j].getChannelName() + " :No topic is set";
                servSend(_fds[i].fd, msg);
                return ;
            }
            else if (topic == "")
            {
                msg = ":localhost 332 " + _client[i].getNickname() + " " + _channel[j].getChannelName() + " " + _channel[j].getChannelTopic();
                servSend(_fds[i].fd, msg);
                return ;
            }
            if (_channel[j].isOperator(_client[i]) == 0 && _channel[j].getChangeTopic() == true)
            {
				msg = ":localhost 482 " + _client[i].getNickname() + " " + _channel[j].getChannelName() + " * TOPIC :You must be operator to change the topic of this channel";
                servSend(_fds[i].fd, msg);
                return ;
            }
            _channel[j].setChannelTopic(topic);
            std::string msg = ":localhost TOPIC " + channelName + " " + topic + "\n";
            _channel[j].sendToAll(msg);
            return ;
        }
    }
    sendError(_client[i], "403", "IRCserv: TOPIC :No such channel");
    return ;
}