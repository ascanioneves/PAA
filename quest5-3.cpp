#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

// Estrutura para guardar as arestas do grafo
struct Edge {
	int src, dest, weight;
};

// Classe para representar o grafo
class Graph
{
public:
	// Uma matriz que representa a lista de adjacencia do grafo
	vector<vector<Edge>> adjList;

	// Construtor
	Graph(vector<Edge> const &edges, int N)
	{
		// alteramos o tamanho do vetor para armazenar N elementos do tipo vector<Edge>
		adjList.resize(N);

		// adicionando as arestas no grafo direcionado
		for (Edge const &edge: edges) {
			adjList[edge.src].push_back(edge);
		}
	}
};

// Executamos o DFS no grafo e setamos o horario de saida de todos
// vertices of the graph
int DFS(Graph const &graph, int v, vector<bool>
	&discovered, vector<int> &departure, int &time)
{
	// Marcamos o nó atual como discovered
	discovered[v] = true;

	// para toda aresta fazememos: v —> u
	for (Edge e: graph.adjList[v])
	{
		int u = e.dest;
		// se u ainda não foi descoberto
		if (!discovered[u]) {
			DFS(graph, u, discovered, departure, time);
		}
	}

	// backtrack
	// setamos o departure do vértice v
	departure[time] = v;
	time++;
}

// A função executa a ordenação topológica em um determinado DAG e, em seguida, encontra
// a maior distancia de todos os vertices de uma dada origem executando um passo do
// algoritmo de Bellman–Ford
void findLongestDistance(Graph const &graph, int source, int N)
{
	// departure[] guarda o numero do vertice que tem essa determinada saida
	// com o tempo igual ao indice
	vector<int> departure(N, -1);

	// Acompanhando se o vértice foi descoberto ou nao
	vector<bool> discovered(N);
	int time = 0;

	// exuctamos a DFS para todos os vertices que nao foram descobertos ainda
	for (int i = 0; i < N; i++)
	{
		if (!discovered[i]) {
			DFS(graph, i, discovered, departure, time);
		}
	}

	vector<int> cost(N, INT_MAX);
	cost[source] = 0;

	// Processamos os vertices em ordem topologica, ou seja, em ordem
	// decrescente de tempo de saida no DFS
	for (int i = N - 1; i >= 0; i--)
	{
		// Para cada vértice em ordem topologica,
		// relaxamos o custo dos vertices adjacentes
		int v = departure[i];
		for (Edge e: graph.adjList[v])
		{
			// aresta e de v para u contendo peso w
			int u = e.dest;
			int w = e.weight * -1;		// tornando o peso negativo

			// Se a distancia para o destino u pode ser reduzida
			// levando a aresta v —> u, entao atualizamos o custo para o menor novo valor
			if (cost[v] != INT_MAX && cost[v] + w < cost[u]) {
				cost[u] = cost[v] + w;
			}
		}
	}

	// Exibindo o maior caminho
	for (int i = 0; i < N; i++)
	{
		cout << "dist(" << source << ", " << i << ") = " << setw(2) << cost[i] * -1;
		cout << endl;
	}
}

int main()
{
	// vetor de arestas do grafo
	vector<Edge> edges =
	{
		{0, 6, 2}, {1, 2, -4}, {1, 4, 1}, {1, 6, 8}, {3, 0, 3}, {3, 4, 5},
		{5, 1, 2}, {7, 0, 6}, {7, 1, -1}, {7, 3, 4}, {7, 5, -4}
	};

	// numero total de nós do grafo
	int N = 8;

	// constroi o grafo
	Graph graph(edges, N);

	// vertice de origem
	int source = 7;

  // encontra a maior distancia de todos os vertices a partir de uma dada origem
	findLongestDistance(graph, source, N);

	return 0;
}
