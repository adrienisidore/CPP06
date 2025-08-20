/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:40:18 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/20 18:18:49 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>
# include <exception>
# include <cstdlib>  // pour rand()
# include <ctime>    // pour time()

class	Base			   {public: virtual ~Base();};

Base * generate(void);

void identify(Base* p);

void identify(Base& p);

#endif