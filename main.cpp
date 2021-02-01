#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include <chrono>
#include<ctime>
#include <string>

using namespace std;
using namespace std::chrono;

typedef struct
{
    int dia;
    int mes;
    int ano;
} Date;

typedef struct
{
    Date dataDeConfirmacao;
    string estado;
    string cidade;
    float codigoDaCidade;
    int numDeCasos;
    int numDeObitos;
} Covid19;

void ImportaArquivos (int n, bool aleatorio, Covid19* buffer)
{
    fstream arquivo;
    arquivo.open ("brazil_covid19_cities.csv");

    if(aleatorio == 1)
    {
        if(arquivo.is_open())
        {
            string sout;
            arquivo.seekg(0,ios::end); //leva o ponteiro para o fim do arquivo
            int tamanho = arquivo.tellg(); //mostra a qtdade de bytes de onde esta o ponteiro no arquivo

            for(int i=0; i<n; i++)
            {
                int blind = rand() %tamanho;
                arquivo.seekg(blind,ios::beg);
                arquivo.ignore(1000,'\n'); //leva o ponteiro ate o final da linha
                getline(arquivo,sout);// getline(arquivo,sout);
                stringstream s(sout); //stringstream reconhece a string como se fosse um arquivo - fluxo continuo de dados
                getline(s, sout,'-');
                buffer[i].dataDeConfirmacao.ano = atoi (sout.c_str());
                getline(s, sout,'-');
                buffer[i].dataDeConfirmacao.mes = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].dataDeConfirmacao.dia = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].estado = sout;
                getline(s, sout,',');
                buffer[i].cidade = sout;
                getline(s, sout,',');
                buffer[i].codigoDaCidade = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].numDeCasos = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].numDeObitos = atoi (sout.c_str());
            }
            arquivo.close();
        }

        else
            cerr<<"Erro ao abrir arquivo de dados!"<<endl<<endl;
    }
    else
    {
        if(arquivo.is_open())
        {
            string sout;
            getline(arquivo,sout);//o primeiro a gente ignora pq eh o cabecario
            for(int i=0; i<n; i++)
            {
                getline(arquivo,sout);// getline(arquivo,sout);
                stringstream s(sout); //stringstream reconhece a string como se fosse um arquivo - fluxo continuo de dados
                getline(s, sout,'-');
                buffer[i].dataDeConfirmacao.ano = atoi (sout.c_str());
                getline(s, sout,'-');
                buffer[i].dataDeConfirmacao.mes = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].dataDeConfirmacao.dia = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].estado = sout;
                getline(s, sout,',');
                buffer[i].cidade = sout;
                getline(s, sout,',');
                buffer[i].codigoDaCidade = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].numDeCasos = atoi (sout.c_str());
                getline(s, sout,',');
                buffer[i].numDeObitos = atoi (sout.c_str());

            }
            arquivo.close();


        }

        else
            cerr<<"Erro ao abrir arquivo de dados!"<<endl;

    }
}

void PrintArquivo(int n,Covid19* buffer)
{
    cout<<"PADRAO: sigla_do_estado,nome_da_cidade,codigo_da_cidade,data_de_confirmacao,numero_de_casos,numero_de_obitos"<<endl<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<buffer[i].estado<<","<<buffer[i].cidade<<","<<buffer[i].codigoDaCidade<<",";
        cout<<buffer[i].dataDeConfirmacao.dia<<"-"<<buffer[i].dataDeConfirmacao.mes<<"-"<<buffer[i].dataDeConfirmacao.ano<<",";
        cout<<buffer[i].numDeCasos<<","<<buffer[i].numDeObitos<<endl;
    }
    cout<<endl<<endl;
}

