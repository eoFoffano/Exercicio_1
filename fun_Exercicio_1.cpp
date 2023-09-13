
#include "fun_head_fast.h"

//Custo de cada firma � uma distribui��o normal
//O pre�o desejado � o custo unit�rio presente ajustado por um markup fixo
//Pre�o � uma m�dia ponderada entre o pre�o desejado e o pre�o m�dio de mercado no per�odo anterior
//Os pesos dessa m�dia s�o uma medida do grau de monop�lio da firma

MODELBEGIN

EQUATION("Price")

v[0] = V("degree_of_monopoly");
v[1] = 1 - v[0];
v[2] = V("Desired");
v[3] = AVEL("Price",1);

/*

	Vers�o alternativa #1
	
v[3] = VL("Average",1);

*/

RESULT((v[0]*v[2])+(v[1]*v[3]))

EQUATION("Average")
RESULT(AVE("Price"))

/*

	Vers�o alternativa #2
	
EQUATION("Average")

v[0] = 0;
v[2] = 0;
CYCLE(cur, "FIRM")
{
	v[1] = VS(cur,"Price");
	v[0] = v[0] + v[1];
	v[2] = v[2] + 1;
	
}
v[3] = v[0]/v[2];

RESULT(v[3])

*/

EQUATION("Desired")

v[0] = V("markup");
v[1] = V("Cost");
v[2] = 1 + v[0];

RESULT(v[1]*v[2])

EQUATION("Cost")

v[0] = V("avg");
v[1] = V("sd");
v[2] = norm(v[0],v[1]);

RESULT(v[2])

EQUATION("Maximum")

v[0] = MAX("Price");

CYCLE(cur, "SECTOR")
{

	v[1] = SUM_CND("Price","Price","==",v[0]);
}

RESULT(v[1])



/*

	Vers�o alternativa #3
	
EQUATION("Maximum")
RESULT(MAX("Price"))

*/

MODELEND

void close_sim( void )
{
	
}
