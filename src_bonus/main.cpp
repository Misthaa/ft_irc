/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:32 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/23 17:40:06 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

int main(int ac, char **av)
{
    if (ac != 4)
    {
        std::cerr << "Usage: ./bot [nickname] [port] [password]" << std::endl;
        return 1;
    }
    bot bot(av[1], av[2], av[3]);
    try {
        bot.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}