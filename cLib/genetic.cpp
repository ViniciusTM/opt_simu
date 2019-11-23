#include <algorithm>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <math.h>
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

void Solution::report()
{
    std::cout << sMin << " ";
    std::cout << sDiff << " ";
    std::cout << orderType << " ";
    std::cout << deliveryType << " ";
    std::cout << totalCost << " ";
    std::cout << inviability << std::endl;
}

// Calcula resultados com metamodelo
void Solution::metamodel()
{
    holdingCost = 118.237290083772 -1.560363452608*sMin - 1.556201013390*sDiff - 2.337559550758*orderType - 22.089073815403*deliveryType + 0.006135136368*pow(sMin,2) + 0.012470928683*sMin*sDiff + 0.014396259698*sMin*orderType + 0.166776999838*sMin*deliveryType + 0.005586082559*pow(sDiff,2) + 0.019427648601*sDiff*orderType + 0.165820582310*sDiff*deliveryType + 0.144579617927*pow(orderType,2) + 0.060376842820*orderType*deliveryType + 1.275641910306*pow(deliveryType,2) - 0.000003854228*pow(sMin,3) - 0.000016925104*pow(sMin,2)*sDiff - 0.000036102021*pow(sMin,2)*orderType - 0.000205554712*pow(sMin,2)*deliveryType - 0.000011257846*sMin*pow(sDiff,2) + 0.000016473543*sMin*sDiff*orderType - 0.000370771529*sMin*sDiff*deliveryType - 0.000460606806*sMin*pow(orderType,2) - 0.000054766380*sMin*orderType*deliveryType - 0.003086994884*sMin*pow(deliveryType,2) - 0.000000524613*pow(sDiff,3) - 0.000120940592*pow(sDiff,2)*orderType - 0.000185483832*pow(sDiff,2)*deliveryType - 0.000480405361*sDiff* pow(orderType,2) - 0.000775843418*sDiff*orderType*deliveryType - 0.002952038718*sDiff*pow(deliveryType,2) - 0.003414809945*pow(orderType,3) + 0.001120330258*pow(orderType,2)*deliveryType + 0.001539090920*orderType*pow(deliveryType,2) - 0.020977753519*pow(deliveryType,3);
    shortageCost = 1710.628768356833 - 12.910875055087*sMin - 12.678016304584*sDiff - 14.758771794164*orderType - 167.708673146196*deliveryType + 0.031016055537*pow(sMin,2) + 0.061203407458*sMin*sDiff + 0.092903653510*sMin*orderType + 0.846876514262*sMin*deliveryType + 0.027533585839*pow(sDiff,2) + 0.103457769730*sDiff*orderType + 0.831555163307*sDiff*deliveryType + 0.858478197008*pow(orderType,2) + 0.368436728092*orderType*deliveryType + 5.467184170560*pow(deliveryType,2) - 0.000020146826* pow(sMin,3) - 0.000081979260*pow(sMin,2)*sDiff - 0.000191558388*pow(sMin,2)*orderType -0.001025940299*pow(sMin,2)*deliveryType - 0.000056775659*sMin*pow(sDiff,2) + 0.000131571847*sMin*sDiff*orderType - 0.001793064277*sMin*sDiff*deliveryType - 0.003650619757*sMin*pow(orderType,2) - 0.001319366028*sMin*orderType*deliveryType - 0.016255651332*sMin*pow(deliveryType,2) - 0.000000761521*pow(sDiff,3) - 0.000590333358*pow(sDiff,2)*orderType - 0.000928932723*pow(sDiff,2)*deliveryType - 0.004485897402*sDiff*pow(orderType,2) - 0.002895354352*sDiff*orderType*deliveryType - 0.016072019200*sDiff*pow(deliveryType,2) - 0.001673003420*pow(orderType,3) + 0.002769446636*pow(orderType,2)*deliveryType + 0.014179986299*orderType*pow(deliveryType,2) - 0.038154837284*pow(deliveryType,3);
    orderCost = 93.896301554204 - 0.034126509516*sMin - 0.096055291729*sDiff - 6.609064529700*orderType + 1.459221243308*deliveryType + 0.000515022809*pow(sMin,2) + 0.000278208963*sMin*sDiff - 0.012123422100*sMin*orderType - 0.002174475578*sMin*deliveryType + 0.001635272870*pow(sDiff,2) - 0.001245197375*sDiff*orderType - 0.005841838542*sDiff*deliveryType + 1.836117200813*pow(orderType,2) + 0.078968352313*orderType*deliveryType + 0.010847903839*pow(deliveryType,2) - 0.000001725653*pow(sMin,3) + 0.000000074907*pow(sMin,2)*sDiff + 0.000037581184*pow(sMin,2)*orderType - 0.000004025821*pow(sMin,2)*deliveryType - 0.000001508380*sMin*pow(sDiff,2) - 0.000008047450*sMin*sDiff*orderType - 0.000019338802*sMin*sDiff*deliveryType + 0.000181674778*sMin*pow(orderType,2) - 0.000007564295*sMin*orderType*deliveryType + 0.000469546775*sMin*pow(deliveryType,2) - 0.000008841324*pow(sDiff,3) + 0.000027008324*pow(sDiff,2)*orderType + 0.000003770463*pow(sDiff,2)*deliveryType + 0.000190705828*sDiff*pow(orderType,2) - 0.000210029526*sDiff*orderType*deliveryType + 0.000836760426*sDiff*pow(deliveryType,2) - 0.078601189657*pow(orderType,3) - 0.001867374627*pow(orderType,2)*deliveryType - 0.006350060031*orderType*pow(deliveryType,2) - 0.004222412964*pow(deliveryType,3);
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
Genetic::Genetic(const char* fileName, bool report, HiperParams hipparams)
{
    Solution::totalSimuNumber = 0;
    hp = hipparams;
    genNumber = 0;
    Solution::tabu.clear();
    initial_pop(fileName);

    if (report) {
        reportFile.open("report.csv");
        if (!reportFile.is_open()) {
            std::cout << "Erro ao abrir report file" << std::endl;
        }
        reportFile << "length;elapsed;holdingCost;shortageCost;orderCost;popStd;viability" << std::endl; 
    }
}

void Genetic::initial_pop(const char *fileName)
{
    std::ifstream file(fileName);
    int s, d, o, l;
    population.reserve(1000);

    if (!file)
    {
        std::cout << "Erro na leitura!" << std::endl;
    }

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
    double elapsedGer = 0;
    while (popStd > hp.stdTreshold || genNumber < hp.itTreshold || elapsed < hp.timeTreshold)
    {
        generation_step();
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        elapsed = duration.count();
        summary_print();

        //CHAMAR FUNCAO PRINT AQUI
        elapsedGer = elapsed;
        report(elapsedGer);
    }

    reportFile.close();
}

// E equi que a magica acontece
void Genetic::generation_step()
{
    std::vector<Solution> winners;
    //Funcao que ira, a partir da populacao atual, definir quais serao os candidatos
    //que irao particicpar do torneio, realizando a disputa dois a dois, definindo qual
    //foi o vencedor, sendo que caso seja necessario ira aplicar a simulacao para definir
    //esse ganhador. Ao final retornara um vetor com os vencedores e aptos a reproduzir
    winners = tournament();
    for (int i = 0; i < winners.size(); i++)
    {
        std::cout << "Valor: " << winners[i].totalCost << '\n';
    }

    //Funcao que, com base nos vencedores do torneio, ira definir quais serao os pais,
    //realizando a reproducao com base no alpha e aplicando a mutacao.
    // reproduction();
    //Funcao que ira determinar qual sera a nova populacao, com base nos filhos e com os
    //pais que foram selecionados, eliminando o restante
    // armagedon();
    std::cout << "Tempo: " << elapsed << std::endl;
}


bool Genetic::x1(Solution& s1, Solution& s2)
{
    std::cout << "FO: : " << s1.totalCost << " " << s2.totalCost << '\n';
    if (abs(s1.totalCost - s2.totalCost) <= hp.slackTreshold)
    {
        // std::cout << "Simulou!" << '\n';
        s1.simulate();
        s2.simulate();
    }
    if (s1.totalCost - s2.totalCost <= 0) { return 0; }
    else { return 1; }
}


std::vector<Solution> Genetic::tournament()
{
    std::vector<Solution> winners;
    winners.reserve(population.size()/2);
    std::random_shuffle(population.begin(), population.end());
    for (int i = 0; i < population.size() - 1; i+=2)
    {
        int m = x1(population[i], population[i+1]);
        if (m == 0) { winners.push_back(population[i]); }
        else { winners.push_back(population[i+1]); }
        std::cout << "Valor winner: " << winners.back().totalCost << '\n';
    }
    return winners;
}


// Calcula a variabilidade da populacao
void Genetic::calc_std()
{
    popStd = 0.0;
    double soma = 0.0;

    for(int i=0; i<hp.popSize; i++)
    {
        soma += population[i].totalCost;
    }

    double average = soma/(hp.popSize-1);

    for(int i=0; i<hp.popSize; i++)
    {
        soma += pow(population[i].totalCost-average, 2);
    }

    popStd = sqrt(soma);
}

// Calcula a quantidade de configuracoes viaveis
int Genetic::calc_viability()
{
    int viability = 0;
    for(int i=0; i<hp.popSize; i++)
    {
        if(population[i].inviability == 0)
        {
            viability++;
        }
    }

    return viability;
}

void Genetic::summary_print() {
    std::cout << "Numero da geração: " << genNumber << std::endl;
    std::cout << "Numero de simulacoes: " << Solution::tabu.length << std::endl;
    std::cout << "Tempo decorrido: " <<  elapsed << std::endl;
    std::cout << "Std da Posulação: " << popStd << std::endl;
    std::cout << "Numero de viaveis: " << calc_viability() << std::endl;
    std::cout << "Melhor solução: sMin = " << bestSol.s << " sDiff = " << bestSol.d;
    std::cout << " orderType = " << bestSol.o << " deliveryType = " << bestSol.l << std::endl; 
    std::cout << std::endl;
}

void Genetic::report(double elapsedGer)
{ 
    if (reportFile.is_open())
    {
        reportFile << Solution::tabu.length << ";"; //numero simulacoes
        reportFile << elapsed - elapsedGer << ";"; //tempo decorrido
        reportFile << bestSol.hc << ";"; //holdingCost
        reportFile << bestSol.sc << ";"; //shortageCost
        reportFile << bestSol.oc << ";"; //orderCost
        reportFile << popStd << ";"; //desvio padrao populacao
        reportFile << calc_viability() << std::endl; // quantidade de configs viaveis
    }
}
