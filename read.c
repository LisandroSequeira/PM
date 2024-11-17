#include <stdio.h>
#include <stdlib.h> //Para usar a função exit()
#include <string.h> // Para manipulação de strings

typedef enum {      	//Subestrutura dos robots (Tipo de robot)

   BOX_TRANSPORTER = 1,   // Representa "Box Transporter" com valor 1
   PALLET_TRANSPORTER = 2 // Representa "Pallet Transporter" com valor 2

} RobotType;


typedef enum {  	//Subestrutura dos robots e da station (Estado do robot / estado da estação)

   IDLE = 0,    	//O robot não está a realizar nenhuma tarefa.
   MOVING = 1,  	//O robot está em trânsito para um destino.
   LOADING = 2, 	//O robot está a carregar produtos.
   UNLOADING = 3,   //O robot está a descarregar produtos.
   CHARGING = 4,	//O robot está a recarregar a bateria.
   PRODUCING = 5,   //A estação está a produzir arroz.
   PALLETIZING = 6  //A estação está a paletizar arroz.

} TaskStatus;


typedef enum {  	//subestrutura da station

   JASMINE_RICE = 1, //Variedade de arroz Jasmine.
   BASMATI_RICE = 2, //Variedade de arroz Basmati.
   SUSHI_RICE = 3   //Variedade de arroz Sushi.

}RyceType;


typedef enum {      	//subestrutura da station

   RICE_PRODUCER = 1,   //Uma estação que produz arroz.
   PALLETIZER = 2,  	//Uma estação que paletiza produtos.
   CHARGING_STATION = 3  //Uma estação para recarregar os robots.

}StationType;


typedef struct robots{  //Estrutura Robots

   int type;        	//Identificador do tipo (2 para robots).
   int id;          	//Identificador único do robot.
   char name[30];   	//Nome do robot (ex.: "R1", "TransportBot").
   RobotType robot_type;   //Tipo de robot (BOX_TRANSPORTER or PALLET_TRANSPORTER).
   int location_x;  	//Coordenada X do robot na grelha.
   int location_y;  	//Coordenada Y do robot na grelha.
   float battery_capacity; //Nível da bateria em percentagem (ex.: 100.0).
   int payload_capacity;   //Capacidade máxima de carga do robot.
   TaskStatus task_status; //Estado atual da tarefa do robot (IDLE, MOVING, etc.).

}Estrutura_Robots;


typedef struct station{ 	//Estrutura Station

   int type;            	//Identificador do tipo (1 para estações).
   int id;              	//Identificador único da estação.
   char name[30];       	//Nome da estação (ex.: "Estação de Produção 1").
   int location_x;      	//Coordenada X da estação na grelha.
   int location_y;      	//Coordenada Y da estação na grelha.
   int production_capacity;  //Capacidade de produção da estação.
   RyceType rice_type;  	//Tipo de arroz produzido ou manipulado pela estação.
   StationType station_type; //Tipo de estação (PRODUTORA_ARROZ, PALETIZADORA, etc.).
   TaskStatus task_status;   //Estado atual da estação (PRODUCING, IDLE, etc.).

}Estrutura_Station;


typedef struct obstaculos{ //Estrutura Obstáculos

   char factory_name[50];  //Nome do layout da fábrica.
   int grid_witdh;  	//Largura da grelha (normalmente 20).
   int grid_height; 	//Altura da grelha (normalmente 20).
   int type;        	//Identificador do tipo (3 para obstáculos).
   int location_x;  	//Coordenada X na grelha.
   int location_y;  	//Coordenada Y na grelha.
 
}Estrutura_obstaculos;


