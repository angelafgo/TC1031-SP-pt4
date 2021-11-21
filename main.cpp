/*
El presente programa tiene como propósito hacer la implementación de grafos, 
con la oportunidad de tener distintas formas para llegar al resultado deseado, en este caso se hizo el uso de mapas "#include <unordered_map>,
para que al momento de ingresar primero el número de Puertos y después el número de conexiones, consecutivamente ingresar los nombres de los puertos y por ende las conexiones que tienen entre sí,
de la cual usando la función "void loadGraph()"  Se crea un mapa sin orden que guarda datos con el nombre del puerto y el indice basado en el orden en que entran, 
para que con ello se tenga el índice del puerto más adelante y guardarlo en la lista de adyacencias,
y utilizando la función DFS adecuada para la situación problema.
Lo ultimo por ingresar sea consultar 2 puertos con respecto a sus conexiones. 
Para que la salida que se desplegará sea que por cada consulta, 
muestra una sola línea que indica el número de caso de prueba (numerados secuencialmente desde uno), 
el número de puertos a los cuales no se puede llegar, y el nombre del puerto inicial, asi como el valor inicial de numero de conexiones.
*/

// Integrantes (Equipo 12) :
// Daniel Evaristo Escalera Bonilla - A00831289
// José Arnoldo Rositas Salinas - A00829760
// Ángela Felicia Guajardo Olveda - A00829821

// SP TC1031
// 16 Nov 2021

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

// Complejidad: O(n)
void loadGraph(int n,int m, unordered_map<string,int> & mapaPuertos, vector<vector<int>> & listAdj){
    // Se crea un mapa sin orden que guarda datos con el nombre del puerto y el indice basado en el orden en que entran
    // Esto se hizo para poder obtener el índice del puerto más adelante y guardarlo en la lista de adyacencias
    string puerto;

    // Se guardan los puertos en el mapa desde el cual podremos acceder a su índice
    for(int i = 0; i < n; i++){
        cin >> puerto;
        mapaPuertos.insert({puerto,i});
    }

    string a,b;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        // La función at busca por la llave, que en este caso es el nombre del puerto, el índice del puerto
        listAdj[mapaPuertos.at(a)].push_back(mapaPuertos.at(b));
        listAdj[mapaPuertos.at(b)].push_back(mapaPuertos.at(a));
    }

}

// Complejidad: O(|V| + |E|)
int DFS(int n, vector<vector<int>> & listAdj, unordered_map<string,int> & mapaPuertos, string puertoInicial, int MNP){
    stack<int> pila1, pila2;
    int dato;
    vector<bool> status(listAdj.size(), false);
    int cantVisitados = 0;

    // Buscamos el índice del puerto incial y lo garudamos en una pila
    pila1.push(mapaPuertos.at(puertoInicial));

    // Este ciclo mete los indices de los puertos adyacentes a una pila en otra
    // Detectando cuando se necesita otro movimiento para alcanzar los siguentes puertos o en otras palabras, un cambio de nivel
    // Se ejecuta un útlimo ciclo para visitar los úlitmos nodos y añadirlos a la cuenta de nodos visitados, para restarla al final de la cuenta de nodos
    while (MNP >= 0 && cantVisitados != listAdj.size()){
        if(MNP >= 0){
            while (!pila1.empty()){
                dato = pila1.top();
                pila1.pop();
                if(!status[dato]){
                    status[dato] = true;
                    cantVisitados++;
                    for(int j = listAdj[dato].size()-1; j >= 0; j--){
                        if(!status[listAdj[dato][j]]){
                            pila2.push(listAdj[dato][j]);
                        }
                    }
                }
            }
            MNP--;
        }    
        if(MNP >= 0){
            while (!pila2.empty()){
                dato = pila2.top();
                pila2.pop();
                if(!status[dato]){
                    status[dato] = true;
                    cantVisitados++;
                    for(int j = listAdj[dato].size()-1; j >= 0; j--){
                        if(!status[listAdj[dato][j]]){
                            pila1.push(listAdj[dato][j]);
                        }
                    }
                }
            }    
            MNP--;
        }
    }

    // Se regresa la cantidad de nodos no visitados
    return n - cantVisitados;
}

int main() {
    int n, m, MNP, na, consultas;
    string puertoInicial;
    cin >> n >> m;
    unordered_map<string,int> mapaPuertos;
    vector<vector<int>> listAdj(n);
    loadGraph(n, m,mapaPuertos, listAdj);

    cin >> consultas;

    for(int i = 0; i < consultas; i++){
        cin >> puertoInicial >> MNP;
        na = DFS(n, listAdj, mapaPuertos, puertoInicial, MNP);
        cout << "Case " << i+1 << ": " << na << " ports not reachable from port " << puertoInicial << " with MNP = " << MNP << endl;
    }

    return 0;
}

/*
    Prueba 1:

    13 16
    Haikou    
    Yantai    
    Fuzhou    
    Alejandria
    Balboa    
    Busan     
    Taipei    
    Karachi   
    London    
    Ambarli   
    Zhuhai    
    Singapore 
    Merin     

    Haikou Yantai
    Haikou Balboa
    Yantai Busan
    Yantai Fuzhou
    Busan Taipei
    Fuzhou Taipei
    Fuzhou Alejandria
    Alejandria Karachi
    Karachi London
    London Ambarli
    Ambarli Zhuhai
    Zhuhai Taipei
    Zhuhai Singapore
    Singapore Busan
    Singapore Merin
    Merin Balboa

    2
    Ambarli 2
    Case 1: 7 ports not reachable from port Ambarli with MNP = 2
    Busan 2
    Case 2: 5 ports not reachable from port Busan with MNP = 2
    -------------------------------------------------------------

    Prueba 2:

    10 9
	Biblio
	Cedes
	Ciap
	Canchas
	Aulas1
	Aulas2
	Aulas3
	Aulas4
	E1
	E6
	
	Biblio Aulas1
	Biblio Aulas3
	Aulas1 E6
	Aulas1 Aulas2
	Aulas2 Ciap
	Ciap Cedes
	Cedes Canchas
	Aulas3 Aulas4
	Aulas4 E1

    2
    Biblio 2
    Case 1: 4 ports not reachable from port Biblio with MNP = 2
    Ciap 3
    Case 2: 3 ports not reachable from port Ciap with MNP = 3
    -------------------------------------------------------------


    Prueba 3:

    10 11
	Biblio
	Cedes
	Ciap
	Canchas
	Aulas1
	Aulas2
	Aulas3
	Aulas4
	E1
	E6
	
	Biblio Aulas1
	Biblio Aulas3
	Aulas1 E6
	Aulas1 Aulas2
	Aulas2 Ciap
	Ciap Cedes
	Cedes Canchas
	Aulas3 Aulas4
	Aulas4 E1
	E6 E1
	E6 Canchas

    2
    Biblio 4
    Case 1: 0 ports not reachable from port Biblio with MNP = 4
    Ciap 3
    Case 2: 3 ports not reachable from port Ciap with MNP = 3
    -------------------------------------------------------------

*/
