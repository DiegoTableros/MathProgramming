#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>
#define LONGMAX 128

enum aux_pronombres{Yo, Tu, ElElla, Nosotros, Ustedes, Ellos, total_pronombres};
enum tiempos_simples{Presente,Preterito,Futuro,Copreterito,Postpreterito,total_tiempos_simples};
typedef char enBasePronombres[total_pronombres*total_tiempos_simples][LONGMAX];

enBasePronombres Pronombres = { "yo", "t�", "�l/ella", "nosotros", "ustedes", "ellos"};                                                                             
char *indicativo_simple[]={"Presente", "Pret�rito", "Futuro","Copret�rito","Postpret�rito"};
char *tiempo_compuesto[]={"Antepresente", "Antecopret�rito", "Antepret�rito","Antefuturo", "Antepospreterito"};
char *tiempo_compuesto_sub[]={"Antepresente", "Antepret�rito", "Antefuturo"};  

enBasePronombres compuesto =  {"        he", "       has", "        ha", "     hemos", "       han", "       han","      hube", "   hubiste", "      hubo", "   hubimos", "  hubieron", "  hubieron","     habr�", "    habr�s", "     habr�", "  habremos", "    habr�n", "    habr�n","     hab�a", "    hab�as", "     hab�a", "  hab�amos", "    hab�an", "    hab�an","    habr�a", "   habr�as", "    habr�a", " habr�amos", "   habr�an", "   habr�an"}; 		   
enBasePronombres termina_sub_AR = {"e      ", "es     ", "e      ", "emos   ", "en     ", "en     ","ara    ", "aras   ", "ara    ", "�ramos ", "aran   ", "aran   ","are    ", "ares   ", "are    ", "�remos ", "aren   ", "aren   "};			
enBasePronombres termina_sub_ER = {"a       ", "as      ", "a       ", "amos    ", "an      ", "an      ","iera    ", "ieras   ", "iera    ", "i�ramos ", "ieran   ", "ieran   ","iere    ", "ieres   ", "iere    ", "i�remos ", "ieren   ", "ieren   "};
enBasePronombres compuestosub = {"       haya", "      hayas", "       haya", "    hayamos", "      hayan", "      hayan","    hubiera", "   hubieras", "    hubiera", " hubi�ramos", "   hubieran", "   hubieran","    hubiere", "   hubieres", "    hubiere", " hubi�remos", "   hubieren", "   hubieren"};
enBasePronombres termina_imperativo_AR = {"a","e","emos","en"};
enBasePronombres termina_imperativo_ER = {"e","a","amos","an"};
void regular_AR(FILE *archivo, char root[]);  
void regular_ER(FILE *archivo, char root[]);                                                                        
void regular_IR(FILE *archivo, char root[]);

