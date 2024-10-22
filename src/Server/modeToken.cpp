/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:22:02 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/18 16:29:12 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// void Server::limitUserChannel(std::string mode, Client& client, std::string channelName)
// {
//     for (int j = 0; j < MAX_CHANNEL; j++)
//     {
//         if (mode == "+l")
//         {
//             if (_channel[j].getChannelName() == channelName)
//             {
//                 if (_channel[j].getChannelClient().size() >= MAX_CLIENT)
//                 {
//                     sendError(client, "405", "* MODE :Channel is full");
//                     return ;
//                 }
//             }
//         }
//         else if (mode == "-l")
//         {
            
//         }
//         // if (_channel[j].getChannelName() == channelName)
//         // {
//         //     if (_channel[j].getChannelClient().size() >= 10)
//         //     {
//         //         sendError(client, "405", "* MODE :Channel is full");
//         //         return ;
//         //     }
//         // }
//     }
// }

void Server::modeToken(std::string content, int i)
{
    std::string nickname;
    std::string mode;

    nickname = content.substr(0, content.find(" "));
    mode = content.substr(content.find(" ") + 1);
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[j].getNickname() == nickname)
        {
            // if (mode == "+o")
            // {
            //     _client[j].setOperator(true);
            //     std::string msg = "You are now operator";
            //     servSend(_fds[j].fd, msg);
            //     return ;
            // }
            // else if (mode == "-o")
            // {
            //     _client[j].setOperator(false);
            //     std::string msg = "You are no longer operator";
            //     servSend(_fds[j].fd, msg);
            //     return ;
            // }
            // else
            // {
            //     sendError(_client[i], "461", "* MODE :Unknown mode");
            //     return ;
            // }
        }
    }
    sendError(_client[i], "461", "* MODE :No such nickname");
    return ;
}