void EscreveDadosEmArquivo(int n, Covid19* buffer)
{
    ofstream saida;
    saida.open("brazil_covid_cities_processado.csv",ios::app);
    if(saida.is_open())
    {
        saida<<"sigla_do_estado,nome_da_cidade,codigo_da_cidade,data_de_confirmacao,numero_de_casos,numero_de_obitos"<<endl;
        for(int i=0; i<n; i++)
        {
            saida<<buffer[i].estado<<","<<buffer[i].cidade<<","<<buffer[i].codigoDaCidade<<",";
            saida<<buffer[i].dataDeConfirmacao.dia<<"-"<<buffer[i].dataDeConfirmacao.mes<<"-"<<buffer[i].dataDeConfirmacao.ano<<",";
            saida<<buffer[i].numDeCasos<<","<<buffer[i].numDeObitos<<endl;
        }
        saida.close();

    }
    else
        cerr<<"Erro ao abrir arquivo de saida para escrita!"<<endl<<endl;
}

void comb_sort11(Covid19 vet[], int tam, double* compara, double* movimenta)
{
    int gap;
    Covid19 aux;
    bool troca = true;
    gap = tam;
    while (gap > 1 || troca == true)
    {
        gap = gap * 10 / 13;
        if (gap == 9 || gap == 10) gap = 11;
        if (gap < 1) gap = 1;
        troca = false;
        for (int i = 0, j = gap; j < tam; i++, j++)
        {
            *compara = *compara +1;
            if (vet[i].numDeCasos > vet[j].numDeCasos)
            {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
                troca = true;
                *movimenta = *movimenta +1;
            }
        }
    }
}


void quick_sort(Covid19 vet[], int inicio, int fim, double* compara, double*movimenta)
{
    Covid19 aux;
    int i = inicio; //direita
    int j = fim;  //esquerda
    Covid19 pivo = vet[(inicio + fim) / 2];
    *movimenta = *movimenta +1;
    while(i <= j)
    {
        *compara = *compara+1;
        while(vet[i].numDeCasos<pivo.numDeCasos && i < fim)
        {
            i++;
            *compara=*compara+1;
        }
        *compara=*compara+1;
        while(vet[j].numDeCasos>pivo.numDeCasos && j > inicio)
        {
            j--;
            *compara=*compara+1;
        }
        if(i <= j)
        {
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
            *movimenta=*movimenta+1;
        }
    }
    if(j > inicio)
        quick_sort(vet, inicio, j,compara,movimenta);
    if(i < fim)
        quick_sort(vet, i, fim, compara, movimenta);
}


void constroiHeap( Covid19 vet[], int tam, int indice_raiz)
{
    int ramificacao;
    Covid19 valor;
    valor = vet[ indice_raiz ];

    while( indice_raiz < tam/2 )
    {
        ramificacao = 2 * indice_raiz + 1;

        if((ramificacao < tam-1) &&
            ((vet[ramificacao].estado<vet[ramificacao +1].estado) ||
            ((vet[ramificacao].estado==vet[ramificacao +1].estado) &&
            (vet[ramificacao].cidade<vet[ramificacao +1].cidade)) ||
            ((vet[ramificacao].estado==vet[ramificacao +1].estado) &&
            (vet[ramificacao].cidade==vet[ramificacao +1].cidade) &&
            (vet[ramificacao].dataDeConfirmacao.ano<vet[ramificacao +1].dataDeConfirmacao.ano)) ||
            ((vet[ramificacao].estado==vet[ramificacao +1].estado) &&
            (vet[ramificacao].cidade==vet[ramificacao +1].cidade) &&
            (vet[ramificacao].dataDeConfirmacao.ano==vet[ramificacao +1].dataDeConfirmacao.ano) &&
            (vet[ramificacao].dataDeConfirmacao.mes<vet[ramificacao +1].dataDeConfirmacao.mes)) ||
            ((vet[ramificacao].estado==vet[ramificacao +1].estado) &&
            (vet[ramificacao].cidade==vet[ramificacao +1].cidade) &&
            (vet[ramificacao].dataDeConfirmacao.ano==vet[ramificacao +1].dataDeConfirmacao.ano) &&
            (vet[ramificacao].dataDeConfirmacao.mes==vet[ramificacao +1].dataDeConfirmacao.mes) &&
            (vet[ramificacao].dataDeConfirmacao.dia<vet[ramificacao +1].dataDeConfirmacao.dia))))

                ramificacao++;

        if( ((valor.estado>vet[ramificacao].estado) ||
            ((valor.estado==vet[ramificacao].estado) &&
            (valor.cidade>vet[ramificacao].cidade)) ||
            ((valor.estado==vet[ramificacao].estado) &&
            (valor.cidade==vet[ramificacao].cidade) &&
            (valor.dataDeConfirmacao.ano>vet[ramificacao].dataDeConfirmacao.ano)) ||
            ((valor.estado==vet[ramificacao].estado) &&
            (valor.cidade==vet[ramificacao].cidade) &&
            (valor.dataDeConfirmacao.ano==vet[ramificacao].dataDeConfirmacao.ano) &&
            (valor.dataDeConfirmacao.mes>vet[ramificacao].dataDeConfirmacao.mes)) ||
            ((valor.estado==vet[ramificacao].estado) && (valor.cidade==vet[ramificacao].cidade) &&
            (valor.dataDeConfirmacao.ano==vet[ramificacao].dataDeConfirmacao.ano) &&
            (valor.dataDeConfirmacao.mes==vet[ramificacao].dataDeConfirmacao.mes) &&
            (valor.dataDeConfirmacao.dia>vet[ramificacao].dataDeConfirmacao.dia))) )//Identifica o max-heap

                break;

        vet[ indice_raiz ] = vet[ ramificacao ];
        indice_raiz = ramificacao;
    }
    vet[ indice_raiz ] = valor;
}

