#pragma once

#include <iostream>

#include "Graph.h"
#include "Edge.h"


bool Prima( Graph5& graph, IArray< Edge >& edges )
{
    // Ищем вершину с минимальным ребром
    int32_t minW = ( std::numeric_limits<int32_t>::max )( );
    size_t minV = 0;
    for( size_t i = 0; i < graph.size(); ++i )
    {
        for( size_t r = 0; r < graph[i].size(); ++r )
        {
            if( graph[i][r].w < minW )
            {
                minV = i;
                minW = graph[i][r].w;
            }
        }
    }

    VectorArray< size_t > useNode( graph.size() );
    useNode.add( minV );

    // данный массив нужен, чтобы не искать в useNode
    VectorArray< bool > used( graph.size() );
    for( size_t i = 0; i < graph.size(); ++i )
        used.add( false );
    used[minV] = true;

    // Идем пока не включим все вершины
    while( useNode.size() != graph.size() )
    {
        size_t v1 = graph.size();
        size_t v2 = graph.size();
        minW = ( std::numeric_limits<int32_t>::max )( );
        for( size_t i = 0; i < useNode.size(); ++i )
        {
            auto v = useNode[i];
            for( size_t s = 0; s < graph[i].size(); ++s )
            {
                auto w = graph[v][s].w;
                // Ребро меньше по весу и при этом оно не является ребром между двумя включеными вершинами
                if( w < minW && used[v] != used[graph[v][s].v] )
                {
                    minW = graph[v][s].w;
                    v1 = v;
                    v2 = graph[v][s].v;
                }
            }
        }

        if( v1 == v2 )
            return false;
        // Нашли грань, добавляем
        edges.add( std::make_pair( v1, v2 ) );
        // Добавляем новую вершину
        useNode.add( v2 );
        used[v2] = true;
    }

    return true;
}