//Função que apresenta o menu
int menu(){
   int opcao = 0;  //variavel a zero para poder usar o ciclo do...while
   do {
   printf("\n\nMENU");
   printf("\n____________________________________________________________________________________________");
   printf("\n1.   Carregar Robots e Mostrar Informações");
   printf("\n2.   Carregar Estações e Mostrar Informações");
   printf("\n3.   Carregar Layout da Fábrica (Obstáculos)");
   printf("\n4.   Adicionar/Retirar Obstáculos e Guardar Layout da Fábrica");
   printf("\n5.   Mostrar Mapa da Fábrica");
   printf("\n6.   Carregar Registo da Fábrica");
   printf("\n7.   Mostrar Informação do Registo - Por Tipo de Entidade");
   printf("\n8.   Mostrar e Guardar Informação do Registo - Por Robot ou Estação Específica");
   printf("\n9.   Resumir Estatísticas de Produção e Transporte (Filtro por Dia, Semana ou Mês)");
   printf("\n10.  Aceder aos Ficheiros de Estado dos Robots e Estações");
   printf("\n11.  Encontrar Percurso Entre Estações e Mostrar no Layout da Fábrica");
   printf("\n12.  Sair do Programa");
   printf("\n____________________________________________________________________________________________");
   printf("\n\nIntroduza o número da ação que deseja realizar: ");
   scanf(" %d", &opcao);


	//if statement para mostrar uma mensagem de "Opção Inválida"
	if (opcao < 0 || opcao > 12){
	printf("\nOpção inválida! Por favor, tente denovo com uma opção válida.");
	}

   } while(opcao < 0 || opcao > 12);
   
   return (opcao);
}


// Função para carregar robots do ficheiro e mostrar as informações
#define MAX_ROBOTS 100 //número maximo de robots
int carregar_robots(Estrutura_Robots robots[]) {
	FILE *file = fopen("robots.txt", "r"); // Abre o ficheiro em modo de leitura

    int num_robots = 0; // Inicializa o contador de robots

    // Verifica se o ficheiro foi aberto com sucesso, e senão imprime uma mensagem de erro e fecha o programa
	if (file == NULL) {
    	printf("Erro ao abrir o ficheiro robots.txt");
    	exit(1);
	}


	// Lê cada linha do ficheiro e armazena na estrutura Estrutura_Robots
	while (fscanf(file, "%d %d %29[^\t\n] %d %d %d %f %d %d", // Literalmente um scanf mas para ficheiros
            	&robots[num_robots].type,                      // Lê o tipo do robot (inteiro)
            	&robots[num_robots].id,                        // Lê o identificador único do robot (inteiro)
            	robots[num_robots].name,                       // Lê o nome do robot como uma string de no máximo 29 caracteres
            	(int*)&robots[num_robots].robot_type,          // Lê o tipo do robot (convertido de inteiro para enum RobotType)
            	&robots[num_robots].location_x,                // Lê a coordenada X do robot (inteiro)
            	&robots[num_robots].location_y,                // Lê a coordenada Y do robot (inteiro)
            	&robots[num_robots].battery_capacity,          // Lê a capacidade da bateria do robot (float)
            	&robots[num_robots].payload_capacity,          // Lê a capacidade de carga do robot (inteiro)
            	(int*)&robots[num_robots].task_status) != EOF) { // Lê o estado atual do robot (convertido de inteiro para enum TaskStatus)
                
                // Lê até ao fim do ficheiro

    	num_robots++; // Incrementa o contador de robots
    	if (num_robots >= MAX_ROBOTS) {
        	printf("Limite máximo de robots alcançado (%d).\n", MAX_ROBOTS);
        	break;
    	}
	}

	fclose(file); // Fecha o ficheiro após leitura
	printf("\nLeitura do ficheiro concluída. Total de robots lidos: %d\n", num_robots);

	return num_robots; // Retorna o número total de robots lidos
}


