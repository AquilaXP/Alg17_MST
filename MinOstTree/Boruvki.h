#pragma once

#include <set>
#include <tuple>

#include "Graph.h"
#include "Edge.h"

// Для union-find
// Дерево хранит вершины и все ребра, которые связывают данное дерево с другими
// внутриние ребра удаляются во время мержа деревьев
//
// Корнем является наименьшая из вершин
//
// При формировании ребер, первая вершина в ребре всегда меньше второй.
// Необходимо для упрощения выбора ребер с одинаковым весом. Берем с меньшим значением первой вершины.
class Subtree
{
public:
    Subtree() = default;
    Subtree( Graph5& graph, size_t v )
    {
        m_vertex.insert( v );
        for( size_t i = 0; i < graph[v].size(); ++i )
        {
            auto& v2 = graph[v][i];
            if( v2.v < v )
            {
                m_edges.insert( { v2.v, v, v2.w } );
            }
            else
            {
                m_edges.insert( { v, v2.v, v2.w } );
            }
        }
    }
    size_t root() const
    {
        return *( m_vertex.begin() );
    }
    std::set< EdgeW >::iterator begin()
    {
        return m_edges.begin();
    }
    std::set< EdgeW >::iterator end()
    {
        return m_edges.end();
    }
    void merge( Subtree& other )
    {
        for( auto& e : other.m_edges )
        {
            // Данное ребро имеется в обоих деревьях, значит надо выкинуть из текущего
            if( auto existsEdge = m_edges.find( e ); existsEdge != m_edges.end() )
            {
                m_edges.erase( existsEdge );
            }
            else
            {
                m_edges.insert( e );
            }
        }
        for( auto& v : other.m_vertex )
        {
            m_vertex.insert( v );
        }
    }
private:
    std::set< size_t > m_vertex;
    std::set< EdgeW > m_edges;
};

bool Boruvki( Graph5& graph, IArray< Edge >& edges )
{
    VectorArray< Subtree* > subtree( graph.size() );
    for( size_t i = 0; i < graph.size(); ++i )
        subtree.add( new Subtree( graph, i ) );

    VectorArray< Edge > candidateMerge( graph.size() );
    bool change = false;

    // Идем пока не наберем N - 1 ребер
    while( edges.size() != graph.size() - 1 )
    {
        change = false;
        // Обходим все поддеревья
        for( size_t i = 0; i < subtree.size(); ++i )
        {
            EdgeW edge = { 0, 0, (std::numeric_limits<int32_t>::max)() };
            // Ищем лучщее ребро
            for( auto& e : *( subtree[i] ) )
            {
                // В случае если вес одинаковый, берем то у которого первая вершина меньше
                if( edge.w > e.w || ( edge.w == e.w && edge.v1 > e.v1 ) )
                {
                    edge = e;
                }
            }
            candidateMerge.add( std::make_pair( edge.v1, edge.v2 ) );
        }

        // Обходим всех кандидатов на слияние
        for( size_t i = 0; i < candidateMerge.size(); ++i )
        {
            auto& p = candidateMerge[i];
            if( subtree[p.first]->root() != subtree[p.second]->root() )
            {
                subtree[p.first]->merge( *subtree[p.second] );
                // Удаляем смерженное дерево
                delete subtree[p.second];
                // Удаленое дерево указывает на то дерево куда было влито
                // для удобства поиска пар кандидатов на слияние
                subtree[p.second] = subtree[p.first];
                // нашли ребро, сохраняем
                edges.add( p );
                change = true;
            }
        }
        candidateMerge.clear();
        if( change == false )
            return false;
    }

    return true;
}
