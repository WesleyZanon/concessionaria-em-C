/*
Wesley Davi Zanon Novaes RA: 190545
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct data      { 
int dia;  
int mes;  
int ano;  
}; 
 
struct historicoVendas     { 
     int reghist; 
     int regcarro; 
     char modelo[20]; 
     
char cor[10]; 
float valor;  
int regloja; 
char nome[30]; 
char cnpj[19]; 
struct data dataVenda;
};

typedef struct endereco{
	char logradouro[80];
	char bairro[15];
	char CEP[10];
	char cidade[15];
	char estado[3];
	char fone[12];
	char email[40];
	
}endereco;

struct infocarro { 
	char sigla; 
	int regcarro; 
}; 
 
 
union dadoscarro { 
	char sigla; 
	struct infocarro reservado; 
}; 
 
 
typedef struct loja { 
	int regloja; //gerar autom�tico 
	char nome[30]; 
	char CNPJ[19]; 
	endereco end;
	int sold; 
	int reserved; 
	union  dadoscarro  tabela[3]; 
}loja; 

struct infoloja { 
	char sigla; 
	char CNPJ[19]; 
}; 
 
union dadosloja { 
	char sigla; 
	struct infoloja reserva; 
}; 
 
typedef struct montadora    { 
	int regcarro; //gerar autom�tico 
	char modelo[20]; 
	char cor[10]; 
	float  valor; 
	union dadosloja status; 
}montadora; 

void menu();
void alocaLoja(loja **p,int tam);
void alocaMont(montadora **p,int tam);
void cadastrar(loja *p, montadora *pe);
void gravaLoja(loja *p,char *str,int pos);
void gravaMont(montadora *p,char *str,int pos);
int  verificaLoja();
int  verificaMont();
void mostraLoja(loja *p);
void mostraCarro(montadora *p);
int buscaLoja(loja *p,char num_reg[19]);
int buscaMont(montadora *p,char status);
int buscaMontMod(montadora *p,char modelo[20]);
void reservaCarro(loja *p, montadora *pe, struct historicoVendas *pr);
void venda(loja *p, montadora *pe, struct historicoVendas *pr);
void deletaCar(montadora *p);
void historico(struct historicoVendas *p);
void gravaHist(struct historicoVendas *pr,char *str,int pos);
int  verifica();

int main()
{
	int op;
	loja *ploja = NULL;
	montadora *pmont = NULL;
	struct historicoVendas *pr= NULL;
	
	
	alocaLoja(&ploja,5);
	alocaMont(&pmont,40);

	do
	{
	system("cls");
	
	menu();
    scanf("%i", &op);

    switch(op)
	{
		case 1:
			cadastrar(ploja,pmont);
	
			break;
		case 2:
			printf("\n1 - LOJA\n2 - CARRO\n3 - HISTORICO\n");
			scanf("%i", &op);
			
			if(op == 1)
				mostraLoja(ploja);
			else if(op == 2)
				mostraCarro(pmont);
			else if(op == 3)
				historico(pr);
			else
				printf("OPCAO INVALIDA\nVOLTANDO AO MENU INICIAL\n");
				
			break;
		case 3:
			reservaCarro(ploja,pmont,pr);
			break;
			
		case 4:
			historico(pr);
			break;
			
		case 5:
			break;

		
		default:
		printf("\nOPCAO INVALIDA!\n\n");
	
		break;
		
		}
	system("PAUSE");
	}while(op!=5);
}

void menu()
{
	printf("\n\nMENU\n");
	printf("1 - CADASTRAR\n2 - CONSULTAR\n3 - RESERVAR CARRO\n4 - Gerar Historico\n5 - Sair\n\n");
}


void alocaLoja(loja **p,int tam)
{
if((*p=(loja*)realloc(*p,tam*sizeof(loja)))==NULL)
  exit(1);
}//aloca


void alocaMont(montadora **p,int tam)
{
if((*p=(montadora*)realloc(*p,tam*sizeof(montadora)))==NULL)
  exit(1);
}//aloca


void cadastrar(loja *p, montadora *pe)
{
	int op;

	printf("\n1 - CADASTRAR CONCESSIONARIA\n2 - CADASTRAR CARRO\n");
	scanf("%i", &op);

	if(op==1)
	{
	
	int qreg;

	qreg=verificaLoja();   //numero de registros

	if(qreg<5)
	{
		p->regloja=qreg+1;	

		printf("\nRegistro: %i",p->regloja);

		printf("\nNOME: \n");
		scanf("%s",p->nome);
		fflush(stdin);
	
		printf("\nCNPJ: \n");
		gets(p->CNPJ);
		fflush(stdin);
	
		printf("\n\n\nCADASTRO DE ENDERECO\n\n");
	
		printf("\nCEP:\n");
		gets(p->end.CEP);
		printf("\nESTADO\n");
		gets(p->end.estado);
		printf("\nCIDADE:\n");
		gets(p->end.cidade);
		printf("\nBAIRRO:\n");
		gets(p->end.bairro);
		printf("\nLAGRADOURO\n");
		gets(p->end.logradouro);
	
		printf("\n\n\nCADASTRO DE DADOS PESSOAIS\n\n");
	
		printf("\nTELEFONE\n");
		gets(p->end.fone);
		printf("\nE-MAIL\n");
		gets(p->end.email);
		printf("\n\n");
	

		p->sold = 0;
		
		p->tabela[0].sigla = 'L';
		p->tabela[1].sigla = 'L';
		p->tabela[2].sigla = 'L';
		p->reserved = 0;
		
		printf("\n");
	
		gravaLoja(p,"ab",1);
	
		printf("\n\nCADASTRADO COM SUCESSO\n\n\n");
	
	}
	else
		printf("\n\nFIXA DE CADASTRO LOTADA\n\n\n");
	
	}//cadastro loja


	else
	{
	int qreg;
	char opi;

	qreg=verificaMont();   //numero de registros

	
	if(qreg<40)
	{
		pe->regcarro=qreg+1;	

		printf("\nRegistro: %i",pe->regcarro);

		printf("\nMODELO: \n");
		scanf("%s",pe->modelo);
		fflush(stdin);
	
		printf("\nCOR: \n");
		gets(pe->cor);
		fflush(stdin);
		printf("\nVALOR: \n");
		scanf("%f",&(pe->valor));

		pe->status.sigla = 'L';
	
	gravaMont(pe,"ab",1);

	printf("\n\nCADASTRADO COM SUCESSO\n\n\n");
	
	}
	else
		printf("\n\nFIXA DE CADASTRO LOTADA\n\n\n");
	
	
	}//cadastar carro
	
	system("Pause");
	
}//cadastro

void gravaLoja(loja *p,char *str,int pos)
{
FILE *fptr=NULL;

if((fptr=fopen("concessionaria.bin",str))==NULL)	
  printf("\nErro ao abrir o arquivo");
else
  {
  	if(strcmp(str,"rb+")==0)
  		fseek(fptr,pos*sizeof(loja),0);
  		
  	fwrite(p,sizeof(loja),1,fptr);
  }//else
fclose(fptr);		//fora do ELSE por conta do ab ou rb+
}//grava

void gravaMont(montadora *p,char *str,int pos)
{
FILE *fptr=NULL;

if((fptr=fopen("carro.bin",str))==NULL)	
  printf("\nErro ao abrir o arquivo");
else
  {
  	if(strcmp(str,"rb+")==0)
  	  fseek(fptr,pos*sizeof(montadora),0);
  	fwrite(p,sizeof(montadora),1,fptr);
  }//else
fclose(fptr);		//fora do ELSE por conta do ab ou rb+
}//grava


int  verificaLoja()
{
	long int cont=0;
	FILE *fptr=NULL;
	
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  		return cont;
  		
	else
  	{
  		fseek(fptr,0,2);  //posiciona no fim do arquivo
  		cont=ftell(fptr)/sizeof(loja);   //qtde de elementos
  		fclose(fptr);    //dentro do ELSE por conta do rb
  		return cont;
  	}//else
}//verifica loja

int verificaMont()
{
	long int cont=0;
	FILE *fptr=NULL;
	
	if((fptr=fopen("carro.bin","rb"))==NULL)
  		return cont;
  		
	else
  	{
		fseek(fptr,0,2);  //posiciona no fim do arquivo
  		cont=ftell(fptr)/sizeof(montadora);   //qtde de elementos
  		fclose(fptr);    //dentro do ELSE por conta do rb
  		return cont;
  }//else
}//verifica loja


void mostraLoja(loja *p)
{
	
int pos = -1,qreg;
char cnpj[19];


FILE *fptr=NULL;
qreg=verificaLoja();   //qtde de registros
system("cls");
if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  //for(i=0;i<qreg;i++)
    //{
    fflush(stdin);
    printf("\nDigite o cnpj que Deseja Buscar: \n");
    gets(cnpj);
    fflush(stdin);
    
    pos = buscaLoja(p,cnpj);
    
    //printf("\n\nValor de POS = %i\n",pos);
    
    if(pos==-1)
    	printf("CNPJ Nao encontrado!\nVoltando para o menu inicial!\n");
    
    else
    {
		fseek(fptr,pos*sizeof(loja),0);
		fread(p,sizeof(loja),1,fptr);
		printf("\nNome: %s\nCNPJ: %s\nQtde Vendidos: %i\nQuantidade de carros reservados: %i\nTabela 0: %c\nTabela 1: %c\nTabela 2: %c\n\n",p->nome,p->CNPJ,p->sold,p->reserved,p->tabela[0],p->tabela[1],p->tabela[2]);
}
   
    //}//for
  fclose(fptr);
  }//else
system("pause");
}//mostra


void mostraCarro(montadora *p)
{
	
int pos = -1,qreg,i;
char status, modelo[20];


FILE *fptr=NULL;
qreg=verificaMont();   //qtde de registros
system("cls");
if((fptr=fopen("carro.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {

    fflush(stdin);
    printf("\nDIGITE: 'R' PARA BUSCAR CARROS RESERVADOS\nDIGITE 'L' PARA PESQUISAR CARROS LIVRES\nDIGITE MAIUSCULO\n");
    scanf("%c",&status);
    fflush(stdin);
    
    for(i=0;i<qreg;i++)
    {
    	
	fseek(fptr,i*sizeof(montadora),0);
	fread(p,sizeof(montadora),1,fptr);
	
	printf("\REgCar: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: %c\n\n",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
    }//for
    
    
    //printf("\n\n saiu do for \n\n");
    //system("pause");
    
}
fclose(fptr);
printf("\n\n");
system("pause");
}//mostra








int buscaLoja(loja *p,char num_reg[19])
{
FILE *fptr=NULL;
int qreg,achou=-1,i,comp;
qreg=verificaLoja();
system("cls");
//printf("\nNum_reg: %s\n",num_reg);
//printf("\nCNPJ: %s\n",p->CNPJ);
//system("pause");
if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  printf("\nErro");
else
  {

  	for(i=0;i<qreg;i++)
  	  {
  	  	fseek(fptr,i*sizeof(loja),0);
  	  	fread(p,sizeof(loja),1,fptr);

  	  	//printf("\n1 CNPJ: %s\n",p->CNPJ);	  	
    	comp = strcmp(p->CNPJ,num_reg);
  	
  	  	if(comp==0)
  	  	  {
  	  	  	//printf("entrou");
  	  	  	//system("pause");
  	  	  	achou=i;
  	  	  	break;  //forca a saida do for
		  }//if
	  }//for
  fclose(fptr);   //DENTRO do else - abriu com rb	  
  }//else
return achou;  //posicao do registro
}//busca


int buscaMont(montadora *p,char status)
{
FILE *fptr=NULL;
int qreg,achou=-1,i;
qreg=verificaMont();

system("cls");



if((fptr=fopen("carro.bin","rb"))==NULL)
  printf("\nErro");
else
  {

  	for(i=0;i<qreg;i++)
  	  {
  	  	fseek(fptr,i*sizeof(montadora),0);
  	  	fread(p,sizeof(montadora),1,fptr);

//printf("\nstatus: %c\n",status);
//printf("\nSTATUS: %c\n",p->status.sigla);
//system("pause");
  	
  	  	if(p->status.sigla==status)
  	  	  {
  	  	  	//printf("entrou");
  	  	  	//system("pause");
  	  	  	achou=i;
  	  	  	break;  //forca a saida do for
		  }//if
	  }//for
  fclose(fptr);   //DENTRO do else - abriu com rb	  
  }//else
return achou;  //posicao do registro
}//busca

int buscaMontMod(montadora *p,char modelo[20])
{
FILE *fptr=NULL;
int qreg,achou=-1,i,comp;
qreg=verificaMont();

system("cls");

if((fptr=fopen("carro.bin","rb"))==NULL)
  printf("\nErro");
else
  {

  	for(i=0;i<qreg;i++)
  	  {
  	  	fseek(fptr,i*sizeof(montadora),0);
  	  	fread(p,sizeof(montadora),1,fptr);

//printf("\nstatus: %s\n",modelo);
//printf("\nSTATUS: %s\n",p->modelo);
//system("pause");
  	
  		comp = strcmp(p->modelo,modelo);
  	
  	  	if(comp==0)
  	  	  {
  	  	  	//printf("entrou");
  	  	  	//system("pause");
  	  	  	achou=i;
  	  	  	break;  //forca a saida do for
		  }//if
	  }//for
  fclose(fptr);   //DENTRO do else - abriu com rb	  
  }//else
return achou;  //posicao do registro
}//busca

void reservaCarro(loja *p, montadora *pe, struct historicoVendas *pr)
{
	FILE *fptr=NULL;
	FILE *fptrl=NULL;
	system("cls");
	
	char op, cnpj[19];
	int reg, qreg, i, posCar = -1, posLoja = -1;
	
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
		
	else
	{
		fflush(stdin);
		printf("\nDeseja Consultar a Tabela de Carros: (s/n): \n");
		scanf("%c",&op);
		fflush(stdin);
	
		if(op=='s')
			mostraCarro(pe);
	
		qreg=verificaMont();
	
		printf("\nDigite o numero de registro do carro que deseja reservar: ");
		scanf("%i", &reg);
	
		for(i=0;i<qreg;i++)
		{
		
  		  	fseek(fptr,i*sizeof(montadora),0);
  	  		fread(pe,sizeof(montadora),1,fptr);
		
			//printf("\n teste qreg: %i", pe->regcarro);
		
			if(pe->regcarro==reg)
				posCar = i;
		
	}
}

	//printf("\n\n teste posCar: %i\n", posCar);
	
	
		
	fflush(stdin);
	printf("Digite o cnpj da empresa que deseja reservar: ");
	gets(cnpj);
	fflush(stdin);
	
		
	fseek(fptrl,posLoja*sizeof(loja),0);
	fread(p,sizeof(loja),1,fptrl);
		
	posLoja = buscaLoja(p,cnpj);
		
	if(posLoja == -1)
		printf("\nCnpj nao encontrado, voltando para o menu inicial!\n");	
		
	else
	{
		//printf("\n\nposLoja: %i",posLoja);
		//system("pause");
	
  		fseek(fptr,posCar*sizeof(montadora),0);
   		fwrite(pe,sizeof(montadora),1,fptr);
	
		fseek(fptrl,posLoja*sizeof(loja),0);
		fwrite(p,sizeof(loja),1,fptr);
		
		if(p->reserved<3 && pe->status.sigla != 'R')
		{
			pe->status.reserva.sigla = 'R';
			
			//pe->status.reserva.CNPJ = p->CNPJ;
		
			//printf("\nteste P - reserva: %i\n",p->reserved);
		
			p->tabela[p->reserved].reservado.regcarro = pe->regcarro;
			p->tabela[p->reserved].reservado.sigla = 'R';
			p->reserved = (p->reserved)+1;
			
			
			pe->status.reserva.sigla = 'R';

			
			//printf("\nteste P - reserva: %i\n",p->reserved);
			//printf("\nteste P - tabela 00: %c\n",p->tabela[0]);
			//printf("\nteste P - tabela 01: %s\n",p->tabela[1]);
			//printf("\nteste P - tabela 02: %s\n",p->tabela[2]);
			
			printf("\nReservado com sucesso\n");
			
			gravaLoja(p,"r+",1);
			gravaMont(pe,"r+",1);
	}
	else
		printf("\nFicha de reservados lotado ou carro ja reservado\nvoltando para o menu inicial:\n");
	
}
	printf("\nDeseja fazer a venda desse carro: (s/n)\n");
	scanf("%c",&op);

	if(op=='s' || op=='S')
		venda(p,pe,pr);
		deletaCar(pe);
		gravaLoja(p,"r+",1);
		gravaMont(pe,"r+",1);

	fclose(fptr);
	fclose(fptrl); 
	
}

void venda(loja *p, montadora *pe, struct historicoVendas *pr)
{
	int dia,mes,ano;

	
	p->sold = p->sold+1;
	p->reserved = p->reserved-1;
	pe->status.sigla = 'L';
	//p->tabela = pe->status.sigla;
	
	deletaCar(pe);
	
	printf("\nDigite a data da venda\n");
	
	printf("\nDia: ");
	scanf("%i",&dia);

	printf("\nMes: ");
	scanf("%i",&mes);
	
	printf("\nAno: ");
	scanf("%i",&ano);
	
	/* TESTES QUE DERAM ERRO
	
	system("pause");
	pr->dataVenda.ano = ano;
	system("pause");
	pr->dataVenda.mes = mes;
	system("pause");
	pr->dataVenda.mes = dia;

	pr->valor = pe->valor;
	system("pause");
	pr->regcarro = pe->regcarro;
	system("pause");
	pr->regloja = p->regloja;
	system("pause");
	pr->valor = pe->valor;
	system("pause");
	
	
	
	strcpy (pr->cor, pe->cor);
	system("pause");
	strcpy (pr->cnpj, p->CNPJ);
	system("pause");
	strcpy (pr->nome, p->nome);
	system("pause");
	strcpy (pr->modelo, pe->modelo);*/
	
	
	
	printf("\nVendido com Sucesso\n");	
	
	
} 

