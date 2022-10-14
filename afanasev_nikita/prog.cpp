#include <cassert>
#include <unordered_map>
#include <vector>

constexpr int kVerticesCount = 14;

class Graph {
 public:
  using VertexId = int;
  using EdgeId = int;

  void add_vertex() {
    const auto vertex_id = next_vertex_id();
    vertices_.try_emplace(vertex_id, vertex_id);
    adjacency_list_[vertex_id];
  }

  void add_edge(VertexId from_vertex_id, VertexId to_vertex_id) {
    assert(has_vertex(from_vertex_id));
    assert(has_vertex(to_vertex_id));
    assert(!has_edge(from_vertex_id, to_vertex_id));
    const auto edge_id = next_edge_id();
    edges_.emplace_back(edge_id, from_vertex_id, to_vertex_id);
    adjacency_list_[from_vertex_id].push_back(edge_id);
    adjacency_list_[to_vertex_id].push_back(edge_id);
  }

 private:
  VertexId current_vertex_id_ = 0;
  EdgeId current_edge_id_ = 0;

  VertexId next_vertex_id() { return current_vertex_id_++; }

  EdgeId next_edge_id() { return current_edge_id_++; }

  bool has_vertex(VertexId vertex_id) const {
    return vertices_.find(vertex_id) != vertices_.end();
  }

  bool has_edge(VertexId from_vertex_id, VertexId to_vertex_id) const {
    assert(adjacency_list_.find(from_vertex_id) != adjacency_list_.end());
    assert(adjacency_list_.find(to_vertex_id) != adjacency_list_.end());
    const auto& connected_from_edges_ids = adjacency_list_.at(from_vertex_id);
    const auto& connected_to_edges_ids = adjacency_list_.at(to_vertex_id);
    for (auto from_edge_id : connected_from_edges_ids) {
      for (auto to_edge_id : connected_to_edges_ids) {
        if (from_edge_id == to_edge_id) {
          return true;
        }
      }
    }
    return false;
  }

  struct Vertex {
   public:
    explicit Vertex(VertexId id) : id_(id) {}
    VertexId id() const { return id_; }

   private:
    VertexId id_ = 0;
  };

  struct Edge {
   public:
    Edge(EdgeId id, VertexId from_vertex_id, VertexId to_vertex_id)
        : id_(id),
          from_vertex_id_(from_vertex_id),
          to_vertex_id_(to_vertex_id) {}

    EdgeId id() const { return id_; }
    VertexId from_vertex_id() const { return from_vertex_id_; }
    VertexId to_vertex_id() const { return to_vertex_id_; }

   private:
    EdgeId id_ = 0;
    VertexId from_vertex_id_ = 0;
    VertexId to_vertex_id_ = 0;
  };

  std::unordered_map<VertexId, Vertex> vertices_;
  std::vector<Edge> edges_;
  std::unordered_map<VertexId, std::vector<EdgeId>> adjacency_list_;
};

int main() {
  auto graph = Graph();

  for (int i = 0; i < kVerticesCount; i++) {
    graph.add_vertex();
  }

  graph.add_edge(0, 1);
  graph.add_edge(0, 2);
  graph.add_edge(0, 3);
  graph.add_edge(1, 4);
  graph.add_edge(1, 5);
  graph.add_edge(1, 6);
  graph.add_edge(2, 7);
  graph.add_edge(2, 8);
  graph.add_edge(3, 9);
  graph.add_edge(4, 10);
  graph.add_edge(5, 10);
  graph.add_edge(6, 10);
  graph.add_edge(7, 11);
  graph.add_edge(8, 11);
  graph.add_edge(9, 12);
  graph.add_edge(10, 13);
  graph.add_edge(11, 13);
  graph.add_edge(12, 13);

  return 0;
}
