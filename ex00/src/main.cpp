/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:43:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/20 17:28:55 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ScalarConverter.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		std::cout << "./convert [argument]" << std::endl;
	else
		ScalarConverter::convert(av[1]);
	return (0);
}