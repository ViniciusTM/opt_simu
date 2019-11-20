#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include "genetic.h"

double ALPHA = 0.0;

//----------- Solution -----------//
TabuList Solution::tabu;           // Lista Tabu como variavel de classe da solucao (evitar passa ela como parametro)
int Solution::totalSimuNumber = 0; // Conta o numer de simulacoes que tiveram que ser feitas

// Inicializa parametros e ja calcula FO estimada ou pela tabu list
Solution::Solution(int s, int d, int o, int l)
{
    sMin = s;
    sDiff = d;
    orderType = o;
    deliveryType = l;

    Node *node = tabu.find(get_params());
    if (node)
    {
        holdingCost = node->holdingCost;
        shortageCost = node->shortageCost;
        orderCost = node->orderCost;
        totalCost = node->totalCost;
        inviability = node->inviability;
        simulated = true;
    }
    else
    {
        metamodel();
        simulated = false;
    }
}

// Retorna a struct Params que tem informações basicas da solução para guardar na tabulist
Params Solution::get_params()
{
    Params params;

    params.s = sMin;
    params.d = sDiff;
    params.o = orderType;
    params.l = deliveryType;

    params.hc = holdingCost;
    params.sc = shortageCost;
    params.oc = orderCost;
    params.inv = inviability;

    return params;
}

// Calcula resultados com metamodelo
void Solution::metamodel()
{
    holdingCost = 1 + 1*sMin + 1*sDiff + 1*orderType + 1*deliveryType;
    shortageCost = 1 + 1*sMin + 1*sDiff + 1*orderType + 1*deliveryType;
    orderCost = 1 + 1*sMin + 1*sDiff + 1*orderType + 1*deliveryType;

    inviability = (std::max(0.0, shortageCost - 30) + std::max(0.0, holdingCost - 100));
    totalCost = ALPHA*inviability + holdingCost + shortageCost + orderCost;
}
// Simula solucao
void Solution::simulate()
{
    simulated = true;

    // ======= simulação =======
    metamodel();
    // =========================

    totalSimuNumber++;
    tabu.add(get_params());
}

//------------ Genetic ------------//

// Por enquanto so reseta variaveis de classe da solucao
Genetic::Genetic(const char* fileName, HiperParams hipparams)
{
    Solution::totalSimuNumber = 0;
    hp = hipparams;
    genNumber = 0;
    Solution::tabu.clear();
    initial_pop(fileName);
}

void Genetic::initial_pop(const char *fileName)
{
    std::ifstream file(fileName);
    int s, d, o, l;
    population.reserve(1000);
    while (file >> s >> d >> o >> l)
    {
        Solution sol(s, d, o, l);
        population.push_back(sol);
    }
    file.close();
    hp.popSize = population.size();
}

// Roda geracao e loga resultados
void Genetic::run()
{
    auto start = std::chrono::high_resolution_clock::now();
    while (popStd > hp.stdTreshold || genNumber < hp.itTreshold || elapsed < hp.timeTreshold)
    {
        int simuNum = Solution::totalSimuNumber;
        std::cout << "=======================================" << std::endl;
        std::cout << "-----> Generation: " << genNumber << std::endl;
        generation_step();
        std::cout << "Best solution:" << bestSol.ct << std::endl;
        std::cout << "Num simulations (gen):" << Solution::totalSimuNumber - simuNum << std::endl;
        std::cout << "Num simutaions (total):" << Solution::totalSimuNumber << std::endl;
        std::cout << "Population std:" << popStd << std::endl;
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        elapsed = duration.count();
        std::cout << "Valores: " << popStd << " " << genNumber << " " << elapsed << std::endl;
    }
}

// E equi que a magica acontece
void Genetic::generation_step()
{
    std::cout << "Tempo: " << elapsed << std::endl;
}

// Calcula a variabilidade da populacao
void Genetic::calc_std()
{

}
