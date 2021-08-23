#include <bits/stdc++.h>

using namespace std;

//retorna se duas atividades sao compativeis
bool is_compatible(pair<int, int> a, pair<int, int> b)
{
  return (a.first >= b.second || b.first >= a.second);
}
vector<pair<int, int>> solve(vector<pair<int, int>> act)
{
  //Nosso subvetor que será a resposta
  vector<pair<int, int>> current;
  //Enquanto ainda tiver atividades
  while (act.size() > 0)
  {
    //pegamos a atividade com o menor horario de termino
    pair<int, int> earliest = act[act.size() - 1];
    //deletamos ela do conjunto e adicionamos na resposta
    current.push_back(earliest);
    act.pop_back();
    //percorremos todas as atividades restantes e eliminamos as que nao são compativeis o earliest
    for (int p = 0; p < act.size(); p++)
      //Se não for compativel removemos o mesmo do conjunto S
      if (!is_compatible(act[p], earliest))
        act.erase(act.begin() + p);
  }
  return current;
}
//Função de comparação para ordenarmos de acordo com o tempo de término
bool comp(const pair<int, int> &a, const pair<int, int> &b)
{
  return (a.second > b.second);
}
int main()
{
  vector<pair<int, int>> act;
  //criando os pares
  act.push_back(make_pair(1, 2));
  act.push_back(make_pair(1, 3));
  act.push_back(make_pair(3, 4));
  act.push_back(make_pair(2, 3));
  act.push_back(make_pair(5, 6));
  //Ordenando de acordo com o horario de termino (decrescente)
  sort(act.begin(), act.end(), comp);
  vector<pair<int, int>> answer = solve(act);
  //printando a resposta
  for (auto a : answer)
    cout << a.first << " " << a.second << endl;

  return 0;
}
