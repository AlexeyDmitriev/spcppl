#include <spcppl/graphs/algorithms/dynamicConnectivityOffline.hpp>
#include <gtest/gtest.h>
#include <utility>

TEST(DynamicConnectivityOfflineTest, NoQueriesEmptyResult) {
	DynamicConnectivityTestBuilder test;
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 5), std::vector<Bool>{});
}

TEST(DynamicConnectivityOfflineTest, NoQueriesWithChangingEdgesEmptyResult) {
	DynamicConnectivityTestBuilder test;
	test.addEdge(0, 1);
	test.addEdge(3, 2);
	test.addEdge(0, 1);
	test.removeEdge(3, 2);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 5), std::vector<Bool>{});
}

TEST(DynamicConnectivityOfflineTest, SameVertexIsConnected) {
	DynamicConnectivityTestBuilder test;
	test.addQuery(0, 0);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 2), std::vector<Bool>{true});
}

TEST(DynamicConnectivityOfflineTest, DifferentVertexAreDisconnectedInEmptyGraph) {
	DynamicConnectivityTestBuilder test;
	test.addQuery(0, 1);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 2), std::vector<Bool>{false});
}

TEST(DynamicConnectivityOfflineTest, AddingEdgeConnectsVertices) {
	DynamicConnectivityTestBuilder test;
	test.addQuery(0, 1);
	test.addEdge(0, 1);
	test.addQuery(0, 1);
	test.removeEdge(0, 1);
	test.addQuery(0, 1);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 2), (std::vector<Bool>{false, true, false}));
}

TEST(DynamicConnectivityOfflineTest, ComponentsAreTransitive) {
	DynamicConnectivityTestBuilder test;
	test.addEdge(0, 1);
	test.addEdge(1, 2);
	test.addQuery(0, 2);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 3), (std::vector<Bool>{true}));
}

TEST(DynamicConnectivityOfflineTest, UnrelatedEdgeDoNotConnect) {
	DynamicConnectivityTestBuilder test;
	test.addEdge(0, 1);
	test.addEdge(2, 3);
	test.addQuery(0, 2);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 4), (std::vector<Bool>{false}));
}

TEST(DynamicConnectivityOfflineTest, MayRemoveEdgeWithWrongOrder) {
	DynamicConnectivityTestBuilder test;
	test.addQuery(0, 1);
	test.addEdge(0, 1);
	test.addQuery(0, 1);
	test.removeEdge(1, 0);
	test.addQuery(0, 1);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 2), (std::vector<Bool>{false, true, false}));
}

TEST(DynamicConnectivityOfflineTest, CanAddSeveralPathAndRemoveBack) {
	DynamicConnectivityTestBuilder test;
	test.addEdge(0, 1);
	test.addEdge(1, 2);
	test.addQuery(0, 2);
	test.addEdge(0, 3);
	test.addEdge(3, 2);
	test.addQuery(0, 2);
	test.removeEdge(3, 2);
	test.addQuery(0, 2);
	test.removeEdge(0, 1);
	test.addQuery(0, 2);
	test.addEdge(1, 3);
	test.addQuery(0, 2);
	ASSERT_EQ(dynamicConnectivity(std::move(test).build(), 4), (std::vector<Bool>{true, true, true, false, true}));
}
