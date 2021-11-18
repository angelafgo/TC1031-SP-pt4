// Borrador de programa

/*
El presente programa tiene como propósito...
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
#include <queue>
#include <vector>
// Agregada la librería unordered map para manejar los nodos como números
#include <unordered_map>

using namespace std;

void loadGraph(int n,int m, vector<string> & vectorPuertos, vector<vector<int>> & listAdj){
    // Se crea un mapa sin orden que guarda datos con el nombre del puerto y el indice basado en el orden en que entran
    // Esto se hizo para poder obtener el índice del puerto más adelante y guardarlo en la lista de adyacencias
    unordered_map<string,int> mapaPuertos;
    string puerto;

    // Se guardan los puertos en el mapa y en un vector desde el cual podremos acceder a ellos
    for(int i = 0; i < n; i++){
        cin >> puerto;
        mapaPuertos.insert({puerto,i});
        vectorPuertos.push_back(puerto);
    }

    string a,b;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        // La función at busca por la llave, que en este caso es el nombre del puerto, el índice del puerto
        // Porque siento que se debe cambiar: La complejidad promedio es constante, pero el peor caso es lineal, y en lo que he leído no he podido entender cuando ocurre el peor caso
        listAdj[mapaPuertos.at(a)].push_back(mapaPuertos.at(b));
        listAdj[mapaPuertos.at(b)].push_back(mapaPuertos.at(a));
    }

}

// Complejidad: O(|V| + |E|)
int DFS(int n, vector<vector<int>> & listAdj, vector<string> & vectorPuertos, string puertoInicial, int MNP){
    stack<int> pila1, pila2;
    int dato;
    vector<bool> status(listAdj.size(), false);
    int cantVisitados = 0;

    // Buscamos el índice del puerto incial y lo garudamos en una pila
    for(int i = 0; i < vectorPuertos.size(); i++){
        if(puertoInicial == vectorPuertos[i]){
            pila1.push(i);
        }
    }

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

    return n - cantVisitados;
}

int main() {
    int n, m, MNP, na, consultas;
    string puertoInicial;
    cin >> n >> m;
    vector<string> vectorPuertos;
    vector<vector<int>> listAdj(n);
    loadGraph(n, m,vectorPuertos, listAdj);

    cin >> consultas;

    for(int i = 0; i < consultas; i++){
        cin >> puertoInicial >> MNP;
        na = DFS(n, listAdj, vectorPuertos, puertoInicial, MNP);
        cout << "Case " << i+1 << ": " << na << " ports not reachable from port " << puertoInicial << " with MNP = " << MNP << endl;
    }

    return 0;
}
