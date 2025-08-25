/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialize.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:19:02 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/25 16:27:22 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Serialize.hpp"


Serialize::Serialize(void) {}

Serialize::Serialize(const Serialize& copy) {static_cast<void>(copy);}

Serialize&	Serialize::operator=(const Serialize& rhs)
{
	static_cast<void>(rhs);
	return (*this);
}

Serialize::~Serialize(void) {}

uintptr_t	Serialize::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	Serialize::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}