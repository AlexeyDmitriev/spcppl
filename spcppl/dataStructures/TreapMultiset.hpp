#pragma once

#include <cstddef>
#include <cstdint>
#include <spcppl/random/random.hpp>

template <typename T>
class TreapMultiset {
private:
	struct NodeStruct {
		T value;
		std::size_t count;
		NodeStruct* l;
		NodeStruct* r;
		int32_t priority;

		template <typename... Args>
		explicit NodeStruct(Args&&... args):
				value(std::forward<Args>(args)...),
				count(1),
				l(nullptr),
				r(nullptr),
				priority(randomInteger()) {

		}

		void push() {

		}

		void recalc() {
			count = 1 + cnt(l) + cnt(r);
		}
	};
	using Node = NodeStruct*;

	static std::size_t cnt(Node v) {
		if (!v)
			return 0;
		return v->count;
	}

	Node merge(Node l, Node r) {
		if (!l) {
			return r;
		}
		if (!r) {
			return l;
		}
		if (l->priority < r->priority) {
			l->push();
			l->r = merge(l->r, r);
			l->recalc();
			return l;
		}
		else {
			r->push();
			r->l = merge(l, r->l);
			r->recalc();
			return r;
		}
	}

	void clear(Node v) {
		if (v) {
			clear(v->l);
			clear(v->r);
		}
		delete v;
	}

	void splitByIndex(Node v, std::size_t index, Node& l, Node& r) {
		l = nullptr;
		r = nullptr;
		if (!v) {
			return;
		}
		v->push();
		if (cnt(v->l) < index) {
			l = v;
			splitByIndex(l->r, index - cnt(v->l) - 1, l->r, r);
			l->recalc();
		}
		else {
			r = v;
			splitByIndex(r->l, index, l, r->l);
			r->recalc();
		}
	}

	void splitByValue(Node v, const T& value, Node& l, Node& r) {
		l = nullptr;
		r = nullptr;
		if (!v) {
			return;
		}
		v->push();
		if (v->value < value) {
			l = v;
			splitByValue(l->r, value, l->r, r);
			l->recalc();
		}
		else {
			r = v;
			splitByValue(r->l, value, l, r->l);
			r->recalc();
		}
	}

	void insertNode(Node newNode) {
		Node l = nullptr;
		Node r = nullptr;
		splitByValue(root, newNode->value, l, r);
		root = merge(merge(l, newNode), r);
	}

public:
	TreapMultiset(): root(nullptr) {
	}

	std::size_t size() const {
		return cnt(root);
	}

	template <typename... Args>
	void emplace(Args&&... args) {
		insertNode(new NodeStruct(std::forward<Args>(args)...));
	}

	void insert(const T& value) {
		insertNode(new NodeStruct(value));
	}

	void insert(T&& value) {
		insertNode(new NodeStruct(std::move(value)));
	}

	void erase_one(const T& value) {
		Node l = nullptr;
		Node m = nullptr;
		Node r = nullptr;
		splitByValue(root, value, l, r);
		splitByIndex(r, 1, m, r);
		SPCPPL_ASSERT(m->value == value);
		delete m;
		root = merge(l, r);
	}

	const T* find(const T& value) {
		const T* result = lower_bound(value);
		if (result == nullptr || value < *result) {
			return result;
		} else {
			return false;
		}
	}

	// todo(performance): rewrite without split/merge
	const T* lower_bound(const T& value) {
		Node l = nullptr;
		Node m = nullptr;
		Node r = nullptr;
		splitByValue(root, value, l, r);
		if (r == nullptr) {
			root = l;
			return nullptr;
		}
		splitByIndex(r, 1, m, r);
		SPCPPL_ASSERT(m != nullptr);
		root = merge(merge(l, m), r);
		return &m->value;
	}

	// todo(performance): rewrite without split/merge
	const T& operator [](std::size_t index) {
		Node l = nullptr;
		Node m = nullptr;
		Node r = nullptr;
		splitByIndex(root, index, l, r);
		splitByIndex(r, 1, m, r);
		SPCPPL_ASSERT(m != nullptr);
		root = merge(merge(l, m), r);
		return m->value;
	}

	void clear() {
		clear(root);
	}

private:
	Node root;
};
