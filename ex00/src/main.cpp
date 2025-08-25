/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:43:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/25 15:12:29 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ScalarConverter.hpp"

int main(int ac, char **argv)
{
	if (ac != 2)
	{
		std::cerr << "./convert [argument]" << std::endl;
		return (0);	
	}
	std::string	av = argv[1];
	if (ScalarConverter::convert(av))//Si j'entre directement av[1] dans convert : conversion implicite
		return (0);
	std::cerr << "./convert [char]-[int]-[float]-[double]" << std::endl;
	return (0);
}