void deletaCar(montadora *p)
{

	p->regcarro = -1;
	p->valor = -1;


}//delerta

void historico(struct historicoVendas *p)
{
	int i,qreg;
FILE *fptr=NULL;
qreg=verifica();   //qtde de registros
system("cls");
if((fptr=fopen("estoque.bin","rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else
  {
  for(i=0;i<qreg;i++)
    {
	fseek(fptr,i*sizeof(struct historicoVendas),0);
	fread(p,sizeof(struct historicoVendas),1,fptr);
	printf("\nRegHist\tRegCarro\tModelo\tCro\tValor\tRegLoja\tNome\tCNPJ\tDataVenda\n%i\t%i\t%s\t%s\t%.2f\t%i\t%s\t%s\t%i/%i/%i",p->reghist,p->regcarro,p->modelo,p->cor,p->valor,p->regloja,p->nome,p->cnpj,p->dataVenda.dia,p->dataVenda.mes,p->dataVenda.ano);
    }//for
  fclose(fptr);
  }//else
system("pause");
}




void gravaHist(struct historicoVendas *p,char *str,int pos)
{
FILE *fptr=NULL;

if((fptr=fopen("historico.bin",str))==NULL)	
  printf("\nErro ao abrir o arquivo");
else
  {
  	if(strcmp(str,"rb+")==0)
  		fseek(fptr,pos*sizeof(struct historicoVendas),0);
  		
  	fwrite(p,sizeof(struct historicoVendas),1,fptr);
  }//else
fclose(fptr);		//fora do ELSE por conta do ab ou rb+
}//grava

int  verifica()
{
long int cont=0;
FILE *fptr=NULL;
if((fptr=fopen("historico.bin","rb"))==NULL)
  return cont;
else
  {
  fseek(fptr,0,2);  //posiciona no fim do arquivo
  cont=ftell(fptr)/sizeof(struct historicoVendas);   //qtde de elementos
  fclose(fptr);    //dentro do ELSE por conta do rb
  return cont;
  }//else
}//verifica
	
