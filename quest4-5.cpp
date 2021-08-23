#include <iostream>
#include <queue>
#include "graph.h"
using namespace std;

int partyAlgo(int numPeople){

	Graph G(numPeople);
	bool invite[numPeople];
	queue<int> rejects;
	int input, accepted = 0;

   //Creando as relações
	for(int i=0;i<numPeople;i++){
      cout << "Quem a " << G.getPerson(i) << " conhece? Digite -1 para terminar.\n";
      do{
         cout << "Pessoa #: ";
         cin >> input;

         //Se é valido adicionamos a matriz de adjacencia
         if(input > 0 && input <= numPeople && input != i+1)
			{
				if (G.isEdge(i,input-1))
					cout << "Pessoa " << i+1 << " e Pessoa " << input << " ja estão conectadas." << endl;
				else
					G.addEdge(i,input-1);
			}
         else if (input == i+1)
            cout << "Esse numero pertence a ele mesmo!" << endl;
         else if (input == -1)
            cout << "Pessoa "<< i+1 << " tem " << G.getDegree
					(i)<<" relacoes." << endl;
         else
            cout << "Input invalido. Tente novamente: ";
      }while(input != -1);
   }

	//Primeiros convites
	for (int i=0;i<numPeople;i++){
		invite[i] = 1; //começamos convidando todos
		if (G.getDegree(i) < 5)
		{
			rejects.push(i); //essa pessoa é rejeitada
			invite[i] = 0; //Cancelando o convite de quem conhece menos de 5
		}
	}

	//Garantindo que todos conhecem mais de 5
	while(!rejects.empty())
	{
		int j = rejects.front();
		rejects.pop();

		for(int i=0;i<numPeople;i++)
		{
			G.removeEdge(i,j);
			if (G.getDegree(i) < 5 && invite[i] == 1)
			{
				rejects.push(i);
				invite[i] = 0;
			}
		}
	}

	//Contagem final de convidados
	cout << endl;
	for (int i=0;i<numPeople;i++)
	{
		if (invite[i] == 1)
		{
			cout << G.getPerson(i) << " pode vir\n";
			accepted++;
		}
	}

	return accepted;
}

int main()
{
	//Inicializando o grafo com o numero de convites
	int n;
	cout << "Informe o numero de pessoas: ";
	cin >> n;
	cout << endl;

	int output = partyAlgo(n);

	//Saida do programa
	if (output == n)
		cout << "Todo mundo se conhece, entao todos podem vir!\n";
	else if (output == 0)
		cout << "Ninguem conhece pessoas suficientes, portante nao podera ter a festa.\n";
	else
		cout << "De " << n << " pessoas, " << output << " podem vir para a festa.\n";

	cout << endl;
	return 0;
}