void HeapSort( Covid19 vet[], int tam )
{
    int indice;
    Covid19 aux;
    for( indice = tam/2; indice >= 0; indice-- )
        constroiHeap( vet, tam, indice );

    while( tam > 0 )
    {
        aux = vet[ 0 ];
        vet[ 0 ] = vet[ tam-1 ];
        vet[ tam-1 ] = aux;
        constroiHeap( vet, --tam, 0 );
    }
}


void Recalcula_CasosAcumuladosPARACasosDiarios (Covid19 vet[], int tam)
{
    int i=0;
    int j=1;
    while(i!=tam)
    {
        if(vet[i].estado==vet[j].estado && vet[i].cidade==vet[j].cidade)
        {
            int aux = vet[j].numDeCasos - vet[i].numDeCasos;
            vet[j].numDeCasos=aux;
        }
        i++;
        j++;
    }

}

void constroiHeap_ETAPA2( Covid19 vet[], int tam, int indice_raiz, double*compara, double*movimenta )
{
    int ramificacao;
    Covid19 valor;
    valor = vet[ indice_raiz ];
    *movimenta=*movimenta+1;

    while( indice_raiz < tam/2 )
    {
        ramificacao = 2 * indice_raiz + 1;

        *compara=*compara+1;
        if( ramificacao < tam-1 && vet[ ramificacao ].numDeCasos < vet[ ramificacao + 1 ].numDeCasos )
            ramificacao++;

        *compara=*compara+1;
        if( valor.numDeCasos >= vet[ ramificacao ].numDeCasos )//Identifica o max-heap
            break;

        vet[ indice_raiz ] = vet[ ramificacao ];
        *movimenta=*movimenta+1;
        indice_raiz = ramificacao;
    }
    vet[ indice_raiz ] = valor;
    *movimenta=*movimenta+1;
}

void HeapSort_ETAPA2( Covid19 vet[], int tam, double* compara, double* movimenta )
{
    int indice;
    Covid19 aux;
    for( indice = tam/2; indice >= 0; indice-- )
        constroiHeap_ETAPA2( vet, tam, indice, compara, movimenta );

    while( tam > 0 )
    {
        aux = vet[ 0 ];
        vet[ 0 ] = vet[ tam-1 ];
        vet[ tam-1 ] = aux;
        *movimenta=*movimenta+1;
        constroiHeap_ETAPA2( vet, --tam, 0, compara, movimenta );
    }
}