enBasePronombres tiempo_simple_sentir ={"iento      ","ientes     ","iente      ","entimos    ","ienten     ","ienten     ","ent�       ","entiste    ","inti�      ","entimos    ","intieron   ","intieron   ","entir�     ","entir�s    ","entir�     ","entiremos  ","entir�n    ","entir�n    ","ent�a      ","ent�as     ","ent�a      ","ent�amos   ","ent�an     ","ent�an     ","entir�a    ","entir�as   ","entir�a    ","entir�amos ","entir�an   ","entir�an   "};					
enBasePronombres tiempo_sub_sentir = {"ienta      ", "ientas     ", "ienta      ", "intamos    ", "ientan     ", "ientan     ","intiera    ", "intieras   ", "intiera    ", "inti�ramos ", "intieran   ", "intieran   ","intiere    ", "intieres   ", "intiere    ", "inti�remos ", "intieren   ", "intieren   "};
enBasePronombres tiempo_simple_erguir = {"irgo        ","irgues      ","irgue       ","erguimos    ","irguen      ","irguen      ","ergu�       ","erguiste    ","irgui�      ","erguimos    ","irguieron   ","irguieron   ","erguir�     ","erguir�s    ","erguir�     ","erguiremos  ","erguir�n    ","erguir�n    ","ergu�a      ","ergu�as     ","ergu�a      ","ergu�amos   ","ergu�an     ","ergu�an     ","erguir�a    ","erguir�as   ","erguir�a    ","erguir�amos ","erguir�an   ","erguir�an   "};				     
enBasePronombres tiempo_sub_erguir = {"a        ", "as       ", "a        ", "amos     ", "ian      ", "ian      ","uiera    ", "uieras   ", "uiera    ", "ui�ramos ", "uieran   ", "uieran   ","uiere    ", "uieres   ", "uiere    ", "ui�remos ", "uieren   ", "uieren   "};
enBasePronombres tiempo_simple_dormir = {"uermo       ","uermes      ","uerme       ","ormimos     ","uermen      ","uermen      ","orm�        ","ormiste     ","urmi�       ","ormimos     ","urmieron    ","urmieron    ","ormir�      ","ormir�s     ","ormir�      ","ormiremos   ","ormir�n     ","ormir�n     ","orm�a       ","orm�as      ","orm�a       ","orm�amos    ","orm�an      ","orm�an      ","ormir�a     ","ormir�as    ","ormir�a     ","ormir�amos  ","ormir�an    ","ormir�an    "};
enBasePronombres tiempo_sub_dormir = {"uerma      ", "uermas     ", "uerma      ", "urmamos    ", "uerman     ", "uerman     ", "urmiera    ", "urmieras   ", "urmiera    ", "urmi�ramos ", "urmieran   ", "urmieran   ", "urmiere    ", "urmieres   ", "urmiere    ", "urmi�remos ", "urmieren   ", "urmieren   "};
enBasePronombres tiempo_simple_adquirir = { "ero      ","eres     ","ere      ","rimos    ","eren     ","eren     ","r�       ","riste    ","ri�      ","rimos    ","rieron   ","rieron   ","rir�     ","rir�s    ","rir�     ","riremos  ","rir�n    ","rir�n    ","r�a      ","r�as     ","r�a      ","r�amos   ","r�an     ","r�an     ","rir�a    ","rir�as   ","rir�a    ","rir�amos ","rir�an   ","rir�an   "};
enBasePronombres tiempo_sub_adquirir = { "era      ", "eras     ", "era      ", "ramos    ", "eran     ", "eran     ", "riera    ", "rieras   ", "riera    ", "ri�ramos ", "rieran   ", "rieran   ", "riere    ", "rieres   ", "riere    ", "ri�remos ", "rieren   ", "rieren   "};
enBasePronombres tiempo_simple_podrir = { "udro       ","udres      ","udre       ","odrimos    ","udren      ","udren      ","udr�       ","udriste    ","udri�      ","udrimos    ","udrieron   ","udieron    ","udrir�     ","udrir�s    ","udrir�     ","udriremos  ","udrir�n    ","udrir�n    ","udr�a      ","udr�as     ","udr�a      ","udr�amos   ","udr�an     ","udr�an     ","udrir�a    ","udrir�as   ","udrir�a    ","udrir�amos ","udrir�an   ","udrir�an   "};	
enBasePronombres tiempo_sub_podrir = { "udra       ", "udras      ", "udra       ", "udramos    ", "udran      ", "udran      ", "udriera    ", "udrieras   ", "udriera    ", "udri�ramos ", "udrieran   ", "udrieran   ", "udriere    ", "udrieres   ", "udriere    ", "udri�remos ", "udrieren   ", "udrieren   "};
enBasePronombres tiempo_simple_jugar = {  "ego      ","egas     ","ega      ","gamos    ","egan     ","egan     ","gu�      ","gaste    ","g�       ","gamos    ","garon    ","garon    ","gar�     ","gar�s    ","gar�     ","garemos  ","gar�n    ","gar�n    ","gaba     ","gabas    ","gaba     ","g�bamos  ","gaban    ","gaban    ","gar�a    ","gar�as   ","gar�a    ","gar�amos ","gar�an   ","gar�an   "};												  
enBasePronombres tiempo_sub_jugar = {"egue     ", "egues    ", "egue     ", "guemos   ", "eguen    ", "eguen    ", "gara     ", "garas    ", "gara     ", "g�ramos  ", "garan    ", "garan    ", "gare     ", "gares    ", "gare     ", "g�remos  ", "garen    ", "garen    "};
enBasePronombres tiempo_simple_hacer = {  "ago      ","aces     ","ace      ","acemos   ","acen     ","acen     ","ice      ","iciste   ","izo      ","icimos   ","icieron  ","icieron  ","ar�      ","ar�s     ","ar�      ","aremos   ","ar�n     ","ar�n     ","ac�a     ","ac�as    ","ac�a     ","ac�amos  ","ac�an    ","ac�an    ","ar�a     ","ar�as    ","ar�a     ","ar�amos  ","ar�an    ","ar�an    "};
enBasePronombres tiempo_sub_hacer = {"aga       ", "agas      ", "aga       ", "agamos    ", "agan      ", "agan      ","iciera    ", "icieras   ", "iciera    ", "ici�ramos ", "icieran   ", "icieran   ","iciere    ", "icieres   ", "iciere    ", "ici�remos ", "icieren   ", "icieren   "};							   
enBasePronombres termina_simple_AR = {"o       ","as      ","a       ","amos    ","an      ","an      ","�       ","aste    ","�       ","amos    ","aron    ","aron    ","ar�     ","ar�s    ","ar�     ","aremos  ","ar�n    ","ar�n    ","aba     ","abas    ","aba     ","�bamos  ","aban    ","aban    ","ar�a    ","ar�as   ","ar�a    ","ar�amos ","ar�an   ","ar�an   "};                                                                             
enBasePronombres termina_simple_ER = {"o       ","es      ","e       ","emos    ","en      ","en      ","�       ","iste    ","�o      ","imos    ","ieron   ","ieron   ","er�     ","er�s    ","er�     ","eremos  ","er�n    ","er�n    ","�a      ","�as     ","�a      ","�amos   ","�an     ","�an     ","er�a    ","er�as   ","er�a    ","er�amos ","er�an   ","er�an   "}; 
enBasePronombres termina_simple_IR = {"o       ","es      ","e       ","imos    ","en      ","en      ","�       ","iste    ","i�      ","imos    ","ieron   ","ieron   ","ir�     ","ir�s    ","ir�     ","iremos  ","ir�n    ","ir�n    ","�a      ","�as     ","�a      ","�amos   ","�an     ","�an     ","ir�a    ","ir�as   ","ir�a    ","ir�amos ","ir�an   ","ir�an   "};
void conj_modelo_sentir(FILE *archivo, char root[]);
void conj_modelo_erguir(FILE *archivo, char root[]);
void conj_modelo_dormir(FILE *archivo, char root[]);
void conj_modelo_adquirir(FILE *archivo, char root[]);
void conj_modelo_podrir(FILE *archivo, char root[]);
void conj_modelo_jugar(FILE *archivo, char root[]);
void conj_modelo_hacer(FILE *archivo, char root[]);

