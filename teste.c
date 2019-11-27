#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void perturbacao(int *Smax, int *s, int *r, int *t, int Smax_c, int s_c, float fo1, float fo0, int n){

  int delta_s,delta_S;
  int y1,y2;
  delta_s = *s - s_c;
  delta_S = *Smax - Smax_c;

  if(fo0 < fo1){
    if(delta_s != 0){
      if(delta_s > 0 && (*s+delta_s<=250)){
        *s += delta_s;
      }
      else if(delta_s < 0 && (*s-delta_s<=250)){
        *s -= delta_s;
      }
    }
    if(delta_S != 0){
      if(delta_S > 0 && (*Smax+delta_S<=250)){
        *Smax += delta_S;
      }
      else if(delta_S < 0 && (*Smax+delta_S<=250)){
        *Smax -= delta_S;
      }
    }
  }
  else{
    srand(time(NULL));
    y1 = rand() % 200 + 50;
    printf("valor do y1 foi de %d\n",y1);
    srand(time(NULL));
    y2 = rand() % 9 + 1;
    printf("valor do y2 foi de %d\n",y2);
    if(y1 > 180){
      *Smax = y1;
    }
    else{
      *s = y1;
    }
    if(n%2 != 0){
      *r = y2;
    }
    else{
      *t = y2;
    }
  }
}

float TempInicial(int Smax, int s, int r, int t, float fo_init){

  float TempIni=0,c_est=0,c_fal=0,c_rep=0;
  float total = fo_init;
  float fo_aux = fo_init;
  int Smax_c, s_c;
  Smax_c = Smax;
  s_c = s;
  int Smax_aux,s_aux;
  Smax_aux = Smax;
  s_aux = s;
  int n = 1;
  while(n!=5){

    perturbacao(&Smax,&s,&r,&t,Smax_c,s_c,fo_init,fo_aux,n);
    Smax_c = Smax_aux;
    s_c = s_aux;
    Smax_aux = Smax;
    s_aux = s;

    FILE* saida;
    saida = fopen("entrada.txt","w");
    if(saida == NULL){
      printf("Erro escrita!");
    }
    fprintf(saida,"%d %d %d %d",Smax,s,r,t);
    fclose(saida);

    system("siman Model1.p -B -L -O");

    FILE* entrada;
    entrada = fopen("saida.txt","r");
    if(entrada == NULL){
      printf("Erro leitura!");
    }
    fscanf(entrada,"%f %f %f",&c_est,&c_fal,&c_rep);
    fclose(entrada);

    fo_init = fo_aux;
    fo_aux = (c_est+c_fal+c_rep)/365;
    total += fo_aux;

    n++;
  }
  TempIni = total/n;
  return TempIni;
}

float SA(int *Smax, int *s, int *r, int *t, float fo_init, float tempini){

  float Smax_o,s_o,r_o,t_o;
  // s* = s
  Smax_o = *Smax;
  s_o = *s;
  r_o = *r;
  t_o = *t;
  float Smax_c,s_c,r_c,t_c;
  // s' = s
  Smax_c = *Smax;
  s_c = *s;
  r_c = *r;
  t_c = *t;
  float total=0,dif=0,c_est=0,c_fal=0,c_rep=0;
  int imax = 100, i = 0, cont = 0, hold = 1000, ite = 0;
  float alpha = 0.95;
  float x;
  float temperatura = tempini;
  float fo_otima = fo_init;
  float fo_aux = fo_init;
  while(temperatura > 0.01){
    while(i < imax){
      cont += 1;
      ite +=1;
      i += 1;
      perturbacao(Smax,s,r,t,Smax_c,s_c,fo_init,fo_aux,i); // passando o endereço de s. s passa a ser s'

      FILE* saida;
      saida = fopen("entrada.txt","w");
      if(saida == NULL){
        printf("Erro escrita!\n");
      }
      fprintf(saida,"%d %d %d %d",*Smax,*s,*r,*t); // salva s' no arquivo
      fclose(saida);

      system("siman Model1.p -B -L -O");

      FILE* entrada;
      entrada = fopen("saida.txt","r");
      if(entrada == NULL){
        printf("Erro leitura!\n");
      }
      fscanf(entrada,"%f %f %f",&c_est,&c_fal,&c_rep);
      fclose(entrada);
      total = (c_est+c_fal+c_rep)/365;

      dif = total - fo_init;
      if(*s<=*Smax && (c_est/365)<=100 && (c_fal/365)<=30 && *r>0 && *t>0 && *Smax>49 && *s>49 && *Smax<251 && *s<251 && *r<11 && *t<11){
        printf("viavel\n");
        if(dif < 0){
          //quero seguir a partir dessa config
          Smax_c = *Smax;
          s_c = *s;
          r_c = *r;
          t_c = *t;
          fo_init = fo_aux;
          fo_aux = total;
          if(total < fo_otima){
            Smax_o = *Smax;
            s_o = *s;
            r_o = *r;
            t_o = *t;
            fo_otima = total;
            cont = 0;
          }
        }
        else{
          srand(time(NULL));
          x = rand() / RAND_MAX;
          if(x < exp(-(dif/temperatura))){
            Smax_c = *Smax;
            s_c = *s;
            r_c = *r;
            t_c = *t;
            fo_init = fo_aux;
            fo_aux = total;
          }
          else{
            *Smax = Smax_c;
            *s = s_c;
            *r = r_c;
            *t = t_c;
          }
        }
      }
      else{
        printf("inviavel\n");
      }
      if(cont > hold){
        temperatura = 0.01;
      }

    }
    temperatura *= alpha;
    i = 0;
  }
  *Smax = Smax_o;
  *s = s_o;
  *r = r_o;
  *t = t_o;
  printf("Total de iteracoes ate solucao final: %d\n",ite);
  return fo_otima;
}

int main(){
  //leitura inicial: 250 160 1 1
  clock_t tempo;
  tempo = clock();

  int Smax,s,r,t;
  float c_est,c_fal,c_rep;
  float tempini,fo_otima,fo_init;

  FILE* f;
  f = fopen("entrada.txt","r");
  if(f == NULL){
    printf("Erro leitura!");
  }
  fscanf(f,"%d %d %d %d",&Smax,&s,&r,&t);
  fclose(f);

  system("siman Model1.p -B -L -O");

  FILE* entrada;
  entrada = fopen("saida.txt","r");
  if(entrada == NULL){
    printf("Erro leitura!");
  }
  fscanf(entrada,"%f %f %f",&c_est,&c_fal,&c_rep);
  fo_init = (c_est+c_fal+c_rep)/365;
  fclose(entrada);

  tempini = TempInicial(Smax, s, r, t, fo_init);
  fo_otima = SA(&Smax,&s,&r,&t,fo_init,tempini);
  tempo = clock() - tempo;
  printf("\n");
  printf("fo inicial: %f\n",fo_init);
  printf("Temperatura inical foi de: %f\n",tempini);
  printf("Funcao objetivo encontrada foi de: %f\n",fo_otima);
  printf("Melhor configuracao de parametros:\n");
  printf("Smax = %d, s = %d, r = %d, t = %d\n", Smax,s,r,t);
  printf("Tempo decorrido: %f segundos\n",((float)tempo)/CLOCKS_PER_SEC);

  return 0;
}
