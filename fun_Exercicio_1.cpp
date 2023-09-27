
#include "fun_head_fast.h"

//Custo de cada firma é uma distribuição normal
//O preço desejado é o custo unitário presente ajustado por um markup fixo
//Preço é uma média ponderada entre o preço desejado e o preço médio de mercado no período anterior
//Os pesos dessa média são uma medida do grau de monopólio da firma

MODELBEGIN

EQUATION("Price")

v[0] = V("degree_of_monopoly");
v[1] = 1-v[0];
v[2] = V("Desired");
v[3] = AVEL("Price",1);

/*

	Versão alternativa #1
	
v[3] = VL("Average",1);

*/

RESULT((v[0]*v[2])+(v[1]*v[3]))

EQUATION("Average")
RESULT(AVE("Price"))

/*

	Versão alternativa #2
	
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

v[0] = 0;

CYCLE(cur,"FIRM")
{

	v[1] = VS(cur,"Price");
	
	if(v[1]>v[0])
		
		{
		
		v[0] = v[1];
		
		}
		
}

RESULT(v[0])

/*

	Versão alternativa #3?
	
EQUATION("Maximum")

v[0] = MAX("Price");

CYCLE(cur, "SECTOR")
{

	v[1] = SUM_CND("Price","Price","==",v[0]);
}

RESULT(v[1])

*/

/*

	Versão alternativa #4
	
EQUATION("Maximum")
RESULT(MAX("Price"))

*/

EQUATION("Quality")

v[0] = VL("Quality",1);
v[1] = uniform(0, 1);
v[2] = v[0]+v[1];

RESULT(v[2])

EQUATION("Competitiveness")

v[0] = V("Quality");
v[1] = V("Price");
v[2] = V("Elast_Q");
v[3] = V("Elast_P");
v[4] = (pow(v[0],v[2]))/(pow(v[1],v[3]));

RESULT(v[4])

EQUATION("Market_Share")

v[0] = VL("Market_Share",1);
v[1] = V("MS_Adjus");
v[2] = V("Competitiveness");
v[3] = AVE("Competitiveness");
v[4] = (v[2]/v[3]) - 1;
v[5] = v[0]*(1+(v[1]*v[4]));

RESULT(v[5])

EQUATION("Consistency_Test")
RESULT(SUM("Market_Share"))

EQUATION("MS_Adjusted")

v[0] = V("Consistency_Test");

CYCLE(cur, "FIRM")
{
	v[1] = V("Market_Share");
	v[2] = v[1]/v[0];
}

RESULT(v[2])

EQUATION("CT_Adjusted")
RESULT(SUM("MS_Adjusted"))

MODELEND

void close_sim( void )
{
	
}
