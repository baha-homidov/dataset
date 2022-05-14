#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

//--------------------------------------------------------------------------------
namespace ds{
template <typename Elem>
class graph
{
public:
    class Edge;
    class Vertex;
    void add_vertex(Vertex new_vertex);
    Vertex get_vertex(int vid);
    bool if_vertex_exist(int ID);
    bool if_edge_exist(int from_vertex, int to_vertex);
    void add_edge_by_id(int from_vertex, int to_vertex, int weight);
    void update_edge_by_id(int from_vertex, int to_vertex, int new_weight);
    void delete_edge_by_id(int from_vertex, int to_vertex);
    void delete_vertex_by_id(int vid);
    void update_vertex(int id, Elem new_elem);
    void get_all_neighbors(int ID);
    void print_graph();
    void demo_app();//menu driven demo app to show ds::graph's functionality

private:
    std::vector<Vertex> vertices;
};
//*******************************************************************************
// graph::Vertex Definition
//*******************************************************************************

template <typename Elem>
class graph<Elem>::Vertex
{
private:
    int city_ID;
    Elem elem;

public:
    std::list<Edge> edge_list;
    Vertex() : city_ID{0}, elem{} {}
    Vertex(int ID, Elem n_elem) : city_ID{ID}, elem{n_elem} {}

    int get_id() { return city_ID; }
    Elem get_elem() { return elem; }
    void set_id(int ID) { city_ID = ID; }
    void set_elem(Elem new_elem) { elem = new_elem; }
    std::list<Edge> get_edge_list() { return edge_list; }

    void print_edge_list()
    {
        std::cout << "[";
        for (auto it = edge_list.begin(); it != edge_list.end(); it++)
        {
            std::cout << it->get_destinaion_vertex_ID() << "(" << it->get_weight() << ") --> ";
        }
        std::cout << "]";
        std::cout << '\n';
    }
};
//*******************************************************************************
// graph::Edge definition
//*******************************************************************************

template <typename Elem>
class graph<Elem>::Edge
{
private:
    int destination_vertex_ID;
    int weight;

public:
    Edge() : destination_vertex_ID{0}, weight{0} {}
    Edge(int destVID, int w) : destination_vertex_ID{destVID}, weight{w} {}

    void set_values(int destVID, int w)
    {
        destination_vertex_ID = destVID;
        weight = w;
    }
    void set_weight(int w) { weight = w; }
    int get_destinaion_vertex_ID() { return destination_vertex_ID; }
    int get_weight() { return weight; }
};
//*******************************************************************************

//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::add_vertex(graph<Elem>::Vertex new_vertex)
{
    bool check = if_vertex_exist(new_vertex.get_id());

    if (check == true)
    {
        std::cout << "Vertex with this ID already exists\n";
    }
    else
    {
        vertices.push_back(new_vertex);
        std::cout << "New Vertex Added Successfully" << std::endl;
    }
}

//--------------------------------------------------------------------------------

template <typename Elem>
typename graph<Elem>::Vertex graph<Elem>::get_vertex(int vid)

{
    Vertex temp;
    for (int i = 0; i < vertices.size(); i++)
    {
        temp = vertices.at(i);
        if (temp.get_id() == vid)
        {
            return temp;
        }
    }
    return temp;
}

//--------------------------------------------------------------------------------
template <typename Elem>
bool graph<Elem>::if_vertex_exist(int ID)
{
    bool flag = false;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.at(i).get_id() == ID)
            return true;
    }
    return false;
}

//--------------------------------------------------------------------------------

template <typename Elem>
bool graph<Elem>::if_edge_exist(int from_vertex, int to_vertex)
{
    Vertex v = get_vertex(from_vertex);
    std::list<Edge> e;
    e = v.get_edge_list();

    for (auto it = e.begin(); it != e.end(); it++)
    {
        if (it->get_destinaion_vertex_ID() == to_vertex)
            return true;
    }
    return false;
}

