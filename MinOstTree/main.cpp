#include "Prima.h"
#include "Boruvki.h"
#include "Kraskala.h"

void testPrima()
{
    /// Из урока, только замена ABCDEFG на 01234567
    Graph5 graph( 7, 5 );

    graph[0].add( { 1, 7 } );
    graph[0].add( { 3, 5 } );

    graph[1].add( { 0, 7 } );
    graph[1].add( { 2, 8 } );
    graph[1].add( { 3, 9 } );
    graph[1].add( { 4, 7 } );

    graph[2].add( { 1, 8 } );
    graph[2].add( { 4, 5 } );

    graph[3].add( { 0, 5 } );
    graph[3].add( { 1, 9 } );
    graph[3].add( { 4, 15 } );
    graph[3].add( { 5, 6 } );

    graph[4].add( { 1, 7 } );
    graph[4].add( { 2, 5 } );
    graph[4].add( { 3, 15 } );
    graph[4].add( { 5, 8 } );
    graph[4].add( { 6, 9 } );

    graph[5].add( { 3, 6 } );
    graph[5].add( { 4, 8 } );
    graph[5].add( { 6, 9 } );

    graph[6].add( { 4, 9 } );
    graph[6].add( { 5, 11 } );

    FactorArray< Edge > edges;
    bool ret = Prima( graph, edges );
    if( ret == false )
        throw std::runtime_error( "incorect working algorithm Prima!" );

    FactorArray< Edge > etalon;
    etalon.add( std::make_pair( 0, 3 ) );
    etalon.add( std::make_pair( 0, 1 ) );
    etalon.add( std::make_pair( 3, 5 ) );
    etalon.add( std::make_pair( 1, 4 ) );
    etalon.add( std::make_pair( 2, 4 ) );
    etalon.add( std::make_pair( 4, 6 ) );

    for( size_t i = 0; i < etalon.size(); ++i )
    {
        bool finded = false;
        for( size_t j = 0; j < edges.size(); ++j )
        {
            if( edges[j] == etalon[i] )
            {
                finded = true;
                break;
            }
            if( std::make_pair( edges[j].second, edges[j].first ) == etalon[i] )
            {
                finded = true;
                break;
            }
        }
        if( finded == false )
            throw std::runtime_error( "incorect working algorithm Prima!" );
    }

    // print
//     for( size_t i = 0; i < edges.size(); ++i )
//     {
//         std::cout << edges[i].first << '-' << edges[i].second << '\n';
//     }
}

void testBoruvki()
{
    /// Из урока, только замена ABCDEFG на 01234567
    Graph5 graph( 7, 5 );

    graph[0].add( { 1, 7 } );
    graph[0].add( { 3, 5 } );

    graph[1].add( { 0, 7 } );
    graph[1].add( { 2, 8 } );
    graph[1].add( { 3, 9 } );
    graph[1].add( { 4, 7 } );

    graph[2].add( { 1, 8 } );
    graph[2].add( { 4, 5 } );

    graph[3].add( { 0, 5 } );
    graph[3].add( { 1, 9 } );
    graph[3].add( { 4, 15 } );
    graph[3].add( { 5, 6 } );

    graph[4].add( { 1, 7 } );
    graph[4].add( { 2, 5 } );
    graph[4].add( { 3, 15 } );
    graph[4].add( { 5, 8 } );
    graph[4].add( { 6, 9 } );

    graph[5].add( { 3, 6 } );
    graph[5].add( { 4, 8 } );
    graph[5].add( { 6, 9 } );

    graph[6].add( { 4, 9 } );
    graph[6].add( { 5, 11 } );

    FactorArray< Edge > edges;
    bool ret = Boruvki( graph, edges );
    if( ret == false )
        throw std::runtime_error( "incorect working algorithm Boruvki!" );

    FactorArray< Edge > etalon;
    etalon.add( std::make_pair( 0, 3 ) );
    etalon.add( std::make_pair( 0, 1 ) );
    etalon.add( std::make_pair( 3, 5 ) );
    etalon.add( std::make_pair( 1, 4 ) );
    etalon.add( std::make_pair( 2, 4 ) );
    etalon.add( std::make_pair( 4, 6 ) );

    // print
//     for( size_t i = 0; i < edges.size(); ++i )
//     {
//         std::cout << edges[i].first << '-' << edges[i].second << '\n';
//     }

    for( size_t i = 0; i < etalon.size(); ++i )
    {
        bool finded = false;
        for( size_t j = 0; j < edges.size(); ++j )
        {
            if( edges[j] == etalon[i] )
            {
                finded = true;
                break;
            }
            if( std::make_pair( edges[j].second, edges[j].first ) == etalon[i] )
            {
                finded = true;
                break;
            }
        }
        if( finded == false )
            throw std::runtime_error( "incorect working algorithm Boruvki!" );
    }
}

