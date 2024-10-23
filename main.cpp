/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:55:46 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/23 18:46:06 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void closeServer(Server *server)
{
    static Server *serv = NULL;

    if (serv == NULL)
    {
        serv = server;
        return ;
    }
    serv->closeAll();
    delete serv;
    exit(0);
}

void sigintHandler(int sig)
{
    (void)sig;
    std::cout << "Caught signal " << std::endl;
    closeServer(NULL);
}

int main(int ac, char **av)
{
    Server *server = new Server();

    if (!server)
    {
        std::cerr << "Error: can't create server" << std::endl;
        return 1;
    }
    if (ac != 3 && av[0])
    {
        std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
        return 1;
    }

    try
    {
        server->start(av);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        delete server;
        return 1;
    }
    
    closeServer(server);
    
    if (signal(SIGINT, sigintHandler) == SIG_ERR)
	{
		std::cerr << "Error: can't catch SIGINT" << std::endl;
		return (1);
	}
    
    while (true)
    {
        server->acceptClient();
    }
    
    return 0;
}