int main(int argc, char *argv[]) {                               
	FILE *archivo;              
	char verbo_cap[128], letra;            
	int longitud;
	archivo = fopen("resultado.txt", "w");
	if (archivo == NULL){
    	fprintf(stderr, "Error al abrir \"resultado.txt\"\n");
    	return 0;                                                          
	}
	printf("CONJUGADOR DE VERBOS REGULARES (y algunos IRREGULARES)\n\nVerbos irregulares conjugables:\n");
  	printf("\n\tModelo Sentir\n");
	printf("1)disentir\n2)desmentir\n3)presentir\n4)arrepentirse\n5)mentir\n6)asentir\n7)desconsentir\n8)consentir\n9)resentirse\n10)repentirse\n");
	printf("\n\tModelo Erguir\n");
	printf("\n\tModelo Dormir\n");
	printf("1)adormir\n2)maldormir\n");
	printf("\n\tModelo Adquirir\n");
	printf("1)readquirir\n2)coadquirir\n3)inquirir\n4)perquirir\n5)pesquirir\n");
	printf("\n\tModelo Podrir\n");
	printf("1)repodrir\n");
  	printf("\n\tModelo Jugar\n");
	printf("\n\tModelo Hacer\n");
	printf("1)rehacer\n2)desfacer\n3)grandifacer\n4)jacer\n5)facer\n6)contrahacer\n7)satisfacer\n8)licuefacer\n9)liquefacer\n10)refacer\n11)desahacer\n12)contrafacer\n13)deshacer\n14)rarefacer\n15)tumefacer\n16)bienfacer\n17)malfacer\n18)afacer\n");
	printf("\n\nEscriba un verbo regular o irregular de la lista anterior: ");
	///Lectura de verbo
	scanf("%s",verbo_cap);
	longitud = strlen(verbo_cap);
	fprintf(archivo,"CONJUGADOR DE VERBOS\n");
	///IF para ver modelo de pertenencia
	if(strcmp(verbo_cap,"sentir")==0 ||strcmp(verbo_cap,"disentir")==0 || strcmp(verbo_cap,"desmentir")==0 || strcmp(verbo_cap,"presentir")==0 || strcmp(verbo_cap,"arrepentirse")==0 ||strcmp(verbo_cap,"mentir")==0 ||strcmp(verbo_cap,"asentir")==0 || strcmp(verbo_cap,"desconsentir")==0 || strcmp(verbo_cap,"consentir")==0 || strcmp(verbo_cap,"resentirse")==0 || strcmp(verbo_cap,"repentirse")==0){
		if(strcmp(verbo_cap,"sentir")==0){
			fprintf(archivo, "Verbo\tSentir\n");
			fprintf(archivo, "\nDefinici�n. Experimentar sensaciones producidas por causas externas o internas.\n\n");
  		}
  		if(strcmp(verbo_cap,"disentir")==0){
  			fprintf(archivo, "Verbo\tDisentir\n");
			fprintf(archivo, "\nDefinici�n. No ajustarse al sentir o parecer de alguien.\n\n");
		}
		if(strcmp(verbo_cap,"desmentir")==0){
  			fprintf(archivo, "Verbo\tDesmentir\n");
			fprintf(archivo, "\nDefinici�n. Sostener o demostrar que un dicho o hecho es falso.\n\n");
		}
		if(strcmp(verbo_cap,"presentir")==0){
  			fprintf(archivo, "Verbo\tPresentir\n");
			fprintf(archivo, "\nDefinici�n. Intuir o tener la impresi�n de que algo va a suceder.\n\n");
		}
		if(strcmp(verbo_cap,"arrepentirse")==0){
  			fprintf(archivo, "Verbo\tArrepentirse\n");
			fprintf(archivo, "\nDefinici�n. Sentir pesar por haber hecho o haber dejado de hacer algo.\n\n");
		}
		if(strcmp(verbo_cap,"mentir")==0){
  			fprintf(archivo, "Verbo\tMentir\n");
			fprintf(archivo, "\nDefinici�n. Decir o manifestar lo contrario de lo que se sabe, cree o piensa.\n\n");
		}
		if(strcmp(verbo_cap,"asentir")==0){
  			fprintf(archivo, "Verbo\tAsentir\n");
			fprintf(archivo, "\nDefinici�n. Admitir como cierto o conveniente lo que otra persona ha afirmado o propuesto antes.\n\n");
		}
		if(strcmp(verbo_cap,"desconsentir")==0){
  			fprintf(archivo, "Verbo\tDesconsentir\n");
			fprintf(archivo, "\nDefinici�n. No consentir, dejar de consentir.\n\n");
		}
		if(strcmp(verbo_cap,"consentir")==0){
  			fprintf(archivo, "Verbo\tConsentir\n");
			fprintf(archivo, "\nDefinici�n. Permitir algo o condescender en que se haga.\n\n");
		}
		if(strcmp(verbo_cap,"resentirse")==0){
  			fprintf(archivo, "Verbo\tResentirse\n");
			fprintf(archivo, "\nDefinici�n. Tener sentimiento, pesar o enojo por algo.\n\n");
		}
		if(strcmp(verbo_cap,"repentirse")==0){
  			fprintf(archivo, "Verbo\tRepentirse\n");
			fprintf(archivo, "\nDefinici�n. Arrepentirse.\n\n");
		}
  		verbo_cap[longitud-2]='\0';
		conj_modelo_sentir(archivo, verbo_cap);	
	}else if(strcmp(verbo_cap,"erguir")==0){
  		fprintf(archivo, "\nVerbo\tErguir\n");
  		fprintf(archivo, "\nDefinici�n. Levantar y poner derecho a alguien o algo, especialmente el cuello o la cabeza.\n\n");
		verbo_cap[longitud-2]='\0';
  		conj_modelo_erguir(archivo, verbo_cap);
	}else if((strcmp(verbo_cap,"dormir")==0)||(strcmp(verbo_cap,"adormir")==0)||(strcmp(verbo_cap,"maldormir")==0)){
		if(strcmp(verbo_cap,"dormir")==0){
  			fprintf(archivo, "Verbo\tDormir\n");
  			fprintf(archivo, "\nDefinici�n. Hallarse en el estado de reposo que consiste en la inacci�n o suspensi�n de los sentidos y de todo movimiento voluntario.\n\n");	
		}
		if(strcmp(verbo_cap,"adormir")==0){
  			fprintf(archivo, "Verbo\tAdormir\n");
  			fprintf(archivo, "\nDefinici�n. Adormecer.\n\n");	
		}
		if(strcmp(verbo_cap,"maldormir")==0){
  			fprintf(archivo, "Verbo\tMaldormir\n");
  			fprintf(archivo, "\nDefinici�n. Dormir no comod�mente.\n\n");	
		}
		verbo_cap[longitud-2]= '\0';
  		conj_modelo_dormir(archivo, verbo_cap);			
	}else if((strcmp(verbo_cap,"adquirir")==0)||(strcmp(verbo_cap,"readquirir")==0)||(strcmp(verbo_cap,"coadquirir")==0)||(strcmp(verbo_cap,"inquirir")==0)||(strcmp(verbo_cap,"perquirir")==0)||(strcmp(verbo_cap,"pesquirir")==0)){
 		if(strcmp(verbo_cap,"adquirir")==0){
 			fprintf(archivo, "Verbo\tAdquirir\n");
  			fprintf(archivo, "\nDefinici�n. Coger, lograr o conseguir.\n\n");
		}
		if(strcmp(verbo_cap,"readquirir")==0){
 			fprintf(archivo, "Verbo\tReadquirir\n");
  			fprintf(archivo, "\nDefinici�n. Volver a adquirir.\n\n");
		}
		if(strcmp(verbo_cap,"coadquirir")==0){
 			fprintf(archivo, "Verbo\tCoadquirir\n");
  			fprintf(archivo, "\nDefinici�n. Adquirir dos o m�s personas una cosa.\n\n");
		}
		if(strcmp(verbo_cap,"inquirir")==0){
 			fprintf(archivo, "Verbo\tInquirir\n");
  			fprintf(archivo, "\nDefinici�n. Indagar, averiguar o examinar cuidadosamente algo.\n\n");
		}
		if(strcmp(verbo_cap,"perquirir")==0){
 			fprintf(archivo, "Verbo\tPerquirir\n");
  			fprintf(archivo, "\nDefinici�n. Investigar, buscar algo con cuidado y diligencia.\n\n");
		}
		if(strcmp(verbo_cap,"pesquirir")==0){
 			fprintf(archivo, "Verbo\tPesquirir\n");
  			fprintf(archivo, "\nDefinici�n. hace referencia en averiguar, comprobar, explorar, investigar, escrutar, indagar, etc.\n\n");
		}
		verbo_cap[longitud-2]='\0';
		conj_modelo_adquirir(archivo, verbo_cap);		
	}else if((strcmp(verbo_cap,"podrir")==0)||(strcmp(verbo_cap,"repodrir")==0)){
  		if(strcmp(verbo_cap,"podrir")==0){
  			fprintf(archivo, "Verbo\tPodrir\n");
  			fprintf(archivo, "\nDefinici�n. Hacer que una materia org�nica se altere y descomponga.\n\n");
  		}
		if(strcmp(verbo_cap,"repodrir")==0){
			fprintf(archivo, "Verbo\tRepodrir\n");
  			fprintf(archivo, "\nDefinici�n. Pudrir mucho.\n\n");	
		}
		verbo_cap[longitud-2]='\0';
		conj_modelo_podrir(archivo, verbo_cap);	
	}else if((strcmp(verbo_cap,"jugar")==0)){
  		fprintf(archivo, "Verbo\tJugar\n");
  		fprintf(archivo, "\nDefinici�n. Hacer algo con alegr�a con el fin de entretenerse, divertirse o desarrollar determinadas capacidades.\n\n");
		verbo_cap[longitud-2]='\0';
  		conj_modelo_jugar(archivo, verbo_cap);	
	}else if((strcmp(verbo_cap,"hacer")==0)||(strcmp(verbo_cap,"rehacer")==0) || (strcmp(verbo_cap,"desfacer")==0)||(strcmp(verbo_cap,"grandifacer")==0)||(strcmp(verbo_cap,"jacer")==0)||(strcmp(verbo_cap,"contrahacer")==0)||(strcmp(verbo_cap,"satisfacer")==0)||(strcmp(verbo_cap,"licuefacer")==0)||(strcmp(verbo_cap,"liquefacer")==0)||(strcmp(verbo_cap,"refacer")==0)||(strcmp(verbo_cap,"desahacer")==0)||(strcmp(verbo_cap,"contrafacer")==0)||(strcmp(verbo_cap,"deshacer")==0)||(strcmp(verbo_cap,"rarefacer")==0)||(strcmp(verbo_cap,"tumefacer")==0)||(strcmp(verbo_cap,"bienfacer")==0)||(strcmp(verbo_cap,"malfacer")==0)||(strcmp(verbo_cap,"afacer")==0)){
  		if(strcmp(verbo_cap,"hacer")==0){
  			fprintf(archivo,"Verbo\tHacer\n");
  			fprintf(archivo,"\nDefinici�n. Fabricar, formar algo d�ndole la forma, norma y trazo que debe tener.\n\n");
		}
		if(strcmp(verbo_cap,"rehacer")==0){
  			fprintf(archivo,"Verbo\tRehacer\n");
  			fprintf(archivo,"\nDefinici�n. Volver a hacer lo que se hab�a deshecho, o hecho mal.\n\n");
		}
		if(strcmp(verbo_cap,"desfacer")==0){
  			fprintf(archivo,"Verbo\tDesfacer\n");
  			fprintf(archivo,"\nDefinici�n. Deshacer.\n\n");
		}
		if(strcmp(verbo_cap,"grandifacer")==0){
  			fprintf(archivo,"Verbo\tGrandifacer\n");
  			fprintf(archivo,"\nDefinici�n. Engrandecer o hacer grande.\n\n");
		}
		if(strcmp(verbo_cap,"jacer")==0){
  			fprintf(archivo,"Verbo\tJacer\n");
  			fprintf(archivo,"\nDefinici�n. Tirar.\n\n");
		}
		if(strcmp(verbo_cap,"contrahacer")==0){
  			fprintf(archivo,"Verbo\tContrahacer\n");
  			fprintf(archivo,"\nDefinici�n. Hacer una copia de una cosa, tan parecida a esta que apenas se distingan una de otra.\n\n");
		}
		if(strcmp(verbo_cap,"satisfacer")==0){
  			fprintf(archivo,"Verbo\tSatisfacer\n");
  			fprintf(archivo,"\nDefinici�n. Cumplir, llenar ciertos requisitos o exigencias.\n\n");
		}
		if(strcmp(verbo_cap,"licuefacer")==0){
  			fprintf(archivo,"Verbo\tLicuefacer\n");
  			fprintf(archivo,"\nDefinici�n. Licuar.\n\n");
		}
		if(strcmp(verbo_cap,"liquefacer")==0){
  			fprintf(archivo,"Verbo\tLiquefacer\n");
		}
		if(strcmp(verbo_cap,"refacer")==0){
  			fprintf(archivo,"Verbo\tRefacer\n");
  			fprintf(archivo,"\nDefinici�n. Indemnizar, resarcir, subsanar, reintegrar, reedificar.\n\n");
		}
		if(strcmp(verbo_cap,"desahacer")==0){
  			fprintf(archivo,"Verbo\tDesahacer\n");
  			fprintf(archivo,"\nDefinici�n. \n\n");
		}
		if(strcmp(verbo_cap,"contrafacer")==0){
  			fprintf(archivo,"Verbo\tContrafacer\n");
  			fprintf(archivo,"\nDefinici�n. Contrahacer.\n\n");
		}
		if(strcmp(verbo_cap,"deshacer")==0){
  			fprintf(archivo,"Verbo\tDeshacer\n");
  			fprintf(archivo,"\nDefinici�n. Quitar la forma a algo, descomponi�ndolo.\n\n");
		}
		if(strcmp(verbo_cap,"rarefacer")==0){
  			fprintf(archivo,"Verbo\tRarefacer\n");
  			fprintf(archivo,"\nDefinici�n. Hacer menos denso un cuerpo gaseoso.\n\n");
		}
		if(strcmp(verbo_cap,"tumefacer")==0){
  			fprintf(archivo,"Verbo\tTumefacer\n");
  			fprintf(archivo,"\nDefinici�n. Causar, provocar y originar un abultamiento, hinchaz�n o una inflamaci�n del cuerpo, incluyendo el quiste, tumor o carcinoma.\n\n");
		}
		if(strcmp(verbo_cap,"bienfacer")==0){
  			fprintf(archivo,"Verbo\tBienfacer\n");
  			fprintf(archivo,"\nDefinici�n. Beneficio.\n\n");
		}
		if(strcmp(verbo_cap,"malfacer")==0){
  			fprintf(archivo,"Verbo\tMalfacer\n");
  			fprintf(archivo,"\nDefinici�n. Obrar mal.\n\n");
		}
		if(strcmp(verbo_cap,"afacer")==0){
  			fprintf(archivo,"Verbo\tAfacer\n");
  			fprintf(archivo,"\nDefinici�n. Acostumbrarse, hacerse a algo.\n\n");
		}
  		verbo_cap[longitud-2]='\0';
  		conj_modelo_hacer(archivo, verbo_cap);
	}else{
		///CASO VERBO REGULAR
		fprintf(archivo,"Verbo\t%s\n\n",verbo_cap);
     	letra=verbo_cap[longitud-2];
  		verbo_cap[longitud-2]= '\0';
  		if(letra=='a'){
  			regular_AR(archivo,verbo_cap);
  		}
  		if(letra=='e'){
  			regular_ER(archivo, verbo_cap);
  		}
  		if(letra=='i'){
  			regular_IR(archivo, verbo_cap);
  		}
	}
	fclose(archivo);
	printf("Conjugacion finalizada exitosamente\n\n");
	system("PAUSE");
	return 0;
}          