//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::add_edge_by_id(int from_vertex, int to_vertex, int weight)
{
    bool check1 = if_vertex_exist(from_vertex);
    bool check2 = if_vertex_exist(to_vertex);
    if (check1 && check2)
    {
        bool check3 = if_edge_exist(from_vertex, to_vertex);
        if (check3)
            std::cout << "Edge between " << get_vertex(from_vertex).get_elem() << "( "
                      << from_vertex << "(" << to_vertex << ") already exists\n";
        else
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).get_id() == from_vertex)
                    vertices.at(i).edge_list.push_back(Edge(to_vertex, weight));
                else if (vertices.at(i).get_id() == to_vertex)
                    vertices.at(i).edge_list.push_back(Edge(from_vertex, weight));
            }
            std::cout << "Edge between " << from_vertex << " and " << to_vertex << " has been added\n";
        }
    }
    else
        std::cout << "Invalid Vertex ID entered\n";
}

//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::update_edge_by_id(int from_vertex, int to_vertex, int new_weight)
{
    bool check = if_edge_exist(from_vertex, to_vertex);
    if (check == true)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_id() == from_vertex)
            {
                for (auto it = vertices.at(i).edge_list.begin(); it != vertices.at(i).edge_list.end(); it++)
                {
                    if (it->get_destinaion_vertex_ID() == to_vertex)
                    {
                        it->set_weight(new_weight);
                        break;
                    }
                }
            }
            else if (vertices.at(i).get_id() == to_vertex)
            {
                for (auto it = vertices.at(i).edge_list.begin(); it != vertices.at(i).edge_list.end(); it++)
                {
                    if (it->get_destinaion_vertex_ID() == from_vertex)
                    {
                        it->set_weight(new_weight);
                        break;
                    }
                }
            }
        }
        std::cout << "Edge Weight Updated Successfully\n";
    }
    else
        std::cout << "Edge between " << get_vertex(from_vertex).get_elem() << "(" << from_vertex << ") and " << get_vertex(to_vertex).get_elem() << "(" << to_vertex << ") doesn't exist.\n";
}
//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::delete_edge_by_id(int from_vertex, int to_vertex)

{
    bool check = if_edge_exist(from_vertex, to_vertex);
    if (check)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_id() == from_vertex)
            {
                for (auto it = vertices.at(i).edge_list.begin(); it != vertices.at(i).edge_list.end(); it++)
                {
                    if (it->get_destinaion_vertex_ID() == to_vertex)
                    {
                        vertices.at(i).edge_list.erase(it);
                        break;
                    }
                }
            }
            if (vertices.at(i).get_id() == to_vertex)
            {
                for (auto it = vertices.at(i).edge_list.begin(); it != vertices.at(i).edge_list.end(); it++)
                {
                    if (it->get_destinaion_vertex_ID() == from_vertex)
                    {
                        vertices.at(i).edge_list.erase(it);
                        break;
                    }
                }
            }
        }
        std::cout << "Edge Deleted Successfully\n";
    }
    else
        std::cout << "Edge between " << get_vertex(from_vertex).get_elem() << "(" << from_vertex << ") and " << get_vertex(to_vertex).get_elem() << "(" << to_vertex << ") doesn't exist.\n";
}

//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::delete_vertex_by_id(int vid)
{
    int v_index = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.at(i).get_id() == vid)
        {
            v_index = i;
            break;
        }
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        for (auto it = vertices.at(i).edge_list.begin(); it != vertices.at(i).edge_list.end(); it++)
        {
            if (it->get_destinaion_vertex_ID() == vid)
            {
                vertices.at(i).edge_list.erase(it);
                break;
            }
        }
    }

    vertices.erase(vertices.begin() + v_index);
    std::cout << "Vertex Deleted Successfully\n";
}

//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::update_vertex(int id, Elem new_elem)
{
    bool check = if_vertex_exist(id);

    if (check)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_id() == id)
            {
                vertices.at(i).set_elem(new_elem);
                break;
            }
        }
        std::cout << "Vertex(City) name updated successfully\n";
    }
    else
    {
        std::cout << "Vertex doesn't exist\n";
    }
}
//--------------------------------------------------------------------------------
template <typename Elem>
void graph<Elem>::get_all_neighbors(int ID)
{
    std::cout << get_vertex(ID).get_elem() << " (" << get_vertex(ID).get_id() << ") --> ";
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.at(i).get_id() == ID)
        {
            std::cout << "[";
            for (auto it = vertices.at(i).edge_list.begin(); it != vertices.at(i).edge_list.end(); it++)
            {
                std::cout << it->get_destinaion_vertex_ID() << "(" << it->get_weight() << ") --> ";
            }
            std::cout << "]";
        }
    }
}
//--------------------------------------------------------------------------------

