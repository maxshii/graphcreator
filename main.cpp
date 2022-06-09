/*
 * Graph creator with breadth first search
 * Max Shi
 * 6/1/2022
 */

#include <iostream>
#include <cstring>

using namespace::std;

struct Node
{
  char label;
  int weight;
  Node* next;
};
struct Vertex
{
  char label;
  Node* list;
};

void print(Vertex* arr[]);
void addVertex(Vertex* arr[], char label);
void rmVertex(Vertex* arr[], char label);
void addEdge(Vertex* arr[], char label1, char label2);
void rmEdge(Vertex* arr[], char label1, char label2);
void shortestPath(Vertex* arr[], char start, char end);

int main()
{
  Vertex* VertexList[26];

  
  for(int i = 0; i < 26; i++)
    {
    /*  Vertex* v = new Vertex;
      v->label = '\0';
      v->list = NULL;*/
      VertexList[i] = NULL;
    }
  
  addVertex(VertexList, 'A');
  addVertex(VertexList, 'B');
  addVertex(VertexList, 'C');
  addVertex(VertexList, 'D');
  addVertex(VertexList, 'E');
  print(VertexList);
  cout << "Edge AB";
  addEdge(VertexList, 'A', 'B');
    cout << "Edge AC";

  addEdge(VertexList, 'A', 'C');
    cout << "Edge AD";

  addEdge(VertexList, 'A', 'D');
    cout << "Edge AE";

  addEdge(VertexList, 'B', 'E');
    cout << "Edge CD";

  addEdge(VertexList, 'C', 'D');

  shortestPath(VertexList, 'A', 'C');
    shortestPath(VertexList, 'A', 'D');

  print(VertexList);
  cout << "remove A\n";
  rmVertex(VertexList, 'A');
  print(VertexList);
  cout<<"remove edge BE\n";
  rmEdge(VertexList, 'B', 'E');
  print(VertexList);

  
  //std::cout << endl;
  //rmVertex(VertexList, 'A');
/*
  //print(VertexList);
  /*while (true) {
    
    std::cout << "Instructions: Enter a number or file name or addVertex, addEdge, rmVertex, rmEdge, print, or quit\n";
		char input[80];
		cin.getline(input, 80, '\n');

    if(strcmp(input, "rmEdge") == 0)
    {
      char label1;
      char label2;
      std::cout << "Enter first vertex (A-Z): ";
      cin >> label1;
      std::cout << "Enter second vertex: ";
      cin >> label2;
     rmEdge(VertexList, label1, label2);
    }
    else if(strcmp(input, "rmVertex") == 0)
    {
      char label1;

      std::cout << "Enter vertex(A-Z): ";
      cin >> label1;

      rmVertex(VertexList, label1);
    }
    else if(strcmp(input, "addEdge") == 0)
    {
      char label1;
      char label2;
      std::cout << "Enter first vertex(A-Z): ";
      cin >> label1;
      std::cout << "Enter second vertex: ";
      cin >> label2;
      

      addEdge(VertexList, label1, label2);
    }
    
    else if(strcmp(input, "addVertex") == 0)
    {
      char label1;

      std::cout << "Enter vertex(A-Z): ";
      cin >> label1;;
      addVertex(VertexList, label1);
    
    }
    else if(strcmp(input, "print") == 0)
    {
      print(VertexList);
    }
    else if(strcmp(input, "quit") == 0)
    {
      break;
    }

  }*/

}

void print(Vertex* arr[])
{
  for(int i = 0; i < 26; i++)
    {
      if(arr[i] != NULL)
      {
        if(arr[i]->label != '\0')
        {
          std::cout << arr[i]->label << ": ";
          Node* adj = arr[i]->list;
          while(adj != NULL)
          {
            std::cout << adj->label << "(" << adj->weight << ")  ";
            adj = adj->next;
          }
        }
        std::cout << endl;
      }  
    }
}

void addVertex(Vertex* arr[], char label)
{
  if(arr[label-'A'] == NULL)
  {
    Vertex* v = new Vertex;
    v->label = label;
    v->list = NULL;
    //std::cout << label - 'a';
    arr[label-'A'] = v;
  }
  else
  {
    std::cout << "Vector already exists.\n";
  }
}

void rmVertex(Vertex* arr[], char label)
{
  int index = label-'A';
  if(arr[index]->label == label)
  {
    Node* curr = arr[index]->list;
    while(curr != NULL)
    {
      //delete the adja
      rmEdge(arr, label, curr->label);
      curr = arr[index]->list;
    }
    delete arr[index];
    arr[index] = NULL;
  }
  else
  {
    std::cout << label << " not found.\n";
  }
}

void addEdge(Vertex* arr[], char label1, char label2)
{
  int index1 = label1 - 'A';
  int index2 = label2 - 'A';

  if(arr[index1] != NULL && arr[index2] != NULL)
  {
    std::cout << "Enter weight: ";
    int weight = 0;
    cin >> weight;
    cin.clear();

    //add node representing edge from label 1 to label2
    Node* current = arr[index1]->list;
    if(current == NULL)
    {
      Node* n = new Node;
      n->label = label2;
      n->next = NULL;
      n->weight = weight;
      arr[index1]->list = n;
    }
    else
    {
      while(current->next != NULL)
      {
        current = current->next;
      }
      Node* n = new Node;
      n->label = label2;     
      n->next = NULL;
      n->weight = weight;
      current->next = n;
    }

    //add node representing edge from label 2 to label1
    current = arr[index2]->list;
    if(current == NULL)
    {
      Node* n = new Node;
      n->label = label1;
      n->next = NULL;
      n->weight = weight;
      arr[index2]->list = n;
    }
    else
    {
      while(current->next != NULL)
      {
        current = current->next;
      }
      Node* n = new Node;
      n->label = label1;
      n->next = NULL;
      n->weight = weight;
      current->next = n;
    }
  }
}