void regular_AR(FILE *archivo, char root[]){                                                                               
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space,i,j, space2;           
	char formato[1024];
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0; tiempo<=4; tiempo++){
  		titulo=strlen(indicativo_simple[tiempo])/2;
	    centrado=(longitud+pronol+ld+1)/2;
	    if (centrado<=titulo){
	    	centrado=0;	
		}else {
			centrado -= titulo;
		}         
		sprintf(formato,"%%%ds%%s%%%ds",centrado, centrado+2);
	    fprintf(archivo,formato, " ",indicativo_simple[tiempo]," ");
	    
	}
	fprintf(archivo,"\n\n");
	for(persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) {
			fprintf(archivo, "%8s %s%s", Pronombres[persona], root, termina_simple_AR[tiempo]);	
		}
	  	fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo){
		centrado=0;	
	}else{
		centrado -= titulo;
	}
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]);    
	}
	fprintf(archivo,"\n\n");
	for(persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) {
			fprintf(archivo, "%9s%s %sado ", Pronombres[persona],compuesto[tiempo], root);
		}
		fprintf(archivo, "\n");
   	}
   	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo){
	    	centrado=0;	
		} else {
			centrado -= titulo;	
		}         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) {
			fprintf(archivo, "%8s %s%s", Pronombres[persona],root, termina_sub_AR[tiempo]);
		} 
        fprintf(archivo, "\n");
	}
	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo){
		centrado=0;	
	}else {
  		centrado -= titulo;	
	}
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
		titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]);    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) {
			fprintf(archivo, "%9s%s %sado ", Pronombres[persona],compuestosub[tiempo], root); 
		}    
		fprintf(archivo, "\n");
   }
	
   	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sado", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%sando", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%sa!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%sen!\n", root);
	return;  
}            

