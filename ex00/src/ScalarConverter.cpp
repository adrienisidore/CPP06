/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:37:31 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/20 21:36:04 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& copy) {static_cast<void>(copy);}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& rhs)
{
	static_cast<void>(rhs);
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

//0 a 9 sont des caracteres qui ne sont pas affichables 
//1) j'utilise strtod pour voir si le av est un numerique






// long strtol(const char *str, char **end, 10);
// Si la chaîne ne commence pas par un nombre valide → retourne 0.
// Si le nombre dépasse la plage de long :
// 	Retourne LONG_MAX ou LONG_MIN selon le signe.
// 	Et errno est positionné à ERANGE.
// Ne supporte pas les nb decimaux



//av : conversion implicite
//const std::string &av
//chaine vide, caractere non imprimable (dont chaine faite que d'espaces)
//Si y'a des espaces avant et apres faut faire quoi ?
void				ScalarConverter::convert(const std::string &av)
{
	if (av.empty()) return;//gere le cas ./convert "" car sinon strtod : val = 0.0 et end = "" (pointe vers '\0')

	//on gere proprement les cas -inff, nan etc ici ? (avec un enum ?)

	//On gere le cas ou le user entre 1 character ici.
	// if (av.length() == 1)// && av[0] est imprimable ( HORS NUMERIQUES)
	//Coder une fonction qui affiche le texte s'il s'agit bien d'un caractere,
	//cette fonction renvoie un booleen qui est positif si qqchose a ete affiche, negatif sinon.
	//Si c'est neg on continue a coder

	char* end;//Pointe vers le 1er element non numerique (hors -+.)
	double val = std::strtod(av.c_str(), &end);//vaut 0.0 si la conversion echoue,
	//mais vaut aussi 0.0 si j'entre 0.0. Donc on regarde plutot end

	float test = 5E-2f;

	//et si le user entre ou truc plus grand qu'un double ? errno ? koor.fr
	if (end != av.c_str() && *end == '\0')
	{
		//A) la conversion a eu lieu, toute la chaine a ete consommee :
		//le user a pu aussi entrer 1.23e4 ou 5E-2
		//le user a entre un nb valide mais on ne sait pas encore s'il s'agit d'un int ou un double.
		
		if (av.find('.') == std::string::npos && av.find('e') == std::string::npos && av.find('E') == std::string::npos)
		{
    		//Pas d'exposant ni de decimal entrees. Il s'agit d'un nombre avec que des chiffres.
			//Si ce nombre est compris entre [INT_MIN; INT_MAX] il s'agit forcement d'un int
		}
		else
		{
			//il s'agit d'un double
		}

		
	}
	else if (end != av.c_str() && *end == 'f' && *(end + 1) == '\0')
	{
    	// Au moins 1 chiffre a ete converti (end ne pointe pas vers le 1er element de la chaien),
		//puis a ete suivi de 'f' et c'est tout. Il s'agit donc d'un float valide.
		//le user a pu aussi entrer 1.23e4 ou 5E-2

		//je recupere val (un double) que je converti en float (downcast) float f = static_cast<float>(val);
		//je retrouverai le float initial car l'upcast en double ne fait pas perdre en precision
		//je peux alors transformer aisement en int et en double et en char avec static_cast.
	}
	



}

// const char* cstr = av.c_str();

//  static_cast<char>(av[0]);