void rmEdge(Vertex* arr[], char label1, char label2)
{
  int index1 = label1 - 'A';
  int index2 = label2 - 'A';

  if(arr[index1] != NULL && arr[index2] != NULL)
  {
    //delete edges from label 1 to label 2
    Node* head = arr[index1]->list;
    Node* current = head;
    Node* previous = head;
    while(current != NULL)
    {
      if(head == NULL){
        //do nothing
        break;
      }
      else if(head->label == label2)
      {
        head = head->next; //move head to next
        delete arr[index1]->list; //delete old head
        arr[index1]->list = head;
      }
      else if(current == NULL)
      {
        //do nothing
        break;
      }
      else if(current->label == label2)
      {
        previous->next = current->next; //previous connects to what is after current
        delete current;
        current = previous->next;
      }
      else if(current->label != label2)
      {
        //go next
        previous = current;
        current = current->next;
      }
    }

    //delete edges from label 2 to label 1
    head = arr[index2]->list;
    current = head;
    previous = head;
    while(current != NULL)
    {
      if(head == NULL){
        //do nothing
        break;
      }
      else if(head->label == label1)
      {
        head = head->next; //move head to next
        delete arr[index2]->list; //delete old head
        arr[index2]->list = head;
      }
      else if(current == NULL)
      {
        //do nothing
        break;
      }
      else if(current->label == label1)
      {
        previous->next = current->next; //previous connects to what is after current
        delete current;
        current = previous->next;
      }
      else if(current->label != label1)
      {
        //go next
        previous = current;
        current = current->next;
      }
    }
  }
  else
  {
    std::cout << "Invalid vertexes.\n";
  }
}

void shortestPath(Vertex* arr[], char start, char end)
{
  bool unvisited[26]; //char array of unvisited vertexes
  int tentativeDist[26]; //int array with index 0 representing vertex A, index 1 = v B, etc.
  char shortestPaths[26][27];
  const int INFINITE = -1;
  
  for(int i = 0; i < 26; i++)
  {

    if(arr[i] != NULL)
    {
      unvisited[i] = true; //make index of label unvisited
    }
    else
    {
      unvisited[i] = false;
    }
    
    if(start-'A' == i)
    {
      tentativeDist[i] = 0; //start node dist is 0
    }
    else
    {
      tentativeDist[i] = INFINITE;
    }

    for(int z = 0; z < 26; z++)
    {
      shortestPaths[i][z] = '\0';
    }
  }

  int current = start - 'A';
  while(true)
  {
    int cont = 0;
    for(int i = 0; i < 26; i++)
    {
      if(unvisited[i] == true)
      {
        cont++;
      }
    }
    if(cont <= 0)
    {
      break;
    }

    
  Node* currentNode = arr[current]->list; //currentNode represents linked list of vertexes adjacent to current
  while(currentNode != NULL)
  {
    char adjacent = currentNode->label;
    int adjIndex = adjacent-'A';

    //find path and dist from start to current node
    //find dist from current to adjacent
    //replace path and dist if the dist is less than dist in tentativeDist

    /*if(shortestPaths[adjIndex][0] == '\0')
    {
      shortestPaths[adjIndex][0] = adjacent;
      tentativeDist[adjIndex] = currentNode->weight;
    }
    else
    {*/
    if(unvisited[adjIndex] == true)
    {
      if(tentativeDist[current] + currentNode->weight < tentativeDist[adjIndex] || tentativeDist[adjIndex] == INFINITE) //if distance start to current to adjacent is less than tentativeDist to adjacent
      {

        //replace tenativepath to adjacent with path to current to adjacent
        int i = 0;
        while(shortestPaths[current][i] != '\0')
        {
          shortestPaths[adjIndex][i] = shortestPaths[current][i];
          i++;
        }
        shortestPaths[adjIndex][i] = adjacent;
        shortestPaths[adjIndex][i+1] = '\0';

        //replace tenativeDist with distance to current to adjacent
        tentativeDist[adjIndex] = tentativeDist[current] + currentNode->weight;
      }
      }
    //}
    currentNode = currentNode->next;
  }

  
    
    unvisited[current] = false;
    
  

  int smallestTent = INFINITE;
  int next = 0;
  for(int i = 1; i < 26; i++)
  {
    if(smallestTent > tentativeDist[i] || smallestTent == INFINITE )
    {
      if(unvisited[i] == true)
      {
        smallestTent = tentativeDist[i];
        next = i;
      }
    }
  }
//std::cout << next;
    current = next;

    if(unvisited[current] == false || tentativeDist[current] == INFINITE)
    {
      break;
    }
  }

  int inting = 0;
  std::cout << "Shortest Path: " << start;
 while(shortestPaths[end-'A'][inting] != '\0')
 {
  std::cout<< shortestPaths[end-'A'][inting];
  inting++;
 }
  std::cout << ": " << tentativeDist[end-'A'] << endl;
}