void regular_ER(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space,i,j, space2;           
	char formato[1024];
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo){
	    	centrado=0;
		} else {
			centrado -= titulo;	
		}
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root, termina_simple_ER[tiempo]); 
		fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo;
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]);    
	}
	fprintf(archivo,"\n\n");
	for(persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona], 
    	compuesto[tiempo], root);         
		fprintf(archivo, "\n");
	} 
	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root, termina_sub_ER[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo;
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]);    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuestosub[tiempo], root);
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%siendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%se!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%san!\n", root);
	return;
}

void regular_IR(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space,i,j, space2;           
	char formato[1024];
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root, termina_simple_IR[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
  	else centrado -= titulo;
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]);    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona], compuesto[tiempo], root);         
		fprintf(archivo, "\n");
	} 
	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root, termina_sub_ER[tiempo]); 
		fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo; 
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]);    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
			fprintf(archivo, "%9s%s %sido ", Pronombres[persona], compuestosub[tiempo], root);
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%siendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%se!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%san!\n", root);
	return;
}

void conj_modelo_sentir(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space=12,i,j, space2;           
	char formato[1024];   
	char sub[strlen(root)];
	if(root[strlen(root)-1]=='r'){
  		root[strlen(root)-2]='\0'; 
  		longitud = strlen(root)+2;
	}else{
		longitud = strlen(root)+2;
	}
  	strcpy(sub,root);                                                    
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	root[(strlen(root)-3)]='\0';
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6){
			fprintf(archivo, "%8s %s%s", Pronombres[persona],root, tiempo_simple_sentir[tiempo]);	 
		}
   		fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo;
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuesto[tiempo], sub);         
		fprintf(archivo, "\n");
	}
    fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona],root, tiempo_sub_sentir[tiempo]); 
		fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo;
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto_sub[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuestosub[tiempo], sub);         
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sentido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%sintiendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%siente!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%sientan!\n", root);
	return;	
}