template <typename Elem>
void graph<Elem>::print_graph()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        Vertex temp;
        temp = vertices.at(i);
        std::cout << temp.get_elem() << " ("
                  << temp.get_id() << ") --> ";
        temp.print_edge_list();
    }
}
//--------------------------------------------------------------------------------
using namespace std;
template <typename Elem>
void ds::graph<Elem>::demo_app()
{
    
    int option;
    bool check;
    std::string city_name;
    int city_ID, id1, id2, weight;
    ds::graph<std::string> g;
    ds::graph<std::string>::Vertex v1;

    while (true)
    {

      cout << "What operation do you want to perform? "
           << " Select Option number. Enter 0 to exit." << endl;
      cout << "1. Add Vertex" << endl;
      cout << "2. Update Vertex" << endl;
      cout << "3. Delete Vertex" << endl;
      cout << "4. Add Edge" << endl;
      cout << "5. Update Edge" << endl;
      cout << "6. Delete Edge" << endl;
      cout << "7. Check if 2 Vertices are Neigbors" << endl;
      cout << "8. Print All Neigbors of a Vertex" << endl;
      cout << "9. Print graph" << endl;
      cout << "0. Exit Program" << endl;

      cin >> option;

      switch (option)
      {
      case 0:
        return;
        break;

      case 1:
        cout << "Add Vertex Operation -" << endl;
        cout << "Enter City ID: ";
        cin >> city_ID;
        cout << "Enter City Name: ";
        cin.ignore();
        getline(cin, city_name);
        v1.set_id(city_ID);
        v1.set_elem(city_name);
        g.add_vertex(v1);
        break;

      case 2:
        cout << "Update Vertex Operation -" << endl;
        cout << "Enter City ID to update: ";
        cin >> id1;
        cout << "Enter City Name: ";
        cin.ignore();

        std::getline(cin, city_name);
        g.update_vertex(id1, city_name);
        break;

      case 3:
        cout << "Delete Vertex Operation -" << endl;
        cout << "Enter ID of Vertex(City) to Delete: ";
        cin >> id1;
        g.delete_vertex_by_id(id1);
        break;

      case 4:
        cout << "Add Edge Operation -" << endl;
        cout << "Enter ID of Source Vertex(Cit): ";
        cin >> id1;
        cout << "Enter ID of destination Vertex(City): ";
        cin >> id2;
        cout << "Enter Weight of the Edge: ";
        cin >> weight;
        g.add_edge_by_id(id1, id2, weight);

        break;

      case 5:
        cout << "Update Edge Operation -" << endl;
        cout << "Enter ID of the source vertex(city): ";
        cin >> id1;
        cout << "Enter ID of the destination vertex(city): ";
        cin >> id2;
        cout << "Enter UPDATED weight of the edge: ";
        cin >> weight;
        g.update_edge_by_id(id1, id2, weight);
        break;

      case 6:
        cout << "Delete Edge Operation -" << endl;
        cout << "Update Edge Operation -" << endl;
        cout << "Enter ID of the source vertex(city): ";
        cin >> id1;
        cout << "Enter ID of the destination vertex(city): ";
        cin >> id2;
        g.delete_edge_by_id(id1, id2);

        break;

      case 7:
        cout << "Check if 2 Vertices are Neigbors -" << endl;
        cout << "Enter ID of Source Vertex(City): ";
        cin >> id1;
        cout << "Enter ID of Source Vertex(City): ";
        cin >> id2;
        check = g.if_edge_exist(id1, id2);
        if (check)
          cout << "Vertices are neighbors(Edge exists)\n";
        else
          cout << "Vertices are not neighbors(Edge doesn't exist)\n";

          break;

      case 8:
        cout << "Print All Neigbors of a Vertex -" << endl;
        cout<<"Enter ID of a vertex(city) to fetch all neighbors : ";
        cin >> id1;
        g.get_all_neighbors(id1);
        break;

      case 9:
        cout << "Print graph Operation -" << endl;
        g.print_graph();
        break;

      default:
        cout << "Enter Proper Option number " << endl;
      }
      cout << endl;
    }

}


//*******************************************************************************
//*******************************************************************************
}