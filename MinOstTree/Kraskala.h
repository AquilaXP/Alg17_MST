#pragma once

#include <set>

#include "Edge.h"
#include "Graph.h"

class ComparatorEdge
{
public:
    bool operator () ( const EdgeW& edge1, const EdgeW& edge2 ) const
    {
        return std::make_tuple(edge1.w,edge1.v1,edge1.v2) < std::make_tuple( edge2.w, edge2.v1, edge2.v2 );
    }
};

bool Kraskala( Graph5& graph, IArray< Edge >& edges )
{
    // Формируем отсортированные грани, для простоты обхода
    std::set< EdgeW, ComparatorEdge > allEdge;
    for( size_t i = 0; i < graph.size(); ++i )
    {
        for( size_t j = 0; j < graph[i].size(); ++j )
        {
            EdgeW edge;
            auto& e = graph[i][j];
            if( i > e.v )
            {
                edge = { e.v, i, e.w };
            }
            else
            {
                edge = { i, e.v, e.w };
            }
            allEdge.insert( edge );
        }
    }


    std::vector< std::vector< bool > > trees;
    while( edges.size() != graph.size() - 1 )
    {
        if( allEdge.empty() )
            return false;

        auto& e = *allEdge.begin();
        size_t otherTree = graph.size();
        size_t i = 0;
        // Учли мы текущее ребро
        bool takeStockEdge = false;
        for( auto& t : trees )
        {
            // В дереве есть обе вершины, значит будет цикл
            if( t[e.v1] == true && t[e.v2] == true )
            {
                takeStockEdge = true;
                break;
            }
            // Разные вершины, запомним, мб соединен с другим деревом
            else if( t[e.v1] != t[e.v2] )
            {
                if( otherTree != graph.size() )
                {
                    // Сливаем дерево в одно и удаляем последнее
                    for( size_t j = 0; j < graph.size(); ++j )
                    {
                        trees[otherTree][j] = trees[otherTree][j] || t[j];
                    }
                    trees.erase( trees.begin() + i );
                    otherTree = graph.size();
                    edges.add( std::make_pair( e.v1, e.v2 ) );
                    takeStockEdge = true;
                    break;
                }
                else
                {
                    otherTree = i;
                }
            }
            ++i;
        }

        // Ребро является часть одного дерева
        if( otherTree != graph.size() )
        {
            trees[otherTree][e.v1] = true;
            trees[otherTree][e.v2] = true;
            edges.add( std::make_pair( e.v1, e.v2 ) );
        }
        // Ребро образует новое дерево
        else if( takeStockEdge == false )
        {
            trees.push_back( std::vector<bool>( (size_t)graph.size() ) );
            trees.back()[e.v1] = true;
            trees.back()[e.v2] = true;
            edges.add( std::make_pair( e.v1, e.v2 ) );
        }
        allEdge.erase( e );
    }

    return true;
}

class UF
{
public:
    UF( size_t size )
    {
        m_data.resize( size, size );
    }
    bool add( const EdgeW& edge )
    {
        if( root( edge.v1 ) == invalid() && root( edge.v2 ) == invalid() )
        {
            // Создаем дерево
            auto curRoot = ( std::min )( edge.v1, edge.v2 );
            m_data[edge.v1] = curRoot;
            m_data[edge.v2] = curRoot;
            return true;
        }
        else if( root( edge.v1 ) != invalid() && root( edge.v2 ) != invalid() )
        {
            // Присутсвует в одном дереве
            if( root( edge.v1 ) == root( edge.v2 ) )
                return false;
            else
                // в разных, мержим
                merge( root(edge.v1), root(edge.v2) );
        }
        else
        {
            // добавляем в одно из деревьев и, если надо, меняем рут
            if( root( edge.v1 ) == invalid() )
            {
                m_data[edge.v1] = root( edge.v2 );
                if( edge.v1 < root( edge.v2 ) )
                {
                    changeRoot( root( edge.v2 ), edge.v1 );
                }
            }
            else
            {
                m_data[edge.v2] = root( edge.v1 );
                if( edge.v2 < root( edge.v1 ) )
                {
                    changeRoot( root( edge.v1 ), edge.v2 );
                }
            }
        }

        return true;
    }
    size_t root( size_t v ) const
    {
        return m_data[v];
    }
private:
    void merge( size_t root1, size_t root2 )
    {
        size_t oldRoot;
        size_t newRoot;
        if( root1 > root2 )
        {
            oldRoot = root1;
            newRoot = root2;
        }
        else
        {
            oldRoot = root2;
            newRoot = root1;
        }
        changeRoot( oldRoot, newRoot );
    }
    void changeRoot( size_t oldRoot, size_t newRoot )
    {
        for( auto& v : m_data )
            if( v == oldRoot )
                v = newRoot;
    }
    size_t invalid() const
    {
        return m_data.size();
    }
    std::vector< size_t > m_data;
};

bool Kraskala2( Graph5& graph, IArray< Edge >& edges )
{
    // Формируем отсортированные грани, для простоты обхода
    std::set< EdgeW, ComparatorEdge > allEdge;
    for( size_t i = 0; i < graph.size(); ++i )
    {
        for( size_t j = 0; j < graph[i].size(); ++j )
        {
            EdgeW edge;
            auto& e = graph[i][j];
            if( i > e.v )
            {
                edge = { e.v, i, e.w };
            }
            else
            {
                edge = { i, e.v, e.w };
            }
            allEdge.insert( edge );
        }
    }

    UF uf( graph.size() );
    while( edges.size() != graph.size() - 1 )
    {
        if( allEdge.empty() )
            return false;

        auto& e = *allEdge.begin();

        // Если добавить смогли, то учитываем
        if( uf.add( e ) == true )
        {
            edges.add( std::make_pair( e.v1, e.v2 ) );
        }
        allEdge.erase( e );
    }

    return true;
}