void conj_modelo_erguir(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space=12,i,j, space2;           
	char formato[1024];
	char sub[3]={'i','r','g'};
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s", Pronombres[persona], tiempo_simple_erguir[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
  	if (centrado<=titulo) centrado=0;
  	else centrado -= titulo; 
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuesto[tiempo], root);         
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona],sub, tiempo_sub_erguir[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo; 
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto_sub[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona], compuestosub[tiempo], root);         
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%siendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%se!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%san!\n", root);
	return;
}

void conj_modelo_dormir(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space=12,i,j, space2;           
	char formato[1024]; 
	char sub[strlen(root)];
	longitud = strlen(root)+2;
	strcpy(sub,root); 
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	root[(strlen(root)-3)]='\0';
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) {	
			fprintf(archivo, "%8s %s%s", Pronombres[persona], root, tiempo_simple_dormir[tiempo]);
		}
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo;
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for(persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuesto[tiempo], sub);         
		fprintf(archivo, "\n");
	}
    fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona],root, tiempo_sub_dormir[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
  	if (centrado<=titulo) centrado=0;
  	else centrado -= titulo; 
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto_sub[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuestosub[tiempo], sub);         
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sormido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%surmiendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%suerme!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%suerman!\n", root);
	return;
	
}

void conj_modelo_adquirir(FILE *archivo, char root[]){
	int pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space=12,i,j, space2;           
	char formato[1024]; 
	char sub[strlen(root)];
	longitud = strlen(root)+2;
	strcpy(sub,root);  
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	root[(strlen(root)-1)]='\0';
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root, tiempo_simple_adquirir[tiempo]); 
        fprintf(archivo, "\n");
   	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo; 
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuesto[tiempo], sub);         
		fprintf(archivo, "\n");
	}
    fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona],root,tiempo_sub_adquirir[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	centrado = (longitud+pronol+ld+1)/2;
	if (centrado<=titulo) centrado=0;
	else centrado -= titulo;
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto_sub[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]," ");    
   	}
	fprintf(archivo,"\n\n");
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuestosub[tiempo], sub);         
		fprintf(archivo, "\n");
   	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%srido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%sriendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%sere!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%seran!\n", root);
	return;
}

