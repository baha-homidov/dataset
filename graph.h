#include <iostream>
#include <vector>
#include <list>
#include <iterator>

class Edge
{
public:
    int destination_vertex_ID;
    int weight;
    Edge() : destination_vertex_ID{0}, weight{0} {}
    Edge(int destVID, int w) : destination_vertex_ID{destVID}, weight{w} {}

    void set_values(int destVID, int w)
    {
        destination_vertex_ID = destVID;
        weight = w;
    }

    void set_weight(int w)
    {
        weight = w;
    }

    int get_destinaion_vertex_ID()
    {
        return destination_vertex_ID;
    }

    int get_weight()
    {
        return weight;
    }
};

//--------------------------------------------------------------------------------

class Vertex
{
public:
    int city_ID;
    std::string city_name;

    std::list<Edge> edge_list;
    Vertex() : city_ID{0}, city_name{""} {}
    Vertex(int ID, std::string name) : city_ID{ID}, city_name{name} {}

    int get_city_id()
    {
        return city_ID;
    }

    std::string get_city_name()
    {
        return city_name;
    }

    void set_id(int ID)
    {
        city_ID = ID;
    }

    void set_name(std::string name)
    {
        city_name = name;
    }

    std::list<Edge> get_edge_list()
    {
        return edge_list;
    }

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

//--------------------------------------------------------------------------------

class Graph
{
public:
    std::vector<Vertex> vertices;
    void add_vertex(Vertex new_vertex)
    {
        bool check = if_vertex_exist(new_vertex.get_city_id());

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

    Vertex get_vertex(int vid)
    {
        Vertex temp;
        for (int i = 0; i < vertices.size(); i++)
        {
            temp = vertices.at(i);
            if (temp.get_city_id() == vid)
            {
                return temp;
            }
        }
        return temp;
    }
    //--------------------------------------------------------------------------------
    bool if_vertex_exist(int ID)
    {
        bool flag = false;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_city_id() == ID)
                return true;
        }
        return false;
    }
    //--------------------------------------------------------------------------------
    bool if_edge_exist(int from_vertex, int to_vertex)
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
    void add_edge_by_id(int from_vertex, int to_vertex, int weight)
    {
        bool check1 = if_vertex_exist(from_vertex);
        bool check2 = if_vertex_exist(to_vertex);
        if (check1 && check2)
        {
            bool check3 = if_edge_exist(from_vertex, to_vertex);
            if (check3)
                std::cout << "Edge between " << get_vertex(from_vertex).get_city_name() << "( "
                          << from_vertex << "(" << to_vertex << ") already exists\n";
            else
            {
                for (int i = 0; i < vertices.size(); i++)
                {
                    if (vertices.at(i).get_city_id() == from_vertex)
                        vertices.at(i).edge_list.push_back(Edge(to_vertex, weight));
                    else if (vertices.at(i).get_city_id() == to_vertex)
                        vertices.at(i).edge_list.push_back(Edge(from_vertex, weight));
                }
                std::cout << "Edge between " << from_vertex << " and " << to_vertex << " has been added\n";
            }
        }
        else
            std::cout << "Invalid Vertex ID entered\n";
    }
    //--------------------------------------------------------------------------------
    void print_graph()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            Vertex temp;
            temp = vertices.at(i);
            std::cout << temp.get_city_name() << " ("
                      << temp.get_city_id() << ") --> ";
            temp.print_edge_list();
        }
    }
};