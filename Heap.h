#pragma once

#include<utility>
#include<vector>

template<typename Key, typename Value, class Comparator = std::less<Key>>
class Heap {
public:
	Heap(const Comparator& comp = Comparator());
	size_t Size() const;
	std::pair<Key, Value> Top() const;
	void Push(const Key& key, const Value& value);
	void Pop();
private:
	void SiftUp(size_t index);
	void SiftDown(size_t index);
private:
	struct _Node {
		Key key;
		Value value;
	};
private:
	std::vector<_Node> _data;
	Comparator _comp;
};

template<typename Key, typename Value, class Comparator>
void Heap<Key, Value, Comparator>::SiftUp(size_t index) {
	if (index == 0) {
		return;
	}
	size_t parent = (index - 1) / 2;
	if (_comp(_data[index].key, _data[parent].key)) {
		std::swap(_data[index], _data[parent]);
		SiftUp(parent);
	}
}

template<typename Key, typename Value, class Comparator>
void Heap<Key, Value, Comparator>::SiftDown(size_t index) {
	size_t left = 2 * index + 1;
	size_t right = 2 * index + 2;
	if (left >= _data.size()) {
		return;
	}
	size_t important = index;
	if (_comp(_data[left].key, _data[important].key)) {
		important = left;
	}
	if (right < _data.size() && (_comp(_data[right].key, _data[important].key))) {
		important = right;
	}
	if (important == index) {
		return;
	}
	std::swap(_data[index], _data[important]);
	SiftDown(important);
}

template<typename Key, typename Value, class Comparator>
Heap<Key, Value, Comparator>::Heap(const Comparator& comp) : _comp(comp) {}

template<typename Key, typename Value, class Comparator>
size_t Heap<Key, Value, Comparator>::Size() const {
	return _data.size();
}

template<typename Key, typename Value, class Comparator>
std::pair<Key, Value> Heap<Key, Value, Comparator>::Top() const {
	return { _data[0].key, _data[0].value };
}

template<typename Key, typename Value, class Comparator>
void Heap<Key, Value, Comparator>::Push(const Key& key, const Value& value) {
	_data.push_back({ key, value });
	SiftUp(_data.size() - 1);
}

template<typename Key, typename Value, class Comparator>
void Heap<Key, Value, Comparator>::Pop() {
	if (_data.size() == 1) {
		_data.pop_back();
		return;
	}
	std::swap(_data[0], _data.back());
	_data.pop_back();
	SiftDown(0);
}