void conj_modelo_podrir(FILE *archivo, char root[]){
	int  pronol=8, ld=5,tiempo, longitud, persona, centrado, titulo, space,i,j, space2;           
	char formato[1024]; 
	char sub[strlen(root)];
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	strcpy(sub,root);
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
   	}
	fprintf(archivo,"\n\n");
	root[strlen(root)-3]='\0';
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6){
			  fprintf(archivo, "%8s %s%s", Pronombres[persona], root, tiempo_simple_podrir[tiempo]);
		}	 
        fprintf(archivo, "\n");
   	}
	fprintf(archivo, "\n");
 	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
 	centrado = (longitud+pronol+ld+1)/2;
  	if (centrado<=titulo) centrado=0;
  	else centrado -= titulo;
	for(tiempo=0;tiempo<=4;tiempo++){
		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]);    
	}
	fprintf(archivo,"\n\n");
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona], compuesto[tiempo], sub);         
		fprintf(archivo, "\n");
   	}
   	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
  	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
   	}
	fprintf(archivo,"\n\n");
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s %s%s", Pronombres[persona], root,tiempo_sub_podrir[tiempo]);
        fprintf(archivo, "\n");
  	}
	fprintf(archivo, "\n");
 	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
 	centrado = (longitud+pronol+ld+1)/2;
  	if (centrado<=titulo) centrado=0;
  	else centrado -= titulo; 
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(tiempo_compuesto[tiempo])/2;
	    titulo+=6;
  		sprintf(formato, "%%%ds%%s", titulo);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]);    
	}
	fprintf(archivo,"\n\n");
  	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sido ", Pronombres[persona],compuestosub[tiempo], sub);         
		fprintf(archivo, "\n");
	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sodrido", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%sudriendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%sudre!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%sudran!\n", root);
	return;
}

