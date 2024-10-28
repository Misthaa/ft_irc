/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:02:56 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/28 19:02:19 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::quitToken(int i)
{
    _client[i].closeClient();
    _fds[i].fd = -1;
    _fds[i].events = 0;
    _fds[i].revents = 0;
    return ;
}