/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:14:07 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/14 15:53:25 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::userToken(std::string content, int i)
{
    int countWord = 0;

    if (_client[i].getNickname() == "")
    {
        sendError(_client[i], "", "* USER :Nickname need to be specify to define user");
        return;
    }
    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    if (countWord < 1)
    {
        sendError(_client[i], "461", "* USER :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        sendError(_client[i], "461", "* USER :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^#") != 0)
    {
        sendError(_client[i], "432", "* USER :Erroneous username");
        return;
    }
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        // if (server == content) //find if server defined
        // {
        //     sendError(_client[i], "462", "Unauthorized command (already registered)");
        //     return ;
        // }
    }
    _client[i].setUser(content);
    std::string msg = "name : " + _client[i].getUser();
    servSend(_fds[i].fd, msg);
}