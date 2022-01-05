#ifndef ACBUFFER_HPP
#define ACBUFFER_HPP

#include <type_traits>
#include <mutex>
#include <memory>
#include <variant>
#include <optional>
#include <deque>
#include <initializer_list>
#include <atomic>

template<typename C,
	std::enable_if_t<std::is_copy_constructible<C>::value, bool> = true>
class acbuffer
{
	public:
	using lock_strategy = std::variant<std::defer_lock_t, std::try_to_lock_t, std::adopt_lock_t>;
	acbuffer(std::initializer_list<C> l) {
		for(C c : l) {
			container.push_back(std::make_unique<C>(c));
			observer.push_back(std::make_shared<C>(nullptr));
		}
	}

	inline std::optional<std::shared_ptr<C>>get() { // todo move this to atomic<shared in c++20
		std::scoped_lock lock(slock);
		unsigned i;
		for(i = 0; i < container.size() && observer[i].lock(); i++);
		if(i == container.size()) {
			return std::nullopt;
		}
		std::shared_ptr<C>res = std::make_shared<C>(*container[i].get());
		observer[i] = res;
		return observer[i];
	}

	std::mutex slock;

	protected:
	std::deque<std::unique_ptr<C>> container;
	std::deque<std::weak_ptr<C>> observer;
};

#endif
