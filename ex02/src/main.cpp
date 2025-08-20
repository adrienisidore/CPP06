/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:05:36 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/20 18:17:04 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Base.hpp"
#include "../A.hpp"
#include "../B.hpp"
#include "../C.hpp"

int main(void)
{
	Base*	ptr = generate();
	Base&	r = *ptr;

	identify(ptr);
	identify(r);

	delete ptr;
	return (0);
}