#ifndef GRAPH
#define GRAPH

#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <type_traits>
#include <vector>

namespace graph {

	// struct to represent the vertex of a graph
	template<typename T>
	struct vertex {
		int x{}, y{};
		T value;
		// default constructor
		vertex() {}

		vertex(const int& _x, const int& _y, const T& _v) : x(_x), y(_y), value(_v) {}

		// copy constructor
		vertex(const vertex<T>& other) {
			x = other.x;
			y = other.y;
			value = other.value;
		}

		bool operator<(const vertex<T>& other) const {
			return (x < other.x || (x == other.x && y < other.y));
		}

		bool operator==(const vertex<T>& other) const {
			return (x == other.x && y == other.y && value == other.value);
		}

		bool operator!=(const vertex<T>& other) const {
			return !(*this == other);
		}

		vertex<T>& operator=(const vertex<T>& other) {
			this->x = other.x;
			this->y = other.y;
			this->value = other.value;
			return *this;
		}

		vertex<T>& operator+=(const vertex<T>& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const vertex<T>& v) {
			os << '"' << v.value << "\" (" << v.x << ',' << v.y << ')';
			return os;
		}
	};

	template<typename T>
	struct edge {
		vertex<T> v;
		int w;

		edge() {}

		edge(const vertex<T>& _v, const int& _w) : v(_v), w(_w) {}

		edge(const edge<T>& other) {
			v = other.v;
			w = other.w;
		}

		bool operator<(const edge<T>& other) const {
			return (v < other.v || v == other.v && w < other.w);
		}

		bool operator==(const edge<T>& other) const {
			return (v == other.v && w = other.w);
		}

		friend std::ostream& operator<<(std::ostream& os, const edge<T>& e) {
			os << e.v << '[' << e.w << ']';
			return os;
		}
	};

	// struct representing the result of a search
	template<typename T>
	struct result {
		std::vector<vertex<T>> path;
		// track how many vertices are visited for curiosity purposes
		int vertices_visited{};
	};

	template<class T>
	class unweighted {

	public:
		using value_type = T;
		using vertex_type = vertex<T>;
		using size_type = size_t;
		using container_type = std::set<vertex_type>;
		using graph_type = std::map<vertex_type, container_type>;
		using result_type = result<value_type>;

		unweighted() = default;

		unweighted(const graph_type& _graph) {
			graph = _graph;
		}

		void add_edge(const vertex_type& a, const vertex_type& b) {
			graph[a].insert(b);
		}

		graph_type data() const {
			return graph;
		}

		vertex_type find_vertex(const vertex_type& _vertex) const {
			for (const auto& [v, e] : graph) {
				if (v == _vertex) {
					return v;
				}
			}
			throw std::invalid_argument("Vertex not found in graph");
		}

		vertex_type find_vertex(const value_type& _val) const {
			for (const auto& [v, e] : graph) {
				if (v.value == _val) {
					return v;
				}
			}
			throw std::invalid_argument("Vertex not found in graph");
		}

		template<class _cont = std::vector<vertex_type>>
		_cont find_vertices_if(std::function<bool(vertex_type)> func) const {
			_cont vertices;
			for (const auto& [v, e] : graph) {
				if (func(v)) {
					vertices.push_back(v);
				}
			}
			return vertices;
		}

		template<class _cont = std::vector<vertex_type>>
		_cont find_vertices_if(std::function<bool(container_type)> func) const {
			_cont vertices;
			for (const auto& [v, e] : graph) {
				if (func(e)) {
					vertices.push_back(v);
				}
			}
			return vertices;
		}

		container_type get_edges(const vertex_type& _vertex) const {
			return graph[_vertex];
		}

		container_type get_vertices() const {
			container_type vertices(graph.size());
			for (const auto& [v, e] : graph) {
				vertices.emplace_back(v);
			}
			return vertices;
		}

		size_type order() const {
			return graph.size();
		}

		size_type size() const {
			size_type size{};
			for (const auto& [v, e] : graph) {
				size += e.size();
			}
			return size;
		}