// Função para mostrar os robots
void mostrar_robots(Estrutura_Robots robots[], int num_robots) {

    char tipo_robot[20];   // Armazena o tipo do robot
    char estado_robot[15]; // Armazena o estado do robot

    // Verifica se existem robots carregados
	if (num_robots == 0) {
    	printf("Nenhum robot foi carregado. Por favor, carregue os robots primeiro.\n");
    	return;
	}

    // Imprime o cabeçalho da tabela de robots
	printf("\nLista de Robots:\n");
	printf("--------------------------------------------------------------------------------------\n");
	printf("ID | Nome                   	| Tipo          	| Localização | Bateria | Estado\n");
	printf("--------------------------------------------------------------------------------------\n");

    // Percorre o array de robots para exibir os detalhes de cada um
	for (int i = 0; i < num_robots; i++) {

    	// Determina o tipo do robot
    	if (robots[i].robot_type == BOX_TRANSPORTER) {

            // Copia a string "Box Transporter" para o array tipo_robot
        	strcpy(tipo_robot, "Box Transporter");

    	} else if (robots[i].robot_type == PALLET_TRANSPORTER) {

            // Copia a string "Pallet Transporter" para o array tipo_robot
        	strcpy(tipo_robot, "Pallet Transporter");

    	} else {

            // Copia a string "Desconhecido" para o array tipo_robot
        	strcpy(tipo_robot, "Desconhecido"); // Caso o tipo seja desconhecido

    	}

    	// Determina o estado do robot
    	if (robots[i].task_status == IDLE) {

            // Copia a string "Idle" para o array estado_robot
        	strcpy(estado_robot, "Idle");

    	} else if (robots[i].task_status == MOVING) {

            // Copia a string "Moving" para o array estado_robot
        	strcpy(estado_robot, "Moving");

    	} else if (robots[i].task_status == LOADING) {

            // Copia a string "Loading" para o array estado_robot
        	strcpy(estado_robot, "Loading");

    	} else if (robots[i].task_status == UNLOADING) {

            // Copia a string "Unloading" para o array estado_robot
        	strcpy(estado_robot, "Unloading");

    	} else if (robots[i].task_status == CHARGING) {

            // Copia a string "Charging" para o array estado_robot
        	strcpy(estado_robot, "Charging");

    	} else {

            // Copia a string "Unknown" para o array estado_robot
        	strcpy(estado_robot, "Unknown");

    	}

    	// Imprime os dados do robot como uma linha da tabela (literalmente um printf)
    	printf("%-3d| %-22s| %-18s| (%d, %d)	| %-7.1f| %-10s\n",
           	robots[i].id,                 // id específico do robot	 
           	robots[i].name,               // nome do robot
           	tipo_robot,                   // tipo do robot
           	robots[i].location_x,         // coordenada X na grelha
           	robots[i].location_y,         // coordenada Y na grelha
           	robots[i].battery_capacity,   // capacidade da bateria
           	estado_robot);                // estado do robot
	}

	printf("--------------------------------------------------------------------------------------\n"); // Ultima linha da tabela
}


// Função para carregar estações do ficheiro e mostrar as informações
#define MAX_STATIONS 100 // número máximo de estações
int carregar_estacoes(Estrutura_Station stations[]) {
   FILE *file = fopen("stations.txt", "r"); // Abre o ficheiro em modo de leitura

   int num_stations = 0; // Inicializa o contador de estações

   // Verifica se o ficheiro foi aberto com sucesso, e senão imprime uma mensagem de erro e fecha o programa
   if (file == NULL) {
   	printf("Erro ao abrir o ficheiro stations.txt");
   	exit(1);
   }

   // Lê cada linha do ficheiro e armazena na estrutura Estrutura_Station
   while (fscanf(file, "%d %d %29[^\t\n] %d %d %d %d %d %d", // Literalmente um scanf mas para ficheiros
            	&stations[num_stations].type,                      // Lê o tipo da estação (inteiro)
            	&stations[num_stations].id,                        // Lê o identificador único da estação (inteiro)
            	stations[num_stations].name,                       // Lê o nome da estação como uma string de no máximo 29 caracteres
            	&stations[num_stations].location_x,                // Lê a coordenada X na grelha (inteiro)
            	&stations[num_stations].location_y,                // Lê a coordenada Y na grelha (inteiro)
            	&stations[num_stations].production_capacity,       // Lê a capacidade de produção da estação (inteiro)
            	(int*)&stations[num_stations].rice_type,           // Lê o tipo de arroz produzido (convertido de inteiro para enum RiceType)
            	(int*)&stations[num_stations].station_type,        // Lê o tipo da estação (convertido de inteiro para enum StationType)
            	(int*)&stations[num_stations].task_status) != EOF) { // Lê o estado atual da estação (convertido de inteiro para enum TaskStatus)

                // Lê até ao fim do ficheiro

     	num_stations++; // Incrementa o contador de estações
    
    // Verifica se o número de estações lidas atingiu o limite máximo
   	if (num_stations >= MAX_STATIONS) {
       	printf("Limite máximo de estações alcançado (%d).\n", MAX_STATIONS);
       	break;
   	}
   }

   fclose(file); // Fecha o ficheiro após leitura
   printf("\nLeitura do ficheiro concluída. Total de estações lidas: %d\n", num_stations);

   return num_stations; // Retorna o número total de estações lidas

}


