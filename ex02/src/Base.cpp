/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:49:04 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/20 18:26:26 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Base.hpp"
#include "../A.hpp"
#include "../B.hpp"
#include "../C.hpp"

Base::~Base() {}

Base * generate(void)
{
	// Initialiser la graine pour avoir des nombres différents à chaque exécution
    std::srand(std::time(NULL));
	int rnd = std::rand() % 3;

	if (rnd == 1)
		return (new A());
	else if (rnd == 2)
		return (new B());
	else
		return (new C());
	return (NULL);
}
// dynamic_cast renvoie NULL si le cast echoue
void identify(Base* p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "undefined type" << std::endl;
}

void identify(Base& p)
{
	try
	{
		static_cast<void>(dynamic_cast<A &>(p));
		std::cout << "A" << std::endl;
	}
	catch (const std::exception& e) {
		try
		{
			static_cast<void>(dynamic_cast<B &>(p));
			std::cout << "B" << std::endl;
		}
		catch (const std::exception& e) {
			try
			{
				static_cast<void>(dynamic_cast<C &>(p));
				std::cout << "C" << std::endl;
			}
			catch (const std::exception& e) {std::cout << "undefined type" << std::endl;}
		}
	}
}