void conj_modelo_jugar(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space=12;           
	char formato[1024];  
	char sub[strlen(root)];
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	strcpy(sub,root);
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	root[strlen(root)-1]='\0';
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root,tiempo_simple_jugar[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sado ", Pronombres[persona],compuesto[tiempo], sub);
		fprintf(archivo, "\n");
	}
    fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6){
    			fprintf(archivo, "%8s %s%s", Pronombres[persona],root,tiempo_sub_jugar[tiempo]);
		}
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n"); 
	for(tiempo=0;tiempo<=2;tiempo++){
	    titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %sado ", Pronombres[persona],compuestosub[tiempo], sub);         
		fprintf(archivo, "\n");
   	}
	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%sando", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%sgando", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%sega!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%seguen!\n", root);
	return;
}

void conj_modelo_hacer(FILE *archivo, char root[]){
	int  pronol=8, ld=4,tiempo, longitud, persona, centrado, titulo, space=11;           
	char formato[1024];  
	char sub[strlen(root)];
	longitud = strlen(root)+2;
	fprintf(archivo,"Modo indicativo, tiempo simple\n\n");
	strcpy(sub,root);
	for(tiempo=0;tiempo<=4;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	root[strlen(root)-2]='\0';
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%8s %s%s", Pronombres[persona], root,tiempo_simple_hacer[tiempo]); 
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo indicativo, tiempo compuesto\n\n");
	for(tiempo=0;tiempo<=4;tiempo++){
		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto[tiempo]," ");    
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<5*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %secho ", Pronombres[persona],compuesto[tiempo], root);         
		fprintf(archivo, "\n");
	} 
   	fprintf(archivo,"\n");
	fprintf(archivo,"Modo subjuntivo, tiempo simple\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
  		titulo = strlen(indicativo_simple[tiempo])/2;
	    centrado = (longitud+pronol+ld+1)/2;
	    if (centrado<=titulo) centrado=0;
  		else centrado -= titulo;         
		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
	    fprintf(archivo, formato, " ", indicativo_simple[tiempo]," ");
	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6){
    		fprintf(archivo, "%8s %s%s", Pronombres[persona],root,tiempo_sub_hacer[tiempo]);
		}
        fprintf(archivo, "\n");
	}
	fprintf(archivo, "\n");
	fprintf(archivo,"Modo subjuntivo, tiempo compuesto\n\n");
	for(tiempo=0;tiempo<=2;tiempo++){
		titulo = strlen(tiempo_compuesto[tiempo])/2;
		centrado = (longitud+pronol+space+1)/2;
		if (centrado<=titulo) centrado=0;
  		else centrado-= titulo;
  		sprintf(formato, "%%%ds%%s%%%ds", centrado, centrado+2);
 		fprintf(archivo, formato, " ", tiempo_compuesto_sub[tiempo]," ");    
   	}
	fprintf(archivo,"\n\n");
	for (persona=0; persona<total_pronombres; persona++){
		for(tiempo=persona;tiempo<3*total_pronombres;tiempo+=6) 
	  		fprintf(archivo, "%9s%s %secho ", Pronombres[persona],compuestosub[tiempo], root);         
		fprintf(archivo, "\n");
	}
   	fprintf(archivo,"\nModo participio\n\n");
	fprintf(archivo, "%secho", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo gerundio\n\n");
	fprintf(archivo, "%saciendo", root);
	fprintf(archivo, "\n");
	fprintf(archivo,"\nModo imperativo\n\n");
	fprintf(archivo, "%s, ", Pronombres[1]);
	fprintf(archivo, "�%saz!\n", root);
	fprintf(archivo, "%s, ", Pronombres[4]);
	fprintf(archivo, "�%sagan!\n", root);
	return;
}