// Função para mostrar as estações
void mostrar_estacoes(Estrutura_Station stations[], int num_stations) {

    char tipo_estacao[20];   // Armazena o tipo de estação
    char tipo_arroz[10];     // Armazena o tipo de arroz
    char estado_estacao[15]; // Armazena o estado atual da estação

    // Verifica se existem estações carregadas
	if (num_stations == 0) {
    	printf("Nenhuma estação foi carregada. Por favor, carregue as estações primeiro.\n");
    	return;
	}

    // Imprime o cabeçalho da tabela de estações
	printf("\nLista de Estações:\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("ID | Nome              	| Tipo         	| Localização | Produção | Tipo de Arroz | Estado\n");
	printf("----------------------------------------------------------------------------------------------\n");

	// Percorre o array de estações para exibir os detalhes de cada uma
    for (int i = 0; i < num_stations; i++) {

    	// Determina o tipo da estação
    	if (stations[i].station_type == RICE_PRODUCER) {

            // Copia a string "Produtor de Arroz" para o array tipo_estacao
        	strcpy(tipo_estacao, "Produtor de Arroz");

    	} else if (stations[i].station_type == PALLETIZER) {

            // Copia a string "Paletizador" para o array tipo_estacao
        	strcpy(tipo_estacao, "Paletizador");

    	} else if (stations[i].station_type == CHARGING_STATION) {

            // Copia a string "Carregador" para o array tipo_estacao
        	strcpy(tipo_estacao, "Carregador");

    	} else {

            // Copia a string "Desconhecido" para o array tipo_estacao
        	strcpy(tipo_estacao, "Desconhecido");  // Caso não corresponda a nenhum valor conhecido

    	}

    	// Determina o tipo de arroz
    	if (stations[i].rice_type == JASMINE_RICE) {

            // Copia a string "Jasmine" para o array tipo_arroz
        	strcpy(tipo_arroz, "Jasmine");

    	} else if (stations[i].rice_type == BASMATI_RICE) {

            // Copia a string "Basmati" para o array tipo_arroz
        	strcpy(tipo_arroz, "Basmati");

    	} else if (stations[i].rice_type == SUSHI_RICE) {

            // Copia a string "Sushi" para o array tipo_arroz
        	strcpy(tipo_arroz, "Sushi");

    	} else {

            // Copia a string "Nenhum" para o array tipo_arroz
        	strcpy(tipo_arroz, "Nenhum");  // Caso a estação não produza arroz

    	}

    	// Determina o estado da estação
    	if (stations[i].task_status == PRODUCING) {

            // Copia a string "Produzindo" para o array estado_estacao
        	strcpy(estado_estacao, "Produzindo");

    	} else if (stations[i].task_status == IDLE) {

            // Copia a string "Ocioso" para o array estado_estacao
        	strcpy(estado_estacao, "Ocioso");

    	} else if (stations[i].task_status == PALLETIZING) {

            // Copia a string "Paletizando" para o array estado_estacao
        	strcpy(estado_estacao, "Paletizando");

    	} else {

            // Copia a string "Desconhecido" para o array estado_estacao
        	strcpy(estado_estacao, "Desconhecido");  // Caso não corresponda a nenhum valor conhecido

    	}

    	// Imprime os dados da estação como uma linha da tabela (literalmente um printf)
    	printf("%-3d| %-21s| %-17s| (%d, %d)	| %-8d| %-13s| %-10s\n",
           	stations[i].id,                   // ID único da estação
           	stations[i].name,                 // Nome da estação
           	tipo_estacao,                     // Tipo da estação
           	stations[i].location_x,           // Coordenada X da estação
           	stations[i].location_y,           // Coordenada Y da estação
           	stations[i].production_capacity,  // Capacidade de produção da estação
           	tipo_arroz,                       // Tipo de arroz produzido pela estação
           	estado_estacao);                  // Estado da estação
	}

	printf("---------------------------------------------------------------------------------------------\n"); //Ultima linha da tabela
}


// Função para carregar os obstáculos do ficheiro binário layout.dat
#define MAX_OBSTACULOS 400 // Número máximo de obstáculos permitidos no layout
int carregar_layout(Estrutura_obstaculos obstaculos[]) {
    FILE *file = fopen("layout.dat", "rb"); // Abre o ficheiro em modo binário para leitura
    if (file == NULL) { // Verifica se o ficheiro foi aberto com sucesso
        printf("Erro ao abrir o ficheiro layout.dat\n");
        exit(1); // Encerra o programa se houver erro
    }

    int num_obstaculos;

    // Lê o conteúdo do ficheiro e armazena no array de obstáculos
    num_obstaculos = fread(obstaculos, sizeof(Estrutura_obstaculos), MAX_OBSTACULOS, file);
    fclose(file); // Fecha o ficheiro após a leitura

    printf("\nLeitura do ficheiro layout.dat concluída. Total de obstáculos lidos: %d\n", num_obstaculos);
    return num_obstaculos; // Retorna o número de obstáculos carregados
}

// Função para adicionar um novo obstáculo ao layout
void adicionar_obstaculo(Estrutura_obstaculos obstaculos[], int *num_obstaculos) {
    if (*num_obstaculos >= MAX_OBSTACULOS) { // Verifica se há espaço no array
        printf("Não é possível adicionar mais obstáculos.\n");
        return;
    }

    printf("Introduza as coordenadas do novo obstáculo (x,y): ");
    int x, y;
    scanf("%d,%d", &x, &y); // Lê as coordenadas do novo obstáculo

    obstaculos[*num_obstaculos].type = 3; // Define o tipo como obstáculo
    obstaculos[*num_obstaculos].location_x = x; // Define a coordenada X
    obstaculos[*num_obstaculos].location_y = y; // Define a coordenada Y
    (*num_obstaculos)++; // Incrementa o número total de obstáculos

    printf("Obstáculo adicionado.\n");
}

// Função para remover um obstáculo 
void remover_obstaculo(Estrutura_obstaculos obstaculos[], int *num_obstaculos) {
    printf("Introduza as coordenadas do obstáculo a remover (x,y): ");
    int x, y;
    scanf("%d,%d", &x, &y); // Lê as coordenadas do obstáculo a ser removido

    for (int i = 0; i < *num_obstaculos; i++) {
        // Verifica se as coordenadas correspondem a um obstáculo existente
        if (obstaculos[i].location_x == x && obstaculos[i].location_y == y) {
            // Move todos os obstáculos seguintes uma posição para trás no array
            for (int j = i; j < *num_obstaculos - 1; j++) {
                obstaculos[j] = obstaculos[j + 1];
            }
            (*num_obstaculos)--; // Decrementa o número total de obstáculos
            printf("Obstáculo removido.\n");
            return;
        }
    }

    printf("Obstáculo não encontrado.\n");
}

// Função para salvar o layout atualizado no ficheiro binário layout.dat
void guardar_layout(Estrutura_obstaculos obstaculos[], int num_obstaculos) {
    FILE *file = fopen("layout.dat", "wb"); // Abre o ficheiro em modo binário para escrita
    if (file == NULL) { // Verifica se o ficheiro foi aberto com sucesso
        printf("Erro ao salvar o ficheiro layout.dat\n");
        exit(1); // Encerra o programa em caso de erro
    }

    // Escreve os obstáculos no ficheiro
    fwrite(obstaculos, sizeof(Estrutura_obstaculos), num_obstaculos, file);
    fclose(file); // Fecha o ficheiro após a escrita
    printf("Layout salvo com sucesso.\n");
}

// Função para exibir o mapa da fábrica
void mostrar_mapa(Estrutura_Robots robots[], int num_robots, 
                  Estrutura_Station stations[], int num_stations, 
                  Estrutura_obstaculos obstaculos[], int num_obstaculos) {
    char mapa[20][20]; // Grelha 20x20 para representar o layout

    // Inicializa a grelha com espaços vazios
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            mapa[i][j] = '.'; // Representa espaço vazio
        }
    }

    // Adiciona obstáculos à grelha
    for (int i = 0; i < num_obstaculos; i++) {
        mapa[obstaculos[i].location_y][obstaculos[i].location_x] = '■';
    }

    // Adiciona robots à grelha
    for (int i = 0; i < num_robots; i++) {
        mapa[robots[i].location_y][robots[i].location_x] = 'R';
    }

    // Adiciona estações à grelha
    for (int i = 0; i < num_stations; i++) {
        if (stations[i].station_type == RICE_PRODUCER) {
            mapa[stations[i].location_y][stations[i].location_x] = 'P';
        } else if (stations[i].station_type == PALLETIZER) {
            mapa[stations[i].location_y][stations[i].location_x] = 'L';
        } else if (stations[i].station_type == CHARGING_STATION) {
            mapa[stations[i].location_y][stations[i].location_x] = 'C';
        }
    }

    // Exibe a grelha no terminal
    printf("\nFactory Layout Map (20x20)\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c ", mapa[i][j]); // Imprime o conteúdo de cada célula
        }
        printf("\n");
    }
}



