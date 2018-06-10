#include <message.h>
#include <cstddef>

namespace net {
template <typename T>
void put(int target, const T& data) {
	auto* ptr = reinterpret_cast<const char*>(&data);
	std::size_t i = 0;
	while (i + 8 <= sizeof(T)) {
		PutLL(target, *reinterpret_cast<const long long*>(&ptr[i]));
		i += 8;
	}
	if (i + 4 <= sizeof(T)) {
		PutInt(target, *reinterpret_cast<const int*>(&ptr[i]));
		i += 4;
	}
	while (i + 1 <= sizeof(T)){
		PutChar(target, ptr[i]);
		i += 1;
	}
}

inline void send(int target) {
	return Send(target);
}

template <typename T>
void get(int source, T& data) {
	auto* ptr = reinterpret_cast<char*>(&data);
	std::size_t i = 0;
	while (i + 8 <= sizeof(T)) {
		*reinterpret_cast<long long*>(&ptr[i]) = GetLL(source);
		i += 8;
	}
	if (i + 4 <= sizeof(T)) {
		*reinterpret_cast<int*>(&ptr[i]) = GetInt(source);
		i += 4;
	}
	while (i + 1 <= sizeof(T)) {
		ptr[i] = GetChar(source);
		i += 1;
	}
}

template <typename T>
T get(int source) {
	T result;
	get(source, result);
	return result;
}

inline int receive(int source) {
	return Receive(source);
}

}
