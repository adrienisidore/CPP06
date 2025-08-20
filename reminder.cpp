
Conversion : transformer les bits d'une valeur, vers le codage d'un autre type (int vers float etc).

Reinterpretation/conversion identitaire : on ne touche pas l ordre des bits

Upcast : conversion vers un type plus general (int vers void par ex), sans toucher l ordre des bits
Downcast : conversion vers un type plus restreint (void vers int par ex), sans toucher l ordre des bits

Implicit : on dit rien au compilateur, il l anticipe
static : a la compilation
dynamic : durant le runtime, via le polymorphisme
const : changer en const ou inversement



											Tableau
					conversion	|	reint.	|	upcast	|	downcast	|	type qualifier
------------------------------------------------------------------------------------------
Implicit cast  	  |		yes		|			|	yes		|				|
static_cast		  |		yes*	|			|	yes*	|		yes*	|
dynamic_cast	  |				|			|	yes**	|		yes**	|
const_cast		  |				|			|			|				|		yes
reinterpret_cast  |				|	yes***	|	yes***	|		yes***	|
Legacy cast en C 		yes			yes			yes				yes				yes

											Tableau
					semantic check	|	reliable at run	|	check at run
------------------------------------------------------------------------------------------
Implicit cast  	  |		  yes		|		yes			|
static_cast		  |		  yes		|					|
dynamic_cast	  |		  yes		|		yes			|			yes
const_cast		  |					|					|
reinterpret_cast  |					|					|
Legacy cast en C		(Aucun check semantique non plus pour le cast en C)


*Si on a une maitrise complete de l arbre d heritage alors pas de souci, mais si par malheur
je cast un objet sur un type dont il n herite pas alors ca va compiler, mais a l execution
ca va peter (voir ex sur intra). Le static verifie juste si on est dans l arbre d'heritage.
UPCAST/DOWNCAST : 
class	Parent;			   {};
class	Child1: public Parent {};
class	Child2 : public Parent {};
class	Unrelated		   {};//N'a aucun lien avec les autres
int main()
{
	Child1	a;

	Parent*	b = &a;//Upcast implicite, pas de souci Parent est plus general
	Child1*	c = b;//Implicit downcast ca compile pas
	Child2* d = static_cast<Child 2*>(b);//Downcast explicite, ca fonctionne
	Unrelated* e = static_cast<Unrelated *>(&a);//Conversion explicite mais IMPOSSIBLE, static_cast détecte lorsque des casts
// sont fait sur des adresses non compatibles: qui ne font pas partie du même arbre d'héritage
	Child1* g;
	Child2* f = static_cast<Child2*>(g);//Accepte mais risque de poser probleme a l'exec

	return (0);
}

**Permet de verifier si le transfert hierarchique d'une classe a l autre est realiste.
Utile si le type peut varier a l execution, par exemple si j ai une classe generique plug in dont herite
pleins de plug in differents. Des que je connecte mon logiciel a un des plug in je dois changer le type 
de mon pointeur vers celui du bon plug in.
Utilisable par polymorphisme.

#include <iostream>
#include <typeinfo>
#include <exception>

class	Parent			   {public: virtual ~Parent(){}};
class	Child1 : public Parent {};
class	Child2 : public Parent {};

int main()
{
	Child1	a;

	Parent*	b = &a;//Upcast implicite, pas de souci Parent est plus general
	
	//Explicit downcast : voyons voir si ca marche pendant le runtime

	Child1*	c = dynamic_cast<Child1 *>(b);
	if (c == NULL) {std::cout << "conversion failed" << std::endl;}
	else {std::cout << "Ok" << std::endl;}

	//Pour les ref on peut pas renvoyer NULL donc on utilise try et bad_cast qui est fait expres en C++
	try {
		Child2&	d = dynamic_cast<Child2 &>(*b); //Le type reel n'etant pas Child2 (ou Child2-compatible) le dynamic cast va echouer
		std::cout << "Ok" << std::endl;
	}
	catch (std::bad_cast &bc) {
		std::cout << "conversion failed because " << bc.what() << std::endl;
		return (0);
	}

	return (0);
}


***C'est le cast le plus permissif : reinterpreter n importe quelle adresse vers une autre adresse (down/up)
avec les consequences aue ca peut avoir. Aucune verification semantique n est faite,
le compilateur reinterprete et a l execution on verra si on a des problemes ou pas.

int main( void ) {
	float a = 420.042f;
	void* b = &a;//promotion implicite, aucun souci
	int *c = reinterpret_cast<int *>(b);//demotion explicite acceptee
	int& d = reinterpret_cast<int &>(b);//demotion explicite acceptee aussi
	return (0);
}

CAS D'USAGE : si je dois retyper, cad je recois une donnee (un flux d'octets)
que je stock dans un void* (buffer de memoire brute non type) et le protocole indique que le flux
d'octets recu c'est des chars. On va donc pouvoir reinterpreter en char *