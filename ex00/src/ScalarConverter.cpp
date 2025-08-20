/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:37:31 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/20 20:17:43 by aisidore         ###   ########.fr       */
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


	//On gere le cas ou le user entre 1 character ici.

	char* end = NULL;//Pointe vers le 1er element non numerique (hors -+.)
	double val = std::strtod(av.c_str(), &end);//vaut 0.0 si la conversion echoue
	//Pour les float il faut considerer la conversion reussie si *end = f et que *(end + 1) = '\0'
	
	//Si la conversion a reussie, et que *end = f et que *(end + 1) = '\0' alors on convertit val
	//en float. Pour char on convertit ce float en char, pour int on convertit ce float en int,
	//pour float on affiche juste std::string av et pour double on affiche val.
	



}

// const char* cstr = av.c_str();

//  static_cast<char>(av[0]);