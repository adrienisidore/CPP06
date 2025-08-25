/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:27:37 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/25 16:32:14 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Serialize.hpp"

int main(void)
{
	Data data;
	data.val1 = 0;
	data.val2 = 1;

	std::cout << "Data pointer: " << &data << std::endl;

	uintptr_t raw = Serialize::serialize(&data);
	std::cout << "Serialized Data pointer: " << raw << std::endl;

	Data *deserialized = Serialize::deserialize(raw);
	std::cout << "Deserialized Data pointer: " << deserialized << std::endl;

	std::cout << "Data val1 = " << data.val1 << std::endl;
	std::cout << "Data val2 = " << data.val2 << std::endl;
	std::cout << "Deserialized Data val1 = " << deserialized->val1 << std::endl;
	std::cout << "Deserialized Data val2 = " << deserialized->val2 << std::endl;

	return (0);
}