/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:55:46 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/13 18:17:46 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/server.hpp"

int main(int ac, char **av)
{
    Server server;

    if (ac != 3 && av[0])
    {
        std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
        return 1;
    }

    try
    {
        server.start(av);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    // if (signal(SIGINT, sigintHandler) == SIG_ERR)
	// {
	// 	std::cerr << "Error: can't catch SIGINT" << std::endl;
	// 	delete (server);
	// 	return (1);
	// }
    while (true)
    {
        server.acceptClient();
    }
    return 0;
}