		result_type bfs(const vertex_type& start, const vertex_type& end) const {
			/*
		Simple BFS implemented using the pseudo-code from wikipedia:

		procedure BFS(G, root) is
			let Q be a queue
			label root as explored
			Q.enqueue(root)
			while Q is not empty do
				v := Q.dequeue()
				if v is the goal then
					return v
				for all edges from v to w in G.adjacentEdges(v) do
					if w is not labelled as explored then
						label w as explored
						w.parent := v
						Q.enqueue(w)
			*/
			result<value_type> r;
			std::queue<vertex_type> q;
			q.push(start);
			// Map is chosen to allow for easy backtracking.
			std::map<vertex_type, vertex_type> explored;
			explored[start] = start;
			while (!q.empty()) {
				vertex_type v = q.front();
				q.pop();
				++r.vertices_visited;
				if (v == end) {
					r.path.insert(r.path.begin(), v);
					while (v != start) {
						v = explored[v];
						r.path.insert(r.path.begin(), v);
					}
					return r;
				}
				for (const vertex_type& e : graph.at(v)) {
					if (explored.find(e) == explored.end()) {
						explored[e] = v;
						q.push(e);
					}
				}
			};
			// no result found - return empty path.
			return r;
		}

		void remove_edge(const vertex_type& v, const vertex_type& neighbour) {
			graph[v].remove(neighbour);
			graph[neighbour].remove(v);
		}

		bool operator==(const unweighted<T>& other) const {
			return (graph == other.data());
		}

		friend std::ostream& operator<<(std::ostream& os, const unweighted& _graph) {
			for (const auto& [v, e] : _graph.graph) {
				os << v << " :\n";
				for (const auto& n : e) {
					os << " -> " << n << '\n';
				}
			}
			return os;
		}

	private:
		graph_type graph;

	};

	template<class T, class W = int>
	class weighted {

	public:
		using value_type = T;
		using weight_type = W;
		using size_type = size_t;
		using vertex_type = vertex<value_type>;
		using edge_type = edge<value_type>;
		using container_type = std::vector<edge_type>;
		using graph_type = std::map<vertex_type, container_type>;
		using result_type = result<value_type>;

		weighted() = default;

		weighted(const graph_type& _graph) {
			graph = _graph;
		}

		void add_edge(const vertex_type& a, const vertex_type& b, const weight_type& w) {
			graph[a].emplace_back(b, w);
			graph[b].emplace_back(a, w);
		}

		void add_edge(const std::vector<vertex_type>& _vertices, const weight_type& w) {
			for (auto v = 0; v < _vertices.size(); ++v) {
				for (auto e = v + 1; e < _vertices.size(); ++e) {
					add_edge(_vertices[v], _vertices[e], w);
				}
			}
		}

		vertex_type find_vertex(const vertex_type& _vertex) const {
			for (const auto& [v, e] : graph) {
				if (v == _vertex) {
					return v;
				}
			}
			throw std::invalid_argument("Vertex not found in graph");
		}

		vertex_type find_vertex(const value_type& _val) const {
			for (const auto& [v, e] : graph) {
				if (v.value == _val) {
					return v;
				}
			}
			throw std::invalid_argument("Vertex not found in graph");
		}

		template<class _cont = std::vector<vertex_type>>
		_cont find_vertices_if(std::function<bool(vertex_type)> func) const {
			_cont vertices;
			for (const auto& [v, e] : graph) {
				if (func(v)) {
					vertices.push_back(v);
				}
			}
			return vertices;
		}

		template<class _cont = std::vector<vertex_type>>
		_cont find_vertices_if(std::function<bool(container_type)> func) const {
			_cont vertices;
			for (const auto& [v, e] : graph) {
				if (func(e)) {
					vertices.push_back(v);
				}
			}
			return vertices;
		}

		container_type get_edges(const vertex_type& _vertex) const {
			return graph[_vertex];
		}

		template<class _cont = std::vector<vertex_type>>
		_cont  get_vertices() const {
			_cont vertices;
			for (const auto& [v, e] : graph) {
				vertices.push_back(v);
			}
			return vertices;
		}

		void optimise(std::function<bool(vertex_type)> pred) {

		}

		size_type order() const {
			return graph.size();
		}

		size_type size() const {
			size_type size{};
			for (const auto& [v, e] : graph) {
				size += e.size();
			}
			return size;
		}

		result_type dijkstra(const vertex_type& start, const vertex_type& end) const {
			return result();
		}

		void remove_edge(const vertex_type& v, const vertex_type& neighbour) {
			graph[v].remove(neighbour);
			graph[neighbour].remove(v);
		}

		friend std::ostream& operator<<(std::ostream& os, const weighted& _graph) {
			os << "--Weighted Graph--\n";
			for (const auto& [v, e] : _graph.graph) {
				os << v << " :\n";
				for (const auto& _edge : e) {
					os << " -> " << _edge << '\n';
				}
			}
			return os;
		}

	private:
		graph_type graph{};
	};
}

#endif // GRAPH