int main()
{
    time_point<high_resolution_clock>ti,tf;
    srand (time(NULL));
    Covid19* buffer_Covid;
    int num_REGISTROS = 1431490;
    int n [5] = {10000, 50000, 100000, 500000, 1000000};
    int m = 5;
    double numComparacoes=0, numMovimentacoes=0;
    int64_t tempo=0;
    double metrica_Comparacoes[3][m];
    double metrica_Movimentacoes[3][m];
    double metrica_Tempo[3][m];
    ofstream saida;

    int menu;
    cout<< "1o TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS 2 - 2020.3" << endl;
    cout<< "DISCENTE: Maria Meiriele Dias da Silva" << endl;
    cout<< "MATRICULA: 201476009 "<< endl;
    cout<< endl << endl << "MENU"<< endl;
    cout<< "1 - ETAPA 1: PRE-PROCESSAMENTO DE DADOS"<<endl;
    cout<< "2 - ETAPA 2: ANALISE DE ALGORITMOS DE ORDENACAO"<<endl;
    cout<< "3 - MODULO DE TESTE: PRE-PROCESSAMENTO DE DADOS - exibicao dos registros com os totais de casos recalculados"<<endl;
    cout<< "4 - MODULO DE TESTE: IMPORTACAO DE N REGISTROS ALEATORIOS"<<endl;
    cout<< "5 - MODULO DE TESTE: ALGORITMOS DE ORDENACAO: Heap Sort"<<endl;
    cout<< "6 - MODULO DE TESTE: ALGORITMOS DE ORDENACAO: Quick Sort - chave: Numero de casos confirmados"<<endl;
    cout<< "7 - MODULO DE TESTE: ALGORITMOS DE ORDENACAO: Comb Sort - chave: Numero de casos confirmados"<<endl;
    cout<< "SUA ESCOLHA: ";
    cin>>menu;
    cout<<endl<<endl<<endl;

    switch (menu)
    {

    case 1://ETAPA 1 - PRE-PROCESSAMENTO
        buffer_Covid = new Covid19 [num_REGISTROS];
        ImportaArquivos(num_REGISTROS,0,buffer_Covid);
        HeapSort(buffer_Covid,num_REGISTROS);
        Recalcula_CasosAcumuladosPARACasosDiarios(buffer_Covid,num_REGISTROS);
        EscreveDadosEmArquivo(num_REGISTROS,buffer_Covid);
        cout<<"Etapa 1 concluida com sucesso!"<<endl<<endl<<endl;
        break;

    case 2://ETAPA 2 ALGORIMOS DE ORDENACAO-
        buffer_Covid = new Covid19 [num_REGISTROS];
        ImportaArquivos(num_REGISTROS,0,buffer_Covid);
        HeapSort(buffer_Covid,num_REGISTROS);
        Recalcula_CasosAcumuladosPARACasosDiarios(buffer_Covid,num_REGISTROS);
        EscreveDadosEmArquivo(num_REGISTROS,buffer_Covid);

        Covid19* buffer_HeapSort;
        Covid19* buffer_QuickSort;
        Covid19* buffer_CombSort;
        int blind;

        saida.open("saida.txt",ios::app);
        if(saida.is_open())
        {
            saida<< "1o TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS 2 - 2020.3" << endl;
            saida<< "DISCENTE: Maria Meiriele Dias da Silva" << endl;
            saida<< "MATRICULA: 201476009 "<< endl<<endl;
            saida<<"AVALIANDO DIFERENTES METODOS DE ORDENACAO"<<endl<<endl;
        }
        else
            cerr<<"Erro ao abrir arquivo de saida!"<<endl;

        for (int i=0; i<5; i++)
        {
            buffer_HeapSort = new Covid19 [n[i]];
            buffer_QuickSort = new Covid19 [n[i]];
            buffer_CombSort = new Covid19[n[i]];

            for (int j=0; j<m; j++)
            {
                for(int k=0; k<n[i]; k++)
                {
                    blind = rand()%num_REGISTROS;
                    buffer_HeapSort[k]=buffer_Covid[blind];
                    buffer_QuickSort[k]=buffer_Covid[blind];
                    buffer_CombSort[k]=buffer_Covid[blind];
                }

                numComparacoes=0;
                numMovimentacoes=0;
                tempo=0;
                ti=high_resolution_clock::now();
                HeapSort_ETAPA2(buffer_HeapSort,n[i],&numComparacoes,&numMovimentacoes);
                tf=high_resolution_clock::now();
                tempo=duration_cast<microseconds>(tf-ti).count();
                metrica_Comparacoes[1][j] = numComparacoes;
                metrica_Movimentacoes[1][j] = numMovimentacoes;
                metrica_Tempo[1][j] = tempo;



                numComparacoes=0;
                numMovimentacoes=0;
                tempo=0;
                ti=high_resolution_clock::now();
                quick_sort(buffer_QuickSort,0,n[i],&numComparacoes,&numMovimentacoes);
                tf=high_resolution_clock::now();
                tempo=duration_cast<microseconds>(tf-ti).count();
                metrica_Comparacoes[2][j] = numComparacoes;
                metrica_Movimentacoes[2][j] = numMovimentacoes;
                metrica_Tempo[2][j] = tempo;

                numComparacoes=0;
                numMovimentacoes=0;
                tempo=0;
                ti=high_resolution_clock::now();
                comb_sort11(buffer_CombSort,n[i],&numComparacoes,&numMovimentacoes);
                tf=high_resolution_clock::now();
                tempo=duration_cast<microseconds>(tf-ti).count();
                metrica_Comparacoes[3][j] = numComparacoes;
                metrica_Movimentacoes[3][j] = numMovimentacoes;
                metrica_Tempo[3][j] = tempo;

            }
            if(saida.is_open())
            {
                saida<<"ESTATISTICA PARA "<<n[i]<<" REGISTROS"<<endl;

                saida<<"HEAP SORT: iteracao, numero de comparacoes, numero de movimentacoes, tempo de execucao (10^-6 s)"<<endl;
                double somaCompara=0, somaMovimenta=0, somaTempo=0;
                    for(int j=0;j<5;j++)
                    {
                        saida<<j<<", "<<metrica_Comparacoes[1][j]<<", "<<metrica_Movimentacoes[1][j]<<", "<<metrica_Tempo[1][j]<<endl;
                        somaCompara =somaCompara +metrica_Comparacoes[1][j];
                        somaMovimenta = somaMovimenta+metrica_Movimentacoes[1][j];
                        somaTempo = somaTempo+metrica_Tempo[1][j];
                    }
                    saida<<"MEDIA ARITMETICA: "<<endl;
                    saida<<"NUMERO DE COMPARACOES MEDIO: "<<somaCompara/5<<"   NUMERO DE MOVIMENTACOES MEDIO: "<<somaMovimenta/5;
                    saida<<"   TEMPO DE EXECUCAO MEDIO: "<<somaTempo/5;
                    saida<<endl<<endl;


                    saida<<"QUICK SORT: iteracao, numero de comparacoes, numero de movimentacoes, tempo de execucao (10^-6 s)"<<endl;
                    somaCompara=0, somaMovimenta=0, somaTempo=0;
                    for(int j=0;j<5;j++)
                    {
                        saida<<j<<", "<<metrica_Comparacoes[2][j]<<", "<<metrica_Movimentacoes[2][j]<<", "<<metrica_Tempo[2][j]<<endl;
                        somaCompara =somaCompara +metrica_Comparacoes[2][j];
                        somaMovimenta =somaMovimenta +metrica_Movimentacoes[2][j];
                        somaTempo = somaTempo+metrica_Tempo[2][j];
                    }
                    saida<<"MEDIA ARITMETICA: "<<endl;
                    saida<<"NUMERO DE COMPARACOES MEDIO: "<<somaCompara/5<<"   NUMERO DE MOVIMENTACOES MEDIO: "<<somaMovimenta/5;
                    saida<<"   TEMPO DE EXECUCAO MEDIO: "<<somaTempo/5;
                    saida<<endl<<endl;


                    saida<<"COMB SORT: iteracao, numero de comparacoes, numero de movimentacoes, tempo de execucao (10^-6 s)"<<endl;
                    somaCompara=0, somaMovimenta=0, somaTempo=0;
                    for(int j=0;j<5;j++)
                    {
                        saida<<j<<", "<<metrica_Comparacoes[3][j]<<", "<<metrica_Movimentacoes[3][j]<<", "<<metrica_Tempo[3][j]<<endl;
                        somaCompara =somaCompara +metrica_Comparacoes[3][j];
                        somaMovimenta =somaMovimenta +metrica_Movimentacoes[3][j];
                        somaTempo =somaTempo +metrica_Tempo[3][j];
                    }
                    saida<<"MEDIA ARITMETICA: "<<endl;
                    saida<<"NUMERO DE COMPARACOES MEDIO: "<<somaCompara/5<<"   NUMERO DE MOVIMENTACOES MEDIO: "<<somaMovimenta/5;
                    saida<<"   TEMPO DE EXECUCAO MEDIO: "<<somaTempo/5;
                    saida<<endl<<endl;
                    saida<<endl<<endl<<endl;


            }
            else
                cerr<<"Erro ao abrir arquivo de saida!"<<endl;

            delete [] buffer_HeapSort;
            delete [] buffer_QuickSort;
            delete [] buffer_CombSort;
        }

        saida.close();
        cout<<"Etapa 2 concluida com sucesso!"<<endl<<endl<<endl;
        break;

    case 3://PRE PROCESSAMENTO MODULO TESTE
        cout<<"O que prefere:"<<endl;
        cout<<"1 - EXIBIR A SAIDA NO CONSOLE"<<endl;
        cout<<"2 - SALVAR EM ARQUIVO"<<endl;
        cout<< "SUA ESCOLHA: ";
        cin>>menu;
        cout<<endl<<endl<<endl;
        if(menu==1) //SAIDA NO CONSOLE
        {
            buffer_Covid = new Covid19 [num_REGISTROS];
            ImportaArquivos(num_REGISTROS,0,buffer_Covid);
            HeapSort(buffer_Covid,num_REGISTROS);
            Recalcula_CasosAcumuladosPARACasosDiarios(buffer_Covid,10);
            PrintArquivo(10,buffer_Covid);
        }
        else if(menu==2)//SALVAR EM ARQUIVO
        {
            buffer_Covid = new Covid19 [num_REGISTROS];
            ImportaArquivos(num_REGISTROS,0,buffer_Covid);
            HeapSort(buffer_Covid,num_REGISTROS);
            Recalcula_CasosAcumuladosPARACasosDiarios(buffer_Covid,100);
            EscreveDadosEmArquivo(100,buffer_Covid);
        }
        else
        {
            cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
        }

        break;

    case 4://IMPORTACAO DE N REGISTROS ALEATORIOS
        cout<<"O que prefere:"<<endl;
        cout<<"1 - EXIBIR A SAIDA NO CONSOLE"<<endl;
        cout<<"2 - SALVAR EM ARQUIVO"<<endl;
        cout<< "SUA ESCOLHA: ";
        cin>>menu;
        cout<<endl<<endl<<endl;
        if(menu==1) //SAIDA NO CONSOLE
        {
            buffer_Covid = new Covid19[10];
            ImportaArquivos(10,1,buffer_Covid);
            PrintArquivo(10,buffer_Covid);
        }
        else if(menu==2)//SALVAR EM ARQUIVO
        {
            buffer_Covid = new Covid19[100];
            ImportaArquivos(100,1,buffer_Covid);
            EscreveDadosEmArquivo(100,buffer_Covid);

        }
        else
        {
            cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
        }

        break;

    case 5://ORDENACAO COM HEAP-SORT
        int etapa;
        cout<<"Deseja rodar o Heap-Sort com qual chave de ordenacao?"<<endl;
        cout<<"1 - ORDENACAO VIA estado->cidade->data"<<endl;
        cout<<"2 - ORDENACAO VIA numero de casos confirmados"<<endl;
        cout<< "SUA ESCOLHA: ";
        cin>>etapa;
        cout<<"O que prefere:"<<endl;
        cout<<"1 - EXIBIR A SAIDA NO CONSOLE"<<endl;
        cout<<"2 - SALVAR EM ARQUIVO"<<endl;
        cout<< "SUA ESCOLHA: ";
        cin>>menu;
        cout<<endl<<endl<<endl;
        if(menu==1) //SAIDA NO CONSOLE
        {
            buffer_Covid = new Covid19[10];
            ImportaArquivos(10,1,buffer_Covid);
            if(etapa == 1)
            {
                HeapSort(buffer_Covid,10);
                PrintArquivo(10,buffer_Covid);
            }
            else if(etapa ==2)
            {
                HeapSort_ETAPA2(buffer_Covid,10, &numComparacoes, &numMovimentacoes);
                PrintArquivo(10,buffer_Covid);
            }
            else
            {
                cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
            }
        }
        else if(menu==2)//SALVAR EM ARQUIVO
        {
            buffer_Covid = new Covid19[100];
            ImportaArquivos(100,1,buffer_Covid);
            if(etapa == 1)
            {
                HeapSort(buffer_Covid,100);
                EscreveDadosEmArquivo(100,buffer_Covid);
            }
            else if(etapa ==2)
            {
                HeapSort_ETAPA2(buffer_Covid,100, &numComparacoes,&numMovimentacoes);
                EscreveDadosEmArquivo(100,buffer_Covid);
            }
            else
            {
                cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
            }
        }
        else
        {
            cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
        }
        break;

    case 6://ORDENACAO COM QUICK-SORT
        cout<<"O que prefere:"<<endl;
        cout<<"1 - EXIBIR A SAIDA NO CONSOLE"<<endl;
        cout<<"2 - SALVAR EM ARQUIVO"<<endl;
        cout<< "SUA ESCOLHA: ";
        cin>>menu;
        cout<<endl<<endl<<endl;
        if(menu==1) //SAIDA NO CONSOLE
        {
            buffer_Covid = new Covid19[10];
            ImportaArquivos(10,1,buffer_Covid);
            quick_sort(buffer_Covid,0,9,&numComparacoes,&numMovimentacoes);
            PrintArquivo(10,buffer_Covid);
        }
        else if(menu==2)//SALVAR EM ARQUIVO
        {
            buffer_Covid = new Covid19[100];
            ImportaArquivos(100,1,buffer_Covid);
            quick_sort(buffer_Covid,0,99,&numComparacoes,&numMovimentacoes);
            EscreveDadosEmArquivo(100,buffer_Covid);
        }
        else
        {
            cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
        }

        break;

    case 7://ORDENACAO COM COMB-SORT
        cout<<"O que prefere:"<<endl;
        cout<<"1 - EXIBIR A SAIDA NO CONSOLE"<<endl;
        cout<<"2 - SALVAR EM ARQUIVO"<<endl;
        cout<< "SUA ESCOLHA: ";
        cin>>menu;
        cout<<endl<<endl<<endl;
        if(menu==1) //SAIDA NO CONSOLE
        {
            buffer_Covid = new Covid19[10];
            ImportaArquivos(10,1,buffer_Covid);
            comb_sort11(buffer_Covid,10,&numComparacoes,&numMovimentacoes);
            PrintArquivo(10,buffer_Covid);
        }
        else if(menu==2)//SALVAR EM ARQUIVO
        {
            buffer_Covid = new Covid19[100];
            ImportaArquivos(100,1,buffer_Covid);
            comb_sort11(buffer_Covid,100,&numComparacoes,&numMovimentacoes);
            EscreveDadosEmArquivo(100,buffer_Covid);
        }
        else
        {
            cout<<"OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;
        }
        break;

    default:
        cout<< "OPCAO INVALIDA! - FIM DE EXECUCAO"<<endl<<endl;

    }
    delete [] buffer_Covid;

    return 0;
}
