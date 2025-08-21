/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:37:31 by aisidore          #+#    #+#             */
/*   Updated: 2025/08/21 16:33:52 by aisidore         ###   ########.fr       */
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



//Si j'entre directement av[1] dans convert : conversion implicite
//chaine vide, caractere non imprimable (dont chaine faite que d'espaces)
//Si y'a des espaces avant et apres faut faire quoi ?
void				ScalarConverter::convert(const std::string &av)
{
	if (av.empty()) return;//gere le cas ./convert "" car sinon strtod : dbl = 0.0 et end = "" (pointe vers '\0')

	//on gere proprement les cas -inff, nan etc ici ? (avec un enum ?)
	//

	char* end;//Pointe vers le 1er element non numerique (hors -+.)
	double dbl = std::strtod(av.c_str(), &end);//vaut 0.0 si la conversion echoue,
	//mais vaut aussi 0.0 si j'entre 0.0. Donc on regarde plutot end
	if (errno == ERANGE)
		return;//std::cerr << "Error" << std::endl; ON PEUT LE METTRE DANS LE MAIN
		//le double a overflow, message d'erreur indiquant es types acceptes puis return;

	
	//et si le user entre ou truc plus grand qu'un double ? errno ? koor.fr
	if (end != av.c_str() && *end == '\0')
	{
		//A) la conversion a eu lieu, toute la chaine a ete consommee :
		//le user a pu aussi entrer 1.23e4 ou 5E-2
		//le user a entre un nb valide (1.23e4 ou 5E-2 sont aussi valides)
		//mais on ne sait pas encore s'il s'agit d'un int ou un double.
		//S'il a entre un nb avec un exposant c'etait forcement un double int ee = 1e4; est un double
		//downcaste implicitement.
		if (av.find('.') == std::string::npos &&
        av.find('e') == std::string::npos &&
        av.find('E') == std::string::npos &&
        dbl >= INT_MIN && dbl <= INT_MAX)
		{
    		//Pas d'exposant ni de decimal entrees. Il s'agit d'un nombre avec que des chiffres.
			//Si ce nombre est compris entre [INT_MIN; INT_MAX] il s'agit forcement d'un int
			int	intt = static_cast<int>(dbl);//downcast explicite a la compilation
		}
		else
		{
			//il s'agit d'un double, on peut travailler directement avec dbl.
		}
	}
	else if (end != av.c_str() && (*end == 'f' || *end == 'F') && *(end + 1) == '\0')
	{
    	// Au moins 1 chiffre a ete converti (end ne pointe pas vers le 1er element de la chaien),
		//puis a ete suivi de 'f' et c'est tout. Il s'agit donc d'un float valide.
		//le user a pu aussi entrer 1.23e4 ou 5E-2, ;ais dans ce cas il s'agissait d'un double.

		//Le seul truc a checker c'est si le user a entre un nb trop grand pr etre
		//un float mais qui passe la 1ere protection (peut etre contenu dans un double):
		//99999999999999999f.
		if (dbl > FLT_MAX || dbl < -FLT_MAX)
			return;//std::cerr << "Error" << std::endl; ON PEUT LE METTRE DANS LE MAIN
		else
		{
			float flt = static_cast<float>(dbl);
			//anc
		}
			
	}
	
	//Cas ou j'ai juste un caractere imprimable :
	// if (av.length() == 1)// && av[0] est imprimable ( HORS NUMERIQUES mais a la limite
	//ca a deja passe le filtre du dessus 0 a 9).

	//Sinon message d'erreur indiquant les types acceptes // std::cerr << << end; return;
	//(ca devrait fonctionner aussi si le user entre "         ")


}

// const char* cstr = av.c_str();

//  static_cast<char>(av[0]);