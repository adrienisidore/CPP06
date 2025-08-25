/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:37:31 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/25 16:52:03 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& copy) {static_cast<void>(copy);}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& rhs)
{
	static_cast<void>(rhs);
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

static bool			IsaNumber(std::string str)
{
	if (str == "nanf" || str == "+inff" || str == "-inff"
		|| str == "nan" || str == "-inf" || str == "+inf" || str == "inf")
		return (false);
	return (true);
}

static bool			printMsg(std::string msg[5], char c, int i, float f, double d)
{
	if (c)
		std::cout << msg[0] << "\'" << c << "\'" << std::endl;
	else if (IsaNumber(msg[4]))
		std::cout << msg[0] << "Non displayable" << std::endl;
	else
		std::cout << msg[0] << "impossible" << std::endl;
	if (IsaNumber(msg[4]))	
		std::cout << msg[1] << i << std::endl;
	else
		std::cout << msg[1] << "impossible" << std::endl;
	if (!std::fabs(f - std::floor(f)) && std::fabs(f) < 1e6f)
		std::cout << msg[2] << f << ".0f" << std::endl;
	else
		std::cout << msg[2] << std::setprecision(7) << f << "f" << std::endl;	
	if (!std::fabs(d - std::floor(d)) && std::fabs(d) < 1e6)
		std::cout << msg[3] << d << ".0" << std::endl;
	else
		std::cout << msg[3] << std::setprecision(15) << d << std::endl;
	return (true);
}

static bool			convertChar(std::string msg[5], char c)
{
	int		i = static_cast<int>(c);
	float	f = static_cast<float>(c);
	double	d = static_cast<double>(c);
	return (printMsg(msg, c, i, f, d));
}

static bool			convertInt(std::string msg[5], int i)
{
	char	c = static_cast<char>(i);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(i);
	if (i < 33 || i > 126)
		c = 0;
	return (printMsg(msg, c, i, f, d));	
}

static bool			convertFloat(std::string msg[5], float f)
{
	char	c = static_cast<char>(f);
	int		i = static_cast<int>(f);
	double	d = static_cast<double>(f);
	if (i < 33 || i > 126)
		c = 0;
	return (printMsg(msg, c, i, f, d));	
}

static bool			convertDouble(std::string msg[5], double dbl)
{
	char	c = static_cast<char>(dbl);
	int		i = static_cast<int>(dbl);
	float	f = static_cast<float>(dbl);
	if (i < 33 || i > 126)
		c = 0;
	return (printMsg(msg, c, i, f, dbl));	
}

bool				ScalarConverter::convert(const std::string &av)
{
	std::string msg[5] = {"char: ", "int: ", "float: ", "double: ", av};
	if (av == " ") return (convertChar(msg, av[0]));
	if (av == "+inff") return (convert("+inf"));
	if (av == "-inff") return (convert("-inf"));
	if (av == "-inff") return (convertChar(msg, av[0]));
	char* end;//Pointe vers le 1er element non numerique (hors -+.)
	double dbl = std::strtod(av.c_str(), &end);//vaut 0.0 si la conversion echoue, mais aussi si j'entre 0.
	if (errno == ERANGE)
		return (false);//le double a overflow le user a entre un argument invalide
	if (end != av.c_str() && *end == '\0')
	{
		//La conversion a eu lieu, toute la chaine a ete consommee :
		//le user a pu aussi entrer 1.23e4 ou 5E-2 ou un nb lambda comme 50943855.545, 999
		//mais on ne sait pas encore s'il s'agit d'un int ou un double.
		//S'il a entre un nb avec un exposant c'etait forcement un double int ee = 1e4; est un double
		//downcaste implicitement.

		//Pas d'exposant ni de decimal entrees et on est dans les bornes [INT_MIN; INT_MAX].
		//Il s'agit d'un int.		
		if (av.find('.') == std::string::npos &&
        av.find('e') == std::string::npos &&
        av.find('E') == std::string::npos &&
        dbl >= INT_MIN && dbl <= INT_MAX)
			return (convertInt(msg, atoi(av.c_str())));//return (convertInt(msg, static_cast<int>(dbl)));//downcast explicite a la compilation
		else
			return (convertDouble(msg, dbl));//il s'agit d'un double, on peut travailler directement avec dbl.
	}
	else if (end != av.c_str() && (*end == 'f' || *end == 'F') && *(end + 1) == '\0')
	{
    	// Au moins 1 chiffre a ete converti (end ne pointe pas vers le 1er element de la chaine),
		//puis a ete suivi de 'f' et c'est tout. Il s'agit donc d'un float valide.

		//Le seul truc a checker c'est si le user a entre un nb trop grand pr etre
		//un float mais qui passe la 1ere protection (peut etre contenu dans un double),
		//par ex 99999999999999999f.
		if (dbl > FLT_MAX || dbl < -FLT_MAX)
			return(false);
		else
			return (convertFloat(msg, std::strtof(av.c_str(), NULL)));//return (convertFloat(msg, static_cast<float>(dbl)));
	}
	if (av.length() == 1 && av[0] >= '!' && av[0] <= '~')
		return (convertChar(msg, av[0]));
	return(false);
}
