/*
 * Graph creator with breadth first search
 * Max Shi
 * 6/1/2022
 */

#include <iostream>

struct Vertex
{
  char label;
  Vertex* next;
};

int main()
{
  Vertex* VertexList[26];
  for(int i = 0; i < 26; i++)
    {
      Vertex* v = new Vertex;
      v->label = '\0';
      v->next = nullptr;
      VertexList[i] = v;
    }
}