void testKraslala()
{
    /// Из урока, только замена ABCDEFG на 01234567
    Graph5 graph( 7, 5 );

    graph[0].add( { 1, 7 } );
    graph[0].add( { 3, 5 } );

    graph[1].add( { 0, 7 } );
    graph[1].add( { 2, 8 } );
    graph[1].add( { 3, 9 } );
    graph[1].add( { 4, 7 } );

    graph[2].add( { 1, 8 } );
    graph[2].add( { 4, 5 } );

    graph[3].add( { 0, 5 } );
    graph[3].add( { 1, 9 } );
    graph[3].add( { 4, 15 } );
    graph[3].add( { 5, 6 } );

    graph[4].add( { 1, 7 } );
    graph[4].add( { 2, 5 } );
    graph[4].add( { 3, 15 } );
    graph[4].add( { 5, 8 } );
    graph[4].add( { 6, 9 } );

    graph[5].add( { 3, 6 } );
    graph[5].add( { 4, 8 } );
    graph[5].add( { 6, 9 } );

    graph[6].add( { 4, 9 } );
    graph[6].add( { 5, 11 } );

    FactorArray< Edge > edges;
    bool ret = Kraskala( graph, edges );
    if( ret == false )
        throw std::runtime_error( "incorect working algorithm Boruvki!" );

    FactorArray< Edge > etalon;
    etalon.add( std::make_pair( 0, 3 ) );
    etalon.add( std::make_pair( 0, 1 ) );
    etalon.add( std::make_pair( 3, 5 ) );
    etalon.add( std::make_pair( 1, 4 ) );
    etalon.add( std::make_pair( 2, 4 ) );
    etalon.add( std::make_pair( 4, 6 ) );

    // print
//     for( size_t i = 0; i < edges.size(); ++i )
//     {
//         std::cout << edges[i].first << '-' << edges[i].second << '\n';
//     }

    for( size_t i = 0; i < etalon.size(); ++i )
    {
        bool finded = false;
        for( size_t j = 0; j < edges.size(); ++j )
        {
            if( edges[j] == etalon[i] )
            {
                finded = true;
                break;
            }
            if( std::make_pair( edges[j].second, edges[j].first ) == etalon[i] )
            {
                finded = true;
                break;
            }
        }
        if( finded == false )
            throw std::runtime_error( "incorect working algorithm Boruvki!" );
    }
}

void testKraslala2()
{
    /// Из урока, только замена ABCDEFG на 01234567
    Graph5 graph( 7, 5 );

    graph[0].add( { 1, 7 } );
    graph[0].add( { 3, 5 } );

    graph[1].add( { 0, 7 } );
    graph[1].add( { 2, 8 } );
    graph[1].add( { 3, 9 } );
    graph[1].add( { 4, 7 } );

    graph[2].add( { 1, 8 } );
    graph[2].add( { 4, 5 } );

    graph[3].add( { 0, 5 } );
    graph[3].add( { 1, 9 } );
    graph[3].add( { 4, 15 } );
    graph[3].add( { 5, 6 } );

    graph[4].add( { 1, 7 } );
    graph[4].add( { 2, 5 } );
    graph[4].add( { 3, 15 } );
    graph[4].add( { 5, 8 } );
    graph[4].add( { 6, 9 } );

    graph[5].add( { 3, 6 } );
    graph[5].add( { 4, 8 } );
    graph[5].add( { 6, 9 } );

    graph[6].add( { 4, 9 } );
    graph[6].add( { 5, 11 } );

    FactorArray< Edge > edges;
    bool ret = Kraskala2( graph, edges );
    if( ret == false )
        throw std::runtime_error( "incorect working algorithm Boruvki!" );

    FactorArray< Edge > etalon;
    etalon.add( std::make_pair( 0, 3 ) );
    etalon.add( std::make_pair( 0, 1 ) );
    etalon.add( std::make_pair( 3, 5 ) );
    etalon.add( std::make_pair( 1, 4 ) );
    etalon.add( std::make_pair( 2, 4 ) );
    etalon.add( std::make_pair( 4, 6 ) );

    // print
    for( size_t i = 0; i < edges.size(); ++i )
    {
        std::cout << edges[i].first << '-' << edges[i].second << '\n';
    }

    for( size_t i = 0; i < etalon.size(); ++i )
    {
        bool finded = false;
        for( size_t j = 0; j < edges.size(); ++j )
        {
            if( edges[j] == etalon[i] )
            {
                finded = true;
                break;
            }
            if( std::make_pair( edges[j].second, edges[j].first ) == etalon[i] )
            {
                finded = true;
                break;
            }
        }
        if( finded == false )
            throw std::runtime_error( "incorect working algorithm Boruvki!" );
    }
}

int main()
{
    try
    {
        testPrima();
        testBoruvki();
        testKraslala();
        // Тестируем Kraslala c Union-Find
        testKraslala2();
    }
    catch( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
