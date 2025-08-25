/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:39:23 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/25 15:53:03 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iomanip> //setprecision
# include <iostream>
# include <cstdlib> //strtod strtol
# include <cfloat>  // Pour FLT_MAX et FLT_MIN (si j'entre un double et que je m'amuse a entrer f a la fin ??????)
# include <cerrno>  // Pour ERANGE (errno vaut ca si mon double a overflow)
# include <climits> // Pour INT_MIN et INT_MAX
# include <cmath>

class ScalarConverter
{
	public:
		static bool	convert(const std::string &av);
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& copy);
		ScalarConverter&	operator=(const ScalarConverter& rhs);
		~ScalarConverter();
};

#endif