//Função main
int main(){
   Estrutura_Robots robots[MAX_ROBOTS];  	 // Array para armazenar os robots
   Estrutura_Station stations[MAX_STATIONS]; // Array para armazenar as stations
   Estrutura_obstaculos obstaculos[MAX_OBSTACULOS]; // Array para armazenar os obstáculos
   int num_robots = 0;                   	 // Número de robots lidos
   int num_stations = 0;                 	 // Número de estações lidas
   int num_obstaculos = 0;                    // Número de obstáculos lidos
   int opcao;                            	 //Variavel para guardar a opção escolhida no menu
   char menu_return;                         //variavel para voltar ao menu
   char yes_no;                           //Variavel para guardar a resposta do utilizador

   do {
	opcao = menu();                          //Chama o menu pela primeira vez

	//switch case para executar as ações de acordo com a opção escolhida no menu
	switch (opcao){
	case 1: num_robots = carregar_robots(robots); // Carrega os robots
         	mostrar_robots(robots, num_robots);  // Mostra os robots lidos
         	
            //Não mostra o menu novamente até o utilizador pressionar ENTER
            printf("\nPressione ENTER para voltar ao menu: ");
         	menu_return = getchar();
         	getchar();
         	menu_return = 'm';
         	if (menu_return == 'm'){
            	break;
         	}
	case 2: num_stations = carregar_estacoes(stations); // Mostra os stations
         	mostrar_estacoes(stations, num_stations); // Mostra as estações lidas
         	
            //Não mostra o menu novamente até o utilizador pressionar ENTER
            printf("\nPressione ENTER para voltar ao menu: ");
         	menu_return = getchar();
         	getchar();
         	menu_return = 'm';
         	if (menu_return == 'm'){
            	break;
         	}
	case 3: num_obstaculos = carregar_layout(obstaculos); // Carrega o layout com os obstáculos
			
			//Não mostra o menu novamente até o utilizador pressionar ENTER
            printf("\nPressione ENTER para voltar ao menu: ");
         	menu_return = getchar();
         	getchar();
         	menu_return = 'm';
         	if (menu_return == 'm'){
            	break;
         	}
	case 4: printf("\nQuer adicionar um novo obstáculo ao layout? (s/n): ");
	        scanf(" %c", &yes_no);
	        if (yes_no =='s'){
				adicionar_obstaculo(obstaculos, &num_obstaculos); // Adiciona um novo obstáculo ao layout
			}
			
			printf("\nQuer remover um obstáculo do layout? (s/n): ");
			scanf(" %c", &yes_no);
            if (yes_no =='s'){
                remover_obstaculo(obstaculos, &num_obstaculos); // Remove um obstáculo do layout
            }
			else {

                // Não mostra o menu novamente até o utilizador pressionar ENTER
            	printf("\nPressione ENTER para voltar ao menu: ");
            	menu_return = getchar();
         		getchar();
            	menu_return ='m';
            	if (menu_return =='m'){
               		break;
            	}
			}
			guardar_layout(obstaculos, num_obstaculos); // Salva o layout atualizado no ficheiro binário layout.dat

			// Não mostra o menu novamente até o utilizador pressionar ENTER
            printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
         	getchar();
            menu_return ='m';
            if (menu_return =='m'){
            	break;
            }
	case 5: mostrar_mapa(robots, num_robots, stations, num_stations, obstaculos, num_obstaculos); // Mostra o mapa

	        // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 6:  
	        
            // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 7:  

	        // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 8:  

	        // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 9:  

	        // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 10: 

	        // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 11: 

	        // Não mostra o menu novamente até o utilizador pressionar ENTER
			printf("\nPressione ENTER para voltar ao menu: ");
            menu_return = getchar();
            getchar();
            menu_return ='m';
            if (menu_return =='m'){
                break;
            }
	case 12: printf("A sair do programa...\n");
        	 exit(0);
        	 break; // caso a opção seja diferente de 1 a 12, termina o programa com exit(0)

	//não é necessário default porque o if statement que mostra a mensagem de "opção inválida" impede que seja diferente das opçoes possiveis
	}
 } while(opcao != 12); //sair do programa quando a opção for 12 (sair do programa - Sair do Programa)
   
}