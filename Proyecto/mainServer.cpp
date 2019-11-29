#include "Respuesta.h"
#include "Registro.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <array>
#include <bits/stdc++.h> 

using namespace std; 
  
const int ALPHABET_SIZE = 10;  //0--9

struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - '0'; 
        //printf("%d\n", index);
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 
  
// Returns true if key presents in trie, else 
// false 
bool search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - '0'; 
        //printf("search index: %d\n", index);
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 

int main(){
    struct timeval stamp;
    //Se inicia el servidor
    Respuesta respuesta(7200);
    long int segundos;
    long int usegundos;
    std::cout << "Servidor Iniciado...\n" << std::endl;
    int num[2], aux;
    int* opOperation;
    long int *op;
    mensaje resp;
    int nbd = 0, aux2, id = 0, idAux;   
    char cTimeStamp[11];
    int archivo;
    struct registro reg1, reg2;
    long t, t2;
    string Snumeros;
    int flag = 0;

    vector<string> numeros;
    struct TrieNode *root = getNode(); 
    char temp[11];


    cout << "Esperando...\n" << std::endl;

    archivo = open("registros2.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);

    if( archivo == -1 ) {
        printf("Error no se puede abrir el archivo\n");
    }


    while(1){

        //Recibe la respuesta del cliente
        memcpy(&resp,(respuesta.getRequest()),sizeof(mensaje));
        gettimeofday(&stamp, NULL);
        segundos = static_cast<long int> (stamp.tv_sec);
        usegundos = static_cast<long int>  (stamp.tv_usec);
        segundos += usegundos;        
        //std::cout << "Cliente: \n" <<  "IP:" << inet_ntoa(respuesta.getSocket()->getDirForanea().sin_addr);
        //std::cout << ", Puerto: " << ntohs(respuesta.getSocket()->getDirForanea().sin_port) << "\n" << std::endl;

        memcpy(&idAux,&resp.requestId,sizeof(unsigned int));
        memcpy(&opOperation,&resp.operationId,sizeof(int));
        memcpy(&reg1,&resp.arguments,sizeof(reg1));
        //itoa(segundos, cTimeStamp, 10);
        sprintf(cTimeStamp, "%ld", segundos);
        //printf("%s\n", cTimeStamp);
        memcpy(&reg1.timestamp, &cTimeStamp, sizeof(cTimeStamp));
        //memcpy(&aux2,&resp.arguments,sizeof(reg1));
        // memcpy(&reg1,paqueteRecepcion.obtieneDatos(),sizeof(reg1));
        //printf("Numero registro: %s \t numero atoi: %d\n", reg1.celular, (int) reg1.celular);  

        // if(id == 0){
        //     memcpy(temp,&reg1.celular, sizeof(reg1.celular));
                       
        // }             

        for (int i = 0; i < numeros.size(); i++){
            insert(root, numeros[i]); 
        }

        if(search(root, reg1.celular)){            
            flag = 1;
            segundos = 0;
            printf("Número repetido...\n");
        }else{               
            numeros.push_back(reg1.celular);        
        }
        // if(id == 999){ //Indicar el id 
        //     if(search(root, temp)){            
        //         flag = 1;
        //         segundos = 0;
        //         printf("Número repetido...\n");
        //     }
        // }
        printf("Paquete: %d\n", id);

        if (idAux == id && flag == 0) {            
            write(archivo, &reg1, sizeof(reg1));
            //fsync(archivo);
            printf("Se recibio y se escribio en la BD: \n");
            write(1, &reg1, sizeof(reg1));        
            printf("\n");
            id++;
        }
        //nbd = 1;
        flag = 0;
        op = (&segundos);
        respuesta.sendReply((char*)op);
    }

    close(archivo);
    
    return 0;
}

