#include "graph.h"
#include "gtest/gtest.h"

TEST( Graph, generic )
{
    {
        auto data = "{0,1,2#1,2#2,2}";
        EXPECT_EQ( data, graph::graph_to_str( graph::graph_from_str( data ) ) );
    }
    {
        auto data = "{}";
        EXPECT_EQ( data, graph::graph_to_str( graph::graph_from_str( data ) ) );
    }
}