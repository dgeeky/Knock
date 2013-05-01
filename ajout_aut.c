

/* 
Le langage est structuré au sein d'un fichier sous la forme : {7000x8000x9000 , 4000x6000x8000} 

*/


struct etat
{
  int indice;
	int numero;
	int hauteur;
	bool final;
	bool b; //Pour éviter l'affichage multiple
	struct transition *lien;
};

struct transition
{
	int etiq;
	struct transition *suivant;
	struct etat *but;

};


//Fonction qui: saisit un langage à partir d'un fichier

void saisie_langage(char *path,struct etat *aut)
{	
	FILE *f;
	f=fopen(path,"r");
	if (f==NULL) 
		perror ("Error opening file");
	else
	{
		char car,retour;
		car=fgetc (f);
		while(car==' ')
			car=fgetc (f);	
		if(car=='{') 
		{
			retour=add_seq(f,aut);
			while(retour==',')
				retour=add_seq(f,aut);
		}
		fclose (f);
	}
}



/*********************************************/

char add_seq(FILE * f,struct etat *aut)
{	
	struct etat *buffer;
	char car,temp;
	buffer=aut;
	car=fgetc (f);
	
	while(car==' ')
		car=fgetc (f);
	
	while((car!=',') && (car!='}'))
	{
		temp=car;
		car=fgetc (f);
		
		while(car==' ')
			car=fgetc (f);
		
		if(car!=',' && car!='}')
			buffer=add_port(filter_port(f , tmp),buffer, 0);
		else
			buffer=add_port(filter_port(f , tmp),buffer, 1);
				
	}
	return car;
}
/****************************************************/

int filter_port(FILE *f , char c)
{
    int i = 0;

    while(isdigit(c))
    {

        i = c - '0' + i*10 ;
        c = fgetc(f);
    }

    return i;

}



/**************************************************/

struct etat* add_port(int port, struct etat *courant, bool b)
{
	static int num=0;
	struct etat *pointe;
	struct transition * test;
	struct etat *f;
	pointe=courant;
	
	//L'automate n'est pas vide
	if( pointe->lien!=NULL)
	{
		test=pointe->lien;
		
		//Teste sur les transitions existantes
		
		if(test->etiq == port)
		{
			if (b==1)
			{
				f=test->but;
				f->final=1;
			}
			return test->but;
		}
		while( test->suivant != NULL)
		{
			test= test->suivant;
			
			if( test->etiq == port)
			{
				if (b==1)
				{
					f=test->but;
					f->final=1;
				}
				return test->but;				
			}
		}
	}
	
	//La transition n'existe pas: il faut la créer et l'initialiser
	struct etat *n_etat;
	
	n_etat=(struct etat *)malloc(sizeof(struct etat));
	
	struct transition *n_transition;
	n_transition=(struct transition *)malloc(sizeof(struct transition));
	
	n_transition->etiq=port;
	n_transition->suivant=NULL;
	
	n_etat->lien=NULL;
	n_etat->final=0;
	
	num++;
	n_etat->numero=num;
	n_etat->indice=-1; //Valeur par défaut
	n_etat->b=0; //Valeur par défaut pour l'affichage
	
	n_transition->but= n_etat;
	
	if(b==1)	n_etat->final = 1;
	
	//L'automate est vide
	
	if( pointe->lien == NULL )
	{
		pointe->lien= n_transition;
		return n_etat;	
	}
	//L'automate n'est pas vide
	test->suivant=n_transition;
	return n_etat;
}
