/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:32 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 15:05:05 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

void closeBot(Bot *bot)
{
    static Bot *savedBot = NULL;

    if (savedBot == NULL)
    {
        savedBot = bot;
        return ;
    }
    delete savedBot;
    exit(0);
}

void sigintHandler(int sig)
{
    (void)sig;
    std::cout << "Caught signal " << std::endl;
    closeBot(NULL);
}

int main(int ac, char **av)
{
    if (ac != 4)
    {
        std::cerr << "Usage: ./bot [nickname] [port] [password]" << std::endl;
        return 1;
    }
    
    Bot *bot = new Bot(av[1], av[2], av[3]);
    
    if (!bot)
    {
        std::cerr << "Error: can't create bot" << std::endl;
        return 1;
    }

    closeBot(bot);
    
    if (signal(SIGINT, sigintHandler) == SIG_ERR)
	{
		std::cerr << "Error: can't catch SIGINT" << std::endl;
		return (1);
	}
    
    try {
        bot->run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}