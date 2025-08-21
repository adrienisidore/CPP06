/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:37:31 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/21 17:53:48 by aisidore         ###   ########.fr       */
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

static bool			printMsg(std::string msg[4], char c, int i, float f, double d)
{
	std::cout << msg[0] << c << std::endl;
	std::cout << msg[1] << i << std::endl;
	std::cout << msg[2] << f << "f" << std::endl;
	std::cout << msg[3] << d << std::endl;
	return (true);
}

static bool			convertChar(std::string msg[4], char c)
{
	int		i = static_cast<int>(c);
	float	f = static_cast<float>(c);
	double	d = static_cast<double>(c);
	return (printMsg(msg, c, i, f, d));
}

static bool			convertInt(std::string msg[4], int i)
{
	char	c = static_cast<char>(i);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(i);
	std::cout << "COUCOUUUU c : " << c << std::endl;//
	return (printMsg(msg, c, i, f, d));	
}

static bool			convertFloat(std::string msg[4], float f)
{
	char	c = static_cast<char>(f);
	int		i = static_cast<int>(f);
	double	d = static_cast<double>(f);
	return (printMsg(msg, c, i, f, d));	
}

static bool			convertDouble(std::string msg[4], double dbl)
{
	char	c = static_cast<char>(dbl);
	int		i = static_cast<int>(dbl);
	float	f = static_cast<float>(dbl);
	return (printMsg(msg, c, i, f, dbl));	
}

//Tester avec des espaces avant et apres "             127f                  "

//PB :
//PARFOIS char ne s'affiche pas
//J;ai l'impression que float et double ont tjrs la meme valeur
bool				ScalarConverter::convert(const std::string &av)
{
	//On gere le cas ./convert "" car sinon strtod : dbl = 0.0 et end = "" (pointe vers '\0')
	if (av.empty()) return (false);
	std::string msg[4] = {"char: ", "int: ", "float: ", "double: "};

	//Testons inf, -inf, +inf, nan, inff, -inff, +inff
	//Comme pour Harl (ex05 CPP01 on peut faire un truc propre) puis return (true); ???????

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
			return (convertInt(msg, static_cast<int>(dbl)));//downcast explicite a la compilation
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
			return(false);//std::cerr << "Error" << std::endl; ON PEUT LE METTRE DANS LE MAIN
		else
			return (convertFloat(msg, static_cast<float>(dbl)));
	}
	//1 caractere a ete entre, et il est imprimable.
	//Meme s'il s'agit d'un nb 0 a 9 ca a deja ete traite avant.
	if (av.length() == 1 && av[0] > 32 && av[0] < 126)
		return (convertChar(msg, av[0]));
	return(false);
}
